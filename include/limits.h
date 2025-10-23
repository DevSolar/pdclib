/* Sizes of integer types <limits.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_LIMITS_H
#define _PDCLIB_LIMITS_H _PDCLIB_LIMITS_H

#include "pdclib/_PDCLIB_config.h"

/* TODO: Defined to 1 as multibyte characters are not supported yet. */
#define MB_LEN_MAX 1

#define CHAR_BIT   _PDCLIB_CHAR_WIDTH

#define SCHAR_MAX _PDCLIB_CHAR_MAX
#define SCHAR_MIN ( -_PDCLIB_CHAR_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UCHAR_MAX ( ( _PDCLIB_CHAR_MAX * 2u ) + 1 )

#if ( _PDCLIB_CHAR_SIGNED + 0 ) == 1
#define CHAR_MAX SCHAR_MAX
#define CHAR_MIN SCHAR_MIN
#else
#define CHAR_MAX UCHAR_MAX
#define CHAR_MIN 0
#endif

#define SHRT_MAX _PDCLIB_SHRT_MAX
#define SHRT_MIN ( -_PDCLIB_SHRT_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define USHRT_MAX ( ( _PDCLIB_SHRT_MAX * 2u ) + 1 )

#define INT_MAX _PDCLIB_INT_MAX
#define INT_MIN ( -_PDCLIB_INT_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define UINT_MAX ( ( _PDCLIB_INT_MAX * 2u ) + 1 )

#define LONG_MAX _PDCLIB_LONG_MAX
#define LONG_MIN ( -_PDCLIB_LONG_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define ULONG_MAX ( ( _PDCLIB_LONG_MAX * 2ul ) + 1 )

#define LLONG_MAX _PDCLIB_LLONG_MAX
#define LLONG_MIN ( -_PDCLIB_LLONG_MAX - _PDCLIB_SIGNED_ENCODING / 2 )
#define ULLONG_MAX ( ( _PDCLIB_LLONG_MAX * 2ull ) + 1 )

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_LIMITS_H
#include _PDCLIB_EXTEND_LIMITS_H
#endif

#endif
