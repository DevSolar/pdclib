/* _PDCLIB_bigint_from_digit( bigint_t *, digit_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

void _PDCLIB_bigint_from_digit( _PDCLIB_bigint_t * bigint, _PDCLIB_bigint_digit_t digit )
{
    bigint->size = ( digit > 0 );
    bigint->data[0] = digit;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t bigint;

    _PDCLIB_bigint_from_digit( &bigint, 0 );
    TESTCASE( bigint.size == 0 );

    _PDCLIB_bigint_from_digit( &bigint, 1 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 1 );

    _PDCLIB_bigint_from_digit( &bigint, _PDCLIB_BIGINT_DIGIT_MAX );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == _PDCLIB_BIGINT_DIGIT_MAX );
#endif

    return TEST_RESULTS;
}

#endif
