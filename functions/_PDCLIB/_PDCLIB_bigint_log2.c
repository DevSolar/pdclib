/* _PDCLIB_bigint_log2( _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

unsigned _PDCLIB_bigint_log2( _PDCLIB_bigint_t const * bigint )
{
    /* DeBruijn lookup, courtesy of
       https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogDeBruijn
    */
    static int const lookup[] =
    {
        0,  9,  1, 10, 13, 21,  2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24,  7, 19, 27, 23,  6, 26,  5, 4, 31
    };

    uint_least32_t value;

    if ( bigint->size == 0 )
    {
        return 0;
    }

    value = bigint->data[ bigint->size - 1 ];

    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;

    return lookup[ ( value * UINT32_C( 0x07C4ACDD ) ) >> 27 ] + ( bigint->size - 1 ) * _PDCLIB_BIGINT_DIGIT_BITS;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdint.h>

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t big;
    _PDCLIB_bigint2( &big, 0 );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 0 );
    _PDCLIB_bigint2( &big, 1 );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 1 );
    _PDCLIB_bigint2( &big, 31 );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 31 );
    _PDCLIB_bigint2( &big, 32 );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 32 );
    _PDCLIB_bigint2( &big, 63 );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 63 );
    _PDCLIB_bigint2( &big, 64 );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 64 );
    _PDCLIB_bigint32( &big, UINT32_C( 0xFFFFFFFF ) );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 31 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x87654321 ) );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 31 );
    _PDCLIB_bigint64( &big, UINT32_C( 0xFFFFFFFF ), UINT32_C( 0xFFFFFFFF ) );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 63 );
    _PDCLIB_bigint64( &big, UINT32_C( 0xfedcba90 ), UINT32_C( 0x87654321 ) );
    TESTCASE( _PDCLIB_bigint_log2( &big ) == 63 );
#endif
    return TEST_RESULTS;
}

#endif
