// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// C++

float ceil( float x ) { /* TODO */ };
long double ceil( long double x ) { /* TODO */ };

// ----------------------------------------------------------------------------
// Standard C

double ceil( double x ) { /* TODO */ };

/* Therx code
{
    return ( x < 0 ) ? (int) x : ( (int) x ) + 1;
}
*/

/* PDPC code - unreviewed
{
    int y;
    
    y = (int)x;
    if ((double)y < x)
    {
        y++;
    }
    return ((double)y);
}
*/

float ceilf( float x ) { /* TODO */ };
long double ceill( long double x ) { /* TODO */ };
