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

typedef float float_t;
typedef double double_t;

#define HUGE_VALF _PDCLIB_HUGE_VALF;
#define HUGE_VAL _PDCLIB_HUGE_VAL;
#define HUGE_VALL _PDCLIB_HUGE_VALL;

#define INFINITY (_PDCLIB_FLT_MAX * 2)
#define NAN ( -(0.0f / 0.0f) )

#define FP_FAST_FMAF
#define FP_FAST_FMA
#define FP_FAST_FMAL

#define FP_ILOGB0 INT_MIN
#define FP_ILOGBNAN INT_MAX

#define MATH_ERRNO 1
#define MATH_ERREXCEPT 2

#define math_errhandling

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

/* Trigonometric functions */

/* The principal value of the arc cosine of x.
   Domain error for arguments not in the interval -1..+1.
   Returns the interval 0..Pi radians.
*/
double acos( double x );
float acosf( float x );
long double acosl( long double x );

/* The principal value of the arc sine of x.
   Domain error for arguments not in the interval -1..+1.
   Returns the interval -Pi/2..Pi/2 radians.
*/
double asin( double x );
float asinf( float x );
long double asinl( long double x );

/* The principal value of the arc tangent of x.
   Returns the interval -Pi/2..Pi/2 radians.
*/
double atan( double x );
float atanf( float x );
long double atanl( long double x );

/* The value of the arc tangent of y/x, using the signs of both
   arguments to determine the quadrant of the return value.
   Domain error if both arguments are zero.
   Returns the interval -Pi..Pi radians.
*/
double atan2( double y, double x );
float atan2f( float y, float x );
long double atan2l( long double y, long double x );

/* Cosine of x in radians. */
double cos( double x );
float cosf( float x );
long double cosl( long double x );

/* Sine of x in radians. */
double sin( double x );
float sinf( float x );
long double sinl( long double x );

/* Tangent of x in radians. */
double tan( double x );
float tanf( float x );
long double tanl( long double x );

/* Hyperbolic functions */

/* The (nonnegative) arc hyberbolic cosine of x.
   Domain error for arguments less than 1.
   Returns the interval 0..INF.
*/
double acosh( double x );
float acoshf( float x );
long double acoshl( long double x );

/* The arc hyberbolic sine of x.
*/
double asinh( double x );
float asinhf( float x );
long double asinhl( long double x );

/* The arc hyberbolic tangent of x.
   Domain error for arguments not in -1..1.
   Range error if -1 or +1.
*/
double atanh( double x );
float atanhf( float x );
long double atanhl( long double x );

/* The hyberbolic cosine of x.
   Range error if magnitude of x is too large.
*/
double cosh( double x );
float coshf( float x );
long double coshl( long double x );

/* The hyberbolic sine of x.
   Range error if magnitude of x is too large.
*/
double sinh( double x );
float sinhf( float x );
long double sinhl( long double x );

/* The hyberbolic tangent of x.
   Range error if magnitude of x is too large.
*/
double tanh( double x );
float tanhf( float x );
long double tanhl( long double x );

/* Exponential and logarithmic functions */

/* The base-e exponential of x.
   Range error if magnitude of x is too large.
*/
double exp( double x );
float expf( float x );
long double expl( long double x );

/* The base-2 exponential of x.
   Range error if magnitude of x is too large.
*/
double exp2( double x );
float exp2f( float x );
long double exp2l( long double x );

/* The base-e exponential of x, minus 1.
   Range error if magnitude of x is too large.
   Returns e^x - 1.
*/
double expm1( double x );
float expm1f( float x );
long double expm1l( long double x );

/* Breaks a floating-point number into a normalized fraction
   and an integral power of 2 (stored in the object pointed
   to by exp).
*/
double frexp( double value, int * exp );
float frexpf( float value, int * exp );
long double frexpl( long double value, int * exp );

/* Extract the exponent of x as a signed int.
 * Returns FP_ILOGB0 if x is zero, INT_MAX if x is infinite,
 * FP_ILOGBNAN if x is a NaN. Range error may occur if x is 0.
*/
double ilogb( double x );
float ilogbf( float x );
long double ilogbl( long double x );

/* Multiply x by 2^exp. Range error may occur. */
double ldexp( double x, int exp );
float ldexpf( float x, int exp );
long double ldexpl( long double x, int exp );

/* Compute the base-e logarithm of x.
   Domain error if argument is negative.
   Range error if argument is zero.
*/
double log( double x );
float logf( float x );
long double logl( long double x );

/* Compute the base-10 logarithm of x.
   Domain error if argument is negative.
   Range error if argument is zero.
*/
double log10( double x );
float log10f( float x );
long double log10l( long double x );

/* Compute the base-e logarithm of 1 plus x.
   Domain error if argument is less than -1.
   Range error if argument is -1.
*/
double log1p( double x );
float log1pf( float x );
long double log1pl( long double x );

/* Compute the base-2 logarithm of x.
   Domain error if argument is negative.
   Range error if argument is zero.
*/
double log2( double x );
float log2f( float x );
long double log2l( long double x );

/* Extract exponent of x, as signed integer in floating-point format.
   Subnormal is treated as though normalized.
   Domain error if argument is zero.
*/
double logb( double x );
float logbf( float x );
long double logbl( long double x );

/* Breaks value into integral and fractional parts, each having
   the same type and sign as the argument. The integral part is
   stored in the object pointed to by iptr.
*/
double modf( double value, double * exp );
float modff( float value, float * exp );
long double modfl( long double value, long double * exp );

/* Compute x * FLT_RADIX^n efficiently. Range error may occur. */
double scalbn( double x, int n );
float scalbnf( float x, int n );
long double scalbnl( long double x, int n );

double scalbln( double x, long int * n );
float scalblnf( float x, long int * n );
long double scalblnl( long double x, long int * n );

/* Power and absolute-value functions */

/* Returns x^1/3. */
double cbrt( double x );
float cbrtf( float x );
long double cbrtl( long double x );

/* Returns absolute value of x. */
double fabs( double x );
float fabsf( float x );
long double fabsl( long double x );

/* Returns square root of the sum of squares of x and y.
   Range error may occur.
*/
double hypot( double x, double y );
float hypotf( float x, float y );
long double hypotl( long double x, long double y );

/* Returns x^y.
   Domain error if x is finite and negative and y is finite and not
   an integer value.
   Domain error if x is zero and y is less or equal zero.
   Range error may occur.
*/
double pow( double x, double y );
float powf( float x, float y );
long double powl( long double x, long double y );

/* Returns x^1/2. */
double sqrt( double x );
float sqrtf( float x );
long double sqrtl( long double x );

/* Error and gamma functions */

/* Compute the error function of x. */
double erf( double x );
float erff( float x );
long double erfl( long double x );

/* Compute the complementary error function of x.
   Range error if x is too large.
*/
double erfc( double x );
float erfcf( float x );
long double erfcl( long double x );

/* Compute the natural logarithm of the absolute value of gamma(x).
   Range error if x is too lange, x is negative, or zero.
*/
double lgamma( double x );
float lgammaf( float x );
long double lgammal( long double x );

/* Compute the gamma function of x.
   Range error if x is negative, or zero, too large or too small.
*/
double tgamma( double x );
float tgammaf( float x );
long double tgammal( long double x );

/* Nearest integer functions */

/* The smallest integer no less than x. */
double ceil( double x );
float ceilf( float x );
long double ceill( long double x );

/* The largest integer no greater than x. */
double floor( double x );
float floorf( float x );
long double floorl( long double x );

/* Round in current rounding direction. No "inexact" exception. */
double nearbyint( double x );
float nearbyintf( float x );
long double nearbyintl( long double x );

/* Round in current rounding direction. Raises "inexact" exception. */
double rint( double x );
float rintf( float x );
long double rintl( long double x );

/* Round in current rounding direction.
   Range error if magnitude is too large.
*/
long int lrint( double x );
long int lrintf( float x );
long int lrintl( long double x );
long long int llrint( double x );
long long int llrintf( float x );
long long int llrintl( long double x );

/* Round to nearest, breaking ties away from zero. */
double round( double x );
float roundf( float x );
long double roundl( long double x );

/* Round to nearest, breaking ties away from zero.
   Range error if magnitude is too large.
*/
long int lround( double x );
long int lroundf( float x );
long int lroundl( long double x );
long long int llround( double x );
long long int llroundf( float x );
long long int llroundl( long double x );

/* Round toward zero. */
double trunc( double x );
float truncf( float x );
long double truncl( long double x );

/* Remainder functions */

/* Compute the remainder of x / y. */
double fmod( double x, double y );
float fmodf( float x, float y );
long double fmodl( long double x, long double y );

/* Compute the remainder of x REM y. */
double remainder( double x, double y );
float remainderf( float x, float y );
long double remainderl( long double x, long double y );

/* Compute the remainder of x REM y. In quo store a value with
   the sign of the quotient and magnitude congruent mod 2^n to
   the magnitude of the integral quotient of x / y, with n
   an implementation-defined integer greater than or equal to 3.
*/
double rmquo( double x, double y );
float rmquof( float x, float y );
long double rmquol( long double x, long double y );

/* Manipulation functions */

/* Returns a value with magnitude of x and sign of y. */
double copysign( double x, double y );
float copysignf( float x, float y );
long double copysignl( long double x, long double y );

/* Returns a NaN value with the given n-char sequence. */
double nan( const char * tagp );
float nanf( const char * tagp );
long double nanl( const char * tagp );

/* Determine the next representable value after x in direction y.
   Range error if result is not representable.
*/
double nextafter( double x, double y );
float nextafterf( float x, float y );
long double nextafterl( long double x, long double y );

/* As nextafter but with long double as second parameter. */
double nexttoward( double x, double y );
float nexttowardf( float x, float y );
long double nexttowardl( long double x, long double y );

/* Maximum, minimum, and positive difference functions */

/* Positive difference. */
double fdim( double x, double y );
float fdimf( float x, float y );
long double fdiml( long double x, long double y );

/* Maximum. */
double fmax( double x, double y );
float fmaxf( float x, float y );
long double fmaxl( long double x, long double y );

/* Minimum. */
double fmin( double x, double y );
float fminf( float x, float y );
long double fminl( long double x, long double y );

/* Multiply-add. */
double fma( double x, double y, double z );
float fmaf( float x, float y, float z );
long double fmal( long double x, long double y, long double z );

/* Comparison macros (without "invalid" FP exception) */

#define isgreater( x, y )

#define isgreaterequal( x, y )

#define isless( x, y )

#define islessequal( x, y )

#define islessgreater( x, y )

#define isunordered( x, y )

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
