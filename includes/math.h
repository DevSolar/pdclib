// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Mathematics
// ----------------------------------------------------------------------------

#ifndef __MATH_H
#define __MATH_H __MATH_H

// TODO: Documentation

// ----------------------------------------------------------------------------
// DEFINES

#define HUGE_VAL  // TODO - personality?
#define HUGE_VALF // TODO - personality?
#define HUGE_VALL // TODO - personality?

#define INFINITY // TODO - personality?
#define NAN      // TODO - personality?

#define FP_FAST_FMA  // TODO - personality?
#define FP_FAST_FMAF // TODO - personality?
#define FP_FAST_FMAL // TODO - personality?

#define FP_INFINITE  // TODO - personality?
#define FP_NAN       // TODO - personality?
#define FP_NORMAL    // TODO - personality?
#define FP_SUBNORMAL // TODO - personality?
#define FP_ZERO      // TODO - personality?

#define FP_ILOGB0   // TODO - personality?
#define FP_ILOGBNAN // TODO - personality?

#define MATH_ERRNO       1 // personality?
#define MATH_ERREXCEPT   2 // personality?
#define math_errhandling // TODO - personality?

// --------------------------------------------------------------------------
// TYPEDEFS

typedef double_t; // TODO - personality?
typedef float_t;  // TODO - personality?

// --------------------------------------------------------------------------
// MACROS

#define isgreater( x, y )      // TODO
#define isgreaterequal( x, y ) // TODO
#define isless( x, y )         // TODO
#define islessequal( x, y )    // TODO
#define islessgreater( x, y )  // TODO
#define isunordered( x, y )    // TODO
#define fpclassify( x )        // TODO
#define isfinite( x )          // TODO

#define isinf( x )             // TODO
#define isnan( x )             // TODO
#define isnormal( x )          // TODO
#define signbit( x )           // TODO

// ----------------------------------------------------------------------------
// FUNCTIONS

// These functions return the magnitude of their parameter.
double      fabs( double       x );
float       fabsf( float       x );
long double fabsl( long double x );

// These functions compute the sine of x (measured in radians).
double      sin( double       x );
float       sinf( float       x );
long double sinl( long double x );

// These functions return the hyperbolic cosine of their parameter.
double      sinh( double       x );
float       sinhf( float       x );
long double sinhl( long double x );

// These functions return the arcsine of their parameter.
double      asin( double       x );
float       asinf( float       x );
long double asinl( long double x );

// These functions return the hyperbolic arcsine of their parameter.
double      asinh( double       x );
float       asinhf( float       x );
long double asinhl( long double x );

// These functions compute the cosine of x (measured in radians).
double      cos( double       x );
float       cosf( float       x );
long double cosl( long double x );

// These functions return the hyperbolic cosine of their parameter.
double      cosh( double       x );
float       coshf( float       x );
long double coshl( long double x );

// These functions return the arccosine of their parameter.
double      acos( double       x );
float       acosf( float       x );
long double acosl( long double x );

// These functions return the hyperbolic arccosine of their parameter.
double      acosh( double       x );
float       acoshf( float       x );
long double acoshl( long double x );

// These functions return the tangent of x.
double      tan( double       x );
float       tanf( float       x );
long double tanl( long double x );

// These functions return the hyperbolic tangent of their parameter.
double      tanh( double       x );
float       tanhf( float       x );
long double tanhl( long double x );

// These functions compute the arctangent of x.
double      atan( double       x );
float       atanf( float       x );
long double atanl( long double x );

// These functions return the hyperbolic arctangent of their parameter.
double      atanh( double       x );
float       atanhf( float       x );
long double atanhl( long double x );

// TODO
double      atan2( double       y, double      x );
float       atan2f( float       y, float       x );
long double atan2l( long double y, long double x );

// These functions return sqrt(x^2 + y^2 ).
double      hypot( double       x, double      y );
float       hypotf( float       x, float       y );
long double hypotl( long double x, long double y );

// These functions return their parameter x, raised to the power y.
double      pow( double       x, double      y );
float       powf( float       x, float       y );
long double powl( long double x, long double y );

// These functions return the square root of their parameter.
double      sqrt( double       x );
float       sqrtf( float       x );
long double sqrtl( long double x );

// TODO
double      cbrt( double       x );
float       cbrtf( float       x );
long double cbrtl( long double x );

// TODO
double      exp( double       x );
float       expf( float       x );
long double expl( long double x );

// TODO
double      exp2( double       x );
float       exp2f( float       x );
long double exp2l( long double x );

// TODO
double      expm1( double       x );
float       expm1f( float       x );
long double expm1l( long double x );

// TODO
double      frexp( double       x, int * exp );
float       frexpf( float       x, int * exp );
long double frexpl( long double x, int * exp );

// TODO
double      ldexp( double       x, int exp );
float       ldexpf( float       x, int exp );
long double ldexpl( long double x, int exp );

// These functions return the natural logarithm of their parameter.
double      log( double       x );
float       logf( float       x );
long double logl( long double x );

// These functions return the logarithm (base 10 ) of their parameter.
double      log10( double       x );
float       log10f( float       x );
long double log10l( long double x );

// These functions return the logarithm (base 2 ) of their parameter.
double      log2( double       x );
float       log2f( float       x );
long double log2l( long double x );

// TODO
double      logb( double       x );
float       logbf( float       x );
long double logbl( long double x );

// TODO
int ilogb( double       x );
int ilogbf( float       x );
int ilogbl( long double x );

// TODO
double      log1p( double       x );
float       log1pf( float       x );
long double log1pl( long double x );

// These functions return the smallest integer no smaller than value.
double      ceil( double       x );
float       ceilf( float       x );
long double ceill( long double x );

// These functions return the largest integer no larger than their parameter.
double      floor( double       x );
float       floorf( float       x );
long double floorl( long double x );

// TODO
double      fmod( double       x, double      y );
float       fmodf( float       x, float       y );
long double fmodl( long double x, long double y );

// TODO
double      modf( double       x, double *      integer );
float       modff( float       x, float *       integer );
long double modfl( long double x, long double * integer );

// These functions return their parameter x, with the sign of parameter y.
double      copysign( double       x, double      y );
float       copysignf( float       x, float       y );
long double copysignl( long double x, long double y );

// TODO
double      erf( double       x );
float       erff( float       x );
long double erfl( long double x );

// TODO
double      erfc( double       x );
float       erfcf( float       x );
long double erfcl( long double x );

// TODO
double      fdim( double       x, double      y );
float       fdimf( float       x, float       y );
long double fdiml( long double x, long double y );

// TODO
double      fma( double       x, double      y, double      z );
float       fmaf( float       x, float       y, float       z );
long double fmal( long double x, long double y, long double z );

// These functions return the larger of their parameters.
double      fmax( double       x, double      y );
float       fmaxf( float       x, float       y );
long double fmaxl( long double x, long double y );

// These functions return the smaller of their parameters.
double      fmin( double       x, double      y );
float       fminf( float       x, float       y );
long double fminl( long double x, long double y );

// TODO
long long llrint( double       x );
long long llrintf( float       x );
long long llrintl( long double x );
long lrint( double       x );
long lrintf( float       x );
long lrintl( long double x );
double      rint( double       x );
float       rintf( float       x );
long double rintl( long double x );

// TODO
long long llround( double       x );
long long llroundf( float       x );
long long llroundl( long double x );
long lround( double       x );
long lroundf( float       x );
long lroundl( long double x );
double      round( double       x );
float       roundf( float       x );
long double roundl( long double x );

// TODO
double      trunc( double       x );
float       truncf( float       x );
long double truncl( long double x );

double      nearbyint( double       x );
float       nearbyintf( float       x );
long double nearbyintl( long double x );

double      nextafter( double       x, double      y );
float       nextafterf( float       x, float       y );
long double nextafterl( long double x, long double y );

// TODO
double      nexttoward( double       x, long double y );
float       nexttowardf( float       x, long double y );
long double nexttowardl( long double x, long double y );

// TODO
double      remainder( double       x, double      y );
float       remainderf( float       x, float       y );
long double remainderl( long double x, long double y );

// TODO
double      remquo( double       x, double      y, int * pquo );
float       remquof( float       x, float       y, int * pquo );
long double remquol( long double x, long double y, int * pquo );

// TODO
double      scalbn( double       x, int ex );
float       scalbnf( float       x, int ex );
long double scalbnl( long double x, int ex );

// TODO
double      scalbln( double       x, long ex );
float       scalblnf( float       x, long ex );
long double scalblnl( long double x, long ex );

// TODO
double      lgamma( double       x );
float       lgammaf( float       x );
long double lgammal( long double x );

// TODO
double      tgamma( double       x );
float       tgammaf( float       x );
long double tgammal( long double x );

// TODO
double      nan( const char  *str );
float       nanf( const char *str );
long double nanl( const char *str );

#endif // __MATH_H
