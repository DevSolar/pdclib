// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// C++

float exp( float x ) { /* TODO */ };
long double exp( long double x ) { /* TODO */ };

float exp2( float x ) { /* TODO */ };
long double exp2( long double x ) { /* TODO */ };

float expm1( float x ) { /* TODO */ };
long double expm1( long double x ) { /* TODO */ };

float frexp( float x, int * exponent ) { /* TODO */ };
long double frexp( long double x, int * exponent ) { /* TODO */ };

float ldexp( float x, int exponent ) { /* TODO */ };
long double ldexp( long double x, int exponent ) { /* TODO */ };

// ----------------------------------------------------------------------------
// Standard C

double exp( double x ) { /* TODO */ };
float expf( float x ) { /* TODO */ };
long double expl( long double x ) { /* TODO */ };

double exp2( double x ) { /* TODO */ };

/* Therx code
{
    double value = 1;
    for( int i = 1; i <= x; i++ )
    {
        value *= 2;
    }
    return value;
}
*/

float exp2f( float x ) { /* TODO */ };
long double exp2l( long double x ) { /* TODO */ };

double expm1( double x ) { /* TODO */ };
float expm1f( float x ) { /* TODO */ };
long double expm1l( long double x ) { /* TODO */ };

double frexp( double x, int * exp ) { /* TODO */ };
float frexpf( float x, int * exp ) { /* TODO */ };
long double frexpl( long double x, int * exp ) { /* TODO */ };

double ldexp( double x, int exp ) { /* TODO */ };
float ldexpf( float x, int exp ) { /* TODO */ };
long double ldexpl( long double x, int exp ) { /* TODO */ };
