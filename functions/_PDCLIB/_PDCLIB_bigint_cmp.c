/* _PDCLIB_bigint_cmp( _PDCLIB_bigint_t const *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

int _PDCLIB_bigint_cmp( _PDCLIB_bigint_t const * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    int i;

    if ( lhs->size != rhs->size )
    {
        return lhs->size - rhs->size;
    }

    for ( i = lhs->size - 1; i >= 0; --i )
    {
        if ( lhs->data[i] != rhs->data[i] )
        {
            return lhs->data[i] - rhs->data[i];
        }
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdint.h>

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs, rhs;
    _PDCLIB_bigint32( &lhs, 0 );
    _PDCLIB_bigint64( &rhs, 0, 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) == 0 );
    _PDCLIB_bigint32( &lhs, 1 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) > 0 );
    _PDCLIB_bigint32( &rhs, UINT32_C( 0x8000000 ) );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) < 0 );
    _PDCLIB_bigint64( &lhs, 0, 1 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) < 0 );
    _PDCLIB_bigint64( &lhs, 1, UINT32_C( 0x80000000 ) );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) > 0 );
#endif
    return TEST_RESULTS;
}

#endif
