/* _PDCLIB_bigint_add( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_add( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    _PDCLIB_bigint_t const * smaller;
    _PDCLIB_bigint_t const * wider;
    unsigned carry = 0;
    unsigned newcarry;
    int i;

    if ( lhs->size < rhs->size )
    {
        smaller = lhs;
        wider = rhs;
    }
    else
    {
        smaller = rhs;
        wider = lhs;
    }

    /* Add up the bigints digit by digit, ensuring no overflow of 32-bit range */
    for ( i = 0; i < smaller->size; ++i )
    {
        uint_least32_t l = ( UINT32_C( 0xFFFFFFFF ) - lhs->data[i] );
        uint_least32_t r = ( UINT32_C( 0xFFFFFFFF ) - rhs->data[i] );

        if ( ( newcarry = ( l < rhs->data[i] ) || ( carry && ( l == rhs->data[i] ) ) ) )
        {
            lhs->data[i] = UINT32_C( 0xFFFFFFFF ) - ( l + r ) - 1 + carry;
        }
        else
        {
            lhs->data[i] = lhs->data[i] + rhs->data[i] + carry;
        }

        carry = newcarry;
    }

    for ( ; i < wider->size; ++i )
    {
        if ( ( newcarry = ( ( UINT32_C( 0xFFFFFFFF ) - wider->data[i] ) < carry ) ) )
        {
            lhs->data[i] = 0;
        }
        else
        {
            lhs->data[i] = wider->data[i] + carry;
        }

        carry = newcarry;
    }

    /* Possible new digit */
    if ( carry )
    {
        lhs->data[i++] = carry;
    }

    lhs->size = i;

    return lhs;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs, rhs;
    _PDCLIB_bigint32( &lhs, 0 );
    _PDCLIB_bigint64( &rhs, 0 );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 0 );
    _PDCLIB_bigint32( &lhs, UINT32_C( 0x12345678 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 1 );
    TESTCASE( lhs.data[0] == UINT32_C( 0x12345678 ) );
    _PDCLIB_bigint32( &rhs, UINT32_C( 0x11111111 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 1 );
    TESTCASE( lhs.data[0] == UINT32_C( 0x23456789 ) );
    _PDCLIB_bigint64( &rhs, UINT64_C( 0x00000001DCBA9877 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 2 );
    TESTCASE( lhs.data[0] == 0 );
    TESTCASE( lhs.data[1] == 2 );
    _PDCLIB_bigint32( &lhs, UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint32( &rhs, UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 2 );
    TESTCASE( lhs.data[0] == UINT32_C( 0xFFFFFFFE ) );
    TESTCASE( lhs.data[1] == 1 );
#endif
    return TEST_RESULTS;
}

#endif
