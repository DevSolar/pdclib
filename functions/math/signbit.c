/* signbit( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <string.h>

int _PDCLIB_signbitd( double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( double ) / sizeof( _PDCLIB_bigint_digit_t ) ];

    memcpy( data, &x, sizeof( double ) );
    return _PDCLIB_DBL_SIGN( data ) != 0;
}

int _PDCLIB_signbitf( float x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( float ) / sizeof( _PDCLIB_bigint_digit_t ) ];

    memcpy( data, &x, sizeof( float ) );
    return _PDCLIB_FLT_SIGN( data ) != 0;
}

int _PDCLIB_signbitl( long double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( long double ) / sizeof( _PDCLIB_bigint_digit_t ) ];

    memcpy( data, &x, sizeof( long double ) );
    return _PDCLIB_LDBL_SIGN( data ) != 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    float f;
    double d;
    long double ld;

    f = 0.123f;
    TESTCASE( ! signbit( f ) );
    f = -0.123f;
    TESTCASE( signbit( f ) );

    d = 0.123;
    TESTCASE( ! signbit( d ) );
    d = -0.123;
    TESTCASE( signbit( d ) );

    ld = 0.123l;
    TESTCASE( ! signbit( ld ) );
    ld = -0.123l;
    TESTCASE( signbit( ld ) );

    return TEST_RESULTS;
}

#endif
