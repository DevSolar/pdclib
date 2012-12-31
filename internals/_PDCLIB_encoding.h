/* Encoding support <_PDCLIB_encoding.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_ENCODING_H
#define _PDCLIB_ENCODING_H _PDCLIB_ENCODING_H
#include "_PDCLIB_int.h"

#ifndef __cplusplus
typedef _PDCLIB_int16_t         _PDCLIB_char16_t;
typedef _PDCLIB_int32_t         _PDCLIB_char32_t;
#else
typedef char16_t                _PDCLIB_char16_t;
typedef char32_t                _PDCLIB_char32_t;
#endif

/* -------------------------------------------------------------------------- */
/* mbstate_t                                                                  */
/* -------------------------------------------------------------------------- */

typedef struct _PDCLIB_mbstate_t {
    union {
        /* Is this the best way to represent this? Is this big enough? */
        _PDCLIB_uint64_t _St64[15];
        _PDCLIB_uint32_t _St32[31];
        _PDCLIB_uint16_t _St16[62];
        unsigned char    _StUC[124];
        signed   char    _StSC[124];
                 char    _StC [124];
    };

    union {
        /* c16/related functions: Surrogate storage
         *
         * If zero, no surrogate pending. If nonzero, surrogate.
         */
        _PDCLIB_uint16_t     _Surrogate;

        /* Reserved for potential mbtoutf8/etc functions */
        unsigned char        _U8[4];
    };
} _PDCLIB_mbstate_t;

#ifdef _PDCLIB_WCHAR_IS_UCS2
/* Must be cauued with bufsize >= 1, in != NULL, out != NULL, ps != NULL
 *
 * Converts a wchar to a UCS4 (char32_t) value. Returns
 *   1, 2   : Valid character (converted to UCS-4)
 *   -1     : Encoding error
 *   -2     : Partial character (only lead surrogate in buffer)
 */
static inline int _PDCLIB_wcrtoc32(
            _PDCLIB_char32_t    *_PDCLIB_restrict   out, 
    const   _PDCLIB_wchar_t     *_PDCLIB_restrict   in,
            _PDCLIB_size_t                          bufsize,
            _PDCLIB_mbstate_t   *_PDCLIB_restrict   ps  
)
{
    if(ps->_Surrogate) {
        // We already have a lead surrogate
        if(*in & ~0x3FF != 0xDC00) {
            // Encoding error
            return -1;
        } else {
            // Decode and reset state
            *out = (ps->_Surrogate & 0x3FF) << 10 | (*in & 0x3FF);
            ps->_Surrogate = 0;
            return 1;
        }
    } if(*in & ~0x3FF == 0xD800) {
        // Lead surrogate
        if(bufsize >= 2) {
            // Buffer big enough
            if(in[1] & ~0x3FF != 0xDC00) {
                // Encoding error
                return -1;
            } else {
                *out = (in[0] & 0x3FF) << 10 | (in[1] & 0x3FF);
                return 2;
            }
        } else {
            // Buffer too small - update state
            ps->_Surrogate = *in;
            return -2;
        }
    } else {
        // BMP character
        *out = *in;
        return 1;
    }
}

static inline _PDCLIB_size_t _PDCLIB_c32rtowc(
            _PDCLIB_wchar_t     *_PDCLIB_restrict   out,
    const   _PDCLIB_char32_t    *_PDCLIB_restrict   in,
            _PDCLIB_size_t                          bufsize,
            _PDCLIB_mbstate_t   *_PDCLIB_restrict   ps
)
{
    if(ps->_Surrogate) {
        *out = ps->_Surrogate;
        ps->_Surrogate = 0;
        return 0;
    }

    if(*in <= 0xFFFF) {
        // BMP character
        *out = *in;
        return 1;
    } else {
        // Supplementary plane character
        *out = 0xD800 | (*in & 0x3FF);
        if(bufsize >= 2) {
            out[1] = 0xDC00 | (*in >> 10);
            return 2;
        } else {
            ps->_Surrogate = 0xDC00 | (*in >> 10);
            return 1;
        }
    }
}
#else
/* Dummy implementation for when wc == c32 */
static inline _PDCLIB_size_t _PDCLIB_wcrtoc32(
            _PDCLIB_char32_t    *_PDCLIB_restrict   out, 
    const   _PDCLIB_wchar_t     *_PDCLIB_restrict   in,
            _PDCLIB_size_t                          bufsize,
            _PDCLIB_mbstate_t   *_PDCLIB_restrict   ps  
)
{
    *out = *in;
    return 1;
}

static inline _PDCLIB_size_t _PDCLIB_c32rtowc(
            _PDCLIB_wchar_t     *_PDCLIB_restrict   out,
    const   _PDCLIB_char32_t    *_PDCLIB_restrict   in,
            _PDCLIB_size_t                          bufsize,
            _PDCLIB_mbstate_t   *_PDCLIB_restrict   ps
)
{
    *out = *in;
    return 1;
}
#endif

typedef struct {
    /* Reads at most *_P_insz code units from *_P_inbuf and writes the result 
     * into *_P_outbuf, writing at most *_P_outsz code units. Updates 
     * *_P_outbuf, *_P_outsz, *_P_inbuf, *_P_outsz with the resulting state
     *
     * If _P_outbuf is NULL, then the input must be processed but no output 
     * generated. _P_outsz may be processed as normal.
     *
     * Returns true if the conversion completed successfully (i.e. one of 
     * _P_outsize or _P_insize reached zero and no coding errors were 
     * encountered), else return false.
     */

    /* UCS-4 variants. Mandatory. */

    _PDCLIB_bool (*__mbstoc32s)(
        _PDCLIB_char32_t       **_PDCLIB_restrict   _P_outbuf,
        _PDCLIB_size_t          *_PDCLIB_restrict   _P_outsz,
        const char             **_PDCLIB_restrict   _P_inbuf,
        _PDCLIB_size_t          *_PDCLIB_restrict   _P_insz,
        _PDCLIB_mbstate_t       *_PDCLIB_restrict   _P_ps
    );

    _PDCLIB_bool (*__c32stombs)(
        char                   **_PDCLIB_restrict  _P_outbuf,
        _PDCLIB_size_t          *_PDCLIB_restrict  _P_outsz,
        const _PDCLIB_char32_t **_PDCLIB_restrict  _P_inbuf,
        _PDCLIB_size_t          *_PDCLIB_restrict  _P_insz,
        _PDCLIB_mbstate_t       *_PDCLIB_restrict  _P_ps
    );

    /* UTF-16 variants; same as above except optional. 
     *
     * If not provided, _PDCLib will internally synthesize on top of the UCS-4
     * variants above, albeit at a performance cost.
     */

    _PDCLIB_bool (*__mbstoc16s)(
        _PDCLIB_char16_t       **_PDCLIB_restrict   _P_outbuf,
        _PDCLIB_size_t          *_PDCLIB_restrict   _P_outsz,
        const char             **_PDCLIB_restrict   _P_inbuf,
        _PDCLIB_size_t          *_PDCLIB_restrict   _P_insz,
        _PDCLIB_mbstate_t       *_PDCLIB_restrict   _P_ps
    );

    _PDCLIB_bool (*__c16stombs)(
        char                   **_PDCLIB_restrict  _P_outbuf,
        _PDCLIB_size_t          *_PDCLIB_restrict  _P_outsz,
        const _PDCLIB_char16_t **_PDCLIB_restrict  _P_inbuf,
        _PDCLIB_size_t          *_PDCLIB_restrict  _P_insz,
        _PDCLIB_mbstate_t       *_PDCLIB_restrict  _P_ps
    );
} _PDCLIB_charcodec;

#endif
