/* _PDCLIB_bigint_mul( bigint_t *, bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdio.h>

void _PDCLIB_bigint_mul( _PDCLIB_bigint_t * bigint, _PDCLIB_bigint_t const * other )
{
    _PDCLIB_size_t s = other->size;
    _PDCLIB_size_t b = bigint->size;

    if ( s == 0 || b == 0 )
    {
        _PDCLIB_bigint_from_digit( bigint, 0 );
        return;
    }

    {
        _PDCLIB_bigint_t result = { s + b, { 0 } };
        _PDCLIB_bigint_t const * small;
        _PDCLIB_bigint_t const * big;

        if ( s <= b )
        {
            small = other;
            big = bigint;
        }
        else
        {
            small = bigint;
            big = other;
        }

        for ( s = 0; s < small->size; ++s )
        {
            _PDCLIB_bigint_arith_t t = 0;

            for ( b = 0; b < big->size; ++b )
            {
                t += result.data[ s + b ]
                    + (_PDCLIB_bigint_arith_t)small->data[ s ]
                    * (_PDCLIB_bigint_arith_t)big->data[ b ];
                result.data[ s + b ] = t & ( ( (_PDCLIB_bigint_arith_t)1u << _PDCLIB_BIGINT_DIGIT_BITS ) - 1 );
                t >>= _PDCLIB_BIGINT_DIGIT_BITS;
            }

            result.data[ s + b ] = t & ( ( (_PDCLIB_bigint_arith_t)1u << _PDCLIB_BIGINT_DIGIT_BITS ) - 1 );
        }

        while ( result.data[ result.size - 1 ] == 0 )
        {
            --result.size;
        }

        _PDCLIB_bigint_from_bigint( bigint, &result );
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
        { 1, { 0x0002u } },
        { 1, ( (_PDCLIB_bigint_arith_t)1u << _PDCLIB_BIGINT_DIGIT_BITS) - 1 },
        { 2, { ( (_PDCLIB_bigint_arith_t)1u << _PDCLIB_BIGINT_DIGIT_BITS) - 1, 1u } }
    };

    _PDCLIB_bigint_from_bigint( &bigint, &testdata[0] );
    _PDCLIB_bigint_mul( &bigint, &testdata[0] );

    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 1u );

    _PDCLIB_bigint_mul( &bigint, &testdata[1] );

    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 2u );

    _PDCLIB_bigint_mul( &bigint, &testdata[2] );

    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[0] == ( (_PDCLIB_bigint_arith_t)1u << _PDCLIB_BIGINT_DIGIT_BITS) - 2 );
    TESTCASE( bigint.data[1] == 1u );

    _PDCLIB_bigint_mul( &bigint, &testdata[1] );

    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[0] == ( (_PDCLIB_bigint_arith_t)1u << _PDCLIB_BIGINT_DIGIT_BITS) - 4 );
    TESTCASE( bigint.data[1] == 3u );

    _PDCLIB_bigint_from_bigint( &bigint, &testdata[3] );
    _PDCLIB_bigint_mul( &bigint, &bigint );

    TESTCASE( bigint.data[0] == 1 );
    TESTCASE( bigint.data[1] == ( (_PDCLIB_bigint_arith_t)1u << _PDCLIB_BIGINT_DIGIT_BITS) - 4 );

#if _PDCLIB_BIGINT_DIGIT_BITS == 16
    TESTCASE( bigint.size == 3 );
    TESTCASE( bigint.data[2] == 3 );
#else
    TESTCASE( bigint.size == 2 );
#endif
#endif

    return TEST_RESULTS;
}

#endif
