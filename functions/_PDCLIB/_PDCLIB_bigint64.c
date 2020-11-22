/* _PDCLIB_bigint64( _PDCLIB_bigint_t *, uint_least32_t, uint_least32_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint64( _PDCLIB_bigint_t * bigint, uint_least32_t high, uint_least32_t low )
{
#if _PDCLIB_BIGINT_DIGIT_BITS == 32
    bigint->data[0] = low;
    bigint->data[1] = high;

    bigint->size = 2;
#else
    bigint->data[0] = low & _PDCLIB_BIGINT_DIGIT_MAX;
    bigint->data[1] = low >> _PDCLIB_BIGINT_DIGIT_BITS;
    bigint->data[2] = high & _PDCLIB_BIGINT_DIGIT_MAX;
    bigint->data[3] = high >> _PDCLIB_BIGINT_DIGIT_BITS;

    bigint->size = 4;
#endif

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
    /* No testdriver; used extensively in other tests. */
    return TEST_RESULTS;
}

#endif
