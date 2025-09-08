/* fpclassify( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <string.h>

int _PDCLIB_fpclassifyd( double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( double ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    _PDCLIB_bigint_digit_t digit = 0;
    size_t size;
    size_t i;
    int exp;

    memcpy( data, &x, sizeof( double ) );
    exp = _PDCLIB_DBL_EXP( data );
    size = _PDCLIB_DBL_SIZE( data );

    for ( i = 0; i < size; ++i )
    {
        digit |= data[i];
    }

    switch ( exp )
    {
        case ( ( _PDCLIB_DBL_MAX_EXP - 1 ) + _PDCLIB_DBL_MAX_EXP ):
            return ( digit == 0 ) ? FP_INFINITE : FP_NAN;
        case 0:
            return ( digit == 0 ) ? FP_ZERO : FP_SUBNORMAL;
        default:
            return FP_NORMAL;
    }
}

int _PDCLIB_fpclassifyf( float x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( float ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    _PDCLIB_bigint_digit_t digit = 0;
    size_t size;
    size_t i;
    int exp;

    memcpy( data, &x, sizeof( float ) );
    exp = _PDCLIB_FLT_EXP( data );
    size = _PDCLIB_FLT_SIZE( data );

    for ( i = 0; i < size; ++i )
    {
        digit |= data[i];
    }

    switch ( exp )
    {
        case ( ( _PDCLIB_FLT_MAX_EXP - 1 ) + _PDCLIB_FLT_MAX_EXP ):
            return ( digit == 0 ) ? FP_INFINITE : FP_NAN;
        case 0:
            return ( digit == 0 ) ? FP_ZERO : FP_SUBNORMAL;
        default:
            return FP_NORMAL;
    }
}

int _PDCLIB_fpclassifyl( long double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( long double ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    _PDCLIB_bigint_digit_t digit = 0;
    size_t size;
    size_t i;
    int exp;

    memcpy( data, &x, sizeof( long double ) );
    exp = _PDCLIB_LDBL_EXP( data );
    size = _PDCLIB_LDBL_SIZE( data );

    for ( i = 0; i < size; ++i )
    {
        digit |= data[i];
    }

    switch ( exp )
    {
        case ( ( _PDCLIB_LDBL_MAX_EXP - 1 ) + _PDCLIB_LDBL_MAX_EXP ):
            return ( digit == 0 ) ? FP_INFINITE : FP_NAN;
        case 0:
            return ( digit == 0 ) ? FP_ZERO : FP_SUBNORMAL;
        default:
            return FP_NORMAL;
    }
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

    f = 0.123;
    TESTCASE( fpclassify( f ) == FP_NORMAL );
    f = FLT_MIN;
    TESTCASE( fpclassify( f ) == FP_NORMAL );
    f = FLT_MIN / 2;
    TESTCASE( fpclassify( f ) == FP_SUBNORMAL );
    f = 0.0;
    TESTCASE( fpclassify( f ) == FP_ZERO );
    f = FLT_MAX;
    TESTCASE( fpclassify( f ) == FP_NORMAL );
    f = FLT_MAX * 2;
    TESTCASE( fpclassify( f ) == FP_INFINITE );
    f = 0.0 / 0.0;
    TESTCASE( fpclassify( f ) == FP_NAN );

    d = 0.123;
    TESTCASE( fpclassify( d ) == FP_NORMAL );
    d = DBL_MIN;
    TESTCASE( fpclassify( d ) == FP_NORMAL );
    d = DBL_MIN / 2;
    TESTCASE( fpclassify( d ) == FP_SUBNORMAL );
    d = 0.0;
    TESTCASE( fpclassify( d ) == FP_ZERO );
    d = DBL_MAX;
    TESTCASE( fpclassify( d ) == FP_NORMAL );
    d = DBL_MAX * 2;
    TESTCASE( fpclassify( d ) == FP_INFINITE );
    d = 0.0 / 0.0;
    TESTCASE( fpclassify( d ) == FP_NAN );

    ld = 0.123;
    TESTCASE( fpclassify( ld ) == FP_NORMAL );
    ld = LDBL_MIN;
    TESTCASE( fpclassify( ld ) == FP_NORMAL );
    ld = LDBL_MIN / 2;
    TESTCASE( fpclassify( ld ) == FP_SUBNORMAL );
    ld = 0.0;
    TESTCASE( fpclassify( ld ) == FP_ZERO );
    ld = LDBL_MAX;
    TESTCASE( fpclassify( ld ) == FP_NORMAL );
    ld = LDBL_MAX * 2;
    TESTCASE( fpclassify( ld ) == FP_INFINITE );
    ld = 0.0 / 0.0;
    TESTCASE( fpclassify( ld ) == FP_NAN );

    return TEST_RESULTS;
}

#endif
