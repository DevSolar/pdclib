/* _PDCLIB_bigint_mul32( _PDCLIB_bigint_t *, uint_least32_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_mul32( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, uint_least32_t rhs )
{
    uint_least64_t digit;     /* Hold intermediary (wide) result. */
    uint_least32_t carry = 0; /* Hold overflow. */
    int i;

    for ( i = 0; i < lhs->size; ++i )
    {
        /* Add product and carry into intermediate result */
        digit = (uint_least64_t)lhs->data[ i ] * (uint_least64_t)rhs + carry;
        /* Get 32bit carry */
        carry = digit >> 32;
        /* Write lower 32bit back into bigint */
        lhs->data[ i ] = ( digit & UINT32_C( 0xFFFFFFFF ) );
    }

    if ( carry > 0 )
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
    _PDCLIB_bigint_t lhs;
    _PDCLIB_bigint32( &lhs, 0 );
    _PDCLIB_bigint_mul32( &lhs, 0 );
    TESTCASE( lhs.size == 0 );
    _PDCLIB_bigint_mul32( &lhs, 1 );
    TESTCASE( lhs.size == 0 );
    _PDCLIB_bigint32( &lhs, 2 );
    _PDCLIB_bigint_mul32( &lhs, 1 );
    TESTCASE( lhs.size == 1 );
    TESTCASE( lhs.data[0] == 2 );
    _PDCLIB_bigint64( &lhs, UINT64_C( 0x100000000 ) );
    _PDCLIB_bigint_mul32( &lhs, 2 );
    TESTCASE( lhs.size == 2 );
    TESTCASE( lhs.data[0] == 0 );
    TESTCASE( lhs.data[1] == 2 );
    _PDCLIB_bigint_mul32( &lhs, UINT32_C( 0x80000000 ) );
    TESTCASE( lhs.size == 3 );
    TESTCASE( lhs.data[0] == 0 );
    TESTCASE( lhs.data[1] == 0 );
    TESTCASE( lhs.data[2] == 1 );
#endif
    return TEST_RESULTS;
}

#endif
