// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// C++

float sqrt( float x ) { /* TODO */ };
long double sqrt( long double x ) { /* TODO */ };

// ----------------------------------------------------------------------------
// Standard C

double sqrt( double x ) { /* TODO */ };

/* Therx code
{
    double i = x / 2;
    if ( x < 0 )
    {
        return 0;
    }
    // (15 DP) HOW GET MORE?
    while ( ( fabs( i - ( x / i ) ) / i ) > 0.000000000000001)
    {
        i = ( i + ( x / i ) ) / 2;
    }
    return i;
}
*/

float sqrtf( float x ) { /* TODO */ };
long double sqrtl( long double x ) { /* TODO */ };
