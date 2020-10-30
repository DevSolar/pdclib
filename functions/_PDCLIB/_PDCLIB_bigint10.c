/* _PDCLIB_bigint10( _PDCLIB_bigint_t *, unsigned )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint10( _PDCLIB_bigint_t * bigint, unsigned n )
{
    _PDCLIB_bigint_t local1, local2;

    _PDCLIB_bigint_t * tmp = &local1;
    _PDCLIB_bigint_t * base = &local2;
    _PDCLIB_bigint_t * result = bigint;
    _PDCLIB_bigint_t * swap;

    _PDCLIB_bigint32( result, UINT32_C( 1 ) );
    _PDCLIB_bigint32( base, UINT32_C( 10 ) );

    while ( n > 0 )
    {
        if ( n & 1 )
        {
            _PDCLIB_bigint_mul( tmp, result, base );
            swap = result; result = tmp; tmp = swap;
        }

        n >>= 1;
        _PDCLIB_bigint_mul( tmp, base, base );
        swap = base; base = tmp; tmp = swap;
    }

    if ( result != bigint )
    {
        _PDCLIB_bigint( bigint, result );
    }

    return bigint;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdint.h>

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t big;
    _PDCLIB_bigint10( &big, 0 );
    TESTCASE( big.size == 1 );
    TESTCASE( big.data[0] == 1 );
    _PDCLIB_bigint10( &big, 1 );
    TESTCASE( big.size == 1 );
    TESTCASE( big.data[0] == 10 );
    _PDCLIB_bigint10( &big, 9 );
    TESTCASE( big.size == 1 );
    TESTCASE( big.data[0] == UINT32_C( 1000000000 ) );
    _PDCLIB_bigint10( &big, 17 );
    TESTCASE( big.size == 2 );
    TESTCASE( big.data[0] == UINT32_C( 0x5d8a0000 ) );
    TESTCASE( big.data[1] == UINT32_C( 0x01634578 ) );
    _PDCLIB_bigint10( &big, 18 );
    TESTCASE( big.size == 2 );
    TESTCASE( big.data[0] == UINT32_C( 0xa7640000 ) );
    TESTCASE( big.data[1] == UINT32_C( 0x0de0b6b3 ) );
#endif
    return TEST_RESULTS;
}

#endif
