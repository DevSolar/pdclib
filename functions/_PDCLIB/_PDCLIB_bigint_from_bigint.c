
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
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
