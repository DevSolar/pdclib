// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

double cbrt( double x ) { /* TODO */ };

/* Therx code
{
    double i = x / 4;
    // (15 DP) HOW GET MORE?
    while ( ( fabs( i - ( x / i / i ) ) / i ) > 0.00000000000001 )
    {
        i = ( i + ( x / i / i ) + i ) / 3;
    }
    return i;
}
*/

float cbrtf( float x ) { /* TODO */ };
long double cbrtl( long double x ) { /* TODO */ };
