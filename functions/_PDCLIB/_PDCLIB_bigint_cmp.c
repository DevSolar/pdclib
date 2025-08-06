/* _PDCLIB_bigint_cmp( bigint_t const *, bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

int _PDCLIB_bigint_cmp( _PDCLIB_bigint_t const * lhs, _PDCLIB_bigint_t const * rhs )
{
    _PDCLIB_size_t i = lhs->size;

    if ( i != rhs->size )
    {
        return i > rhs->size ? 1 : -1;
    }

    while ( i-- > 0 )
    {
        if ( lhs->data[i] != rhs->data[i] )
        {
            return lhs->data[i] > rhs->data[i] ? 1 : -1;
        }
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs, rhs;
    _PDCLIB_bigint_t testdata[] =
    {
        { 2, { 0, 0x0001u } },
        { 1, { 1 } }
    };

    _PDCLIB_bigint_from_digit( &lhs, 0 );
    _PDCLIB_bigint_from_digit( &rhs, 0 );

    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) == 0 );

    _PDCLIB_bigint_add( &lhs, &testdata[1] );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) > 0 );

    _PDCLIB_bigint_add( &rhs, &testdata[1] );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) == 0 );

    _PDCLIB_bigint_add( &rhs, &testdata[1] );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) < 0 );

    _PDCLIB_bigint_from_bigint( &lhs, &testdata[0] );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) > 0 );

    _PDCLIB_bigint_from_bigint( &rhs, &testdata[0] );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) == 0 );

    _PDCLIB_bigint_add( &rhs, &testdata[1] );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &rhs ) < 0 );
#endif

    return TEST_RESULTS;
}

#endif
