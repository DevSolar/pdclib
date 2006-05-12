/* $Id$ */

/* PDCLib internal integer logic <_PDCLIB_int.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* You should not have to edit anything in this file; if you DO have to, it   */
/* would be considered a bug / missing feature: notify the author(s).         */
/* -------------------------------------------------------------------------- */

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H
#include <_PDCLIB_config.h>
#endif

#ifndef _PDCLIB_AUX_H
#define _PDCLIB_AUX_H _PDCLIB_AUX_H
#include <_PDCLIB_aux.h>
#endif

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
#ifdef  _PDCLIB_CHAR_SIGNED
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
#define _PDCLIB_ULLONG_MAX 0xffffffffffffffffffffffffffffffffLL
#else
#error Unsupported width of 'long long' (neither 64 nor 128 bit).
#endif
#define _PDCLIB_ULLONG_MIN 0

/* -------------------------------------------------------------------------- */
/* <stdint.h> exact-width types and their limits                              */
/* -------------------------------------------------------------------------- */

/* Setting 'int8_t', its limits, and its literal.                             */
#if     _PDCLIB_CHAR_BIT == 8
typedef signed char        _PDCLIB_int8_t;
typedef unsigned char      _PDCLIB_uint8_t;
#define _PDCLIB_INT8_MAX   _PDCLIB_CHAR_MAX
#define _PDCLIB_INT8_MIN   _PDCLIB_CHAR_MIN
#define _PDCLIB_UINT8_MAX  _PDCLIB_UCHAR_MAX
#define _PDCLIB_INT8_LITERAL
#define _PDCLIB_UINT8_LITERAL
#else
#error Unsupported width of char (not 8 bits).
#endif

/* Setting 'int16_t', its limits, and its literal                             */
#if     _PDCLIB_INT_BYTES  == 2
typedef signed int         _PDCLIB_int16_t;
typedef unsigned int       _PDCLIB_uint16_t;
#define _PDCLIB_INT16_MAX  _PDCLIB_INT_MAX
#define _PDCLIB_INT16_MIN  _PDCLIB_INT_MIN
#define _PDCLIB_UINT16_MAX _PDCLIB_UINT_MAX
#define _PDCLIB_INT16_LITERAL
#define _PDCLIB_UINT16_LITERAL
#elif   _PDCLIB_SHRT_BYTES == 2
typedef signed short       _PDCLIB_int16_t;
typedef unsigned short     _PDCLIB_uint16_t;
#define _PDCLIB_INT16_MAX  _PDCLIB_SHRT_MAX
#define _PDCLIB_INT16_MIN  _PDCLIB_SHRT_MIN
#define _PDCLIB_UINT16_MAX _PDCLIB_USHRT_MAX
#define _PDCLIB_INT16_LITERAL  s
#define _PDCLIB_UINT16_LITERAL us
#else
#error Neither 'short' nor 'int' are 16-bit.
#endif

/* Setting 'int32_t', its limits, and its literal                             */
#if     _PDCLIB_INT_BYTES  == 4
typedef signed int         _PDCLIB_int32_t;
typedef unsigned int       _PDCLIB_uint32_t;
#define _PDCLIB_INT32_MAX  _PDCLIB_INT_MAX
#define _PDCLIB_INT32_MIN  _PDCLIB_INT_MIN
#define _PDCLIB_UINT32_MAX _PDCLIB_UINT_MAX
#define _PDCLIB_INT32_LITERAL
#define _PDCLIB_UINT32_LITERAL
#elif   _PDCLIB_LONG_BYTES == 4
typedef signed long        _PDCLIB_int32_t;
typedef unsigned long      _PDCLIB_uint32_t;
#define _PDCLIB_INT32_MAX  _PDCLIB_LONG_MAX
#define _PDCLIB_INT32_MIN  _PDCLIB_LONG_MIN
#define _PDCLIB_UINT32_MAX _PDCLIB_LONG_MAX
#define _PDCLIB_INT32_LITERAL  l
#define _PDCLIB_UINT32_LITERAL ul
#else
#error Neither 'int' nor 'long' are 32-bit.
#endif

#if     _PDCLIB_LONG_BYTES == 8
typedef signed long        _PDCLIB_int64_t;
typedef unsigned long      _PDCLIB_uint64_t;
#define _PDCLIB_INT64_MAX  _PDCLIB_LONG_MAX
#define _PDCLIB_INT64_MIN  _PDCLIB_LONG_MIN
#define _PDCLIB_UINT64_MAX  _PDCLIB_ULONG_MAX
#define _PDCLIB_INT64_LITERAL  l
#define _PDCLIB_UINT64_LITERAL ul
#elif _PDCLIB_LLONG_BYTES  == 8
typedef signed long long   _PDCLIB_int64_t;
typedef unsigned long long _PDCLIB_uint64_t;
#define _PDCLIB_INT64_MAX  _PDCLIB_LLONG_MAX
#define _PDCLIB_INT64_MIN  _PDCLIB_LLONG_MIN
#define _PDCLIB_UINT64_MAX  _PDCLIB_ULLONG_MAX
#define _PDCLIB_INT64_LITERAL  ll
#define _PDCLIB_UINT64_LITERAL ull
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

/* Flags for representing mode (see fopen()). */
#define _PDCLIB_FREAD    1
#define _PDCLIB_FWRITE   2
#define _PDCLIB_FAPPEND  4
#define _PDCLIB_FRW      8
#define _PDCLIB_FBIN    16

struct _PDCLIB_file_t
{
    _PDCLIB_fd_t            handle;   /* OS-specific file descriptor */
    _PDCLIB_fpos_t          position; /* file position indicator */
    void *                  buffer;   /* file buffer */
    _PDCLIB_size_t          bufsize;  /* size of buffer */
    unsigned int            status;   /* misc. status bits */
  /*mbstate_t               mbstate;    multibyte parse state - TODO: Unmask. */
    struct _PDCLIB_file_t * next;     /* provisions for linked list handling */
};

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
    int              base;  /* base to which the value shall be converted    */
    _PDCLIB_int_fast32_t flags; /* flags and length modifiers                */
    _PDCLIB_size_t   n;     /* maximum number of characters to be written    */
    _PDCLIB_size_t   i;     /* number of characters already written          */
    _PDCLIB_size_t   this;  /* output chars in the current conversion        */
    char *           s;     /* target buffer                                 */
    _PDCLIB_size_t   width; /* width of current field                        */
    _PDCLIB_size_t   prec;  /* precision of current field                    */
    struct _PDCLIB_file_t * stream;/* for to-stream output                   */
    _PDCLIB_va_list  arg;   /* argument stack passed to the printf function  */
};

/* -------------------------------------------------------------------------- */
/* Declaration of helper functions (implemented in functions/_PDCLIB).        */
/* -------------------------------------------------------------------------- */

/* This is the main function called by atoi(), atol() and atoll().            */
_PDCLIB_intmax_t _PDCLIB_atomax( const char * s );

/* Two helper functions used by strtol(), strtoul() and long long variants.   */
const char * _PDCLIB_strtox_prelim( const char * p, char * sign, int * base );
_PDCLIB_uintmax_t _PDCLIB_strtox_main( const char ** p, unsigned int base, _PDCLIB_uintmax_t error, _PDCLIB_uintmax_t limval, _PDCLIB_uintmax_t limdigit, char * sign );

/* Digits array used by various integer conversion functions in <stdlib.h>    */
extern char _PDCLIB_digits[];

/* The worker for all printf() type of functions. */
const char * _PDCLIB_print( const char * spec, struct _PDCLIB_status_t * status );
