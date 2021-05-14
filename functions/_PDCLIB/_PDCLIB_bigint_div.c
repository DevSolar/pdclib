/* _PDCLIB_bigint_div( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stddef.h>
#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_div( _PDCLIB_bigint_t * _PDCLIB_restrict result, _PDCLIB_bigint_t const * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    return NULL;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
#endif
    return TEST_RESULTS;
}

#endif
