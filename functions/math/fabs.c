
/* fabs( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

double fabs( double x )
{
    if ( isnan( x ) )
    {
        return NAN;
    }

    return ( x < 0.0 ) ? -x : x;
}

float fabsf( float x )
{
    if ( isnan( x ) )
    {
        return NAN;
    }

    return ( x < 0.0 ) ? -x : x;
}

long double fabsl( long double x )
{
    if ( isnan( x ) )
    {
        return NAN;
    }

    return ( x < 0.0 ) ? -x : x;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <errno.h>

int main( void )
{
    float f;
    double d;
    long double ld;

    TESTCASE( fabsf( 3.15f ) == 3.15f );
    TESTCASE( fabsf( -3.15f ) == 3.15f );
    errno = 0;
    TESTCASE( fabsf( INFINITY ) == INFINITY );
    TESTCASE( errno == 0 );
    errno = 0;
    TESTCASE( fabsf( -INFINITY ) == INFINITY );
    TESTCASE( errno == 0 );
    errno = 0;
    f = fabsf( NAN );
    TESTCASE( isnan( f ) );
    TESTCASE( ! signbit( f ) );
    TESTCASE( errno == 0 );
    f = fabsf( -NAN );
    TESTCASE( isnan( f ) );
    TESTCASE( ! signbit( f ) );
    TESTCASE( errno == 0 );

    TESTCASE( fabs( 3.15 ) == 3.15 );
    TESTCASE( fabs( -3.15 ) == 3.15 );
    errno = 0;
    TESTCASE( fabs( INFINITY ) == INFINITY );
    TESTCASE( errno == 0 );
    errno = 0;
    TESTCASE( fabs( -INFINITY ) == INFINITY );
    TESTCASE( errno == 0 );
    errno = 0;
    d = fabs( NAN );
    TESTCASE( isnan( d ) );
    TESTCASE( ! signbit( d ) );
    TESTCASE( errno == 0 );
    d = fabs( -NAN );
    TESTCASE( isnan( d ) );
    TESTCASE( ! signbit( d ) );
    TESTCASE( errno == 0 );

    TESTCASE( fabsl( 3.15l ) == 3.15l );
    TESTCASE( fabsl( -3.15l ) == 3.15l );
    errno = 0;
    TESTCASE( fabsl( INFINITY ) == INFINITY );
    TESTCASE( errno == 0 );
    errno = 0;
    TESTCASE( fabsl( -INFINITY ) == INFINITY );
    TESTCASE( errno == 0 );
    errno = 0;
    ld = fabsl( NAN );
    TESTCASE( isnan( ld ) );
    TESTCASE( ! signbit( ld ) );
    TESTCASE( errno == 0 );
    ld = fabsl( -NAN );
    TESTCASE( isnan( ld ) );
    TESTCASE( ! signbit( ld ) );
    TESTCASE( errno == 0 );


    return TEST_RESULTS;
}

#endif
