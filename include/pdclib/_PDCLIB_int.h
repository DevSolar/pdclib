/* PDCLib internal integer logic <_PDCLIB_int.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDCLIB_INT_H

/* -------------------------------------------------------------------------- */
/* You should not have to edit anything in this file; if you DO have to, it   */
/* would be considered a bug / missing feature: notify the author(s).         */
/* -------------------------------------------------------------------------- */

#include "pdclib/_PDCLIB_config.h"
#include "pdclib/_PDCLIB_aux.h"

/* null pointer constant */
#define _PDCLIB_NULL 0

/* -------------------------------------------------------------------------- */
/* Limits of native datatypes                                                 */
/* -------------------------------------------------------------------------- */
/* The definition of minimum limits for unsigned datatypes is done because    */
/* later on we will "construct" limits for other abstract types:              */
/* USHRT -> _PDCLIB_ + USHRT + _MIN -> _PDCLIB_USHRT_MIN -> 0                 */
/* INT -> _PDCLIB_ + INT + _MIN -> _PDCLIB_INT_MIN -> ... you get the idea.   */
/* -------------------------------------------------------------------------- */

/* Setting 'char' limits                                                      */
#define _PDCLIB_CHAR_BIT    8
#define _PDCLIB_UCHAR_MIN   0
#define _PDCLIB_UCHAR_MAX   0xff
#define _PDCLIB_SCHAR_MIN   (-0x7f - 1)
#define _PDCLIB_SCHAR_MAX   0x7f
#if _PDCLIB_CHAR_SIGNED == 1
#define _PDCLIB_CHAR_MIN    _PDCLIB_SCHAR_MIN
#define _PDCLIB_CHAR_MAX    _PDCLIB_SCHAR_MAX
#else
#define _PDCLIB_CHAR_MIN    0
#define _PDCLIB_CHAR_MAX    _PDCLIB_UCHAR_MAX
#endif

/* Setting 'short' limits                                                     */
#if     _PDCLIB_SHRT_BYTES == 2
#define _PDCLIB_SHRT_MAX      0x7fff
#define _PDCLIB_SHRT_MIN      (-0x7fff - 1)
#define _PDCLIB_USHRT_MAX     0xffff
#else
#error Unsupported width of 'short' (not 16 bit).
#endif
#define _PDCLIB_USHRT_MIN 0

#if _PDCLIB_INT_BYTES < _PDCLIB_SHRT_BYTES
#error Bogus setting: short > int? Check _PDCLIB_config.h.
#endif

/* Setting 'int' limits                                                       */
#if     _PDCLIB_INT_BYTES == 2
#define _PDCLIB_INT_MAX   0x7fff
#define _PDCLIB_INT_MIN   (-0x7fff - 1)
#define _PDCLIB_UINT_MAX  0xffffU
#elif   _PDCLIB_INT_BYTES == 4
#define _PDCLIB_INT_MAX   0x7fffffff
#define _PDCLIB_INT_MIN   (-0x7fffffff - 1)
#define _PDCLIB_UINT_MAX  0xffffffffU
#elif _PDCLIB_INT_BYTES   == 8
#define _PDCLIB_INT_MAX   0x7fffffffffffffff
#define _PDCLIB_INT_MIN   (-0x7fffffffffffffff - 1)
#define _PDCLIB_UINT_MAX  0xffffffffffffffff
#else
#error Unsupported width of 'int' (neither 16, 32, nor 64 bit).
#endif
#define _PDCLIB_UINT_MIN 0

/* Setting 'long' limits                                                      */
#if   _PDCLIB_LONG_BYTES   == 4
#define _PDCLIB_LONG_MAX   0x7fffffffL
#define _PDCLIB_LONG_MIN   (-0x7fffffffL - 1L)
#define _PDCLIB_ULONG_MAX  0xffffffffUL
#elif   _PDCLIB_LONG_BYTES == 8
#define _PDCLIB_LONG_MAX   0x7fffffffffffffffL
#define _PDCLIB_LONG_MIN   (-0x7fffffffffffffffL - 1L)
#define _PDCLIB_ULONG_MAX  0xffffffffffffffffUL
#else
#error Unsupported width of 'long' (neither 32 nor 64 bit).
#endif
#define _PDCLIB_ULONG_MIN 0

/* Setting 'long long' limits                                                 */
#if _PDCLIB_LLONG_BYTES    == 8
#define _PDCLIB_LLONG_MAX  0x7fffffffffffffffLL
#define _PDCLIB_LLONG_MIN  (-0x7fffffffffffffffLL - 1LL)
#define _PDCLIB_ULLONG_MAX 0xffffffffffffffffULL
#elif _PDCLIB_LLONG_BYTES  == 16
#define _PDCLIB_LLONG_MAX  0x7fffffffffffffffffffffffffffffffLL
#define _PDCLIB_LLONG_MIN  (-0x7fffffffffffffffffffffffffffffffLL - 1LL)
#define _PDCLIB_ULLONG_MAX 0xffffffffffffffffffffffffffffffffULL
#else
#error Unsupported width of 'long long' (neither 64 nor 128 bit).
#endif
#define _PDCLIB_ULLONG_MIN 0

/* -------------------------------------------------------------------------- */
/* <stdint.h> exact-width types and their limits                              */
/* -------------------------------------------------------------------------- */
/* Note that, for the "standard" widths of 8, 16, 32 and 64 bit, the "LEAST"  */
/* types are identical to the "exact-width" types, by definition.             */

/* Setting 'int8_t', its limits, its literal, and conversion macros.          */
#if     _PDCLIB_CHAR_BIT == 8
typedef signed char        _PDCLIB_int8_t;
typedef unsigned char      _PDCLIB_uint8_t;
#define _PDCLIB_INT8_MAX   _PDCLIB_CHAR_MAX
#define _PDCLIB_INT8_MIN   _PDCLIB_CHAR_MIN
#define _PDCLIB_UINT8_MAX  _PDCLIB_UCHAR_MAX
#define _PDCLIB_8_CONV     hh
#else
#error Unsupported width of char (not 8 bits).
#endif

/* Setting 'int16_t', its limits, its literal, and conversion macros.         */
#if     _PDCLIB_INT_BYTES  == 2
typedef signed int         _PDCLIB_int16_t;
typedef unsigned int       _PDCLIB_uint16_t;
#define _PDCLIB_INT16_MAX  _PDCLIB_INT_MAX
#define _PDCLIB_INT16_MIN  _PDCLIB_INT_MIN
#define _PDCLIB_UINT16_MAX _PDCLIB_UINT_MAX
#define _PDCLIB_16_CONV
#elif   _PDCLIB_SHRT_BYTES == 2
typedef signed short       _PDCLIB_int16_t;
typedef unsigned short     _PDCLIB_uint16_t;
#define _PDCLIB_INT16_MAX  _PDCLIB_SHRT_MAX
#define _PDCLIB_INT16_MIN  _PDCLIB_SHRT_MIN
#define _PDCLIB_UINT16_MAX _PDCLIB_USHRT_MAX
#define _PDCLIB_16_CONV    h
#else
#error Neither 'short' nor 'int' are 16-bit.
#endif

/* Setting 'int32_t', its limits, its literal, and conversion macros.         */
#if     _PDCLIB_INT_BYTES  == 4
typedef signed int         _PDCLIB_int32_t;
typedef unsigned int       _PDCLIB_uint32_t;
#define _PDCLIB_INT32_MAX  _PDCLIB_INT_MAX
#define _PDCLIB_INT32_MIN  _PDCLIB_INT_MIN
#define _PDCLIB_UINT32_MAX _PDCLIB_UINT_MAX
#define _PDCLIB_INT32_LITERAL
#define _PDCLIB_UINT32_LITERAL
#define _PDCLIB_32_CONV
#elif   _PDCLIB_LONG_BYTES == 4
typedef signed long        _PDCLIB_int32_t;
typedef unsigned long      _PDCLIB_uint32_t;
#define _PDCLIB_INT32_MAX  _PDCLIB_LONG_MAX
#define _PDCLIB_INT32_MIN  _PDCLIB_LONG_MIN
#define _PDCLIB_UINT32_MAX _PDCLIB_LONG_MAX
#define _PDCLIB_INT32_LITERAL  l
#define _PDCLIB_UINT32_LITERAL ul
#define _PDCLIB_32_CONV        l
#else
#error Neither 'int' nor 'long' are 32-bit.
#endif

/* Setting 'int64_t', its limits, its literal, and conversion macros.         */
#if     _PDCLIB_LONG_BYTES == 8
typedef signed long        _PDCLIB_int64_t;
typedef unsigned long      _PDCLIB_uint64_t;
#define _PDCLIB_INT64_MAX  _PDCLIB_LONG_MAX
#define _PDCLIB_INT64_MIN  _PDCLIB_LONG_MIN
#define _PDCLIB_UINT64_MAX  _PDCLIB_ULONG_MAX
#define _PDCLIB_INT64_LITERAL  l
#define _PDCLIB_UINT64_LITERAL ul
#define _PDCLIB_64_CONV        l
#elif _PDCLIB_LLONG_BYTES  == 8
typedef signed long long   _PDCLIB_int64_t;
typedef unsigned long long _PDCLIB_uint64_t;
#define _PDCLIB_INT64_MAX  _PDCLIB_LLONG_MAX
#define _PDCLIB_INT64_MIN  _PDCLIB_LLONG_MIN
#define _PDCLIB_UINT64_MAX  _PDCLIB_ULLONG_MAX
#define _PDCLIB_INT64_LITERAL  ll
#define _PDCLIB_UINT64_LITERAL ull
#define _PDCLIB_64_CONV        ll
#else
#error Neither 'long' nor 'long long' are 64-bit.
#endif

/* -------------------------------------------------------------------------- */
/* <stdint.h> "fastest" types and their limits                                */
/* -------------------------------------------------------------------------- */
/* This is, admittedly, butt-ugly. But at least it's ugly where the average   */
/* user of PDCLib will never see it, and makes <_PDCLIB_config.h> much        */
/* cleaner.                                                                   */
/* -------------------------------------------------------------------------- */

typedef _PDCLIB_fast8          _PDCLIB_int_fast8_t;
typedef unsigned _PDCLIB_fast8 _PDCLIB_uint_fast8_t;
#define _PDCLIB_INT_FAST8_MIN  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_FAST8 ), _MIN )
#define _PDCLIB_INT_FAST8_MAX  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_FAST8 ), _MAX )
#define _PDCLIB_UINT_FAST8_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_U, _PDCLIB_FAST8 ), _MAX )

typedef _PDCLIB_fast16          _PDCLIB_int_fast16_t;
typedef unsigned _PDCLIB_fast16 _PDCLIB_uint_fast16_t;
#define _PDCLIB_INT_FAST16_MIN  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_FAST16 ), _MIN )
#define _PDCLIB_INT_FAST16_MAX  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_FAST16 ), _MAX )
#define _PDCLIB_UINT_FAST16_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_U, _PDCLIB_FAST16 ), _MAX )

typedef _PDCLIB_fast32          _PDCLIB_int_fast32_t;
typedef unsigned _PDCLIB_fast32 _PDCLIB_uint_fast32_t;
#define _PDCLIB_INT_FAST32_MIN  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_FAST32 ), _MIN )
#define _PDCLIB_INT_FAST32_MAX  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_FAST32 ), _MAX )
#define _PDCLIB_UINT_FAST32_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_U, _PDCLIB_FAST32 ), _MAX )

typedef _PDCLIB_fast64          _PDCLIB_int_fast64_t;
typedef unsigned _PDCLIB_fast64 _PDCLIB_uint_fast64_t;
#define _PDCLIB_INT_FAST64_MIN  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_FAST64 ), _MIN )
#define _PDCLIB_INT_FAST64_MAX  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_FAST64 ), _MAX )
#define _PDCLIB_UINT_FAST64_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_U, _PDCLIB_FAST64 ), _MAX )

/* -------------------------------------------------------------------------- */
/* Various <stddef.h> typedefs and limits                                     */
/* -------------------------------------------------------------------------- */

typedef _PDCLIB_ptrdiff     _PDCLIB_ptrdiff_t;
#define _PDCLIB_PTRDIFF_MIN _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_PTRDIFF ), _MIN )
#define _PDCLIB_PTRDIFF_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_PTRDIFF ), _MAX )

#define _PDCLIB_SIG_ATOMIC_MIN _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_SIG_ATOMIC ), _MIN )
#define _PDCLIB_SIG_ATOMIC_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_SIG_ATOMIC ), _MAX )

typedef _PDCLIB_size     _PDCLIB_size_t;
#define _PDCLIB_SIZE_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_SIZE ), _MAX )

typedef _PDCLIB_wchar     _PDCLIB_wchar_t;
#define _PDCLIB_WCHAR_MIN _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_WCHAR ), _MIN )
#define _PDCLIB_WCHAR_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_WCHAR ), _MAX )

typedef _PDCLIB_wint     _PDCLIB_wint_t;
#define _PDCLIB_WINT_MIN _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_WINT ), _MIN )
#define _PDCLIB_WINT_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_WINT ), _MAX )

typedef _PDCLIB_intptr          _PDCLIB_intptr_t;
typedef unsigned _PDCLIB_intptr _PDCLIB_uintptr_t;
#define _PDCLIB_INTPTR_MIN  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_INTPTR ), _MIN )
#define _PDCLIB_INTPTR_MAX  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_INTPTR ), _MAX )
#define _PDCLIB_UINTPTR_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_U, _PDCLIB_INTPTR ), _MAX )

typedef _PDCLIB_intmax          _PDCLIB_intmax_t;
typedef unsigned _PDCLIB_intmax _PDCLIB_uintmax_t;
#define _PDCLIB_INTMAX_MIN  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_INTMAX ), _MIN )
#define _PDCLIB_INTMAX_MAX  _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_, _PDCLIB_INTMAX ), _MAX )
#define _PDCLIB_UINTMAX_MAX _PDCLIB_concat( _PDCLIB_concat( _PDCLIB_U, _PDCLIB_INTMAX ), _MAX )
#define _PDCLIB_INTMAX_C( value )  _PDCLIB_concat( value, _PDCLIB_INTMAX_LITERAL )
#define _PDCLIB_UINTMAX_C( value ) _PDCLIB_concat( value, _PDCLIB_concat( u, _PDCLIB_INTMAX_LITERAL ) )

/* -------------------------------------------------------------------------- */
/* Various <stdio.h> internals                                                */
/* -------------------------------------------------------------------------- */

/* Flags for representing mode (see fopen()). Note these must fit the same
   status field as the _IO?BF flags in <stdio.h> and the internal flags below.
*/
#define _PDCLIB_FREAD   (1u<<3)
#define _PDCLIB_FWRITE  (1u<<4)
#define _PDCLIB_FAPPEND (1u<<5)
#define _PDCLIB_FRW     (1u<<6)
#define _PDCLIB_FBIN    (1u<<7)

/* Internal flags, made to fit the same status field as the flags above. */
/* FIXME: too many flags to work on a 16-bit machine */
/* -------------------------------------------------------------------------- */
/* free() the buffer memory on closing (false for user-supplied buffer) */
#define _PDCLIB_FREEBUFFER  (1u<<8)
/* stream has encountered error / EOF */
#define _PDCLIB_ERRORFLAG   (1u<<9)
#define _PDCLIB_EOFFLAG     (1u<<10)
/* stream is wide-oriented */
#define _PDCLIB_WIDESTREAM  (1u<<11)
/* stream is byte-oriented */
#define _PDCLIB_BYTESTREAM  (1u<<12)
/* file associated with stream should be remove()d on closing (tmpfile()) */
#define _PDCLIB_DELONCLOSE  (1u<<13)
/* stream handle should not be free()d on close (stdin, stdout, stderr) */
#define _PDCLIB_STATIC      (1u<<14)
/* stream filename allocated separately, and needs free()ing on fclode(). */
#define _PDCLIB_FREENAME    (1u<<15)

/* Position / status structure for getpos() / fsetpos(). */
struct _PDCLIB_fpos_t
{
    _PDCLIB_uint64_t offset; /* File position offset */
    int              status; /* Multibyte parsing state (unused, reserved) */
};

/* FILE structure */
struct _PDCLIB_file_t
{
    _PDCLIB_fd_t            handle;   /* OS file handle */
    char *                  buffer;   /* Pointer to buffer memory */
    _PDCLIB_size_t          bufsize;  /* Size of buffer */
    _PDCLIB_size_t          bufidx;   /* Index of current position in buffer */
    _PDCLIB_size_t          bufend;   /* Index of last pre-read character in buffer */
    struct _PDCLIB_fpos_t   pos;      /* Offset and multibyte parsing state */
    _PDCLIB_size_t          ungetidx; /* Number of ungetc()'ed characters */
    unsigned char *         ungetbuf; /* ungetc() buffer */
    unsigned int            status;   /* Status flags; see above */
    /* multibyte parsing status to be added later */
#ifndef __STDC_NO_THREADS__
    _PDCLIB_mtx_t           mtx;      /* Multithreading safety */
#endif
    char *                  filename; /* Name the current stream has been opened with */
    struct _PDCLIB_file_t * next;     /* Pointer to next struct (internal) */
};

/* -------------------------------------------------------------------------- */
/* Various <time.h> internals                                                 */
/* -------------------------------------------------------------------------- */

typedef _PDCLIB_time            _PDCLIB_time_t;
typedef _PDCLIB_clock           _PDCLIB_clock_t;

/* -------------------------------------------------------------------------- */
/* Internal data types                                                        */
/* -------------------------------------------------------------------------- */

/* Structure required by both atexit() and exit() for handling atexit functions */
struct _PDCLIB_exitfunc_t
{
    struct _PDCLIB_exitfunc_t * next;
    void (*func)( void );
};

/* Structures required by malloc(), realloc(), and free(). */
struct _PDCLIB_headnode_t
{
    struct _PDCLIB_memnode_t * first;
    struct _PDCLIB_memnode_t * last;
};

struct _PDCLIB_memnode_t
{
    _PDCLIB_size_t size;
    struct _PDCLIB_memnode_t * next;
};

/* Status structure required by _PDCLIB_print(). */
struct _PDCLIB_status_t
{
    int              base;   /* base to which the value shall be converted   */
    _PDCLIB_int_fast32_t flags; /* flags and length modifiers                */
    _PDCLIB_size_t   n;      /* print: maximum characters to be written      */
                             /* scan:  number matched conversion specifiers  */
    _PDCLIB_size_t   i;      /* number of characters read/written            */
    _PDCLIB_size_t   current;/* chars read/written in the CURRENT conversion */
    char *           s;      /* *sprintf(): target buffer                    */
                             /* *sscanf():  source string                    */
    _PDCLIB_size_t   width;  /* specified field width                        */
    int              prec;   /* specified field precision                    */
    struct _PDCLIB_file_t * stream; /* *fprintf() / *fscanf() stream         */
    _PDCLIB_va_list  arg;    /* argument stack                               */
};

/* -------------------------------------------------------------------------- */
/* Declaration of helper functions (implemented in functions/_PDCLIB).        */
/* -------------------------------------------------------------------------- */

/* This is the main function called by atoi(), atol() and atoll().            */
_PDCLIB_LOCAL _PDCLIB_intmax_t _PDCLIB_atomax( const char * s );

/* Two helper functions used by strtol(), strtoul() and long long variants.   */
_PDCLIB_LOCAL const char * _PDCLIB_strtox_prelim( const char * p, char * sign, int * base );
_PDCLIB_LOCAL _PDCLIB_uintmax_t _PDCLIB_strtox_main( const char ** p, unsigned int base, _PDCLIB_uintmax_t error, _PDCLIB_uintmax_t limval, int limdigit, char * sign );

/* Digits arrays used by various integer conversion functions */
extern const char _PDCLIB_digits[];
extern const char _PDCLIB_Xdigits[];

/* The worker for all printf() type of functions. The pointer spec should point
   to the introducing '%' of a conversion specifier. The status structure is to
   be that of the current printf() function, of which the members n, s, stream
   and arg will be preserved; i will be updated; and all others will be trashed
   by the function.
   Returns a pointer to the first character not parsed as conversion specifier.
*/
_PDCLIB_LOCAL const char * _PDCLIB_print( const char * spec, struct _PDCLIB_status_t * status );

/* The worker for all scanf() type of functions. The pointer spec should point
   to the introducing '%' of a conversion specifier. The status structure is to
   be that of the current scanf() function, of which the member stream will be
   preserved; n, i, and s will be updated; and all others will be trashed by
   the function.
   Returns a pointer to the first character not parsed as conversion specifier,
   or NULL in case of error.
   FIXME: Should distinguish between matching and input error
*/
_PDCLIB_LOCAL const char * _PDCLIB_scan( const char * spec, struct _PDCLIB_status_t * status );

/* Parsing any fopen() style filemode string into a number of flags. */
_PDCLIB_LOCAL unsigned int _PDCLIB_filemode( const char * mode );

/* Sanity checking and preparing of read buffer, should be called first thing
   by any stdio read-data function.
   Returns 0 on success, EOF on error.
   On error, EOF / error flags and errno are set appropriately.
*/
_PDCLIB_LOCAL int _PDCLIB_prepread( struct _PDCLIB_file_t * stream );

/* Sanity checking, should be called first thing by any stdio write-data
   function.
   Returns 0 on success, EOF on error.
   On error, error flags and errno are set appropriately.
*/
_PDCLIB_LOCAL int _PDCLIB_prepwrite( struct _PDCLIB_file_t * stream );

/* Closing all streams on program exit */
_PDCLIB_LOCAL void _PDCLIB_closeall( void );

/* Check if a given year is a leap year. Parameter is offset to 1900. */
_PDCLIB_LOCAL int _PDCLIB_is_leap( int year_offset );

/* Read a specified number of lines from a file stream; return a pointer to
   allocated memory holding the lines (newlines replaced with zero terminators)
   or NULL in case of error.
*/
_PDCLIB_LOCAL char * _PDCLIB_load_lines( struct _PDCLIB_file_t * fh, _PDCLIB_size_t lines );

/* -------------------------------------------------------------------------- */
/* errno                                                                      */
/* -------------------------------------------------------------------------- */

/* A mechanism for delayed evaluation.
   If PDCLib would call its error number "errno" directly, there would be no way
   to catch its value from underlying system calls that also use it (i.e., POSIX
   operating systems). That is why we use an internal name, providing a means to
   access it through <errno.h>.
*/
_PDCLIB_PUBLIC int * _PDCLIB_errno_func( void );

/* -------------------------------------------------------------------------- */
/* <locale.h> support                                                         */
/* -------------------------------------------------------------------------- */

#define _PDCLIB_LC_ALL        0
#define _PDCLIB_LC_COLLATE    1
#define _PDCLIB_LC_CTYPE      2
#define _PDCLIB_LC_MONETARY   3
#define _PDCLIB_LC_NUMERIC    4
#define _PDCLIB_LC_TIME       5
#define _PDCLIB_LC_MESSAGES   6
#define _PDCLIB_LC_COUNT      7

#define _PDCLIB_CTYPE_ALPHA   1
#define _PDCLIB_CTYPE_BLANK   2
#define _PDCLIB_CTYPE_CNTRL   4
#define _PDCLIB_CTYPE_GRAPH   8
#define _PDCLIB_CTYPE_PUNCT  16
#define _PDCLIB_CTYPE_SPACE  32
#define _PDCLIB_CTYPE_LOWER  64
#define _PDCLIB_CTYPE_UPPER 128

#define _PDCLIB_CHARSET_SIZE ( 1 << _PDCLIB_CHAR_BIT )

struct _PDCLIB_lc_lconv_numeric_t
{
    char * decimal_point;
    char * thousands_sep;
    char * grouping;
};

struct _PDCLIB_lc_lconv_monetary_t
{
    char * mon_decimal_point;
    char * mon_thousands_sep;
    char * mon_grouping;
    char * positive_sign;
    char * negative_sign;
    char * currency_symbol;
    char * int_curr_symbol;
    char frac_digits;
    char p_cs_precedes;
    char n_cs_precedes;
    char p_sep_by_space;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    char int_frac_digits;
    char int_p_cs_precedes;
    char int_n_cs_precedes;
    char int_p_sep_by_space;
    char int_n_sep_by_space;
    char int_p_sign_posn;
    char int_n_sign_posn;
};

struct _PDCLIB_lc_numeric_monetary_t
{
    struct lconv * lconv;
    int numeric_alloced;
    int monetary_alloced;
};

extern struct _PDCLIB_lc_numeric_monetary_t _PDCLIB_lc_numeric_monetary;

struct _PDCLIB_lc_collate_t
{
    int alloced;
    /* 1..3 code points */
    /* 1..8, 18 collation elements of 3 16-bit integers */
};

extern struct _PDCLIB_lc_collate_t _PDCLIB_lc_collate;

struct _PDCLIB_lc_ctype_entry_t
{
    _PDCLIB_uint16_t flags;
    unsigned char upper;
    unsigned char lower;
};

struct _PDCLIB_lc_ctype_t
{
    int alloced;
    int digits_low;
    int digits_high;
    int Xdigits_low;
    int Xdigits_high;
    int xdigits_low;
    int xdigits_high;
    struct _PDCLIB_lc_ctype_entry_t * entry;
};

extern struct _PDCLIB_lc_ctype_t _PDCLIB_lc_ctype;

struct _PDCLIB_lc_messages_t
{
    int alloced;
    char * errno_texts[_PDCLIB_ERRNO_MAX]; /* strerror() / perror()   */
};

extern struct _PDCLIB_lc_messages_t _PDCLIB_lc_messages;

struct _PDCLIB_lc_time_t
{
    int alloced;
    char * month_name_abbr[12]; /* month names, abbreviated                   */
    char * month_name_full[12]; /* month names, full                          */
    char * day_name_abbr[7];    /* weekday names, abbreviated                 */
    char * day_name_full[7];    /* weekday names, full                        */
    char * date_time_format;    /* date / time format for strftime( "%c" )    */
    char * time_format_12h;     /* 12-hour time format for strftime( "%r" )   */
    char * date_format;         /* date format for strftime( "%x" )           */
    char * time_format;         /* time format for strftime( "%X" )           */
    char * am_pm[2];            /* AM / PM designation                        */
};

extern struct _PDCLIB_lc_time_t _PDCLIB_lc_time;

_PDCLIB_LOCAL struct _PDCLIB_lc_lconv_numeric_t * _PDCLIB_load_lc_numeric( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_lconv_monetary_t * _PDCLIB_load_lc_monetary( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_collate_t * _PDCLIB_load_lc_collate( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_ctype_t * _PDCLIB_load_lc_ctype( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_time_t * _PDCLIB_load_lc_time( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_messages_t * _PDCLIB_load_lc_messages( const char * path, const char * locale );

/* -------------------------------------------------------------------------- */
/* Sanity checks                                                              */
/* -------------------------------------------------------------------------- */

/* Width of basic types */
_PDCLIB_static_assert( sizeof( short ) == _PDCLIB_SHRT_BYTES, "Compiler disagrees on _PDCLIB_SHRT_BYTES." );
_PDCLIB_static_assert( sizeof( int ) == _PDCLIB_INT_BYTES, "Compiler disagrees on _PDCLIB_INT_BYTES." );
_PDCLIB_static_assert( sizeof( long ) == _PDCLIB_LONG_BYTES, "Compiler disagrees on _PDCLIB_LONG_BYTES." );
_PDCLIB_static_assert( sizeof( long long ) == _PDCLIB_LLONG_BYTES, "Compiler disagrees on _PDCLIB_LLONG_BYTES." );

/* Signed-ness of char and size_t */
_PDCLIB_static_assert( ( (char)-1 < 0 ) == _PDCLIB_CHAR_SIGNED, "Compiler disagrees on _PDCLIB_CHAR_SIGNED." );

/* size_t as the result of sizeof */
_PDCLIB_static_assert( sizeof( sizeof( int ) ) == sizeof( _PDCLIB_size ), "Compiler disagrees on _PDCLIB_size." );

/* wchar_t as the type of wide character literals */
_PDCLIB_static_assert( sizeof( _PDCLIB_wchar ) == sizeof( L'x' ), "Compiler disagrees on _PDCLIB_wchar." );
#ifdef __cplusplus
_PDCLIB_static_assert( sizeof( _PDCLIB_wchar ) == sizeof( wchar_t ), "Compiler disagrees on _PDCLIB_wchar / wchar_t (C++)." );
#endif

/* intptr_t being wide enough to store the value of a pointer */
_PDCLIB_static_assert( sizeof( void * ) == sizeof( _PDCLIB_intptr ), "Compiler disagrees on _PDCLIB_intptr." );

/* ptrdiff_t as the result of pointer arithmetic */
_PDCLIB_static_assert( sizeof( &_PDCLIB_digits[1] - &_PDCLIB_digits[0] ) == sizeof( _PDCLIB_ptrdiff ), "Compiler disagrees on _PDCLIB_ptrdiff." );

#endif
