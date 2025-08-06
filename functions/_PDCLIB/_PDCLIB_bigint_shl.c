/* _PDCLIB_bigint_shl( bigint_t *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <stdlib.h>

void _PDCLIB_bigint_shl( _PDCLIB_bigint_t * bigint, _PDCLIB_size_t bits )
{
    ldiv_t dv = ldiv( bits, _PDCLIB_BIGINT_DIGIT_BITS );
    _PDCLIB_bigint_arith_t t = 0;
    size_t i;

    if ( dv.quot > 0 )
    {
        i = bigint->size;

        /* shifting whole digits */
        while ( i-- > 0 )
        {
            bigint->data[ i + dv.quot ] = bigint->data[ i ];
        }

        bigint->size += dv.quot;

        /* zero out shifted low digits */
        while ( (long)i < dv.quot )
        {
            bigint->data[ i++ ] = 0;
        }
    }

    for ( i = dv.quot; i < bigint->size; ++i )
    {
        t = ( (_PDCLIB_bigint_arith_t)bigint->data[ i ] << dv.rem ) + t;
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
        { 3, { 0x0000u, 0x0100u, 0x0203u } }
    };

    _PDCLIB_bigint_from_digit( &bigint, 1 );
    _PDCLIB_bigint_shl( &bigint, 2 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 4 );

    _PDCLIB_bigint_from_bigint( &bigint, &testdata[0] );
    _PDCLIB_bigint_shl( &bigint, _PDCLIB_BIGINT_DIGIT_BITS + 1 );
    TESTCASE( bigint.size == 3 );
    TESTCASE( bigint.data[0] == 0 );
    TESTCASE( bigint.data[1] == 0x0100 );
    TESTCASE( bigint.data[2] == 0x0203 );
#endif

    return TEST_RESULTS;
}

#endif
