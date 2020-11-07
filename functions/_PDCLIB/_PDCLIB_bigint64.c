/* _PDCLIB_bigint64( _PDCLIB_bigint_t *, uint_least64_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint64( _PDCLIB_bigint_t * bigint, uint_least64_t value )
{
    if ( value == UINT64_C( 0 ) )
    {
        bigint->size = 0;
        return bigint;
    }

    bigint->data[0] = (uint_least32_t)( value & UINT32_C( 0xFFFFFFFF ) );

    if ( ( bigint->data[1] = (uint_least32_t)( value >> 32 ) ) > 0 )
    {
        bigint->size = 2;
    }
    else
    {
        bigint->size = 1;
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
    _PDCLIB_bigint64( &big, 0 );
    TESTCASE( big.size == 0 );
    _PDCLIB_bigint64( &big, UINT64_C( 0x12345678 ) );
    TESTCASE( big.size == 1 );
    TESTCASE( big.data[0] == UINT32_C( 0x12345678 ) );
    _PDCLIB_bigint64( &big, UINT64_C( 0x1234567890abcdef ) );
    TESTCASE( big.size == 2 );
    TESTCASE( big.data[0] == UINT32_C( 0x90abcdef ) );
    TESTCASE( big.data[1] == UINT32_C( 0x12345678 ) );
#endif
    return TEST_RESULTS;
}

#endif
