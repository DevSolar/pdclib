/* _PDCLIB_bigint_mul( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_mul( _PDCLIB_bigint_t * _PDCLIB_restrict result, _PDCLIB_bigint_t const * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    _PDCLIB_bigint_t const * smaller;
    _PDCLIB_bigint_t const * wider;
    int s, w;

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
        uint_least64_t digit;     /* Hold intermediary (wide) result. */
        uint_least32_t carry = 0; /* Hold overflow. */

        for ( w = 0; w < wider->size; ++w )
        {
            /* Add product and carry into intermediate result */
            digit = result->data[ w + s ] + ( (uint_least64_t)smaller->data[ s ] * (uint_least64_t)wider->data[ w ] ) + carry;
            /* Get 32bit carry */
            carry = digit >> 32;
            /* Write lower 32bit back into result */
            result->data[ w + s ] = ( digit & UINT32_C( 0xFFFFFFFF ) );
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
    _PDCLIB_bigint_t lhs, rhs, result;
    _PDCLIB_bigint32( &lhs, 0 );
    _PDCLIB_bigint32( &rhs, 0 );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 0 );
    _PDCLIB_bigint32( &rhs, 1 );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 0 );
    _PDCLIB_bigint32( &lhs, 2 );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 1 );
    TESTCASE( result.data[0] == 2 );
    _PDCLIB_bigint64( &rhs, UINT64_C( 0x100000000 ) );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 2 );
    TESTCASE( result.data[0] == 0 );
    TESTCASE( result.data[1] == 2 );
    _PDCLIB_bigint32( &rhs, UINT32_C( 0x80000000 ) );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 2 );
    TESTCASE( result.data[0] == 0 );
    TESTCASE( result.data[1] == 1 );
    _PDCLIB_bigint( &rhs, &result );
    _PDCLIB_bigint( &lhs, &result );
    lhs.data[0] = 1;
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 3 );
    TESTCASE( result.data[0] == 0 );
    TESTCASE( result.data[1] == 1 );
    TESTCASE( result.data[2] == 1 );
    _PDCLIB_bigint( &lhs, &result );
    lhs.data[0] = 1;
    _PDCLIB_bigint32( &rhs, UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 3 );
    TESTCASE( result.data[0] == UINT32_C( 0xFFFFFFFF ) );
    TESTCASE( result.data[1] == UINT32_C( 0xFFFFFFFF ) );
    TESTCASE( result.data[2] == UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint( &rhs, &result );
    _PDCLIB_bigint( &lhs, &result );
    _PDCLIB_bigint_mul( &result, &lhs, &rhs );
    TESTCASE( result.size == 6 );
    TESTCASE( result.data[0] == 1 );
    TESTCASE( result.data[1] == 0 );
    TESTCASE( result.data[2] == 0 );
    TESTCASE( result.data[3] == UINT32_C( 0xFFFFFFFE ) );
    TESTCASE( result.data[4] == UINT32_C( 0xFFFFFFFF ) );
    TESTCASE( result.data[5] == UINT32_C( 0xFFFFFFFF ) );
#endif
    return TEST_RESULTS;
}

#endif
