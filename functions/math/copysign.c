// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

double copysign( double x, double y ) { /* TODO */ };

/* Own code
{
    if ( y < 0 )
    {
        return ( x < 0 ) ? x : -x;
    }
    else
    {
        return ( x < 0 ) ? -x : x;
    }
}

float copysignf( float x, float y ) { /* TODO */ };
long double copysignl( long double x, long double y ) { /* TODO */ };
