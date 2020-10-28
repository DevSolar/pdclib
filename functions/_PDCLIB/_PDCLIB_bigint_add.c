/* _PDCLIB_bigint_add( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_add( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    _PDCLIB_bigint_t const * smaller = ( lhs->size < rhs->size ) ? lhs : rhs;
    unsigned carry = 0;
    int i;

    for ( i = 0; i < smaller->size; ++i )
    {
        lhs->data[i] += rhs->data[i] + carry;
        carry = ( lhs->data[i] < rhs->data[i] );
    }

    if ( smaller == lhs )
    {
        for ( i = lhs->size; i < rhs->size; ++i )
        {
            lhs->data[i] += rhs->data[i] + carry;
            carry = ( lhs->data[i] < rhs->data[i] );
        }

        lhs->size = rhs->size;
    }
    else
    {
        for ( i = rhs->size; i < lhs->size; ++i )
        {
            lhs->data[i] += carry;
            carry = ( lhs->data[i] < carry );
        }
    }

    if ( carry )
    {
        lhs->data[ lhs->size++ ] = carry;
    }

    return lhs;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs, rhs;
    _PDCLIB_bigint32( &lhs, UINT32_C( 0 ) );
    _PDCLIB_bigint64( &rhs, UINT64_C( 0 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 0 );
    _PDCLIB_bigint32( &lhs, UINT32_C( 0x12345678 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 1 );
    TESTCASE( lhs.data[0] == 0x12345678 );
    _PDCLIB_bigint32( &rhs, UINT32_C( 0x11111111 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 1 );
    TESTCASE( lhs.data[0] == 0x23456789 );
    _PDCLIB_bigint64( &rhs, UINT64_C( 0x00000001DCBA9877 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 2 );
    TESTCASE( lhs.data[0] == 0x00000000 );
    TESTCASE( lhs.data[1] == 0x00000002 );
    _PDCLIB_bigint32( &lhs, UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint32( &rhs, UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 2 );
    TESTCASE( lhs.data[0] == 0xFFFFFFFE );
    TESTCASE( lhs.data[1] == 0x00000001 );
#endif
    return TEST_RESULTS;
}

#endif
