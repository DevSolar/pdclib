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

    _PDCLIB_bigint32( result, 1 );
    _PDCLIB_bigint32( base, 10 );

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
    _PDCLIB_bigint_t big, expected;
    _PDCLIB_bigint10( &big, 0 );
    _PDCLIB_bigint32( &expected, 1 );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint10( &big, 1 );
    _PDCLIB_bigint32( &expected, 10 );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint10( &big, 9 );
    _PDCLIB_bigint32( &expected, UINT32_C( 1000000000 ) );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint10( &big, 17 );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x01634578 ), UINT32_C( 0x5d8a0000 ) );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint10( &big, 18 );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x0de0b6b3 ), UINT32_C( 0xa7640000 ) );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
