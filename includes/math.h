// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Provides floating point math functions.
// ----------------------------------------------------------------------------

#ifndef __MATH_H
#define __MATH_H __MATH_H

// ----------------------------------------------------------------------------
// DEFINES

#define HUGE_VAL  // TODO
#define HUGE_VALF // TODO
#define HUGE_VALL // TODO

#define INFINITY // TODO
#define NAN      // TODO

#define FP_FAST_FMA  // TODO
#define FP_FAST_FMAF // TODO
#define FP_FAST_FMAL // TODO

#define FP_INFINITE  // TODO
#define FP_NAN       // TODO
#define FP_NORMAL    // TODO
#define FP_SUBNORMAL // TODO
#define FP_ZERO      // TODO

#define FP_ILOGB0   // TODO
#define FP_ILOGBNAN // TODO

#define MATH_ERRNO       1
#define MATH_ERREXCEPT   2
#define math_errhandling // TODO

// --------------------------------------------------------------------------
// TYPEDEFS

typedef f-type double_t; // TODO
typedef f-type float_t;  // TODO

// --------------------------------------------------------------------------
// MACROS

#ifndef __cplusplus

#define signbit(x)           // TODO
#define fpclassify(x)        // TODO
#define isfinite(x)          // TODO
#define isinf(x)             // TODO
#define isnan(x)             // TODO
#define isnormal(x)          // TODO

#define isgreater(x, y)      // TODO
#define isgreaterequal(x, y) // TODO
#define isless(x, y)         // TODO
#define islessequal(x, y)    // TODO
#define islessgreater(x, y)  // TODO
#define isunordered(x, y)    // TODO

#else // __cplusplus

// The same functionality as above is implemented as functions in C++.
bool signbit( float x );
bool signbit( double x );
bool signbit( long double x );
int fpclassify( float x );
int fpclassify( double x );
int fpclassify( long double x );
bool isfinite( float x );
bool isfinite( double x );
bool isfinite( long double x );
bool isinf( float x );
bool isinf( double x );
bool isinf( long double x );
bool isnan( float x );
bool isnan( double x );
bool isnan( long double x );
bool isnormal( float x );
bool isnormal( double x );
bool isnormal( long double x );
bool isgreater( float x, float y );
bool isgreater( double x, double y );
bool isgreater( long double x, long double y );
bool isgreaterequal( float x, float y );
bool isgreaterequal( double x, double y );
bool isgreaterequal( long double x, long double y );
bool isless( float x, float y );
bool isless( double x, double y );
bool isless( long double x, long double y );
bool islessequal( float x, float y );
bool islessequal( double x, double y );
bool islessequal( long double x, long double y );
bool islessgreater( float x, float y );
bool islessgreater( double x, double y );
bool islessgreater( long double x, long double y );
bool isunordered( float x, float y );
bool isunordered( double x, double y );
bool isunordered( long double x, long double y );

#endif // __cplusplus

// --------------------------------------------------------------------------
// FUNCTIONS - C++

// These functions return the magnitude of their parameter.
double      abs(double      x);
float       abs(float       x);
long double abs(long double x);
float       fabs(float       x);
long double fabs(long double x);

// These functions return the sine of their parameter.
float       sin(float       x);
long double sin(long double x);

// These functions return the hyperbolic sine of their parameter.
float       sinh(float       x);
long double sinh(long double x);

// These functions return the arcsine of their parameter.
float       asin(float       x);
long double asin(long double x);

// These functions return the hyperbolic arcsine of their parameter.
float       asinh(float       x);
long double asinh(long double x);

// These functions return the cosine of their parameter.
float       cos(float       x);
long double cos(long double x);

// These functions return the hyperbolic cosine of their parameter.
float       cosh(float       x);
long double cosh(long double x);

// These functions return the arccosine of their parameter.
float       acos(float       x);
long double acos(long double x);

// These functions return the hyperbolic arccosine of their parameter.
float       acosh(float       x);
long double acosh(long double x);

// These functions return the tangent of their parameter.
float       tan(float       x);
long double tan(long double x);

// These functions return the hyperbolic tangent of their parameter.
float       tanh(float       x);
long double tanh(long double x);

// These functions return the arctangent of their parameter.
float       atan(float       x);
long double atan(long double x);

// These functions return the hyperbolic arctangent of their parameter.
float       atanh(float       x);
long double atanh(long double x);

// TODO
float       atan2(float       y, float       x);
long double atan2(long double y, long double x);

// These functions return sqrt(x^2 + y^2).
float       hypot(float       x, float       y);
long double hypot(long double x, long double y);

// These functions return their parameter x, raised to the power y.
float       pow(float       x, float       y);
long double pow(long double x, long double y);
double      pow(double      x, int         y);
float       pow(float       x, int         y);
long double pow(long double x, int         y);

// These functions return the square root of their parameter.
float       sqrt(float       x);
long double sqrt(long double x);

// TODO
float       cbrt(float       x);
long double cbrt(long double x);

// TODO
float       exp(float       x);
long double exp(long double x);

// TODO
float       exp2(float       x);
long double exp2(long double x);

// TODO
float       expm1(float       x);
long double expm1(long double x);

// TODO
float       frexp(float       x, int * exponent);
long double frexp(long double x, int * exponent);

// TODO
float       ldexp(float       x, int exponent);
long double ldexp(long double x, int exponent);

// These functions return the natural logarithm of their parameter.
float       log(float       x);
long double log(long double x);

// These functions return the logarithm (base 10) of their parameter.
float       log10(float       x);
long double log10(long double x);

// These functions return the logarithm (base 2) of their parameter.
float       log2(float       x);
long double log2(long double x);

// TODO
float       logb(float       x);
long double logb(long double x);

// TODO
int ilogb(float       x);
int ilogb(long double x);

// TODO
float       log1p(float       x);
long double log1p(long double x);

// These functions return the smallest integer no larger than their parameter
float       ceil(float       x);
long double ceil(long double x);

// These functions return the biggest integer no larger than their parameter.
float       floor(float       x);
long double floor(long double x);

// TODO
float       fmod(float       x, float       y);
long double fmod(long double x, long double y);

// TODO
float       modf(float       x, float *       integer);
long double modf(long double x, long double * integer);

// These functions return their parameter x, with the sign of parameter y.
float       copysign(float       x, float       y);
long double copysign(long double x, long double y);

// TODO
float       erf(float       x);
long double erf(long double x);

// TODO
float       erfc(float       x);
long double erfc(long double x);

// TODO
float       fdim(float       x, float       y);
long double fdim(long double x, long double y);

// TODO
float       fma(float       x, float       y, float       z);
long double fma(long double x, long double y, long double z);

// These functions return the larger of their parameters.
float       fmax(float       x, float       y);
long double fmax(long double x, long double y);

// These functions return the smaller of their parameters.
float       fmin(float       x, float       y);
long double fmin(long double x, long double y);

// TODO
long long llrint(float x);
long long llrint(long double x);
long lrint(float       x);
long lrint(long double x);
float       rint(float       x);
long double rint(long double x);

// TODO
long long llround(float       x);
long long llround(long double x);
long lround(float       x);
long lround(long double x);
float       round(float       x);
long double round(long double x);

// TODO
float       trunc(float       x);
long double trunc(long double x);

// TODO
float       nearbyint(float       x);
long double nearbyint(long double x);

// TODO
float       nextafter(float       x, float       y);
long double nextafter(long double x, long double y);

// TODO
float       nexttoward(float       x, long double y);
long double nexttoward(long double x, long double y);

// TODO
float       remainder(float       x, float       y);
long double remainder(long double x, long double y);

// TODO
float       remquo(float       x, float       y, int * quotient);
long double remquo(long double x, long double y, int * quotient);

// TODO
float       scalbn(float       x, int ex);
long double scalbn(long double x, int ex);

// TODO
float       scalbln(float       x, long ex);
long double scalbln(long double x, long ex);

// TODO
float       lgamma(float       x);
long double lgamma(long double x);

// TODO
float       tgamma(float       x);
long double tgamma(long double x);

// ----------------------------------------------------------------------------
// FUNCTIONS - Standard C

// These functions return the magnitude of its parameter.
double      fabs(double       x);
float       fabsf(float       x);
long double fabsl(long double x);

// These functions return the sine of its parameter.
double      sin(double       x);
float       sinf(float       x);
long double sinl(long double x);

// These functions return the hyperbolic cosine of its parameter.
double      sinh(double       x);
float       sinhf(float       x);
long double sinhl(long double x);

// These functions return the arcsine of its parameter.
double      asin(double       x);
float       asinf(float       x);
long double asinl(long double x);

// These functions return the hyperbolic arcsine of their parameter.
double      asinh(double       x);
float       asinhf(float       x);
long double asinhl(long double x);

// These functions return the cosine of its parameter.
double      cos(double       x);
float       cosf(float       x);
long double cosl(long double x);

// These functions return the hyperbolic cosine of its parameter.
double      cosh(double       x);
float       coshf(float       x);
long double coshl(long double x);

// These functions return the arccosine of its parameter.
double      acos(double       x);
float       acosf(float       x);
long double acosl(long double x);

// These functions return the hyperbolic arccosine of their parameter.
double      acosh(double       x);
float       acoshf(float       x);
long double acoshl(long double x);

// These functions return the tangent of its parameter.
double      tan(double       x);
float       tanf(float       x);
long double tanl(long double x);

// These functions return the hyperbolic tangent of its parameter.
double      tanh(double       x);
float       tanhf(float       x);
long double tanhl(long double x);

// These functions return the arctangent of its parameter.
double      atan(double       x);
float       atanf(float       x);
long double atanl(long double x);

// These functions return the hyperbolic arctangent of their parameter.
double      atanh(double       x);
float       atanhf(float       x);
long double atanhl(long double x);

// TODO
double      atan2(double       y, double      x);
float       atan2f(float       y, float       x);
long double atan2l(long double y, long double x);

// These functions return sqrt(x^2 + y^2).
double      hypot(double       x, double      y);
float       hypotf(float       x, float       y);
long double hypotl(long double x, long double y);

// These functions return its parameter x, raised to the power y.
double      pow(double       x, double      y);
float       powf(float       x, float       y);
long double powl(long double x, long double y);

// These functions return the square root of its parameter.
double      sqrt(double       x);
float       sqrtf(float       x);
long double sqrtl(long double x);

// TODO
double      cbrt(double       x);
float       cbrtf(float       x);
long double cbrtl(long double x);

// TODO
double      exp(double       x);
float       expf(float       x);
long double expl(long double x);

// TODO
double      exp2(double       x);
float       exp2f(float       x);
long double exp2l(long double x);

// TODO
double      expm1(double       x);
float       expm1f(float       x);
long double expm1l(long double x);

// TODO
double      frexp(double       x, int * exp);
float       frexpf(float       x, int * exp);
long double frexpl(long double x, int * exp);

// TODO
double      ldexp(double       x, int exp);
float       ldexpf(float       x, int exp);
long double ldexpl(long double x, int exp);

// These functions return the natural logarithm of its parameter.
double      log(double       x);
float       logf(float       x);
long double logl(long double x);

// These functions return the logarithm (base 10) of its parameter.
double      log10(double       x);
float       log10f(float       x);
long double log10l(long double x);

// These functions return the logarithm (base 2) of their parameter.
double      log2(double       x);
float       log2f(float       x);
long double log2l(long double x);

// TODO
double      logb(double       x);
float       logbf(float       x);
long double logbl(long double x);

// TODO
int ilogb(double       x);
int ilogbf(float       x);
int ilogbl(long double x);

// TODO
double      log1p(double       x);
float       log1pf(float       x);
long double log1pl(long double x);

// These functions return the smallest integer no smaller than value.
double      ceil(double       x);
float       ceilf(float       x);
long double ceill(long double x);

// These functions return the largest integer no larger than its parameter.
double      floor(double       x);
float       floorf(float       x);
long double floorl(long double x);

// TODO
double      fmod(double       x, double      y);
float       fmodf(float       x, float       y);
long double fmodl(long double x, long double y);

// TODO
double      modf(double       x, double *      integer);
float       modff(float       x, float *       integer);
long double modfl(long double x, long double * integer);

// These functions return their parameter x, with the sign of parameter y.
double      copysign(double       x, double      y);
float       copysignf(float       x, float       y);
long double copysignl(long double x, long double y);

// TODO
double      erf(double       x);
float       erff(float       x);
long double erfl(long double x);

// TODO
double      erfc(double       x);
float       erfcf(float       x);
long double erfcl(long double x);

// TODO
double      fdim(double       x, double      y);
float       fdimf(float       x, float       y);
long double fdiml(long double x, long double y);

// TODO
double      fma(double       x, double      y, double      z);
float       fmaf(float       x, float       y, float       z);
long double fmal(long double x, long double y, long double z);

// These functions return the larger of their parameters.
double      fmax(double       x, double      y);
float       fmaxf(float       x, float       y);
long double fmaxl(long double x, long double y);

// These functions return the smaller of their parameters.
double      fmin(double       x, double      y);
float       fminf(float       x, float       y);
long double fminl(long double x, long double y);

// TODO
long long llrint(double       x);
long long llrintf(float       x);
long long llrintl(long double x);
long lrint(double       x);
long lrintf(float       x);
long lrintl(long double x);
double      rint(double       x);
float       rintf(float       x);
long double rintl(long double x);

// TODO
long long llround(double       x);
long long llroundf(float       x);
long long llroundl(long double x);
long lround(double       x);
long lroundf(float       x);
long lroundl(long double x);
double      round(double       x);
float       roundf(float       x);
long double roundl(long double x);

// TODO
double      trunc(double       x);
float       truncf(float       x);
long double truncl(long double x);

double      nearbyint(double       x);
float       nearbyintf(float       x);
long double nearbyintl(long double x);

double      nextafter(double       x, double      y);
float       nextafterf(float       x, float       y);
long double nextafterl(long double x, long double y);

// TODO
double      nexttoward(double       x, long double y);
float       nexttowardf(float       x, long double y);
long double nexttowardl(long double x, long double y);

// TODO
double      remainder(double       x, double      y);
float       remainderf(float       x, float       y);
long double remainderl(long double x, long double y);

// TODO
double      remquo(double       x, double      y, int * pquo);
float       remquof(float       x, float       y, int * pquo);
long double remquol(long double x, long double y, int * pquo);

// TODO
double      scalbn(double       x, int ex);
float       scalbnf(float       x, int ex);
long double scalbnl(long double x, int ex);

// TODO
double      scalbln(double       x, long ex);
float       scalblnf(float       x, long ex);
long double scalblnl(long double x, long ex);

// TODO
double      lgamma(double       x);
float       lgammaf(float       x);
long double lgammal(long double x);

// TODO
double      tgamma(double       x);
float       tgammaf(float       x);
long double tgammal(long double x);

// TODO
double      nan(const char  *str);
float       nanf(const char *str);
long double nanl(const char *str);

#endif // __MATH_H
