// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

double floor( double x ) { /* TODO */ };

/* Therx code
{
    return ( x > 0 ) ? (int) x : (int) ( x - 0.9999999999999999 );
}
*/

/* PDPC code - unreviewed
{
    int y;
    
    if (x < 0.0)
    {
        y = (int)fabs(x);
        if ((double)y != x)
        {
            y--;
        }
    }
    else
    {
        y = (int)x;
    }
    return ((double)x);
}
*/

float floorf( float x ) { /* TODO */ };
long double floorl( long double x ) { /* TODO */ };
