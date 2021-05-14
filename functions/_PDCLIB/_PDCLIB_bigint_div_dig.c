/* _PDCLIB_bigint_div_dig( _PDCLIB_bigint_t *, _PDCLIB_bigint_digit_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_div_dig( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, _PDCLIB_bigint_digit_t rhs )
{
    unsigned i;
    _PDCLIB_bigint_digit_t digit;
    _PDCLIB_bigint_arith_t carry = 0;

    for ( i = lhs->size; i > 0; --i )
    {
        digit = lhs->data[ i - 1 ];
        lhs->data[ i - 1 ] = (_PDCLIB_bigint_digit_t)( ( carry * _PDCLIB_BIGINT_BASE + digit ) / rhs );
        carry = ( _PDCLIB_BIGINT_BASE + digit ) - lhs->data[ i - 1 ] * rhs;
    }

    while ( lhs->size > 0 && lhs->data[ lhs->size - 1 ] == 0 )
    {
        --lhs->size;
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

    /* 1 / 2 = 0 */
    _PDCLIB_bigint32( &lhs, 1 );
    _PDCLIB_bigint32( &expected, 0 );
    _PDCLIB_bigint_div_dig( &lhs, 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    /* 2 / 2 = 0 */
    _PDCLIB_bigint32( &lhs, 2 );
    _PDCLIB_bigint32( &expected, 1 );
    _PDCLIB_bigint_div_dig( &lhs, 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    /* 10 / 2 = 5 */
    _PDCLIB_bigint64( &lhs, 1, 0 );
    _PDCLIB_bigint32( &expected, UINT32_C( 0x80000000 ) );
    _PDCLIB_bigint_div_dig( &lhs, 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    /* 24 / 2 = 12 */
    _PDCLIB_bigint64( &lhs, 2, 4 );
    _PDCLIB_bigint64( &expected, 1, 2 );
    _PDCLIB_bigint_div_dig( &lhs, 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
