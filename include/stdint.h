/* Integer types <stdint.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDINT_H
#define _PDCLIB_STDINT_H _PDCLIB_STDINT_H

#include "pdclib/_PDCLIB_lib_ext1.h"
#include "pdclib/_PDCLIB_config.h"

/* Exact-width integer types. */

#ifdef _PDCLIB_int8_t
typedef signed _PDCLIB_int8_t int8_t;
typedef unsigned _PDCLIB_int8_t uint8_t;
#endif

#ifdef _PDCLIB_int16_t
typedef signed _PDCLIB_int16_t int16_t;
typedef unsigned _PDCLIB_int16_t uint16_t;
#endif

#ifdef _PDCLIB_int32_t
typedef signed _PDCLIB_int32_t int32_t;
typedef unsigned _PDCLIB_int32_t uint32_t;
#endif

#ifdef _PDCLIB_int64_t
typedef signed _PDCLIB_int64_t int64_t;
typedef unsigned _PDCLIB_int64_t uint64_t;
#endif

/* Minimum-width integer types */

/* You are allowed to add more types here, e.g. int_least24_t. */

#ifdef _PDCLIB_int_least8_t
typedef signed _PDCLIB_int_least8_t int_least8_t;
typedef unsigned _PDCLIB_int_least8_t uint_least8_t;
#endif

#ifdef _PDCLIB_int_least16_t
typedef signed _PDCLIB_int_least16_t int_least16_t;
typedef unsigned _PDCLIB_int_least16_t uint_least16_t;
#endif

#ifdef _PDCLIB_int_least32_t
typedef signed _PDCLIB_int_least32_t int_least32_t;
typedef unsigned _PDCLIB_int_least32_t uint_least32_t;
#endif

#ifdef _PDCLIB_least64_t
typedef signed _PDCLIB_int_least64_t int_least64_t;
typedef unsigned _PDCLIB_int_least64_t uint_least64_t;
#endif

/* Fastest minimum-width integer types */

/* You are allowed to add more types here, e.g. int_fast24_t. */

#ifdef _PDCLIB_int_fast8_t
typedef signed _PDCLIB_int_fast8_t int_fast8_t;
typedef unsigned _PDCLIB_int_fast8_t uint_fast8_t;
#endif

#ifdef _PDCLIB_int_fast16_t
typedef signed _PDCLIB_int_fast16_t int_fast16_t;
typedef unsigned _PDCLIB_int_fast16_t uint_fast16_t;
#endif

#ifdef _PDCLIB_int_fast32_t
typedef signed _PDCLIB_int_fast32_t int_fast32_t;
typedef unsigned _PDCLIB_int_fast32_t uint_fast32_t;
#endif

#ifdef _PDCLIB_fast64_t
typedef signed _PDCLIB_int_fast64_t int_fast64_t;
typedef unsigned _PDCLIB_int_fast64_t uint_fast64_t;
#endif

/* Integer types capable of taking the (cast) value of a void *, and having
   the value cast back to void *, comparing equal to the original.
*/

typedef signed _PDCLIB_intptr_t intptr_t;
typedef unsigned _PDCLIB_intptr_t uintptr_t;

/* Largest supported integer type. Implementation note: see _PDCLIB_atomax(). */

typedef signed _PDCLIB_intmax_t intmax_t;
typedef unsigned _PDCLIB_intmax_t uintmax_t;

/* Limits of specified-width integer types */

/* C99 specifies that C++ implementations should define these macros only if
   __STDC_LIMIT_MACROS is defined before <stdint.h> is incuded. C++11, however,
   specified that no such definition should be necessary. PDCLib goes with the
   C++11 specification.
*/

/* Limits of exact-width integer types */

#ifdef _PDCLIB_int8_t
#define INT8_MAX _PDCLIB_INT8_MAX
#define INT8_MIN ( -_PDCLIB_INT8_MAX - 1 )
#define UINT8_MAX _PDCLIB_UINT8_MAX
#endif

#ifdef _PDCLIB_INT16_MAX
#define INT16_MAX _PDCLIB_INT16_MAX
#define INT16_MIN ( -_PDCLIB_INT16_MAX - 1 )
#define UINT16_MAX _PDCLIB_UINT16_MAX
#endif

#ifdef _PDCLIB_INT32_MAX
#define INT32_MAX _PDCLIB_INT32_MAX
#define INT32_MIN ( -_PDCLIB_INT32_MAX - 1 )
#define UINT32_MAX _PDCLIB_UINT32_MAX
#endif

#ifdef _PDCLIB_INT64_MAX
#define INT64_MAX _PDCLIB_INT64_MAX
#define INT64_MIN ( -_PDCLIB_INT64_MAX - 1 )
#define UINT64_MAX _PDCLIB_UINT64_MAX
#endif

/* Limits of minimum-width integer types */

#ifdef _PDCLIB_INT_LEAST8_MAX
#define INT_LEAST8_MAX _PDCLIB_INT_LEAST8_MAX
#define INT_LEAST8_MIN ( -_PDCLIB_INT_LEAST8_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_LEAST8_MAX ( _PDCLIB_INT_LEAST8_MAX * _PDCLIB_UINT8_C( 2 ) + 1 )
#endif

#ifdef _PDCLIB_INT_LEAST16_MAX
#define INT_LEAST16_MAX _PDCLIB_INT_LEAST16_MAX
#define INT_LEAST16_MIN ( -_PDCLIB_INT_LEAST16_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_LEAST16_MAX ( _PDCLIB_INT_LEAST16_MAX * _PDCLIB_UINT16_C( 2 ) + 1 )
#endif

#ifdef _PDCLIB_INT_LEAST32_MAX
#define INT_LEAST32_MAX _PDCLIB_INT_LEAST32_MAX
#define INT_LEAST32_MIN ( -_PDCLIB_INT_LEAST32_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_LEAST32_MAX ( _PDCLIB_INT_LEAST32_MAX * _PDCLIB_UINT32_C( 2 ) + 1 )
#endif

#ifdef _PDCLIB_INT_LEAST64_MAX
#define INT_LEAST64_MAX _PDCLIB_INT_LEAST64_MAX
#define INT_LEAST64_MIN ( -_PDCLIB_INT_LEAST64_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_LEAST64_MAX ( _PDCLIB_INT_LEAST64_MAX * _PDCLIB_UINT64_C( 2 ) + 1 )
#endif

/* Limits of fastest minimum-width integer types */

#ifdef _PDCLIB_INT_FAST8_MAX
#define INT_FAST8_MAX _PDCLIB_INT_FAST8_MAX
#define INT_FAST8_MIN ( -_PDCLIB_INT_FAST8_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_FAST8_MAX _PDCLIB_UINT_FAST8_MAX
#endif

#ifdef _PDCLIB_INT_FAST16_MAX
#define INT_FAST16_MAX _PDCLIB_INT_FAST16_MAX
#define INT_FAST16_MIN ( -_PDCLIB_INT_FAST16_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_FAST16_MAX _PDCLIB_UINT_FAST16_MAX
#endif

#ifdef _PDCLIB_INT_FAST32_MAX
#define INT_FAST32_MAX _PDCLIB_INT_FAST32_MAX
#define INT_FAST32_MIN ( -_PDCLIB_INT_FAST32_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_FAST32_MAX _PDCLIB_UINT_FAST32_MAX
#endif

#ifdef _PDCLIB_INT_FAST64_MAX
#define INT_FAST64_MAX _PDCLIB_INT_FAST64_MAX
#define INT_FAST64_MIN ( -_PDCLIB_INT_FAST64_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_FAST64_MAX _PDCLIB_UINT_FAST64_MAX
#endif

/* Limits of integer types capable of holding object pointers */

#define INTPTR_MAX _PDCLIB_INTPTR_MAX
#define INTPTR_MIN ( -_PDCLIB_INTPTR_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINTPTR_MAX _PDCLIB_UINTPTR_MAX

/* Limits of greatest-width integer types */

#define INTMAX_MIN _PDCLIB_INTMAX_MAX
#define INTMAX_MAX ( -_PDCLIB_INTMAX_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINTMAX_MAX ( _PDCLIB_INTMAX_MAX * _PDCLIB_UINTMAX_C( 2 ) + 1 )

/* Limits of other integer types */

#define PTRDIFF_MAX _PDCLIB_PTRDIFF_MAX
#define PTRDIFF_MIN ( -_PDCLIB_PTRDIFF_MAX - _PDCLIB_SIGNED_ENCODING / 2 )

#define SIG_ATOMIC_MAX _PDCLIB_SIG_ATOMIC_MAX
#define SIG_ATOMIC_MIN ( -_PDCLIB_SIG_ATOMIC_MAX - _PDCLIB_SIGNED_ENCODING / 2 )

#define SIZE_MAX _PDCLIB_SIZE_MAX

#define WCHAR_MAX _PDCLIB_WCHAR_MAX
#define WCHAR_MIN _PDCLIB_WCHAR_MIN

#define WINT_MAX _PDCLIB_WINT_MAX
#define WINT_MIN _PDCLIB_WINT_MIN

/* Macros for integer constants */

/* Macros for minimum-width integer constants */

/* Expand to an integer constant of specified value and type int_leastN_t */

#define INT8_C  _PDCLIB_INT8_C
#define INT16_C _PDCLIB_INT16_C
#define INT32_C _PDCLIB_INT32_C
#define INT64_C _PDCLIB_INT64_C

/* Expand to an integer constant of specified value and type uint_leastN_t */

#define UINT8_C  _PDCLIB_UINT8_C
#define UINT16_C _PDCLIB_UINT16_C
#define UINT32_C _PDCLIB_UINT32_C
#define UINT64_C _PDCLIB_UINT64_C

/* Macros for greatest-width integer constants */

/* Expand to an integer constant of specified value and type intmax_t */

#define INTMAX_C _PDCLIB_INTMAX_C

/* Expand to an integer constant of specified value and type uintmax_t */

#define UINTMAX_C _PDCLIB_UINTMAX_C

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

#endif
