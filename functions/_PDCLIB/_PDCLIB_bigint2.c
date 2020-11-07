/* _PDCLIB_bigint2( _PDCLIB_bigint_t *, unsigned )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

_PDCLIB_bigint_t * _PDCLIB_bigint2( _PDCLIB_bigint_t * bigint, unsigned n )
{
    int i;

    bigint->size = ( n / 32 ) + 1;
    bigint->data[ bigint->size - 1 ] = 1 << ( n - ( bigint->size - 1 ) * 32 );

    for ( i = 0; i < bigint->size - 1; ++i )
    {
        bigint->data[ i ] = 0;
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
    _PDCLIB_bigint_t * bigptr;
    bigptr = _PDCLIB_bigint2( &big, 0 );
    TESTCASE( bigptr == &big );
    TESTCASE( big.size == 1 );
    TESTCASE( big.data[0] == 1 );
    _PDCLIB_bigint2( &big, 3 );
    TESTCASE( big.size == 1 );
    TESTCASE( big.data[0] == 8 );
    _PDCLIB_bigint2( &big, 31 );
    TESTCASE( big.size == 1 );
    TESTCASE( big.data[0] == UINT32_C( 0x80000000 ) );
    _PDCLIB_bigint2( &big, 32 );
    TESTCASE( big.size == 2 );
    TESTCASE( big.data[0] == 0 );
    TESTCASE( big.data[1] == 1 );
    _PDCLIB_bigint2( &big, 34 );
    TESTCASE( big.size == 2 );
    TESTCASE( big.data[0] == 0 );
    TESTCASE( big.data[1] == 4 );
    _PDCLIB_bigint2( &big, 63 );
    TESTCASE( big.size == 2 );
    TESTCASE( big.data[0] == 0 );
    TESTCASE( big.data[1] == UINT32_C( 0x80000000 ) );
    _PDCLIB_bigint2( &big, 64 );
    TESTCASE( big.size == 3 );
    TESTCASE( big.data[0] == 0 );
    TESTCASE( big.data[1] == 0 );
    TESTCASE( big.data[2] == 1 );
#endif
    return TEST_RESULTS;
}

#endif
