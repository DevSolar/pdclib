// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Type-generic math
// ----------------------------------------------------------------------------

#ifndef __TGMATH_H
#define __TGMATH_H __TGMATH_H

// These functions return the sine of their parameter.
double               sin(double               value);
float                sin(float                value);
long double          sin(long double          value);
double _Complex      sin(double _Complex      value);
float _Complex       sin(float _Complex       value);
long double _Complex sin(long double _Complex value);

// These functions return the hyperbolic sine of their parameter.
double               sinh(double               value);
float                sinh(float                value);
long double          sinh(long double          value);
double _Complex      sinh(double _Complex      value);
float _Complex       sinh(float _Complex       value);
long double _Complex sinh(long double _Complex value);

// These functions return the arcsine of their parameter.
double               asin(double               value);
float                asin(float                value);
long double          asin(long double          value);
double _Complex      asin(double _Complex      value);
float _Complex       asin(float _Complex       value);
long double _Complex asin(long double _Complex value);

// These functions return the hyperbolic arcsine of their parameter.
double               asinh(double               value);
float                asinh(float                value);
long double          asinh(long double          value);
double _Complex      asinh(double _Complex      value);
float _Complex       asinh(float _Complex       value);
long double _Complex asinh(long double _Complex value);

// These functions return the cosine of their parameter.
double               cos(double               value);
float                cos(float                value);
long double          cos(long double          value);
double _Complex      cos(double _Complex      value);
float _Complex       cos(float _Complex       value);
long double _Complex cos(long double _Complex value);

// These functions return the hyperbolic cosine of their parameter.
double               cosh(double               value);
float                cosh(float                value);
long double          cosh(long double          value);
double _Complex      cosh(double _Complex      value);
float _Complex       cosh(float _Complex       value);
long double _Complex cosh(long double _Complex value);

// These functions return the arccosine of their parameter.
double               acos(double               value);
float                acos(float                value);
long double          acos(long double          value);
double _Complex      acos(double _Complex      value);
float _Complex       acos(float _Complex       value);
long double _Complex acos(long double _Complex value);

// These functions return the hyperbolic arccosine of their parameter.
double               acosh(double               value);
float                acosh(float                value);
long double          acosh(long double          value);
double _Complex      acosh(double _Complex      value);
float _Complex       acosh(float _Complex       value);
long double _Complex acosh(long double _Complex value);

// These functions return the tangent of their parameter.
double               tan(double               value);
float                tan(float                value);
long double          tan(long double          value);
double _Complex      tan(double _Complex      value);
float _Complex       tan(float _Complex       value);
long double _Complex tan(long double _Complex value);

// These functions return the hyperbolic tangent of their parameter.
double               tanh(double               value);
float                tanh(float                value);
long double          tanh(long double          value);
double _Complex      tanh(double _Complex      value);
float _Complex       tanh(float _Complex       value);
long double _Complex tanh(long double _Complex value);

// These functions return the arctangent of their parameter.
double               atan(double               value);
float                atan(float                value);
long double          atan(long double          value);
double _Complex      atan(double _Complex      value);
float _Complex       atan(float _Complex       value);
long double _Complex atan(long double _Complex value);

// These functions return the hyperbolic arctangent of their parameter.
double               atanh(double               value);
float                atanh(float                value);
long double          atanh(long double          value);
double _Complex      atanh(double _Complex      value);
float _Complex       atanh(float _Complex       value);
long double _Complex atanh(long double _Complex value);

// These functions return the angle whose tangent is x / y.
double      atan2(double      x, double      y);
float       atan2(float       x, float       y);
long double atan2(long double x, long double y);

// These functions return the phase angle of their parameter.
double      carg(double _Complex      value);
float       carg(float _Complex       value);
long double carg(long double _Complex value);

// These functions return the largest integer no larger than their parameter.
double      floor(double      value);
float       floor(float       value);
long double floor(long double value);

// These functions return the smallest integer not less than their parameter.
double      ceil(double      value);
float       ceil(float       value);
long double ceil(long double value);

// These functions return the square root of their parameter.
double               sqrt(double               value);
float                sqrt(float                value);
long double          sqrt(long double          value);
double _Complex      sqrt(double _Complex      value);
float _Complex       sqrt(float _Complex       value);
long double _Complex sqrt(long double _Complex value);

// These functions return the cube root of their parameter.
double      cbrt(double      value);
float       cbrt(float       value);
long double cbrt(long double value);

// These functions return the imaginary part of their parameter.
double      cimag(double _Complex      value);
float       cimag(float _Complex       value);
long double cimag(long double _Complex value);

// These functions return the real value of their parameter.
double      creal(double _Complex      value);
float       creal(float _Complex       value);
long double creal(long double _Complex value);

// These functions return the conjugate of their parameter.
double _Complex      conj(double _Complex      value);
float _Complex       conj(float _Complex       value);
long double _Complex conj(long double _Complex value);

// These functions return their parameter x with the sign of y.
double      copysign(double      x, double      y);
float       copysign(float       x, float       y);
long double copysign(long double x, long double y);

// These functions return the projection of their parameter.
double _Complex      cproj(double _Complex      value);
float _Complex       cproj(float _Complex       value);
long double _Complex cproj(long double _Complex value);

// These functions return the error function of their parameter.
double      erf(double      value);
float       erf(float       value);
long double erf(long double value);

// These functions return the complementary error function of their parameter.
double      erfc(double      value);
float       erfc(float       value);
long double erfc(long double value);

// These functions return the exponential of their parameter (e^x).
double               exp(double               value);
float                exp(float                value);
long double          exp(long double          value);
double _Complex      exp(double _Complex      value);
float _Complex       exp(float _Complex       value);
long double _Complex exp(long double _Complex value);

// These functions return 2 raised to the power of their parameter (2^x).
double      exp2(double      value);
float       exp2(float       value);
long double exp2(long double value);

// These functions return exp(value) - 1.
double      expm1(double      value);
float       expm1(float       value);
long double expm1(long double value);

// These functions return the magnitude of their parameter.
double      fabs(double               value);
float       fabs(float                value);
long double fabs(long double          value);
double      fabs(double _Complex      value);
float       fabs(float _Complex       value);
long double fabs(long double _Complex value);

// These functions return the larger of (x-y) and zero.
double      fdim(double      x, double      y);
float       fdim(float       x, float       y);
long double fdim(long double x, long double y);

// These functions return (x * y + z) to arbitrary intermediate precision.
double      fma(double      x, double      y, double      z);
float       fma(float       x, float       y, float       z);
long double fma(long double x, long double y, long double z);

// These functions return the larger of their parameters.
double      fmax(double      x, double      y);
float       fmax(float       x, float       y);
long double fmax(long double x, long double y);

// These functions return the smaller of their parameters.
double      fmin(double      x, double      y);
float       fmin(float       x, float       y);
long double fmin(long double x, long double y);

// These functions return the remainder of (x/y).
double      fmod(double      x, double      y);
float       fmod(float       x, float       y);
long double fmod(long double x, long double y);

// These functions return a fraction (as return value) and an integer
// exponent (in the parameter 'exponent') that represent value, with the
// fraction being in the interval [0.5, 1) or being zero. If value is zero,
// exponent will also be zero.
// (fraction * 2^exponent) == value)
double      frexp(double      value, int * exponent);
float       frexp(float       value, int * exponent);
long double frexp(long double value, int * exponent);

// These functions return x raised to the power of y.
double               pow(double               x, double               y);
float                pow(float                x, float                y);
long double          pow(long double          x, long double          y);
double _Complex      pow(double _Complex      x, double _Complex      y);
float _Complex       pow(float _Complex       x, float _Complex       y);
long double _Complex pow(long double _Complex x, long double _Complex y);

// TODO: Check spelling of hypothenuse and cathedes.
// These functions determine the length of the hypothenuse for the cathedes
// x and y. (Square root of a^2 + b^2.)
double      hypot(double      a, double      b);
float       hypot(float       a, float       b);
long double hypot(long double a, long double b);

// These functions return (int) logb(value).
int ilogb(double      value);
int ilogb(float       value);
int ilogb(long double value);

// These functions return (value * 2^exponent).
double      ldexp(double      value, int exponent);
float       ldexp(float       value, int exponent);
long double ldexp(long double value, int exponent);

// These functions return the natural logarithm of their parameter.
double               log(double               value);
float                log(float                value);
long double          log(long double          value);
double _Complex      log(double _Complex      value);
float _Complex       log(float _Complex       value);
long double _Complex log(long double _Complex value);

// These functions return the logarithm (base 10) of their parameter.
double      log10(double      value);
float       log10(float       value);
long double log10(long double value);

// These functions return the natural logarithm of (their parameter + 1).
double      log1p(double      value);
float       log1p(float       value);
long double log1p(long double value);

// These functions return the logarithm (base 2) of their parameter.
double      log2(double      value);
float       log2(float       value);
long double log2(long double value);

// TODO: What do these functions actually do?
double      logb(double      value);
float       logb(float       value);
long double logb(long double value);

// These functions return their parameter rounded to the next integer, using
// the current rounding mode.
long long   llrint(double      value);
long long   llrint(float       value);
long long   llrint(long double value);
long        lrint(double       value);
long        lrint(float        value);
long        lrint(long double  value);
double      rint(double        value);
float       rint(float         value);
long double rint(long double   value);

// These functions return their parameter rounded to the next integer, with
// halfway values rounded away from zero regardless of current rounding mode.
long long   llround(double      value);
long long   llround(float       value);
long long   llround(long double value);
long        lround(double       value);
long        lround(float        value);
long        lround(long double  value);
// TODO: Do the round() functions really return FP values?
double      round(double        value);
float       round(float         value);
long double round(long double   value);

// These functions return their parameter, rounded toward zero.
// TODO: Do these functions really return FP values?
double      trunc(double      value);
float       trunc(float       value);
long double trunc(long double value);

// These functions store the integer part of value in integer, and return the
// remaining part of value.
double      modf(double      value, double *      integer);
float       modf(float       value, float *       integer);
long double modf(long double value, long double * integer);

// These functions return their parameter rounded to the next integer, using
// the current rounding mode but without raising an inexact FP exception.
double      nearbyint(double      value);
float       nearbyint(float       value);
long double nearbyint(long double value);

// These functions return the next representable value after the smaller of
// their parameters.
// TODO: This might be a wrong description.
double      nextafter(double      x, double      y);
float       nextafter(float       x, float       y);
long double nextafter(long double x, long double y);

// These functions return the next representable value after the smaller of
// their parameters.
// TODO: This might be a wrong description.
double      nexttoward(double      x, long double y);
float       nexttoward(float       x, long double y);
long double nexttoward(long double x, long double y);

// TODO
double      remainder(double      x, double      y);
float       remainder(float       x, float       y);
long double remainder(long double x, long double y);

// TODO
double      remquo(double      x, double      y, int * pquo);
float       remquo(float       x, float       y, int * pquo);
long double remquo(long double x, long double y, int * pquo);

// TODO
double      scalbln(double      x, long ex);
float       scalbln(float       x, long ex);
long double scalbln(long double x, long ex);

// TODO
double      scalbn(double      x, int ex);
float       scalbn(float       x, int ex);
long double scalbn(long double x, int ex);

// These functions return the gamma function of their parameter.
double      tgamma(double      value);
float       tgamma(float       value);
long double tgamma(long double value);

// These functions return log( fabs( tgamma(value) ) ).
double      lgamma(double      value);
float       lgamma(float       value);
long double lgamma(long double value);

#endif // __TGMATH_H
