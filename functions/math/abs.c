// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

double fabs( double x ) { /* TODO */ };

/* Therx code
{
    return ( x < 0 ) ? -x : x;
}
*/

/* PDPC code - unreviewed
{
    if (x < 0.0)
    {
        x = -x;
    }
    return (x);
}
*/

float fabsf( float x ) { /* TODO */ };
long double fabsl( long double x ) { /* TODO */ };

int abs( int i ) { /* TODO */ };
long long llabs( long long i ) { /* TODO */ };
long labs( long i ) { /* TODO */ };
