/* Characteristics of floating types <float.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_FLOAT_H
#define _PDCLIB_FLOAT_H _PDCLIB_FLOAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_internal.h"

/* The following parameters are used to define the model for each
   floating-point type:

     s  sign (±1)
     b  base or radix of exponent representation (an integer > 1)
     e  exponent (an integer between a minimum eₘₙ and a maximum eₘₓ)
     p  precision (the number of base-b digits in the significand)
     ƒₖ nonnegative integers less than b (the significand digits)

   A floating-point number (x) is defined by the following model:

     x = sbᵉ ₖ₌₁∑ᵖ ƒₖb⁻ᵏ, eₘₙ ≤ e ≤ eₘₓ

   In addition to normalized floating-point numbers (ƒ₁ > 0 if x ≠ 0),
   floating types may be able to contain other kinds of floating-point
   numbers, such as subnormal floating-point numbers (x ≠ 0, e = eₘₙ,
   ƒ₁ = 0) and unnormalized floating-point numbers (x ≠ 0, e > eₘₙ,
   ƒ₁ = 0), and values that are not floating-point numbers, such as
   infinities and NaNs.
*/

/* Whether rounding toward zero (0), to nearest (1), toward positive
   infinity (2), toward negative infinity (3), or indeterminate (-1).
   FLT_ROUNDS is not a compile-time constant, and may change due to
   calls to fesetround() (in <fenv.h>).
*/
#define FLT_ROUNDS _PDCLIB_FLT_ROUNDS

/* Whether operations are done in the given type (0), float is
   evaluated as double (1), float and double are evaluated as
   long double (2), or evaluation method is indeterminate (-1).
*/
#define FLT_EVAL_METHOD  _PDCLIB_FLT_EVAL_METHOD

/* Whether the type supports subnormal numbers (1), does not support
   them (0), or support is indeterminate (-1).
*/
#define FLT_HAS_SUBNORM  _PDCLIB_FLT_HAS_SUBNORM
#define DBL_HAS_SUBNORM  _PDCLIB_DBL_HAS_SUBNORM
#define LDBL_HAS_SUBNORM _PDCLIB_LDBL_HAS_SUBNORM

/* Radix of exponent representation, b */
#define FLT_RADIX        _PDCLIB_FLT_RADIX

/* Number of base-b digits in the floating point significand, p */
#define FLT_MANT_DIG     _PDCLIB_FLT_MANT_DIG
#define DBL_MANT_DIG     _PDCLIB_DBL_MANT_DIG
#define LDBL_MANT_DIG    _PDCLIB_LDBL_MANT_DIG

/* Number of decimal digits, n, so that any floating point number with
   p radix b digits can be rounded to a floating point number with n
   decimal digits and back without changing the value
        pₘₓlog₁₀b  if b is a power of 10,
   ⌈1 + pₘₓlog₁₀b⌉ otherwise.
*/
#define FLT_DECIMAL_DIG  _PDCLIB_FLT_DECIMAL_DIG
#define DBL_DECIMAL_DIG  _PDCLIB_DBL_DECIMAL_DIG
#define LDBL_DECIMAL_DIG _PDCLIB_LDBL_DECIMAL_DIG

/* As above, for the widest supported type. */
#define DECIMAL_DIG      _PDCLIB_DECIMAL_DIG

/* Number of decimal digits, q, so that any floating point number with
   q decimal digits can be rounded to a floating point number with p
   radix b digits and back without changing the value of the q decimal
   digits.
         p log₁₀b   if b is a power of 10,
   ⌊(p - 1)log₁₀b⌋  otherwise.
*/
#define FLT_DIG          _PDCLIB_FLT_DIG
#define DBL_DIG          _PDCLIB_DBL_DIG
#define LDBL_DIG         _PDCLIB_LDBL_DIG

/* Minimum negative integer such that FLT_RADIX raised to one less
   than that power is a normalized floating point number, eₘₙ
*/
#define FLT_MIN_EXP      _PDCLIB_FLT_MIN_EXP
#define DBL_MIN_EXP      _PDCLIB_DBL_MIN_EXP
#define LDBL_MIN_EXP     _PDCLIB_LDBL_MIN_EXP

/* Minimum negative integer such that 10 raised to one less than that
   power is in the range of normalized floating point numbers,
   ⌈log₁₀b^{eₘₙ⁻¹}⌉
*/
#define FLT_MIN_10_EXP   _PDCLIB_FLT_MIN_10_EXP
#define DBL_MIN_10_EXP   _PDCLIB_DBL_MIN_10_EXP
#define LDBL_MIN_10_EXP  _PDCLIB_LDBL_MIN_10_EXP

/* Maximum integer such that FLT_RADIX raised to one less than that
   power is a representable finite floating point number, eₘₓ
*/
#define FLT_MAX_EXP      _PDCLIB_FLT_MAX_EXP
#define DBL_MAX_EXP      _PDCLIB_DBL_MAX_EXP
#define LDBL_MAX_EXP     _PDCLIB_LDBL_MAX_EXP

/* Maximum integer such that 10 raised to that power is in the range
   of representable finite floating-point numbers,
   ⌊log₁₀((1-b⁻ᵖ)b^{eₘₓ})⌋
*/
#define FLT_MAX_10_EXP   _PDCLIB_FLT_MAX_10_EXP
#define DBL_MAX_10_EXP   _PDCLIB_DBL_MAX_10_EXP
#define LDBL_MAX_10_EXP  _PDCLIB_LDBL_MAX_10_EXP

/* Maximum representable finite floating-point number, (1-b⁻ᵖ)b^{eₘₓ}
*/
#define FLT_MAX          _PDCLIB_FLT_MAX
#define DBL_MAX          _PDCLIB_DBL_MAX
#define LDBL_MAX         _PDCLIB_LDBL_MAX

/* Difference between 1 and the least value greater than 1 that is
   representable in the type, b¹⁻ᵖ
*/
#define FLT_EPSILON      _PDCLIB_FLT_EPSILON
#define DBL_EPSILON      _PDCLIB_DBL_EPSILON
#define LDBL_EPSILON     _PDCLIB_LDBL_EPSILON

/* Minimum normalized positive floating-point number, b^{eₘₙ⁻¹} */
#define FLT_MIN          _PDCLIB_FLT_MIN
#define DBL_MIN          _PDCLIB_DBL_MIN
#define LDBL_MIN         _PDCLIB_LDBL_MIN

/* Minimum positive floating-point number */
#define FLT_TRUE_MIN     _PDCLIB_FLT_TRUE_MIN
#define DBL_TRUE_MIN     _PDCLIB_DBL_TRUE_MIN
#define LDBL_TRUE_MIN    _PDCLIB_LDBL_TRUE_MIN

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_FLOAT_H
#include _PDCLIB_EXTEND_FLOAT_H
#endif

#ifdef __cplusplus
}
#endif

#endif
