/* _PDCLIB_bigint_from_pow2( bigint_t *, unsigned )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdlib.h>

void _PDCLIB_bigint_from_pow2( _PDCLIB_bigint_t * bigint, unsigned pow )
{
    ldiv_t dv = ldiv( pow, _PDCLIB_BIGINT_DIGIT_BITS );
    long i;

    for ( i = 0; i < dv.quot; ++i )
    {
        bigint->data[i] = 0;
    }

    bigint->data[i] = 1u << dv.rem;
    bigint->size = i + 1;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t bigint;

    _PDCLIB_bigint_from_pow2( &bigint, 0 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 1 );

    _PDCLIB_bigint_from_pow2( &bigint, 1 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 2 );

    _PDCLIB_bigint_from_pow2( &bigint, 2 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 4 );
#endif

    return TEST_RESULTS;
}

#endif
