/* _PDCLIB_bigint_mul_dig( _PDCLIB_bigint_t *, _PDCLIB_bigint_digit_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stddef.h>
#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_mul_dig( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, _PDCLIB_bigint_digit_t rhs )
{
    _PDCLIB_bigint_arith_t digit;     /* Hold intermediary (wide) result. */
    _PDCLIB_bigint_digit_t carry = 0; /* Hold overflow. */
    size_t i;

    for ( i = 0; i < lhs->size; ++i )
    {
        /* Add product and carry into intermediate result */
        digit = (_PDCLIB_bigint_arith_t)lhs->data[ i ] * (_PDCLIB_bigint_arith_t)rhs + carry;
        /* High bits into carry */
        carry = digit >> _PDCLIB_BIGINT_DIGIT_BITS;
        /* Low bits back into bigint */
        lhs->data[ i ] = ( digit & _PDCLIB_BIGINT_DIGIT_MAX );
    }

    if ( carry > 0 )
    {
        /* New digit. */
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

    _PDCLIB_bigint32( &lhs, 0 );
    _PDCLIB_bigint_mul_dig( &lhs, 0 );
    _PDCLIB_bigint32( &expected, 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    _PDCLIB_bigint32( &lhs, 2 );
    _PDCLIB_bigint_mul_dig( &lhs, 1 );
    _PDCLIB_bigint32( &expected, 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    _PDCLIB_bigint_mul_dig( &lhs, _PDCLIB_BIGINT_DIGIT_MAX / 2 + 1 );
#if _PDCLIB_BIGINT_DIGIT_BITS == 32
    _PDCLIB_bigint64( &expected, 1, 0 );
#elif _PDCLIB_BIGINT_DIGIT_BITS == 16
    _PDCLIB_bigint32( &expected, 0x00010000 );
#else
    _PDCLIB_bigint32( &expected, 0x00000100 );
#endif
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
