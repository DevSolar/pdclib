/* _PDCLIB_bigint_shl( _PDCLIB_bigint_t *, unsigned )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>
#include <string.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_shl( _PDCLIB_bigint_t * lhs, unsigned rhs )
{
    unsigned word_shifts = rhs / _PDCLIB_BIGINT_DIGIT_BITS;
    unsigned bit_shifts = rhs - ( word_shifts * _PDCLIB_BIGINT_DIGIT_BITS );
    _PDCLIB_bigint_arith_t digit;
    _PDCLIB_bigint_digit_t carry = 0;
    size_t i;

    if ( lhs->size == 0 )
    {
        return lhs;
    }

    if ( word_shifts > 0 )
    {
        memmove( lhs->data + word_shifts, lhs->data, sizeof( _PDCLIB_bigint_digit_t ) * lhs->size );
        memset( lhs->data, 0, sizeof( _PDCLIB_bigint_digit_t ) * word_shifts );
        lhs->size += word_shifts;
    }

    for ( i = 0 + word_shifts; i < lhs->size; ++i )
    {
        digit = ( (_PDCLIB_bigint_arith_t)lhs->data[i] << bit_shifts ) | carry;
        carry = digit >> _PDCLIB_BIGINT_DIGIT_BITS;
        lhs->data[i] = digit & _PDCLIB_BIGINT_DIGIT_MAX;
    }

    if ( carry > 0 )
    {
        lhs->data[ lhs->size++ ] = carry;
    }

    return lhs;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs, expected;

    _PDCLIB_bigint32( &lhs, 12 );
    _PDCLIB_bigint32( &expected, 48 );
    _PDCLIB_bigint_shl( &lhs, 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    _PDCLIB_bigint32( &lhs, UINT32_C( 0x80000001 ) );
    _PDCLIB_bigint64( &expected, 1, 2 );
    _PDCLIB_bigint_shl( &lhs, 1 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
