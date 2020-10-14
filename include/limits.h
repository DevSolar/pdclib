/* Sizes of integer types <limits.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_LIMITS_H
#define _PDCLIB_LIMITS_H _PDCLIB_LIMITS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_internal.h"

/* TODO: Defined to 1 as multibyte characters are not supported yet. */
#define MB_LEN_MAX 1

#define LLONG_MIN  _PDCLIB_LLONG_MIN
#define LLONG_MAX  _PDCLIB_LLONG_MAX
#define ULLONG_MAX _PDCLIB_ULLONG_MAX

#define CHAR_BIT   _PDCLIB_CHAR_BIT
#define CHAR_MAX   _PDCLIB_CHAR_MAX
#define CHAR_MIN   _PDCLIB_CHAR_MIN
#define SCHAR_MAX  _PDCLIB_SCHAR_MAX
#define SCHAR_MIN  _PDCLIB_SCHAR_MIN
#define UCHAR_MAX  _PDCLIB_UCHAR_MAX
#define SHRT_MAX   _PDCLIB_SHRT_MAX
#define SHRT_MIN   _PDCLIB_SHRT_MIN
#define INT_MAX    _PDCLIB_INT_MAX
#define INT_MIN    _PDCLIB_INT_MIN
#define LONG_MAX   _PDCLIB_LONG_MAX
#define LONG_MIN   _PDCLIB_LONG_MIN
#define USHRT_MAX  _PDCLIB_USHRT_MAX
#define UINT_MAX   _PDCLIB_UINT_MAX
#define ULONG_MAX  _PDCLIB_ULONG_MAX

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_LIMITS_H
#include _PDCLIB_EXTEND_LIMITS_H
#endif

#ifdef __cplusplus
}
#endif

#endif
