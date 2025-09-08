/* isinf( double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <math.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <string.h>

int _PDCLIB_isinfd( double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( double ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    size_t size;
    int exp;

    memcpy( data, &x, sizeof( double ) );
    exp = _PDCLIB_DBL_EXP( data );
    size = _PDCLIB_DBL_SIZE( data );

    if ( exp == ( ( _PDCLIB_DBL_MAX_EXP - 1 ) + _PDCLIB_DBL_MAX_EXP ) )
    {
        _PDCLIB_bigint_digit_t digit = 0;
        size_t i;

        for ( i = 0; i < size; ++i )
        {
            digit |= data[i];
        }

        return digit == 0;
    }

    return 0;
}

int _PDCLIB_isinff( float x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( float ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    size_t size;
    int exp;

    memcpy( data, &x, sizeof( float ) );
    exp = _PDCLIB_FLT_EXP( data );
    size = _PDCLIB_FLT_SIZE( data );

    if ( exp == ( ( _PDCLIB_FLT_MAX_EXP - 1 ) + _PDCLIB_FLT_MAX_EXP ) )
    {
        _PDCLIB_bigint_digit_t digit = 0;
        size_t i;

        for ( i = 0; i < size; ++i )
        {
            digit |= data[i];
        }

        return digit == 0;
    }

    return 0;
}

int _PDCLIB_isinfl( long double x )
{
    _PDCLIB_bigint_digit_t data[ sizeof( long double ) / sizeof( _PDCLIB_bigint_digit_t ) ];
    size_t size;
    int exp;

    memcpy( data, &x, sizeof( long double ) );
    exp = _PDCLIB_LDBL_EXP( data );
    size = _PDCLIB_LDBL_SIZE( data );

    if ( exp == ( ( _PDCLIB_LDBL_MAX_EXP - 1 ) + _PDCLIB_LDBL_MAX_EXP ) )
    {
        _PDCLIB_bigint_digit_t digit = 0;
        size_t i;

        for ( i = 0; i < size; ++i )
        {
            digit |= data[i];
        }

        return digit == 0;
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    float f;
    double d;
    long double ld;

    f = 1e100;
    TESTCASE( isinf( f ) == 1 );
    f = 0.0 / 0.0;
    TESTCASE( isinf( f ) == 0 );

    d = 1e500;
    TESTCASE( isinf( d ) == 1 );
    d = 0.0 / 0.0;
    TESTCASE( isinf( d ) == 0 );

    ld = 1e500;
    TESTCASE( isinf( ld ) == 1 );
    ld = 0.0 / 0.0;
    TESTCASE( isinf( ld ) == 0 );

    return TEST_RESULTS;
}

#endif
