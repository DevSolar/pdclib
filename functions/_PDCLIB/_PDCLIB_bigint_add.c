/* _PDCLIB_bigint_add( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stddef.h>
#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_add( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    _PDCLIB_bigint_t const * smaller;
    _PDCLIB_bigint_t const * wider;
    _PDCLIB_bigint_digit_t carry = 0;
    _PDCLIB_bigint_digit_t newcarry;
    size_t i;

    if ( lhs->size < rhs->size )
    {
        smaller = lhs;
        wider = rhs;
    }
    else
    {
        smaller = rhs;
        wider = lhs;
    }

    /* Add up the bigints digit by digit, ensuring no overflow of 32-bit range */
    for ( i = 0; i < smaller->size; ++i )
    {
        _PDCLIB_bigint_digit_t l = _PDCLIB_BIGINT_DIGIT_MAX - lhs->data[i];
        _PDCLIB_bigint_digit_t r = _PDCLIB_BIGINT_DIGIT_MAX - rhs->data[i];

        if ( ( newcarry = ( l < rhs->data[i] ) || ( carry && ( l == rhs->data[i] ) ) ) )
        {
            lhs->data[i] = _PDCLIB_BIGINT_DIGIT_MAX - ( l + r ) - 1 + carry;
        }
        else
        {
            lhs->data[i] = lhs->data[i] + rhs->data[i] + carry;
        }

        carry = newcarry;
    }

    for ( ; i < wider->size; ++i )
    {
        if ( ( newcarry = ( ( _PDCLIB_BIGINT_DIGIT_MAX - wider->data[i] ) < carry ) ) )
        {
            lhs->data[i] = 0;
        }
        else
        {
            lhs->data[i] = wider->data[i] + carry;
        }

        carry = newcarry;
    }

    /* Possible new digit */
    if ( carry )
    {
        lhs->data[i++] = carry;
    }

    lhs->size = i;

    return lhs;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs, rhs, expected;

    _PDCLIB_bigint32( &lhs, 0 );
    _PDCLIB_bigint64( &rhs, 0, 0 );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( lhs.size == 0 );

    _PDCLIB_bigint32( &lhs, UINT32_C( 0x12345678 ) );
    _PDCLIB_bigint32( &expected, UINT32_C( 0x12345678 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    _PDCLIB_bigint32( &rhs, UINT32_C( 0x11111111 ) );
    _PDCLIB_bigint32( &expected, UINT32_C( 0x23456789 ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    _PDCLIB_bigint64( &rhs, 1, UINT32_C( 0xDCBA9877 ) );
    _PDCLIB_bigint64( &expected, 2, 0 );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );

    _PDCLIB_bigint32( &lhs, UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint32( &rhs, UINT32_C( 0xFFFFFFFF ) );
    _PDCLIB_bigint64( &expected, 1, UINT32_C( 0xFFFFFFFE ) );
    _PDCLIB_bigint_add( &lhs, &rhs );
    TESTCASE( _PDCLIB_bigint_cmp( &lhs, &expected ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
