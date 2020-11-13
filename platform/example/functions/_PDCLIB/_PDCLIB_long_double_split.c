/* _PDCLIB_long_double_split( long double, unsigned *, _PDCLIB_bigint_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

int _PDCLIB_long_double_split( long double value, unsigned * exponent, _PDCLIB_bigint_t * significand )
{
    union
    {
        long double value;
        unsigned char byte[ sizeof( long double ) ];
    } ldbl = { value };

#if defined( _PDCLIB_LDBL_64 )

    *exponent            = ( ( (unsigned)ldbl.byte[7] & 0x7F ) <<  4 ) | ( ( (unsigned)ldbl.byte[6] & 0xF0 ) >>  4 );
    significand->data[1] = ( ( (unsigned)ldbl.byte[6] & 0x0F ) << 16 ) |   ( (unsigned)ldbl.byte[5]          <<  8 ) |   (unsigned)ldbl.byte[4];
    significand->data[0] =   ( (unsigned)ldbl.byte[3]          << 24 ) |   ( (unsigned)ldbl.byte[2]          << 16 ) | ( (unsigned)ldbl.byte[1] << 8 ) | (unsigned)ldbl.byte[0];
    significand->size    = 2;
    return ldbl.byte[7] >> 7;

#elif defined( _PDCLIB_LDBL_80 )

    *exponent            = ( ( (unsigned)ldbl.byte[9] & 0x7F ) <<  8 ) |   (unsigned)ldbl.byte[8];
    significand->data[1] =   ( (unsigned)ldbl.byte[7]          << 24 ) | ( (unsigned)ldbl.byte[6] << 16 ) | ( (unsigned)ldbl.byte[5] << 8 ) | (unsigned)ldbl.byte[4];
    significand->data[0] =   ( (unsigned)ldbl.byte[3]          << 24 ) | ( (unsigned)ldbl.byte[2] << 16 ) | ( (unsigned)ldbl.byte[1] << 8 ) | (unsigned)ldbl.byte[0];
    significand->size    = 2;

    return ldbl.byte[9] >> 7;

#elif defined( _PDCLIB_LDBL_128 )

    *exponent            = ( ( (unsigned)ldbl.byte[15] & 0x7F ) <<  8 ) |   (unsigned)ldbl.byte[14];
    significand->data[3] =   ( (unsigned)ldbl.byte[13]          >>  8 ) |   (unsigned)ldbl.byte[12];
    significand->data[2] =   ( (unsigned)ldbl.byte[11]          << 24 ) | ( (unsigned)ldbl.byte[10] << 16 ) | ( (unsigned)ldbl.byte[9] << 8 ) | (unsigned)ldbl.byte[8];
    significand->data[1] =   ( (unsigned)ldbl.byte[ 7]          << 24 ) | ( (unsigned)ldbl.byte[ 6] << 16 ) | ( (unsigned)ldbl.byte[5] << 8 ) | (unsigned)ldbl.byte[4];
    significand->data[0] =   ( (unsigned)ldbl.byte[ 3]          << 24 ) | ( (unsigned)ldbl.byte[ 2] << 16 ) | ( (unsigned)ldbl.byte[1] << 8 ) | (unsigned)ldbl.byte[0];
    significand->size    = 4;

    return ldbl.byte[15] >> 7;

#else
#error Unsupported long double encoding.
#endif
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t significand;
    unsigned exponent;

#if defined( _PDCLIB_LDBL_64 )

    TESTCASE( _PDCLIB_long_double_split( 0.8l, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x03fe );
    TESTCASE( significand.size == 2 );
    TESTCASE( significand.data[1] == 0x00099999 );
    TESTCASE( significand.data[0] == 0x9999999a );

    TESTCASE( _PDCLIB_long_double_split( -24.789l, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x0403 );
    TESTCASE( significand.size == 2 );
    TESTCASE( significand.data[1] == 0x0008c9fb );
    TESTCASE( significand.data[0] == 0xe76c8b44 );

#elif defined( _PDCLIB_LDBL_80 )

    TESTCASE( _PDCLIB_long_double_split( 0.8l, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x3ffe );
    TESTCASE( significand.size == 2 );
    TESTCASE( significand.data[1] == 0xcccccccc );
    TESTCASE( significand.data[0] == 0xcccccccd );

    TESTCASE( _PDCLIB_long_double_split( -24.789l, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x4003 );
    TESTCASE( significand.size == 2 );
    TESTCASE( significand.data[1] == 0xc64fdf3b );
    TESTCASE( significand.data[0] == 0x645a1cac );

#elif defined( _PDCLIB_LDBL_128 )

    TESTCASE( _PDCLIB_long_double_split( 0.8l, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x3ffe );
    TESTCASE( significand.size == 2 );
    TESTCASE( significand.data[3] == 0x00009999 );
    TESTCASE( significand.data[2] == 0x99999999 );
    TESTCASE( significand.data[1] == 0x99999999 );
    TESTCASE( significand.data[0] == 0x9999999a );

    TESTCASE( _PDCLIB_long_double_split( -24.789l, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x4003 );
    TESTCASE( significand.size == 2 );
    TESTCASE( significand.data[3] == 0x00008c9f );
    TESTCASE( significand.data[2] == 0xbe76c8b4 );
    TESTCASE( significand.data[1] == 0x39581062 );
    TESTCASE( significand.data[0] == 0x4dd2f1aa );

#else
#error Unsupported long double encoding.
#endif
#endif

    return TEST_RESULTS;
}

#endif
