/* _PDCLIB_bigint_log2( bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

int _PDCLIB_bigint_log2( _PDCLIB_bigint_t const * bigint )
{
    _PDCLIB_size_t s = bigint->size;

    if ( s == 0 )
    {
        return -1;
    }

    --s;

    return _PDCLIB_bigint_digit_log2( bigint->data[ s ] ) + s * _PDCLIB_BIGINT_DIGIT_BITS;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t bigint;
    _PDCLIB_bigint_t one;
    _PDCLIB_bigint_from_digit( &bigint, 0 );
    _PDCLIB_bigint_from_digit( &one, 1 );

    TESTCASE( _PDCLIB_bigint_log2( &bigint ) == -1 );
    TESTCASE( _PDCLIB_bigint_log2( &one ) == 0 );

    _PDCLIB_bigint_mul10( &one );
    TESTCASE( _PDCLIB_bigint_log2( &one ) == 3 );

    _PDCLIB_bigint_mul10( &one );
    TESTCASE( _PDCLIB_bigint_log2( &one ) == 6 );

    _PDCLIB_bigint_mul10( &one );
    TESTCASE( _PDCLIB_bigint_log2( &one ) == 9 );

    _PDCLIB_bigint_mul10( &one );
    TESTCASE( _PDCLIB_bigint_log2( &one ) == 13 );

    _PDCLIB_bigint_mul10( &one );
    TESTCASE( _PDCLIB_bigint_log2( &one ) == 16 );

    _PDCLIB_bigint_mul10( &one );
    TESTCASE( _PDCLIB_bigint_log2( &one ) == 19 );
#endif

    return TEST_RESULTS;
}

#endif
