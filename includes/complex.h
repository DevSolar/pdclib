// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Provides the types float _Complex, double _Complex and long double _Complex
// plus math functions on those types.
// ----------------------------------------------------------------------------

#ifndef __COMPLEX_H
#define __COMPLEX_H __COMPLEX_H

// ----------------------------------------------------------------------------
// DEFINES

// TODO: #defines for complex, _Complex_I, imaginary, _Imaginary_I, and I.

// ----------------------------------------------------------------------------
// FUNCTIONS - C++

#ifdef __cplusplus

// These functions return the absolute value (magnitude) of their parameter.
double               abs( double      _Complex   x );
float                abs( float       _Complex   x );
long double          abs( long double _Complex   x );
double               fabs( double      _Complex  x );
float                fabs( float       _Complex  x );
long double          fabs( long double _Complex  x );

// These functions return the sine of their parameter.
double _Complex      sin( double _Complex        x );
float _Complex       sin( float _Complex         x );
long double _Complex sin( long double _Complex   x );

// These functions return the hyperbolic sine of their parameter.
double _Complex      sinh( double _Complex       x );
float _Complex       sinh( float _Complex        x );
long double _Complex sinh( long double _Complex  x );

// These functions return the arcsine of their parameter.
double _Complex      asin( double _Complex       x );
float _Complex       asin( float _Complex        x );
long double _Complex asin( long double _Complex  x );

// These functions return the hyperbolic arcsine of their parameter.
double _Complex      asinh( double _Complex      x );
float _Complex       asinh( float _Complex       x );
long double _Complex asinh( long double _Complex x );

// These functions return the cosine of their parameter.
double _Complex      cos( double _Complex        x );
float _Complex       cos( float _Complex         x );
long double _Complex cos( long double _Complex   x );

// These functions return the hyperbolic cosine of their parameter.
double _Complex      cosh( double _Complex       x );
float _Complex       cosh( float _Complex        x );
long double _Complex cosh( long double _Complex  x );

// These functions return the arccosine of their parameter.
double _Complex      acos( double      _Complex  x );
float _Complex       acos( float       _Complex  x );
long double _Complex acos( long double _Complex  x );

// These functions return the hyperbolic arccosine of their parameter.
double _Complex      acosh( double      _Complex x );
float _Complex       acosh( float       _Complex x );
long double _Complex acosh( long double _Complex x );

// These functions return the tangent of their parameter.
double _Complex      tan( double _Complex        x );
float _Complex       tan( float _Complex         x );
long double _Complex tan( long double _Complex   x );

// These functions return the hyperbolic tangent of their parameter.
double _Complex      tanh( double _Complex       x );
float _Complex       tanh( float _Complex        x );
long double _Complex tanh( long double _Complex  x );

// These functions return the arctangent of their parameter.
double _Complex      atan( double _Complex       x );
float _Complex       atan( float _Complex        x );
long double _Complex atan( long double _Complex  x );

// These functions return the hyperbolic arctangent of their parameter.
double _Complex      atanh( double _Complex      x );
float _Complex       atanh( float _Complex       x );
long double _Complex atanh( long double _Complex x );

// These functions return the imaginary part of their parameter.
double               imag( double _Complex       x );
float                imag( float _Complex        x );
long double          imag( long double _Complex  x );
float                cimag( float _Complex       x );
long double          cimag( long double _Complex x );

// These functions return the real part of their parameter.
double               real( double _Complex       x );
float                real( float _Complex        x );
long double          real( long double _Complex  x );
float                creal( float _Complex       x );
long double          creal( long double _Complex x );

// These functions return value^exponent.
double _Complex      pow( double _Complex        value,
                         double _Complex        exponent );
float _Complex       pow( float _Complex         value,
                         float _Complex         exponent );
long double _Complex pow( long double _Complex   value,
                         long double _Complex   exponent );

// These functions return the square root of their parameter.
double _Complex      sqrt( double _Complex       x );
float _Complex       sqrt( float _Complex        x );
long double _Complex sqrt( long double _Complex  x );

// These functions return the exponential of their parameter.
double _Complex      exp( double _Complex        x );
float _Complex       exp( float _Complex         x );
long double _Complex exp( long double _Complex   x );

// These functions return the logarithm of their parameter.
double _Complex      log( double _Complex        x );
float _Complex       log( float _Complex         x );
long double _Complex log( long double _Complex   x );

// These functions return the phase angle of their parameter.
double               arg( double _Complex        x );
float                arg( float _Complex         x );
long double          arg( long double _Complex   x );
float                carg( float _Complex        x );
long double          carg( long double _Complex  x );

// These functions return the conjugate of their parameter.
float _Complex       conj( float _Complex        x );
long double _Complex conj( long double _Complex  x );

// These functions return the projection of their parameter.
float _Complex       cproj( float _Complex       x );
long double _Complex cproj( long double _Complex x );

#endif // __cplusplus

// ----------------------------------------------------------------------------
// FUNCTIONS - Standard C

// These functions return the absolute value (magnitude) of their parameter.
double               cabs( double _Complex         x );
float                cabsf( float _Complex         x );
long double          cabsl( long double _Complex   x );

// These functions return the sine of their parameter.
double _Complex      csin( double _Complex         x );
float _Complex       csinf( float _Complex         x );
long double _Complex csinl( long double _Complex   x );

// These functions return the hyperbolic sine of their parameter.
double _Complex      csinh( double _Complex        x );
float _Complex       csinhf( float _Complex        x );
long double _Complex csinhl( long double _Complex  x );

// These functions return the arcsine of their parameter.
double _Complex      casin( double _Complex        x );
float _Complex       casinf( float _Complex        x );
long double _Complex casinl( long double _Complex  x );

// These functions return the hyperbolic arcsine of their parameter.
double _Complex      casinh( double _Complex       x );
float _Complex       casinhf( float _Complex       x );
long double _Complex casinhl( long double _Complex x );

// These functions return the cosine of their parameter.
double _Complex      ccos( double _Complex         x );
float _Complex       ccosf( float _Complex         x );
long double _Complex ccosl( long double _Complex   x );

// These functions return the hyperbolic cosine of their parameter.
double _Complex      ccosh( double _Complex        x );
float _Complex       ccoshf( float _Complex        x );
long double _Complex ccoshl( long double _Complex  x );

// These functions return the arccosine of their parameter.
double _Complex      cacos( double _Complex        x );
float _Complex       cacosf( float _Complex        x );
long double _Complex cacosl( long double _Complex  x );

// These functions return the hyperbolic arccosine of their parameter.
double _Complex      cacosh( double _Complex       x );
float _Complex       cacoshf( float _Complex       x );
long double _Complex cacoshl( long double _Complex x );

// These functions return the tangent of their parameter.
double _Complex      ctan( double _Complex         x );
float _Complex       ctanf( float _Complex         x );
long double _Complex ctanl( long double _Complex   x );

// These functions return the hyperbolic tangent of their parameter.
double _Complex      ctanh( double _Complex        x );
float _Complex       ctanhf( float _Complex        x );
long double _Complex ctanhl( long double _Complex  x );

// These functions return the arctangent of their parameter.
double _Complex      catan( double _Complex        x );
float _Complex       catanf( float _Complex        x );
long double _Complex catanl( long double _Complex  x );

// These functions return the hyperbolic arctangent of their parameter.
double _Complex      catanh( double _Complex       x );
float _Complex       catanhf( float _Complex       x );
long double _Complex catanhl( long double _Complex x );

// These functions return the imaginary part of their parameter.
double               cimag( double _Complex        x );
float                cimagf( float _Complex        x );
long double          cimagl( long double _Complex  x );

// These functions return the real part of their parameter.
double               creal( double _Complex        x );
float                crealf( float _Complex        x );
long double          creall( long double _Complex  x );

// These functions return value^exponent.
double _Complex      cpow( double _Complex         value,
                          double _Complex         exponent );
float _Complex       cpowf( float _Complex         value,
                           float _Complex         exponent );
long double _Complex cpowl( long double _Complex   value,
                           long double _Complex   exponent );

// These functions return the square root of their parameter.
double _Complex      csqrt( double _Complex        x );
float _Complex       csqrtf( float _Complex        x );
long double _Complex csqrtl( long double _Complex  x );

// These functions return the exponential of their parameter.
double _Complex      cexp( double _Complex         x );
float _Complex       cexpf( float _Complex         x );
long double _Complex cexpl( long double _Complex   x );

// These functions return the logarithm of their parameter.
double _Complex      clog( double _Complex         x );
float _Complex       clogf( float _Complex         x );
long double _Complex clogl( long double _Complex   x );

// These functions return the phase angle of their value.
double               carg( double _Complex         x );
float                cargf( float _Complex         x );
long double          cargl( long double _Complex   x );

// These functions return the conjugate of their parameter.
double _Complex      conj( double _Complex         x );
float _Complex       conjf( float _Complex         x );
long double _Complex conjl( long double _Complex   x );

// These functions return the projection of their parameter.
double _Complex      cproj( double _Complex        x );
float _Complex       cprojf( float _Complex        x );
long double _Complex cprojl( long double _Complex  x );

#endif // __COMPLEX_H
