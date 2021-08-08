/* Integer types <stdint.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDINT_H
#define _PDCLIB_STDINT_H _PDCLIB_STDINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_lib_ext1.h"
#include "pdclib/_PDCLIB_internal.h"

/* 7.18.1.1 Exact-width integer types. */

#ifdef _PDCLIB_int8_t
typedef _PDCLIB_int8_t int8_t;
typedef _PDCLIB_uint8_t uint8_t;
#endif

#ifdef _PDCLIB_int16_t
typedef _PDCLIB_int16_t int16_t;
typedef _PDCLIB_uint16_t uint16_t;
#endif

#ifdef _PDCLIB_int32_t
typedef _PDCLIB_int32_t int32_t;
typedef _PDCLIB_uint32_t uint32_t;
#endif

#ifdef _PDCLIB_int64_t
typedef _PDCLIB_int64_t int64_t;
typedef _PDCLIB_uint64_t uint64_t;
#endif

/* 7.18.1.2 Minimum-width integer types */

/* You are allowed to add more types here, e.g. int_least24_t. */

typedef _PDCLIB_int_least8_t  int_least8_t;
typedef _PDCLIB_int_least16_t int_least16_t;
typedef _PDCLIB_int_least32_t int_least32_t;
typedef _PDCLIB_int_least64_t int_least64_t;

typedef _PDCLIB_uint_least8_t  uint_least8_t;
typedef _PDCLIB_uint_least16_t uint_least16_t;
typedef _PDCLIB_uint_least32_t uint_least32_t;
typedef _PDCLIB_uint_least64_t uint_least64_t;

/* 7.18.1.3 Fastest minimum-width integer types */

/* You are allowed to add more types here, e.g. int_fast24_t. */

typedef _PDCLIB_int_fast8_t  int_fast8_t;
typedef _PDCLIB_int_fast16_t int_fast16_t;
typedef _PDCLIB_int_fast32_t int_fast32_t;
typedef _PDCLIB_int_fast64_t int_fast64_t;

typedef _PDCLIB_uint_fast8_t  uint_fast8_t;
typedef _PDCLIB_uint_fast16_t uint_fast16_t;
typedef _PDCLIB_uint_fast32_t uint_fast32_t;
typedef _PDCLIB_uint_fast64_t uint_fast64_t;

/* 7.18.1.4 Integer types capable of holding object pointers */

typedef _PDCLIB_intptr_t  intptr_t;
typedef _PDCLIB_uintptr_t uintptr_t;

/* 7.18.1.5 Greatest-width integer types */

typedef _PDCLIB_intmax_t  intmax_t;
typedef _PDCLIB_uintmax_t uintmax_t;

/* 7.18.2 Limits of specified-width integer types */

#if defined( __cplusplus ) && __cplusplus < 201103L
#ifndef __STDC_LIMIT_MACROS
#define _PDCLIB_NO_LIMIT_MACROS
#endif
#endif

#ifndef _PDCLIB_NO_LIMIT_MACROS

/* 7.18.2.1 Limits of exact-width integer types */

#if _PDCLIB_TWOS_COMPLEMENT == 1

#if _PDCLIB_INT_LEAST8_MAX == 0x7f
#define INT8_MAX _PDCLIB_INT_LEAST8_MAX
#define INT8_MIN _PDCLIB_INT_LEAST8_MIN
#define UINT8_MAX _PDCLIB_UINT_LEAST8_MAX
#endif

#if _PDCLIB_INT_LEAST16_MAX == 0x7fff
#define INT16_MAX _PDCLIB_INT_LEAST16_MAX
#define INT16_MIN _PDCLIB_INT_LEAST16_MIN
#define UINT16_MAX _PDCLIB_UINT_LEAST16_MAX
#endif

#if _PDCLIB_INT_LEAST32_MAX == 0x7fffffffl
#define INT32_MAX _PDCLIB_INT_LEAST32_MAX
#define INT32_MIN _PDCLIB_INT_LEAST32_MIN
#define UINT32_MAX _PDCLIB_UINT_LEAST32_MAX
#endif

#if _PDCLIB_INT_LEAST64_MAX == 0x7fffffffffffffffll
#define INT64_MAX _PDCLIB_INT_LEAST64_MAX
#define INT64_MIN _PDCLIB_INT_LEAST64_MIN
#define UINT64_MAX _PDCLIB_UINT_LEAST64_MAX
#endif

#endif

/* 7.18.2.2 Limits of minimum-width integer types */

#define INT_LEAST8_MIN  _PDCLIB_INT_LEAST8_MIN
#define INT_LEAST8_MAX  _PDCLIB_INT_LEAST8_MAX
#define UINT_LEAST8_MAX _PDCLIB_UINT_LEAST8_MAX

#define INT_LEAST16_MIN  _PDCLIB_INT_LEAST16_MIN
#define INT_LEAST16_MAX  _PDCLIB_INT_LEAST16_MAX
#define UINT_LEAST16_MAX _PDCLIB_UINT_LEAST16_MAX

#define INT_LEAST32_MIN  _PDCLIB_INT_LEAST32_MIN
#define INT_LEAST32_MAX  _PDCLIB_INT_LEAST32_MAX
#define UINT_LEAST32_MAX _PDCLIB_UINT_LEAST32_MAX

#define INT_LEAST64_MIN  _PDCLIB_INT_LEAST64_MIN
#define INT_LEAST64_MAX  _PDCLIB_INT_LEAST64_MAX
#define UINT_LEAST64_MAX _PDCLIB_UINT_LEAST64_MAX

/* 7.18.2.3 Limits of fastest minimum-width integer types */

#define INT_FAST8_MIN  _PDCLIB_INT_FAST8_MIN
#define INT_FAST8_MAX  _PDCLIB_INT_FAST8_MAX
#define UINT_FAST8_MAX _PDCLIB_UINT_FAST8_MAX

#define INT_FAST16_MIN  _PDCLIB_INT_FAST16_MIN
#define INT_FAST16_MAX  _PDCLIB_INT_FAST16_MAX
#define UINT_FAST16_MAX _PDCLIB_UINT_FAST16_MAX

#define INT_FAST32_MIN  _PDCLIB_INT_FAST32_MIN
#define INT_FAST32_MAX  _PDCLIB_INT_FAST32_MAX
#define UINT_FAST32_MAX _PDCLIB_UINT_FAST32_MAX

#define INT_FAST64_MIN  _PDCLIB_INT_FAST64_MIN
#define INT_FAST64_MAX  _PDCLIB_INT_FAST64_MAX
#define UINT_FAST64_MAX _PDCLIB_UINT_FAST64_MAX

/* 7.18.2.4 Limits of integer types capable of holding object pointers */

#define INTPTR_MIN  _PDCLIB_INTPTR_MIN
#define INTPTR_MAX  _PDCLIB_INTPTR_MAX
#define UINTPTR_MAX _PDCLIB_UINTPTR_MAX

/* 7.18.2.5 Limits of greatest-width integer types */

#define INTMAX_MIN  _PDCLIB_INTMAX_MIN
#define INTMAX_MAX  _PDCLIB_INTMAX_MAX
#define UINTMAX_MAX _PDCLIB_UINTMAX_MAX

/* 7.18.3 Limits of other integer types */

#define PTRDIFF_MIN _PDCLIB_PTRDIFF_MIN
#define PTRDIFF_MAX _PDCLIB_PTRDIFF_MAX

#define SIG_ATOMIC_MIN _PDCLIB_SIG_ATOMIC_MIN
#define SIG_ATOMIC_MAX _PDCLIB_SIG_ATOMIC_MAX

#define SIZE_MAX _PDCLIB_SIZE_MAX

#define WCHAR_MIN _PDCLIB_WCHAR_MIN
#define WCHAR_MAX _PDCLIB_WCHAR_MAX

#define WINT_MIN _PDCLIB_WINT_MIN
#define WINT_MAX _PDCLIB_WINT_MAX

#endif

/* 7.18.4 Macros for integer constants */

#if defined( __cplusplus ) && __cplusplus < 201103L
#ifndef __STDC_CONSTANT_MACROS
#define _PDCLIB_NO_CONSTANT_MACROS
#endif
#endif

#ifndef _PDCLIB_NO_CONSTANT_MACROS

/* 7.18.4.1 Macros for minimum-width integer constants */

/* Expand to an integer constant of specified value and type int_leastN_t */

#define INT8_C  _PDCLIB_INT_LEAST8_C
#define INT16_C _PDCLIB_INT_LEAST16_C
#define INT32_C _PDCLIB_INT_LEAST32_C
#define INT64_C _PDCLIB_INT_LEAST64_C

/* Expand to an integer constant of specified value and type uint_leastN_t */

#define UINT8_C  _PDCLIB_UINT_LEAST8_C
#define UINT16_C _PDCLIB_UINT_LEAST16_C
#define UINT32_C _PDCLIB_UINT_LEAST32_C
#define UINT64_C _PDCLIB_UINT_LEAST64_C

/* 7.18.4.2 Macros for greatest-width integer constants */

/* Expand to an integer constant of specified value and type intmax_t */
#define INTMAX_C( value ) _PDCLIB_INTMAX_C( value )

/* Expand to an integer constant of specified value and type uintmax_t */
#define UINTMAX_C( value ) _PDCLIB_UINTMAX_C( value )

#endif

/* Annex K -- Bounds-checking interfaces */

#if ( __STDC_WANT_LIB_EXT1__ + 0 ) != 0
#define RSIZE_MAX ( _PDCLIB_SIZE_MAX >> 1 )
#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_STDINT_H
#include _PDCLIB_EXTEND_STDINT_H
#endif

#ifdef __cplusplus
}
#endif

#endif
