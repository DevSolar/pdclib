/* _PDCLIB_bigint_mant( _PDCLIB_bigint_t *, int, unsigned char const *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdlib.h>

#include <stdio.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_mant( _PDCLIB_bigint_t * bigint, unsigned char const * mant, size_t mant_dig )
{
    div_t mant_byte = div( mant_dig - 1, _PDCLIB_CHAR_BIT );

    size_t digit = 0;
    size_t offset = 0;
    size_t i;

    bigint->size = ( ( mant_dig - 1 ) / _PDCLIB_BIGINT_DIGIT_BITS ) + 1;

    for ( i = 0; i < bigint->size; ++i )
    {
        bigint->data[ i ] = 0;
    }

    // Copy less significant bytes
    for ( i = 0; i < (unsigned)mant_byte.quot; ++i )
    {
        bigint->data[ digit ] |= ( (_PDCLIB_bigint_digit_t)*( mant _PDCLIB_FLT_OP ( mant_byte.quot - i ) ) ) << offset;

        offset += _PDCLIB_CHAR_BIT;

        if ( offset == _PDCLIB_BIGINT_DIGIT_BITS )
        {
            ++digit;
            offset = 0;
        }
    }

    // Copy most significant bytes
    bigint->data[ digit ] |= ( ( (_PDCLIB_bigint_digit_t)*mant ) & ( ( 1 << ( mant_byte.rem + 1 ) ) - 1 ) ) << offset;

    while ( bigint->size > 0 && bigint->data[ bigint->size - 1 ] == 0 )
    {
        --bigint->size;
    }

    return bigint;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    unsigned char mant[] = {
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
        0x33
    };
    _PDCLIB_bigint_t bigint;
    char buffer[ _PDCLIB_BIGINT_CHARS ];

    _PDCLIB_bigint_mant( &bigint, mant + 16, 1 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x01 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, 2 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x03 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, 3 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x03 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, 4 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x03 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, 5 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x13 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, 6 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x33 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, 7 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x33 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, 8 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x33 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[ bigint.size - 1 ] >> ( _PDCLIB_BIGINT_DIGIT_BITS - _PDCLIB_CHAR_BIT ) == 0x33 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS + 1 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x01 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS + 2 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x03 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS + 3 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x03 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS + 4 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x03 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS + 5 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x13 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS + 6 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x33 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS + 7 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x33 );

    _PDCLIB_bigint_mant( &bigint, mant + 16, _PDCLIB_BIGINT_DIGIT_BITS + 8 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[ bigint.size - 1 ] == 0x33 );
#endif

    return TEST_RESULTS;
}

#endif
