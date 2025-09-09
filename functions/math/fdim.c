/* fdim( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

double fdim( double x, double y )
{
    return fmax( x - y, 0 );
}

float fdimf( float x, float y )
{
    return fmaxf( x - y, 0 );
}

long double fdiml( long double x, long double y )
{
    return fmaxl( x - y, 0 );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    float f1, f2;
    double d1, d2;
    long double ld1, ld2;

    f1 = 3.5f;
    f2 = 3.75f;
    TESTCASE( fdimf( f1, f2 ) == 0.0f );
    TESTCASE( fdimf( f2, f1 ) == 0.25f );
    TESTCASE( fdimf( f1, INFINITY ) == 0.0f );
    TESTCASE( fdimf( INFINITY, f1 ) == INFINITY );
    TESTCASE( fdimf( f1, -INFINITY ) == INFINITY );
    TESTCASE( fdimf( -INFINITY, f1 ) == 0.0f );
    TESTCASE( fdimf( f1, NAN ) != f1 );
    TESTCASE( fdimf( NAN, f1 ) != f1 );

    d1 = 3.5;
    d2 = 3.75;
    TESTCASE( fdim( d1, d2 ) == 0.0 );
    TESTCASE( fdim( d2, d1 ) == 0.25 );
    TESTCASE( fdim( d1, INFINITY ) == 0.0 );
    TESTCASE( fdim( INFINITY, d1 ) == INFINITY );
    TESTCASE( fdim( d1, -INFINITY ) == INFINITY );
    TESTCASE( fdim( -INFINITY, d1 ) == 0.0 );
    TESTCASE( fdim( d1, NAN ) != d1 );
    TESTCASE( fdim( NAN, d1 ) != d1 );

    ld1 = 3.5l;
    ld2 = 3.75l;
    TESTCASE( fdiml( ld1, ld2 ) == 0.0l );
    TESTCASE( fdiml( ld2, ld1 ) == 0.25l );
    TESTCASE( fdiml( ld1, INFINITY ) == 0.0l );
    TESTCASE( fdiml( INFINITY, ld1 ) == INFINITY );
    TESTCASE( fdiml( ld1, -INFINITY ) == INFINITY );
    TESTCASE( fdiml( -INFINITY, ld1 ) == 0.0l );
    TESTCASE( fdiml( ld1, NAN ) != ld1 );
    TESTCASE( fdiml( NAN, ld1 ) != ld1 );

    return TEST_RESULTS;
}

#endif
