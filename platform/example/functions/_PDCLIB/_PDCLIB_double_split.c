/* _PDCLIB_double_split( double, unsigned *, _PDCLIB_bigint_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

int _PDCLIB_double_split( double value, unsigned * exponent, _PDCLIB_bigint_t * significand )
{
    union
    {
        double value;
        unsigned char byte[ sizeof( double ) ];
    } dbl = { value };

    *exponent            = ( ( (unsigned)dbl.byte[7] & 0x7F ) <<  4 ) | ( ( (unsigned)dbl.byte[6] & 0xF0 ) >>  4 );

#if _PDCLIB_BIGINT_DIGIT_BITS == 32
    significand->data[1] = ( ( (unsigned)dbl.byte[6] & 0x0F ) << 16 ) |   ( (unsigned)dbl.byte[5]          <<  8 ) |   (unsigned)dbl.byte[4];
    significand->data[0] =   ( (unsigned)dbl.byte[3]          << 24 ) |   ( (unsigned)dbl.byte[2]          << 16 ) | ( (unsigned)dbl.byte[1] << 8 ) | (unsigned)dbl.byte[0];
    significand->size    = 2;
#elif _PDCLIB_BIGINT_DIGIT_BITS == 16
    significand->data[3] =   (unsigned)dbl.byte[6] & 0x0F;
    significand->data[2] = ( (unsigned)dbl.byte[5] << 8 ) | (unsigned)dbl.byte[4];
    significand->data[1] = ( (unsigned)dbl.byte[3] << 8 ) | (unsigned)dbl.byte[2];
    significand->data[0] = ( (unsigned)dbl.byte[1] << 8 ) | (unsigned)dbl.byte[0];
    significand->size    = 4;
#else
    significand->data[6] = (unsigned)dbl.byte[6] & 0x0F;
    significand->data[5] = (unsigned)dbl.byte[5];
    significand->data[4] = (unsigned)dbl.byte[4];
    significand->data[3] = (unsigned)dbl.byte[3];
    significand->data[2] = (unsigned)dbl.byte[2];
    significand->data[1] = (unsigned)dbl.byte[1];
    significand->data[0] = (unsigned)dbl.byte[0];
    significand->size    = 7;
#endif

    return dbl.byte[7] >> 7;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdint.h>

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t significand, expected;
    unsigned exponent;

    TESTCASE( _PDCLIB_double_split( 0.8, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x03fe );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x00099999 ), UINT32_C( 0x9999999a ) );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );

    TESTCASE( _PDCLIB_double_split( -24.789, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x0403 );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x0008c9fb ), UINT32_C( 0xe76c8b44 ) );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );
#endif

    return TEST_RESULTS;
}

#endif
