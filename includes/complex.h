// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Complex arithmetic
// ----------------------------------------------------------------------------

#ifndef __COMPLEX_H
#define __COMPLEX_H __COMPLEX_H

#include "__personality.h"

// ----------------------------------------------------------------------------
// DEFINES

#ifndef __cplusplus
#define complex     _Complex
#endif

#define _Complex_I  ( const float _Complex ) { 0, 1 }

#ifdef __PERSONALITY_SUPPORTS_IMAGINARY
#define imaginary   _Imaginary
#endif // __PERSONALITY_SUPPORTS_IMAGINARY

#ifdef imaginary
#define _Imaginary_I ( ( const float _Imaginary ) 1 )
#endif

#ifdef imaginary
#define I _Imaginary_I
#else
#define I _Complex_I
#endif

// ----------------------------------------------------------------------------
// FUNCTIONS

// These functions return the absolute value (magnitude) of their parameter.
double               cabs( double _Complex       x );
float                cabsf( float _Complex       x );
long double          cabsl( long double _Complex x );

// These functions return the sine of their parameter.
double _Complex      csin( double _Complex       x );
float _Complex       csinf( float _Complex       x );
long double _Complex csinl( long double _Complex x );

// These functions return the hyperbolic sine of their parameter.
double _Complex      csinh( double _Complex       x );
float _Complex       csinhf( float _Complex       x );
long double _Complex csinhl( long double _Complex x );

// These functions return the arcsine of their parameter.
double _Complex      casin( double _Complex       x );
float _Complex       casinf( float _Complex       x );
long double _Complex casinl( long double _Complex x );

// These functions return the hyperbolic arcsine of their parameter.
double _Complex      casinh( double _Complex       x );
float _Complex       casinhf( float _Complex       x );
long double _Complex casinhl( long double _Complex x );

// These functions return the cosine of their parameter.
double _Complex      ccos( double _Complex       x );
float _Complex       ccosf( float _Complex       x );
long double _Complex ccosl( long double _Complex x );

// These functions return the hyperbolic cosine of their parameter.
double _Complex      ccosh( double _Complex       x );
float _Complex       ccoshf( float _Complex       x );
long double _Complex ccoshl( long double _Complex x );

// These functions return the arccosine of their parameter.
double _Complex      cacos( double _Complex       x );
float _Complex       cacosf( float _Complex       x );
long double _Complex cacosl( long double _Complex x );

// These functions return the hyperbolic arccosine of their parameter.
double _Complex      cacosh( double _Complex       x );
float _Complex       cacoshf( float _Complex       x );
long double _Complex cacoshl( long double _Complex x );

// These functions return the tangent of their parameter.
double _Complex      ctan( double _Complex       x );
float _Complex       ctanf( float _Complex       x );
long double _Complex ctanl( long double _Complex x );

// These functions return the hyperbolic tangent of their parameter.
double _Complex      ctanh( double _Complex       x );
float _Complex       ctanhf( float _Complex       x );
long double _Complex ctanhl( long double _Complex x );

// These functions return the arctangent of their parameter.
double _Complex      catan( double _Complex       x );
float _Complex       catanf( float _Complex       x );
long double _Complex catanl( long double _Complex x );

// These functions return the hyperbolic arctangent of their parameter.
double _Complex      catanh( double _Complex       x );
float _Complex       catanhf( float _Complex       x );
long double _Complex catanhl( long double _Complex x );

// These functions return the imaginary part of their parameter.
double               cimag( double _Complex       x );
float                cimagf( float _Complex       x );
long double          cimagl( long double _Complex x );

// These functions return the real part of their parameter.
double               creal( double _Complex       x );
float                crealf( float _Complex       x );
long double          creall( long double _Complex x );

// These functions return x^y.
double _Complex      cpow( double _Complex       x, double _Complex      y );
float _Complex       cpowf( float _Complex       x, float _Complex       y );
long double _Complex cpowl( long double _Complex x, long double _Complex y );

// These functions return the square root of their parameter.
double _Complex      csqrt( double _Complex       x );
float _Complex       csqrtf( float _Complex       x );
long double _Complex csqrtl( long double _Complex x );

// These functions return the exponential of their parameter.
double _Complex      cexp( double _Complex       x );
float _Complex       cexpf( float _Complex       x );
long double _Complex cexpl( long double _Complex x );

// These functions return the logarithm of their parameter.
double _Complex      clog( double _Complex       x );
float _Complex       clogf( float _Complex       x );
long double _Complex clogl( long double _Complex x );

// These functions return the phase angle of their value.
double               carg( double _Complex       x );
float                cargf( float _Complex       x );
long double          cargl( long double _Complex x );

// These functions return the conjugate of their parameter.
double _Complex      conj( double _Complex       x );
float _Complex       conjf( float _Complex       x );
long double _Complex conjl( long double _Complex x );

// These functions return the projection of their parameter.
double _Complex      cproj( double _Complex       x );
float _Complex       cprojf( float _Complex       x );
long double _Complex cprojl( long double _Complex x );

#endif // __COMPLEX_H
