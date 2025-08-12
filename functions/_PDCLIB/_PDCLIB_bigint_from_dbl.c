/* _PDCLIB_bigint_from_dbl( _PDCLIB_bigint_t *, double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdlib.h>
#include <string.h>

#if _PDCLIB_BIGINT_DIGIT_BITS == 16
typedef _PDCLIB_int_least16_t sint;
#else
typedef _PDCLIB_int_least32_t sint;
#endif

void _PDCLIB_bigint_from_dbl( _PDCLIB_bigint_t * fp, double d )
{
    sint exp;
    int state;
    int size;

    memcpy( fp->data, &d, sizeof( double ) );

    state = _PDCLIB_DBL_SIGN( fp->data ); /* 1<<0: negative */
    exp = _PDCLIB_DBL_EXP( fp->data );
    size = _PDCLIB_DBL_SIZE( fp->data );

    switch ( exp )
    {
        case 0:
            /* Subnormal */
            /* Set (unbiased, unscaled) exponent */
            exp = 1 - ( _PDCLIB_DBL_MAX_EXP - 1 );
            state |= 1<<1; /* 1<<1: subnormal */
            state |= ( _PDCLIB_DBL_MANT_DIG - 1 ) << 8;
            break;
        case ( _PDCLIB_DBL_MAX_EXP - 1 ) + _PDCLIB_DBL_MAX_EXP:
            /* INF / NAN */
            state |= 1<<2; /* 1<<2: INF / NAN */
            break;
        default:
        {
            /* Normal */
            /* Set implicit decimal */
            div_t dv = div( _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_BIGINT_DIGIT_BITS );
            if ( dv.rem == 0 )
            {
                fp->data[ size++ ] = 1u;
            }
            else
            {
                fp->data[ dv.quot ] |= ( 1u << dv.rem );
            }
            /* Set (unbiased, unscaled) exponent */
            exp = exp - ( _PDCLIB_DBL_MAX_EXP - 1 );
            state |= ( _PDCLIB_DBL_MANT_DIG - 1 ) << 8;
            break;
        }
    }

    while ( size > 0 && fp->data[ size - 1 ] == 0 )
    {
        --size;
    }

    fp->size = size;
    fp->data[ fp->size ] = state;
    fp->data[ fp->size + 1 ] = (_PDCLIB_bigint_digit_t)exp;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t fp;
    _PDCLIB_bigint_t t;
    size_t i;

    /* Normal */
    _PDCLIB_bigint_from_dbl( &fp, -1.0 );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_DBL_MANT_DIG - 1 );
    TESTCASE( _PDCLIB_bigint_cmp( &fp, &t ) == 0 );
    TESTCASE( fp.data[ fp.size ] == ( 1 | ( _PDCLIB_DBL_MANT_DIG - 1 ) << 8 ) );
    TESTCASE( fp.data[ fp.size + 1 ] == 0 );

    /* Inf */
    _PDCLIB_bigint_from_dbl( &fp, 1e500 );

    for ( i = 0; i < fp.size; ++i )
    {
        TESTCASE( fp.data[i] == 0 );
    }

    TESTCASE( fp.data[ fp.size ] == 1<<2 );

    /* NaN */
    _PDCLIB_bigint_from_dbl( &fp, -0.0/0.0 );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_DBL_MANT_DIG - 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &fp, &t ) == 0 );
    TESTCASE( fp.data[ fp.size ] & 1<<2 );

    /* Subnormal */
    _PDCLIB_bigint_from_dbl( &fp, _PDCLIB_DBL_MIN / 2 );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_DBL_MANT_DIG - 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &fp, &t ) == 0 );
    TESTCASE( fp.data[ fp.size ] == ( 1<<1 | ( _PDCLIB_DBL_MANT_DIG - 1 ) << 8 ) );
    TESTCASE( fp.data[ fp.size + 1 ] == (_PDCLIB_bigint_digit_t)(1 - ( _PDCLIB_DBL_MAX_EXP - 1 ) ) );
#endif

    return TEST_RESULTS;
}

#endif
