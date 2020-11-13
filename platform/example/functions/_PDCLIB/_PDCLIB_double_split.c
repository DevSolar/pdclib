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
    significand->data[1] = ( ( (unsigned)dbl.byte[6] & 0x0F ) << 16 ) |   ( (unsigned)dbl.byte[5]          <<  8 ) |   (unsigned)dbl.byte[4];
    significand->data[0] =   ( (unsigned)dbl.byte[3]          << 24 ) |   ( (unsigned)dbl.byte[2]          << 16 ) | ( (unsigned)dbl.byte[1] << 8 ) | (unsigned)dbl.byte[0];
    significand->size    = 2;
    return dbl.byte[7] >> 7;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t significand;
    unsigned exponent;

    TESTCASE( _PDCLIB_double_split( 0.8, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x03fe );
    TESTCASE( significand.size == 2 );
    TESTCASE( significand.data[1] == 0x00099999 );
    TESTCASE( significand.data[0] == 0x9999999a );

    TESTCASE( _PDCLIB_double_split( -24.789, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x0403 );
    TESTCASE( significand.size == 2 );
    TESTCASE( significand.data[1] == 0x0008c9fb );
    TESTCASE( significand.data[0] == 0xe76c8b44 );
#endif

    return TEST_RESULTS;
}

#endif
