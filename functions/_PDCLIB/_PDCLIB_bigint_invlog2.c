/* _PDCLIB_bigint_invlog2( _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

unsigned _PDCLIB_bigint_invlog2( _PDCLIB_bigint_t const * bigint )
{
    static int const lookup[] =
    {
       32,  0,  1, 26,  2, 23, 27,  0,  3, 16, 24, 30, 28, 11,  0, 13,
        4,  7, 17,  0, 25, 22, 31, 15, 29, 10, 12,  6,  0, 21, 14,  9,
        5, 20,  8, 19, 18
    };

    unsigned i;
    unsigned zeroes = 0;

    for ( i = 0; i < bigint->size; ++i )
    {
        if ( bigint->data[ i ] == 0 )
        {
            zeroes += _PDCLIB_BIGINT_DIGIT_BITS;
        }
        else
        {
            return zeroes + ( lookup[ ( -bigint->data[ i ] & bigint->data[ i ] ) % 37 ] );
        }
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdint.h>

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t big;
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000000 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 0 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000001 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 0 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000002 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 1 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000004 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 2 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000008 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 3 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000010 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 4 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000020 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 5 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000040 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 6 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x00000080 ) );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 7 );
    _PDCLIB_bigint64( &big, UINT32_C( 0x00000080 ), 0 );
    TESTCASE( _PDCLIB_bigint_invlog2( &big ) == 39 );
#endif
    return TEST_RESULTS;
}

#endif
