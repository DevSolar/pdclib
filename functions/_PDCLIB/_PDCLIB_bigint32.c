/* _PDCLIB_bigint32( _PDCLIB_bigint_t *, uint_least32_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

#define DIGITS_PER_32BIT ( 32 / _PDCLIB_BIGINT_DIGIT_BITS )

_PDCLIB_bigint_t * _PDCLIB_bigint32( _PDCLIB_bigint_t * bigint, uint_least32_t value )
{
    for ( bigint->size = 0; bigint->size < DIGITS_PER_32BIT; ++bigint->size )
    {
        bigint->data[ bigint->size ] = value & _PDCLIB_BIGINT_DIGIT_MAX;
#if _PDCLIB_BIGINT_DIGIT_BITS < 32
        value >>= _PDCLIB_BIGINT_DIGIT_BITS;
#endif
    }

    while ( bigint->size > 0 && bigint->data[ bigint->size - 1 ] == 0 )
    {
        --bigint->size;
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
    uint_least32_t value;
    unsigned n;

    for ( n = 0; n < 32; ++n )
    {
        value = UINT32_C( 1 ) << n;
        _PDCLIB_bigint32( &big, value );
        TESTCASE( big.size == n / _PDCLIB_BIGINT_DIGIT_BITS + 1 );
    }
#endif

    return TEST_RESULTS;
}

#endif
