/* _PDCLIB_bigint( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

_PDCLIB_bigint_t * _PDCLIB_bigint( _PDCLIB_bigint_t * _PDCLIB_restrict bigint, _PDCLIB_bigint_t const * _PDCLIB_restrict value )
{
    for ( bigint->size = 0; bigint->size < value->size; ++bigint->size )
    {
        bigint->data[ bigint->size ] = value->data[ bigint->size ];
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
    _PDCLIB_bigint_t other;
    _PDCLIB_bigint32( &other, UINT32_C( 0x12345678 ) );
    _PDCLIB_bigint( &big, &other );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &other ) == 0 );
    _PDCLIB_bigint64( &other, UINT32_C( 0x12345678 ), UINT32_C( 0x90abcdef ) );
    _PDCLIB_bigint( &big, &other );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &other ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
