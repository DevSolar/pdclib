/* _PDCLIB_bigint_mul( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stddef.h>
#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_mul( _PDCLIB_bigint_t * _PDCLIB_restrict result, _PDCLIB_bigint_t const * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    _PDCLIB_bigint_t const * smaller;
    _PDCLIB_bigint_t const * wider;
    size_t s, w;

    /* Largest possible result size */
    result->size = lhs->size + rhs->size;

    /* Zeroing result struct (where it matters) */
    for ( w = 0; w < result->size; ++w )
    {
        result->data[w] = 0;
    }

    /* Select smaller / wider number so we spend more time in the *inner* loop. */
    if ( lhs->size < rhs->size )
    {
        smaller = lhs;
        wider = rhs;
    }
    else
    {
        wider = lhs;
        smaller = rhs;
    }

    for ( s = 0; s < smaller->size; ++s )
    {
        _PDCLIB_bigint_arith_t digit;     /* Hold intermediary (wide) result. */
        _PDCLIB_bigint_arith_t carry = 0; /* Hold overflow. */

        for ( w = 0; w < wider->size; ++w )
        {
            /* Add product and carry into intermediate result */
            digit = result->data[ w + s ] + ( (_PDCLIB_bigint_arith_t)smaller->data[ s ] * (_PDCLIB_bigint_arith_t)wider->data[ w ] ) + carry;
            /* High bits into carry */
            carry = digit >> _PDCLIB_BIGINT_DIGIT_BITS;
            /* Low bits into result */
            result->data[ w + s ] = ( digit & _PDCLIB_BIGINT_DIGIT_MAX );
        }

        result->data[ w + s ] += carry;
    }

    /* Shrink result size back down if appropriate. */
    while ( ( result->size > 0 ) && ( result->data[ result->size - 1 ] == 0 ) )
    {
        --result->size;
    }

    return result;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs, rhs, result, expected;

    /* 0 x 0 = 0 */
    _PDCLIB_bigint32( &lhs, 0 );
    _PDCLIB_bigint32( &rhs, 0 );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 0 );

    /* 0 x 1 = 0 */
    _PDCLIB_bigint32( &rhs, 1 );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 0 );

    /* 2 x 1 = 2 */
    _PDCLIB_bigint32( &lhs, 2 );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    _PDCLIB_bigint32( &expected, 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &result, &expected ) == 0 );

    /* 2 x 10 = 20 */
    _PDCLIB_bigint64( &rhs, 1, 0 );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    _PDCLIB_bigint64( &expected, 2, 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &result, &expected ) == 0 );

    /* 2 x 5 = 10 */
    _PDCLIB_bigint32( &rhs, UINT32_C( 0x80000000 ) );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    _PDCLIB_bigint64( &expected, 1, 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &result, &expected ) == 0 );

    /* 11 x 10 = 110 */
    _PDCLIB_bigint( &rhs, &result );
    _PDCLIB_bigint( &lhs, &result );
    lhs.data[0] = 1;
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    _PDCLIB_bigint64( &expected, 1, 1 );
    _PDCLIB_bigint_shl( &expected, 32 );
    TESTCASE( _PDCLIB_bigint_cmp( &result, &expected ) == 0 );

    /* 111 x 9 = 999 */
    _PDCLIB_bigint( &lhs, &result );
    lhs.data[0] = 1;
    _PDCLIB_bigint32( &rhs, UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    _PDCLIB_bigint64( &expected, UINT32_C( 0xFFFFFFFF ), UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint_shl( &expected, 32 );
    _PDCLIB_bigint_add( &expected, &rhs );
    TESTCASE( _PDCLIB_bigint_cmp( &result, &expected ) == 0 );

    /* 999 x 999 = 998001 */
    _PDCLIB_bigint( &rhs, &result );
    _PDCLIB_bigint( &lhs, &result );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    --expected.data[0];
    _PDCLIB_bigint_shl( &expected, 96 );
    expected.data[0] = 1;
    TESTCASE( _PDCLIB_bigint_cmp( &result, &expected ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
