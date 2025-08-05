
/* _PDCLIB_bigint_from_bigint( bigint_t *, bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <string.h>

#include "pdclib/_PDCLIB_internal.h"

void _PDCLIB_bigint_from_bigint( _PDCLIB_bigint_t * bigint, _PDCLIB_bigint_t const * other )
{
    bigint->size = other->size;
    memcpy( bigint->data, other->data, other->size * sizeof( _PDCLIB_bigint_digit_t ) );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    _PDCLIB_bigint_t bigint;
    _PDCLIB_bigint_t testdata[] =
    {
        /* Only 16bit, works with 32bit digits as well. */
        { 0, { 0u } },
        { 1, { 0xFFFFu } },
        { 2, { 0xAAAAu, 0xFFFFu } }
    };

    _PDCLIB_bigint_from_bigint( &bigint, &testdata[0] );
    TESTCASE( bigint.size == 0 );

    _PDCLIB_bigint_from_bigint( &bigint, &testdata[1] );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 0xFFFFu );

    _PDCLIB_bigint_from_bigint( &bigint, &testdata[2] );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[0] == 0xAAAAu );
    TESTCASE( bigint.data[1] == 0xFFFFu );

    return TEST_RESULTS;
}

#endif
