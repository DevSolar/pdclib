/* Internal PDCLib configuration <_PDCLIB_config.h>
   (x86_64-linux-gcc)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H

/* -------------------------------------------------------------------------- */
/* Integers                                                                   */
/* -------------------------------------------------------------------------- */

/* Bits in a char                                                             */
#define _PDCLIB_CHAR_WIDTH 8

/* Whether 'char' is signed                                                   */
#define _PDCLIB_CHAR_SIGNED 1

/* Encoding of signed values - (2) two's complement, (1) one's complement,    */
/* (0) signed magnitude                                                       */
#define _PDCLIB_SIGNED_ENCODING 2

/* Maximum values of base types                                               */
#define _PDCLIB_CHAR_MAX 0x7f
#define _PDCLIB_SHRT_MAX 0x7fff
#define _PDCLIB_INT_MAX 0x7fffffff
#define _PDCLIB_LONG_MAX 0x7fffffffffffffffL
#define _PDCLIB_LLONG_MAX 0x7fffffffffffffffLL

/* Exact-width, two's complement types (leave undefined if not available)     */
/* Base type only, signed / unsigned is added in <stdint.h>.                  */
/* (The max values could be hardcoded in <stdint.h> directly, but the *type*  */
/* suffixes could not.)                                                       */
#define _PDCLIB_int8_t char
#define _PDCLIB_int16_t short
#define _PDCLIB_int32_t int
#define _PDCLIB_int64_t long

#define _PDCLIB_INT8_MAX 0x7f
#define _PDCLIB_INT16_MAX 0x7fff
#define _PDCLIB_INT32_MAX 0x7fffffff
#define _PDCLIB_INT64_MAX 0x7fffffffffffffffL

#define _PDCLIB_UINT8_MAX 0xffU
#define _PDCLIB_UINT16_MAX 0xffffU
#define _PDCLIB_UINT32_MAX 0xffffffffU
#define _PDCLIB_UINT64_MAX 0xffffffffffffffffUL

/* Minimal type with at least n bits width (leave undefined if not available) */
/* Base type only, signed / unsigned is added in <stdint.h>.                  */
#define _PDCLIB_int_least8_t char
#define _PDCLIB_int_least16_t short
#define _PDCLIB_int_least32_t int
#define _PDCLIB_int_least64_t long

#define _PDCLIB_INT_LEAST8_MAX 0x7f
#define _PDCLIB_INT_LEAST16_MAX 0x7fff
#define _PDCLIB_INT_LEAST32_MAX 0x7fffffff
#define _PDCLIB_INT_LEAST64_MAX 0x7fffffffffffffffL

#define _PDCLIB_INT8_C( x ) x
#define _PDCLIB_INT16_C( x ) x
#define _PDCLIB_INT32_C( x ) x
#define _PDCLIB_INT64_C( x ) x ## L

#define _PDCLIB_UINT8_C( x ) x ## U
#define _PDCLIB_UINT16_C( x ) x ## U
#define _PDCLIB_UINT32_C( x ) x ## U
#define _PDCLIB_UINT64_C( x ) x ## UL

/* Fastest type with at least n bits width (leave undefined if not available) */
/* Base type only, signed / unsigned is added in <stdint.h>.                  */
#define _PDCLIB_int_fast8_t char
#define _PDCLIB_int_fast16_t long
#define _PDCLIB_int_fast32_t long
#define _PDCLIB_int_fast64_t long

#define _PDCLIB_INT_FAST8_MAX 0x7f
#define _PDCLIB_INT_FAST16_MAX 0x7fffffffffffffffL
#define _PDCLIB_INT_FAST32_MAX 0x7fffffffffffffffL
#define _PDCLIB_INT_FAST64_MAX 0x7fffffffffffffffL

#define _PDCLIB_UINT_FAST8_MAX 0xffU
#define _PDCLIB_UINT_FAST16_MAX 0xffffffffffffffffUL
#define _PDCLIB_UINT_FAST32_MAX 0xffffffffffffffffUL
#define _PDCLIB_UINT_FAST64_MAX 0xffffffffffffffffUL

/* Integer types capable of taking the (cast) value of a void *, and having   */
/* the value cast back to void *, comparing equal to the original.            */
/* Base type only, signed / unsigned is added in <stdint.h>.                  */
#define _PDCLIB_intptr_t long
#define _PDCLIB_INTPTR_MAX 0x7fffffffffffffffL
#define _PDCLIB_UINTPTR_MAX 0xffffffffffffffffUL

/* Largest supported integer type. Implemetation note: see _PDCLIB_atomax().  */
/* Base type only, signed / unsigned is added in <stdint.h>.                  */
#define _PDCLIB_intmax_t long
#define _PDCLIB_INTMAX_MAX 0x7fffffffffffffffL

#define _PDCLIB_INTMAX_C( x ) x ## L
#define _PDCLIB_UINTMAX_C( x ) x ## UL

/* (Signed) type resulting from substracting one pointer from another         */
#define _PDCLIB_ptrdiff_t long
#define _PDCLIB_PTRDIFF_MAX 0x7fffffffffffffffL

/* Type that can be accessed atomically.                                      */
#define _PDCLIB_sig_atomic_t int
#define _PDCLIB_SIG_ATOMIC_MAX 0x7fffffff

/* (Unsigned) type that sizeof() evaluates to.                                */
#define _PDCLIB_size_t unsigned long
#define _PDCLIB_SIZE_MAX 0xffffffffffffffffUL

/* Type that L'x' evaluates to                                                */
#define _PDCLIB_wchar_t int
#define _PDCLIB_WCHAR_MAX 0x7fffffff
#define _PDCLIB_WCHAR_MIN ( -_PDCLIB_WCHAR_MAX - _PDCLIB_SIGNED_ENCODING / 2 )

/* Type that can hold any wchar_t value, plus WEOF                            */
#define _PDCLIB_wint_t unsigned int
#define _PDCLIB_WINT_MAX 0xffffffff
#define _PDCLIB_WINT_MIN 0

#endif
