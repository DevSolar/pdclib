/* _PDCLIB_bigint_mul_pow10( bigint_t *, int pow10 )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

void _PDCLIB_bigint_mul_pow10( _PDCLIB_bigint_t * bigint, int pow10 )
{
    _PDCLIB_bigint_t multiplier;
    _PDCLIB_bigint_from_pow10( &multiplier, pow10 );
    _PDCLIB_bigint_mul( bigint, &multiplier );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
