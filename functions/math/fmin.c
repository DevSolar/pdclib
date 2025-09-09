
/* fmin( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

double fmin( double x, double y )
{
    if ( isnan( x ) ) return y;
    if ( isnan( y ) ) return x;
    return ( x < y ) ? x : y;
}

float fminf( float x, float y )
{
    if ( isnan( x ) ) return y;
    if ( isnan( y ) ) return x;
    return ( x < y ) ? x : y;
}

long double fminl( long double x, long double y )
{
    if ( isnan( x ) ) return y;
    if ( isnan( y ) ) return x;
    return ( x < y ) ? x : y;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    float f1, f2;
    double d1, d2;
    long double ld1, ld2;

    f1 = 3.16f;
    f2 = 3.15f;
    TESTCASE( fminf( f1, f2 ) == f2 );
    TESTCASE( fminf( f2, f1 ) == f2 );
    TESTCASE( fminf( f1, f1 ) == f1 );
    TESTCASE( fminf( f1, INFINITY ) == f1 );
    TESTCASE( fminf( INFINITY, f1 ) == f1 );
    TESTCASE( fminf( f1, -INFINITY ) == -INFINITY );
    TESTCASE( fminf( -INFINITY, f1 ) == -INFINITY );
    TESTCASE( fminf( f1, NAN ) == f1 );
    TESTCASE( fminf( NAN, f1 ) == f1 );
    TESTCASE( fminf( f1, -NAN ) == f1 );
    TESTCASE( fminf( -NAN, f1 ) == f1 );
    TESTCASE( fminf( NAN, NAN ) != fminf( NAN, NAN ) );
    f1 = -0.0f;
    f2 = 0.0f;
    TESTCASE( fminf( f1, f2 ) == f1 );
    TESTCASE( fminf( f2, f1 ) == f1 );

    d1 = 3.16f;
    d2 = 3.15f;
    TESTCASE( fmin( d1, d2 ) == d2 );
    TESTCASE( fmin( d2, d1 ) == d2 );
    TESTCASE( fmin( d1, d1 ) == d1 );
    TESTCASE( fmin( d1, INFINITY ) == d1 );
    TESTCASE( fmin( INFINITY, d1 ) == d1 );
    TESTCASE( fmin( d1, -INFINITY ) == -INFINITY );
    TESTCASE( fmin( -INFINITY, d1 ) == -INFINITY );
    TESTCASE( fmin( d1, NAN ) == d1 );
    TESTCASE( fmin( NAN, d1 ) == d1 );
    TESTCASE( fmin( d1, -NAN ) == d1 );
    TESTCASE( fmin( -NAN, d1 ) == d1 );
    TESTCASE( fmin( NAN, NAN ) != fmin( NAN, NAN ) );
    d1 = -0.0;
    d2 = 0.0;
    TESTCASE( fmin( d1, d2 ) == d1 );
    TESTCASE( fmin( d2, d1 ) == d1 );

    ld1 = 3.16f;
    ld2 = 3.15f;
    TESTCASE( fminl( ld1, ld2 ) == ld2 );
    TESTCASE( fminl( ld2, ld1 ) == ld2 );
    TESTCASE( fminl( ld1, ld1 ) == ld1 );
    TESTCASE( fminl( ld1, INFINITY ) == ld1 );
    TESTCASE( fminl( INFINITY, ld1 ) == ld1 );
    TESTCASE( fminl( ld1, -INFINITY ) == -INFINITY );
    TESTCASE( fminl( -INFINITY, ld1 ) == -INFINITY );
    TESTCASE( fminl( ld1, NAN ) == ld1 );
    TESTCASE( fminl( NAN, ld1 ) == ld1 );
    TESTCASE( fminl( ld1, -NAN ) == ld1 );
    TESTCASE( fminl( -NAN, ld1 ) == ld1 );
    TESTCASE( fminl( NAN, NAN ) != fminl( NAN, NAN ) );
    ld1 = -0.0;
    ld2 = 0.0;
    TESTCASE( fminl( ld1, ld2 ) == ld1 );
    TESTCASE( fminl( ld2, ld1 ) == ld1 );

    return TEST_RESULTS;
}

#endif
