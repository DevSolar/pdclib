/* _PDCLIB_bigint2( _PDCLIB_bigint_t *, unsigned )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stddef.h>

_PDCLIB_bigint_t * _PDCLIB_bigint2( _PDCLIB_bigint_t * bigint, unsigned n )
{
    size_t i;

    /* Check which bigint digit will contain the set bit */
    bigint->size = ( n / _PDCLIB_BIGINT_DIGIT_BITS ) + 1;

    /* Set that bit */
    bigint->data[ bigint->size - 1 ] = 1 << ( n - ( bigint->size - 1 ) * _PDCLIB_BIGINT_DIGIT_BITS );

    /* Set all lower digits to zero */
    for ( i = 0; i < bigint->size - 1; ++i )
    {
        bigint->data[ i ] = 0;
    }

    return bigint;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdint.h>

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t big, expected;
    _PDCLIB_bigint2( &big, 0 );
    _PDCLIB_bigint32( &expected, 1 );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint2( &big, 3 );
    _PDCLIB_bigint32( &expected, 8 );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint2( &big, 31 );
    _PDCLIB_bigint32( &expected, UINT32_C( 0x80000000 ) );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint2( &big, 32 );
    _PDCLIB_bigint64( &expected, 1, 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint2( &big, 34 );
    _PDCLIB_bigint64( &expected, 4, 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint2( &big, 63 );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x80000000 ), 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );

    _PDCLIB_bigint2( &big, 64 );
    _PDCLIB_bigint_mul_dig( &expected, 2 );
    TESTCASE( _PDCLIB_bigint_cmp( &big, &expected ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
