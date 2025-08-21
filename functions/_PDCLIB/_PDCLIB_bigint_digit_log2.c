/* _PDCLIB_bigint_digit_log2( bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <stdio.h>

int _PDCLIB_bigint_digit_log2( _PDCLIB_bigint_digit_t digit )
{
    unsigned char log2_lookup[] =
    {
        0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
    };
    _PDCLIB_bigint_digit_t t;

#if _PDCLIB_BIGINT_DIGIT_BITS > 16
    if ( ( t = ( digit >> 24 ) ) )
    {
        return log2_lookup[ t ] + 24;
    }
    else if ( ( t = ( digit >> 16 ) ) )
    {
        return log2_lookup[ t ] + 16;
    }
    else
#endif
    if ( ( t = ( digit >> 8 ) ) )
    {
        return log2_lookup[ t ] + 8;
    }
    else if ( digit > 0 )
    {
        return log2_lookup[ digit ];
    }
    else
    {
        return -1;
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <math.h>

int main( void )
{
#ifndef REGTEST
    unsigned i;

    for ( i = 1; i < (1 << _PDCLIB_BIGINT_DIGIT_BITS); ++i )
    {
        //TESTCASE( _PDCLIB_bigint_digit_log2( i ) == (int)log2( i ) );
    }
#endif

    return TEST_RESULTS;
}

#endif
