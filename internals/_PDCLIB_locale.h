#ifndef __PDCLIB_LOCALE_H
#define __PDCLIB_LOCALE_H __PDCLIB_LOCALE_H
#include <_PDCLIB_int.h>
#include <locale.h>
#include <threads.h>
#include <stdlib.h>

#define _PDCLIB_LOCALE_METHOD_TSS           't'
#define _PDCLIB_LOCALE_METHOD_THREAD_LOCAL  'T'

#if !defined(_PDCLIB_LOCALE_METHOD)
    #error _PDCLIB_LOCALE_METHOD undefined: don't know where I'm storing the thread locale
#elif _PDCLIB_LOCALE_METHOD == _PDCLIB_LOCALE_METHOD_TSS
    extern tss_t _PDCLIB_locale_tss;
    static inline locale_t _PDCLIB_threadlocale( void )
    {
        locale_t l = tss_get(_PDCLIB_locale_tss);
        if(l == NULL)
            l = &_PDCLIB_global_locale;
        return l;
    }

    static inline void _PDCLIB_setthreadlocale( locale_t l )
    {
        if(tss_set(_PDCLIB_locale_tss, l) != thrd_success)
            abort();
    }
#elif _PDCLIB_LOCALE_METHOD == _PDCLIB_LOCALE_METHOD_THREAD_LOCAL
    extern thread_local locale_t _PDCLIB_locale_tls;
    #define _PDCLIB_threadlocale() (_PDCLIB_locale_tls || &_PDCLIB_global_locale)
    static inline locale_t _PDCLIB_threadlocale( void )
    {
        locale_t l = _PDCLIB_locale_tls;
        if(l == NULL)
            l = &_PDCLIB_global_locale;
        return l;
    }

    static inline void _PDCLIB_setthreadlocale( locale_t l )
    {
        _PDCLIB_locale_tls = l;
    }
#else
    #error Locale TSS method unspecified
#endif

/* -------------------------------------------------------------------------- */
/* <ctype.h> lookup tables                                                    */
/* -------------------------------------------------------------------------- */

#define _PDCLIB_CTYPE_ALPHA   1
#define _PDCLIB_CTYPE_BLANK   2
#define _PDCLIB_CTYPE_CNTRL   4
#define _PDCLIB_CTYPE_GRAPH   8
#define _PDCLIB_CTYPE_PUNCT  16
#define _PDCLIB_CTYPE_SPACE  32
#define _PDCLIB_CTYPE_LOWER  64
#define _PDCLIB_CTYPE_UPPER 128
#define _PDCLIB_CTYPE_DIGIT 256
#define _PDCLIB_CTYPE_XDIGT 512

typedef struct _PDCLIB_ctype
{
    _PDCLIB_uint16_t flags;
    unsigned char upper;
    unsigned char lower;
    unsigned char collation;
} _PDCLIB_ctype_t;

typedef struct _PDCLIB_wcinfo
{
    _PDCLIB_uint32_t num;
    _PDCLIB_uint16_t flags;
    _PDCLIB_uint32_t lower;
    _PDCLIB_uint32_t upper;
} _PDCLIB_wcinfo_t;

extern _PDCLIB_wcinfo_t _PDCLIB_wcinfo[];
extern size_t           _PDCLIB_wcinfo_size;

static inline int _PDCLIB_wcinfo_cmp( const void * _key, const void * _obj )
{
    _PDCLIB_uint32_t * key = (_PDCLIB_uint32_t *) _key;
    _PDCLIB_wcinfo_t * obj = (_PDCLIB_wcinfo_t *) _obj;
    return *key - obj->num;
}

static inline _PDCLIB_wcinfo_t * _PDCLIB_wcgetinfo( _PDCLIB_uint32_t num )
{
    _PDCLIB_wcinfo_t *info = (_PDCLIB_wcinfo_t*) 
        bsearch( &num, _PDCLIB_wcinfo, _PDCLIB_wcinfo_size, 
                 sizeof( _PDCLIB_wcinfo[0] ), _PDCLIB_wcinfo_cmp );

    return info;
}

static inline _PDCLIB_wint_t _PDCLIB_unpackwint( _PDCLIB_wint_t wc )
{
    if( sizeof(_PDCLIB_wchar_t) == 2 && sizeof(_PDCLIB_wint_t) == 4 ) {
        /* On UTF-16 platforms, as an extension accept a "packed surrogate"
         * encoding. We accept the surrogate pairs either way
         */

        _PDCLIB_wint_t c = (wc & 0xF800F800);
        if(c == (_PDCLIB_wint_t) 0xD800DC00) {
            // MSW: Lead, LSW: Trail
            _PDCLIB_wint_t lead  = wc >> 16 & 0x3FF;
            _PDCLIB_wint_t trail = wc       & 0x3FF;
            wc = lead << 10 | trail;
        } else if(c == (_PDCLIB_wint_t) 0xDC00D800) {
            // MSW: Trail, LSW: Lead
            _PDCLIB_wint_t trail = wc >> 16 & 0x3FF;
            _PDCLIB_wint_t lead  = wc       & 0x3FF;
            wc = lead << 10 | trail;
        }

    }
    return wc;
}

struct _PDCLIB_locale {
    _PDCLIB_charcodec_t          _Codec;
    struct lconv                 _Conv;

    /* ctype */
    _PDCLIB_ctype_t             *_CType; 

    /* perror/strerror */
    char                        *_ErrnoStr[_PDCLIB_ERRNO_MAX];
};

#endif
