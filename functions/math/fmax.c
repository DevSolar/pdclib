
/* fmax( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

double fmax( double x, double y )
{
    if ( isnan( x ) ) return y;
    if ( isnan( y ) ) return x;
    return ( x > y ) ? x : y;
}

float fmaxf( float x, float y )
{
    if ( isnan( x ) ) return y;
    if ( isnan( y ) ) return x;
    return ( x > y ) ? x : y;
}

long double fmaxl( long double x, long double y )
{
    if ( isnan( x ) ) return y;
    if ( isnan( y ) ) return x;
    return ( x > y ) ? x : y;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    float f1, f2;
    double d1, d2;
    long double ld1, ld2;

    f1 = 3.15f;
    f2 = 3.16f;
    TESTCASE( fmaxf( f1, f2 ) == f2 );
    TESTCASE( fmaxf( f2, f1 ) == f2 );
    TESTCASE( fmaxf( f1, f1 ) == f1 );
    TESTCASE( fmaxf( f1, INFINITY ) == INFINITY );
    TESTCASE( fmaxf( INFINITY, f1 ) == INFINITY );
    TESTCASE( fmaxf( f1, -INFINITY ) == f1 );
    TESTCASE( fmaxf( -INFINITY, f1 ) == f1 );
    TESTCASE( fmaxf( f1, NAN ) == f1 );
    TESTCASE( fmaxf( NAN, f1 ) == f1 );
    TESTCASE( fmaxf( f1, -NAN ) == f1 );
    TESTCASE( fmaxf( -NAN, f1 ) == f1 );
    TESTCASE( fmaxf( NAN, NAN ) != fmaxf( NAN, NAN ) );
    f1 = 0.0f;
    f2 = -0.0f;
    TESTCASE( fmaxf( f1, f2 ) == f1 );
    TESTCASE( fmaxf( f2, f1 ) == f1 );

    d1 = 3.15f;
    d2 = 3.16f;
    TESTCASE( fmax( d1, d2 ) == d2 );
    TESTCASE( fmax( d2, d1 ) == d2 );
    TESTCASE( fmax( d1, d1 ) == d1 );
    TESTCASE( fmax( d1, INFINITY ) == INFINITY );
    TESTCASE( fmax( INFINITY, d1 ) == INFINITY );
    TESTCASE( fmax( d1, -INFINITY ) == d1 );
    TESTCASE( fmax( -INFINITY, d1 ) == d1 );
    TESTCASE( fmax( d1, NAN ) == d1 );
    TESTCASE( fmax( NAN, d1 ) == d1 );
    TESTCASE( fmax( d1, -NAN ) == d1 );
    TESTCASE( fmax( -NAN, d1 ) == d1 );
    TESTCASE( fmax( NAN, NAN ) != fmax( NAN, NAN ) );
    d1 = 0.0;
    d2 = -0.0;
    TESTCASE( fmax( d1, d2 ) == d1 );
    TESTCASE( fmax( d2, d1 ) == d1 );

    ld1 = 3.15f;
    ld2 = 3.16f;
    TESTCASE( fmaxl( ld1, ld2 ) == ld2 );
    TESTCASE( fmaxl( ld2, ld1 ) == ld2 );
    TESTCASE( fmaxl( ld1, ld1 ) == ld1 );
    TESTCASE( fmaxl( ld1, INFINITY ) == INFINITY );
    TESTCASE( fmaxl( INFINITY, ld1 ) == INFINITY );
    TESTCASE( fmaxl( ld1, -INFINITY ) == ld1 );
    TESTCASE( fmaxl( -INFINITY, ld1 ) == ld1 );
    TESTCASE( fmaxl( ld1, NAN ) == ld1 );
    TESTCASE( fmaxl( NAN, ld1 ) == ld1 );
    TESTCASE( fmaxl( ld1, -NAN ) == ld1 );
    TESTCASE( fmaxl( -NAN, ld1 ) == ld1 );
    TESTCASE( fmaxl( NAN, NAN ) != fmaxl( NAN, NAN ) );
    ld1 = 0.0;
    ld2 = -0.0;
    TESTCASE( fmaxl( ld1, ld2 ) == ld1 );
    TESTCASE( fmaxl( ld2, ld1 ) == ld1 );

    return TEST_RESULTS;
}

#endif
