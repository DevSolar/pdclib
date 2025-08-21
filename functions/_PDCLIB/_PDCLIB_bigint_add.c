/* _PDCLIB_bigint_add( bigint_t *, bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

void _PDCLIB_bigint_add( _PDCLIB_bigint_t * bigint, _PDCLIB_bigint_t const * other )
{
    unsigned i = 0;
    _PDCLIB_bigint_arith_t arith = 0;

    for ( i = bigint->size; i < other->size; ++i )
    {
        bigint->data[i] = 0;
    }

    bigint->size = i;

    for ( i = 0; i < bigint->size; ++i )
    {
        arith += bigint->data[i] + other->data[i];
        bigint->data[i] = arith & ( ( (_PDCLIB_bigint_arith_t)1 << _PDCLIB_BIGINT_DIGIT_BITS ) - 1 );
        arith >>= _PDCLIB_BIGINT_DIGIT_BITS;
    }

    if ( arith > 0 )
    {
        bigint->data[i] = arith;
        --(bigint->size);
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
        { 1, { 0x0001u } },
        { 2, { (_PDCLIB_bigint_digit_t)( ( (_PDCLIB_bigint_arith_t)1 << _PDCLIB_BIGINT_DIGIT_BITS ) - 1 ), 0x0001u } },
        { 1, { 0x0002u } },
        { 2, { 0x0001u, 0x0002u } },
        { 2, { 0x0000u, 0x0002u } }
    };

    /* 1 + 1 */
    _PDCLIB_bigint_from_digit( &bigint, 1 );
    _PDCLIB_bigint_add( &bigint, &bigint );
    _PDCLIB_bigint_cmp( &bigint, &testdata[2] );

    /* 1 + 0x0001 0xFFFF -- carry */
    _PDCLIB_bigint_add( &bigint, &testdata[1] );
    _PDCLIB_bigint_cmp( &bigint, &testdata[3] );

    /* 0x0001 0xFFFF + 1 -- carry */
    _PDCLIB_bigint_from_bigint( &bigint, &testdata[1] );
    _PDCLIB_bigint_add( &bigint, &testdata[0] );
    _PDCLIB_bigint_cmp( &bigint, &testdata[4] );

    /* 0 + 0 */
    _PDCLIB_bigint_from_digit( &bigint, 0 );
    _PDCLIB_bigint_add( &bigint, &bigint );
    TESTCASE( bigint.size == 0 );

    /* 0 + 1 */
    _PDCLIB_bigint_add( &bigint, &testdata[0] );
    _PDCLIB_bigint_cmp( &bigint, &testdata[0] );
#endif

    return TEST_RESULTS;
}

#endif
