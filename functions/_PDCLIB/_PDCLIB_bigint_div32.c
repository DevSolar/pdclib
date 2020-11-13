/* _PDCLIB_bigint_div32( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const *, uint_least32_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_div32( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, uint_least32_t rhs )
{
    unsigned i;
    uint_least32_t digit;
    uint_least64_t carry = 0;
    uint_least64_t base = UINT64_C(1)<<32;

    for ( i = lhs->size; i > 0; --i )
    {
        digit = lhs->data[ i - 1 ];
        lhs->data[ i - 1 ] = (uint_least32_t)( ( carry * base + digit ) / rhs );
        carry = ( base + digit ) - lhs->data[ i - 1 ] * rhs;
    }

    while ( lhs->size > 0 && lhs->data[ lhs->size - 1 ] == 0 )
    {
        --lhs->size;
    }

    return lhs;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs;
    _PDCLIB_bigint32( &lhs, 1 );
    _PDCLIB_bigint_div32( &lhs, 2 );
    TESTCASE( lhs.size == 0 );
    _PDCLIB_bigint32( &lhs, 2 );
    _PDCLIB_bigint_div32( &lhs, 2 );
    TESTCASE( lhs.size == 1 );
    TESTCASE( lhs.data[0] == 1 );
    _PDCLIB_bigint64( &lhs, UINT64_C( 0x0000000100000000 ) );
    _PDCLIB_bigint_div32( &lhs, 2 );
    TESTCASE( lhs.size == 1 );
    TESTCASE( lhs.data[0] == UINT32_C( 0x80000000 ) );
    _PDCLIB_bigint64( &lhs, UINT64_C( 0x0000000200000000 ) );
    _PDCLIB_bigint_div32( &lhs, 2 );
    TESTCASE( lhs.data[0] == 0 );
    TESTCASE( lhs.data[1] == 1 );
    TESTCASE( lhs.size == 2 );
#endif
    return TEST_RESULTS;
}

#endif
