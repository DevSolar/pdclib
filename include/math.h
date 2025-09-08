/* Mathematics <math.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_MATH_H
#define _PDCLIB_MATH_H _PDCLIB_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_lib_ext1.h"
#include "pdclib/_PDCLIB_internal.h"

/* Classification */

/* FP_ZERO, FP_SUBNORMAL, FP_NORMAL */
#define isfinite( x ) _PDCLIB_GENERIC( isfinite, x )

/* FP_INFINITE */
#define isinf( x ) _PDCLIB_GENERIC( isinf, x )

/* FP_NAN */
#define isnan( x ) _PDCLIB_GENERIC( isnan, x )

/* FP_NORMAL */
#define isnormal( x ) _PDCLIB_GENERIC( isnormal, x )

/* Negative */
#define signbit( x ) _PDCLIB_GENERIC( signbit, x )

/* See FP_* classes */
#define fpclassify( x ) _PDCLIB_GENERIC( fpclassify, x )

#define FP_INFINITE   1
#define FP_NAN        2
#define FP_NORMAL     3
#define FP_SUBNORMAL  4
#define FP_ZERO       5

#ifdef __cplusplus
}
#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_MATH_H
#include _PDCLIB_EXTEND_MATH_H
#endif

#endif
