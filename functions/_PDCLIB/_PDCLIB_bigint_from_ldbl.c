/* _PDCLIB_bigint_from_ldbl( _PDCLIB_bigint_t *, long double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdlib.h>
#include <string.h>

void _PDCLIB_bigint_from_ldbl( _PDCLIB_bigint_t * fp, long double ld )
{
    int exp;
    int sign;
    int size;

    memcpy( fp->data, &ld, sizeof( long double ) );

    sign = _PDCLIB_LDBL_SIGN( fp->data );
    exp = _PDCLIB_LDBL_EXP( fp->data );
    size = _PDCLIB_LDBL_SIZE( fp->data );

    switch ( exp )
    {
        case 0:
            /* Subnormal */
            /* Set (unbiased, scaled) exponent */
            exp = 1 - ( _PDCLIB_LDBL_MAX_EXP - 1 ) - ( _PDCLIB_LDBL_MANT_DIG - 1 );
            break;
        case ( _PDCLIB_LDBL_MAX_EXP - 1 ) + _PDCLIB_LDBL_MAX_EXP:
            /* INF / NAN */
            exp = _PDCLIB_BIGINT_DIGIT_MAX;
            break;
        default:
        {
            /* Normal */
            /* Set implicit decimal */
            div_t dv = div( _PDCLIB_LDBL_MANT_DIG - 1, _PDCLIB_BIGINT_DIGIT_BITS );
            if ( dv.rem == 0 )
            {
                fp->data[ size++ ] = 1u;
            }
            else
            {
                fp->data[ dv.quot ] |= ( 1u << dv.rem );
            }
            /* Set (unbiased, scaled) exponent */
            exp = exp - ( _PDCLIB_LDBL_MAX_EXP - 1 ) - ( _PDCLIB_LDBL_MANT_DIG - 1 );
            break;
        }
    }

    while ( size > 0 && fp->data[ size - 1 ] == 0 )
    {
        --size;
    }

    fp->size = size;
    fp->data[ fp->size ] = exp;
    fp->data[ fp->size + 1 ] = sign;
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
    _PDCLIB_bigint_from_ldbl( &fp, -1.0L );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_LDBL_MANT_DIG - 1 );
    TESTCASE( _PDCLIB_bigint_cmp( &fp, &t ) == 0 );
    TESTCASE( fp.data[ fp.size ] == (_PDCLIB_bigint_digit_t)( 1 - _PDCLIB_LDBL_MANT_DIG ) );
    TESTCASE( fp.data[ fp.size + 1 ] == 1 );

    /* Inf */
    _PDCLIB_bigint_from_ldbl( &fp, 1e5000L );

    for ( i = 0; i < fp.size; ++i )
    {
        TESTCASE( fp.data[i] == 0 );
    }

    TESTCASE( fp.data[ fp.size ] == _PDCLIB_BIGINT_DIGIT_MAX );
    TESTCASE( fp.data[ fp.size + 1 ] == 0 );

    /* NaN */
    _PDCLIB_bigint_from_ldbl( &fp, -0.0L/0.0L );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_LDBL_MANT_DIG - 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &fp, &t ) == 0 );
    TESTCASE( fp.data[ fp.size ] == _PDCLIB_BIGINT_DIGIT_MAX );

    /* Subnormal */
    _PDCLIB_bigint_from_ldbl( &fp, _PDCLIB_LDBL_MIN / 2L );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_LDBL_MANT_DIG - 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &fp, &t ) == 0 );
    TESTCASE( fp.data[ fp.size ] == (_PDCLIB_bigint_digit_t)(1 - ( _PDCLIB_LDBL_MAX_EXP - 1 ) - ( _PDCLIB_LDBL_MANT_DIG - 1 ) ) );
    TESTCASE( fp.data[ fp.size + 1 ] == 0 );
#endif

    return TEST_RESULTS;
}

#endif
