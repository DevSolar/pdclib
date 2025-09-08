/* isnormal( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <string.h>

int _PDCLIB_isnormald( double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( double ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    int exp;
    memcpy( data, &x, sizeof( double ) );
    exp = _PDCLIB_DBL_EXP( data );
    return ( exp != ( ( _PDCLIB_DBL_MAX_EXP - 1 ) + _PDCLIB_DBL_MAX_EXP ) ) && ( exp != 0 );
}

int _PDCLIB_isnormalf( float x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( float ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    int exp;
    memcpy( data, &x, sizeof( float ) );
    exp = _PDCLIB_FLT_EXP( data );
    return ( exp != ( ( _PDCLIB_FLT_MAX_EXP - 1 ) + _PDCLIB_FLT_MAX_EXP ) ) && ( exp != 0 );
}

int _PDCLIB_isnormall( long double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( long double ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    int exp;
    memcpy( data, &x, sizeof( long double ) );
    exp = _PDCLIB_LDBL_EXP( data );
    return ( exp != ( ( _PDCLIB_LDBL_MAX_EXP - 1 ) + _PDCLIB_LDBL_MAX_EXP ) ) && ( exp != 0 );
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
    TESTCASE( isnormal( f ) );
    f = FLT_MAX;
    TESTCASE( isnormal( f ) );
    f = FLT_MAX * 2;
    TESTCASE( ! isnormal( f ) );
    f = FLT_MIN;
    TESTCASE( isnormal( f ) );
    f = FLT_MIN / 2;
    TESTCASE( ! isnormal( f ) );
    f = 0.0f;
    TESTCASE( ! isnormal( f ) );
    f = 1e100;
    TESTCASE( ! isnormal( f ) );
    f = 0.0 / 0.0;
    TESTCASE( ! isnormal( f ) );

    d = 0.123f;
    TESTCASE( isnormal( d ) );
    d = DBL_MAX;
    TESTCASE( isnormal( d ) );
    d = DBL_MAX * 2;
    TESTCASE( ! isnormal( d ) );
    d = DBL_MIN;
    TESTCASE( isnormal( d ) );
    d = DBL_MIN / 2;
    TESTCASE( ! isnormal( d ) );
    d = 0.0f;
    TESTCASE( ! isnormal( d ) );
    d = 1e500;
    TESTCASE( ! isnormal( d ) );
    d = 0.0 / 0.0;
    TESTCASE( ! isnormal( d ) );

    ld = 0.123f;
    TESTCASE( isnormal( ld ) );
    ld = LDBL_MAX;
    TESTCASE( isnormal( ld ) );
    ld = LDBL_MAX * 2;
    TESTCASE( ! isnormal( ld ) );
    ld = LDBL_MIN;
    TESTCASE( isnormal( ld ) );
    ld = LDBL_MIN / 2;
    TESTCASE( ! isnormal( ld ) );
    ld = 0.0f;
    TESTCASE( ! isnormal( ld ) );
    ld = 1e1000;
    TESTCASE( ! isnormal( ld ) );
    ld = 0.0 / 0.0;
    TESTCASE( ! isnormal( ld ) );

    return TEST_RESULTS;
}

#endif
