// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Integer types
// ----------------------------------------------------------------------------

#ifndef __STDINT_H
#define __STDINT_H __STDINT_H

// This file is part of the platform personality (see personality.txt).

// TODO: Documentation

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef int8_t;  // TODO
typedef int16_t; // TODO
typedef int32_t; // TODO
typedef int64_t; // TODO

typedef uint8_t;  // TODO
typedef uint16_t; // TODO
typedef uint32_t; // TODO
typedef uint64_t; // TODO

typedef int_least8_t;  // TODO
typedef int_least16_t; // TODO
typedef int_least32_t; // TODO
typedef int_least64_t; // TODO

typedef uint_least8_t;  // TODO
typedef uint_least16_t; // TODO
typedef uint_least32_t; // TODO
typedef uint_least64_t; // TODO

typedef int_fast8_t;  // TODO
typedef int_fast16_t; // TODO
typedef int_fast32_t; // TODO
typedef int_fast64_t; // TODO

typedef uint_fast8_t;  // TODO
typedef uint_fast16_t; // TODO
typedef uint_fast32_t; // TODO
typedef uint_fast64_t; // TODO

typedef intptr_t;  // TODO
typedef uintptr_t; // TODO

typedef intmax_t;  // TODO
typedef uintmax_t; // TODO

// ----------------------------------------------------------------------------
// MACROS

#define INT8_MIN  // TODO
#define INT16_MIN // TODO
#define INT32_MIN // TODO
#define INT64_MIN // TODO

#define INT8_MAX  0x7f
#define INT16_MAX 0x7fff
#define INT32_MAX 0x7fffffff
#define INT64_MAX 0x7fffffffffffffff

#define UINT8_MAX  0xff
#define UINT16_MAX 0xffff
#define UINT32_MAX 0xffffffff
#define UINT64_MAX 0xffffffffffffffff

#define INT_LEAST8_MIN  // TODO
#define INT_LEAST16_MIN // TODO
#define INT_LEAST32_MIN // TODO
#define INT_LEAST64_MIN // TODO

#define INT_LEAST8_MAX  // TODO
#define INT_LEAST16_MAX // TODO
#define INT_LEAST32_MAX // TODO
#define INT_LEAST64_MAX // TODO

#define UINT_LEAST8_MAX  // TODO
#define UINT_LEAST16_MAX // TODO
#define UINT_LEAST32_MAX // TODO
#define UINT_LEAST64_MAX // TODO

#define INT_FAST8_MIN  // TODO
#define INT_FAST16_MIN // TODO
#define INT_FAST32_MIN // TODO
#define INT_FAST64_MIN // TODO

#define INT_FAST8_MAX  // TODO
#define INT_FAST16_MAX // TODO
#define INT_FAST32_MAX // TODO
#define INT_FAST64_MAX // TODO

#define UINT_FAST8_MAX  // TODO
#define UINT_FAST16_MAX // TODO
#define UINT_FAST32_MAX // TODO
#define UINT_FAST64_MAX // TODO

#define INTPTR_MIN  // TODO
#define INTPTR_MAX  // TODO
#define UINTPTR_MAX // TODO

#define INT8_C(x)  // TODO
#define INT16_C(x) // TODO
#define INT32_C(x) // TODO
#define INT64_C(x) // TODO

#define UINT8_C(x)  // TODO
#define UINT16_C(x) // TODO
#define UINT32_C(x) // TODO
#define UINT64_C(x) // TODO

#define INTMAX_C(x)  // TODO
#define UINTMAX_C(x) // TODO

#define PTRDIFF_MIN // TODO
#define PTRDIFF_MAX // TODO

#define SIG_ATOMIC_MIN // TODO
#define SIG_ATOMIC_MAX // TODO

#define SIZE_MAX  // TODO

#define WCHAR_MIN // TODO
#define WCHAR_MAX // TODO

#include "__WCHAR.h"

#define INTMAX_MIN  // TODO
#define INTMAX_MAX  // TODO
#define UINTMAX_MAX // TODO

#endif // __STDINT_H
