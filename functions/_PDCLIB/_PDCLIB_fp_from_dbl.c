/* _PDCLIB_fp_from_dbl( _PDCLIB_fp_t *, double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <stdlib.h>
#include <string.h>

void _PDCLIB_fp_from_dbl( _PDCLIB_fp_t * fp, double d )
{
    memcpy( fp->mantissa.data, &d, sizeof( double ) );

    fp->sign = _PDCLIB_DBL_SIGN( fp->mantissa.data );
    fp->exponent = _PDCLIB_DBL_EXP( fp->mantissa.data );
    fp->mantissa.size = _PDCLIB_DBL_SIZE( fp->mantissa.data );

    switch ( fp->exponent )
    {
        case 0:
            fp->state = _PDCLIB_FP_SUBNORMAL;
            fp->exponent = 1 - ( _PDCLIB_DBL_MAX_EXP - 1 );
            fp->scale = _PDCLIB_DBL_MANT_DIG - 1;
            break;
        case ( _PDCLIB_DBL_MAX_EXP - 1 ) + _PDCLIB_DBL_MAX_EXP:
            fp->state = _PDCLIB_FP_NAN;
            break;
        default:
        {
            div_t dv = div( _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_BIGINT_DIGIT_BITS );
            fp->state = _PDCLIB_FP_NORMAL;

            if ( dv.rem == 0 )
            {
                fp->mantissa.data[ fp->mantissa.size++ ] = 1u;
            }
            else
            {
                fp->mantissa.data[ dv.quot ] |= ( 1u << dv.rem );
            }

            fp->exponent -= ( _PDCLIB_DBL_MAX_EXP - 1 );
            fp->scale = _PDCLIB_DBL_MANT_DIG - 1;
            break;
        }
    }

    while ( fp->mantissa.size > 0 && fp->mantissa.data[ fp->mantissa.size - 1 ] == 0 )
    {
        --fp->mantissa.size;
    }

    if ( ( fp->state == _PDCLIB_FP_NAN ) && ( fp->mantissa.size == 0 ) )
    {
        fp->state = _PDCLIB_FP_INF;
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_fp_t fp;
    _PDCLIB_bigint_t t;

    /* Normal */
    _PDCLIB_fp_from_dbl( &fp, -1.0 );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_DBL_MANT_DIG - 1 );
    TESTCASE( fp.state == _PDCLIB_FP_NORMAL );
    TESTCASE( _PDCLIB_bigint_cmp( &fp.mantissa, &t ) == 0 );
    TESTCASE( fp.scale == ( _PDCLIB_DBL_MANT_DIG - 1 ) );
    TESTCASE( fp.exponent == 0 );

    /* Inf */
    _PDCLIB_fp_from_dbl( &fp, 1e500 );
    TESTCASE( fp.state == _PDCLIB_FP_INF );
    TESTCASE( fp.mantissa.size == 0 );

    /* NaN */
    _PDCLIB_fp_from_dbl( &fp, -0.0/0.0 );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_DBL_MANT_DIG - 2 );
    TESTCASE( fp.state == _PDCLIB_FP_NAN );
    TESTCASE( _PDCLIB_bigint_cmp( &fp.mantissa, &t ) == 0 );

    /* Subnormal */
    _PDCLIB_fp_from_dbl( &fp, _PDCLIB_DBL_MIN / 2 );
    _PDCLIB_bigint_from_pow2( &t, _PDCLIB_DBL_MANT_DIG - 2 );
    TESTCASE( fp.state == _PDCLIB_FP_SUBNORMAL );
    TESTCASE( _PDCLIB_bigint_cmp( &fp.mantissa, &t ) == 0 );
    TESTCASE( fp.scale == ( _PDCLIB_DBL_MANT_DIG - 1 ) );
    TESTCASE( fp.exponent == (_PDCLIB_int_least16_t)(1 - ( _PDCLIB_DBL_MAX_EXP - 1 ) ) );
#endif

    return TEST_RESULTS;
}

#endif
