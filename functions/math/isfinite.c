/* isfinite( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <string.h>

int _PDCLIB_isfinited( double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( double ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    memcpy( data, &x, sizeof( double ) );
    return _PDCLIB_DBL_EXP( data ) != ( ( _PDCLIB_DBL_MAX_EXP - 1 ) + _PDCLIB_DBL_MAX_EXP );
}

int _PDCLIB_isfinitef( float x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( float ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    memcpy( data, &x, sizeof( float ) );
    return _PDCLIB_FLT_EXP( data ) != ( ( _PDCLIB_FLT_MAX_EXP - 1 ) + _PDCLIB_FLT_MAX_EXP );
}

int _PDCLIB_isfinitel( long double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( long double ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    memcpy( data, &x, sizeof( long double ) );
    return _PDCLIB_LDBL_EXP( data ) != ( ( _PDCLIB_LDBL_MAX_EXP - 1 ) + _PDCLIB_LDBL_MAX_EXP );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <float.h>

int main( void )
{
    float f;
    double d;
    long double ld;

    f = 0.123f;
    TESTCASE( isfinite( f ) );
    f = FLT_MAX;
    TESTCASE( isfinite( f ) );
    f *= 2;
    TESTCASE( ! isfinite( f ) );
    f = FLT_MIN;
    TESTCASE( isfinite( f ) );
    f /= 2;
    TESTCASE( isfinite( f ) );
    f = 0.0f / 0.0f;
    TESTCASE( ! isfinite( f ) );

    d = 0.123;
    TESTCASE( isfinite( d ) );
    d = DBL_MAX;
    TESTCASE( isfinite( d ) );
    d *= 2;
    TESTCASE( ! isfinite( d ) );
    d = DBL_MIN;
    TESTCASE( isfinite( d ) );
    d /= 2;
    TESTCASE( isfinite( d ) );
    d = 0.0 / 0.0;
    TESTCASE( ! isfinite( d ) );

    ld = 0.123l;
    TESTCASE( isfinite( ld ) );
    ld = LDBL_MAX;
    TESTCASE( isfinite( ld ) );
    ld *= 2;
    TESTCASE( ! isfinite( ld ) );
    ld = LDBL_MIN;
    TESTCASE( isfinite( ld ) );
    ld /= 2;
    TESTCASE( isfinite( ld ) );
    ld = 0.0l / 0.0l;
    TESTCASE( ! isfinite( ld ) );

    return TEST_RESULTS;
}

#endif
