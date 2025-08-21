/* _PDCLIB_bigint_mul10( bigint_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

void _PDCLIB_bigint_mul10( _PDCLIB_bigint_t * bigint )
{
    _PDCLIB_bigint_arith_t t = 0;
    _PDCLIB_size_t i;

    for ( i = 0; i < bigint->size; ++i )
    {
        t = (_PDCLIB_bigint_arith_t)bigint->data[ i ] * 10 + t;
        bigint->data[ i ] = t & _PDCLIB_BIGINT_DIGIT_MAX;
        t >>= _PDCLIB_BIGINT_DIGIT_BITS;
    }

    if ( t > 0 )
    {
        bigint->data[ bigint->size++ ] = t;
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t bigint;
    _PDCLIB_bigint_t testdata[] =
    {
        { 2, { 0x8080u, 0x0101u } },
        { 2, { 0x0500u, 0x0a0fu } },
        { 1, { 0x000au } }
    };

    _PDCLIB_bigint_from_digit( &bigint, 1 );
    _PDCLIB_bigint_mul10( &bigint );
    TESTCASE( _PDCLIB_bigint_cmp( &bigint, &testdata[2] ) == 0 );

    _PDCLIB_bigint_from_bigint( &bigint, &testdata[0] );
    _PDCLIB_bigint_mul10( &bigint );
    TESTCASE( _PDCLIB_bigint_cmp( &bigint, &testdata[1] ) == 0 );
#endif

    return TEST_RESULTS;
}

#endif
