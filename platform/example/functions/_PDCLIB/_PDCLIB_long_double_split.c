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
#if _PDCLIB_BIGINT_DIGIT_BITS == 32
    significand->data[1] = ( ( (unsigned)ldbl.byte[6] & 0x0F ) << 16 ) |   ( (unsigned)ldbl.byte[5]          <<  8 ) |   (unsigned)ldbl.byte[4];
    significand->data[0] =   ( (unsigned)ldbl.byte[3]          << 24 ) |   ( (unsigned)ldbl.byte[2]          << 16 ) | ( (unsigned)ldbl.byte[1] << 8 ) | (unsigned)ldbl.byte[0];
    significand->size    = 2;
#else
    significand->data[3] =   (unsigned)ldbl.byte[6] & 0x0F;
    significand->data[2] = ( (unsigned)ldbl.byte[5] << 8 ) | (unsigned)ldbl.byte[4];
    significand->data[1] = ( (unsigned)ldbl.byte[3] << 8 ) | (unsigned)ldbl.byte[2];
    significand->data[0] = ( (unsigned)ldbl.byte[1] << 8 ) | (unsigned)ldbl.byte[0];
    significand->size    = 4;
#endif
    return ldbl.byte[7] >> 7;

#elif defined( _PDCLIB_LDBL_80 )

    *exponent            = ( ( (unsigned)ldbl.byte[9] & 0x7F ) <<  8 ) |   (unsigned)ldbl.byte[8];
#if _PDCLIB_BIGINT_DIGIT_BITS == 32
    significand->data[1] = ( (unsigned)ldbl.byte[7] << 24 ) | ( (unsigned)ldbl.byte[6] << 16 ) | ( (unsigned)ldbl.byte[5] << 8 ) | (unsigned)ldbl.byte[4];
    significand->data[0] = ( (unsigned)ldbl.byte[3] << 24 ) | ( (unsigned)ldbl.byte[2] << 16 ) | ( (unsigned)ldbl.byte[1] << 8 ) | (unsigned)ldbl.byte[0];
    significand->size    = 2;
#else
    significand->data[3] = ( (unsigned)ldbl.byte[7] << 8 ) | (unsigned)ldbl.byte[6];
    significand->data[2] = ( (unsigned)ldbl.byte[5] << 8 ) | (unsigned)ldbl.byte[4];
    significand->data[1] = ( (unsigned)ldbl.byte[3] << 8 ) | (unsigned)ldbl.byte[2];
    significand->data[0] = ( (unsigned)ldbl.byte[1] << 8 ) | (unsigned)ldbl.byte[0];
    significand->size    = 4;
#endif
    return ldbl.byte[9] >> 7;

#elif defined( _PDCLIB_LDBL_128 )

    *exponent            = ( ( (unsigned)ldbl.byte[15] & 0x7F ) <<  8 ) |   (unsigned)ldbl.byte[14];
#if _PDCLIB_BIGINT_DIGIT_BITS == 32
    significand->data[3] = ( (unsigned)ldbl.byte[13] <<  8 ) |   (unsigned)ldbl.byte[12];
    significand->data[2] = ( (unsigned)ldbl.byte[11] << 24 ) | ( (unsigned)ldbl.byte[10] << 16 ) | ( (unsigned)ldbl.byte[9] << 8 ) | (unsigned)ldbl.byte[8];
    significand->data[1] = ( (unsigned)ldbl.byte[ 7] << 24 ) | ( (unsigned)ldbl.byte[ 6] << 16 ) | ( (unsigned)ldbl.byte[5] << 8 ) | (unsigned)ldbl.byte[4];
    significand->data[0] = ( (unsigned)ldbl.byte[ 3] << 24 ) | ( (unsigned)ldbl.byte[ 2] << 16 ) | ( (unsigned)ldbl.byte[1] << 8 ) | (unsigned)ldbl.byte[0];
    significand->size    = 4;
#else
    significand->data[6] = ( (unsigned)ldbl.byte[13] << 8 ) | (unsigned)ldbl.byte[12];
    significand->data[5] = ( (unsigned)ldbl.byte[11] << 8 ) | (unsigned)ldbl.byte[10];
    significand->data[4] = ( (unsigned)ldbl.byte[ 9] << 8 ) | (unsigned)ldbl.byte[ 8];
    significand->data[3] = ( (unsigned)ldbl.byte[ 7] << 8 ) | (unsigned)ldbl.byte[ 6];
    significand->data[2] = ( (unsigned)ldbl.byte[ 5] << 8 ) | (unsigned)ldbl.byte[ 4];
    significand->data[1] = ( (unsigned)ldbl.byte[ 3] << 8 ) | (unsigned)ldbl.byte[ 2];
    significand->data[0] = ( (unsigned)ldbl.byte[ 1] << 8 ) | (unsigned)ldbl.byte[ 0];
    significand->size    = 7;
#endif
    return ldbl.byte[15] >> 7;

#else
#error Unsupported long double encoding.
#endif
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

#if defined( _PDCLIB_LDBL_64 )

    TESTCASE( _PDCLIB_long_double_split( 0.8l, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x03fe );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x00099999 ), UINT32_C( 0x9999999a ) );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );

    TESTCASE( _PDCLIB_long_double_split( -24.789l, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x0403 );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x0008c9fb ), UINT32_C( 0xe76c8b44 ) );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );

#elif defined( _PDCLIB_LDBL_80 )

    TESTCASE( _PDCLIB_long_double_split( 0.8l, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x3ffe );
    _PDCLIB_bigint64( &expected, UINT32_C( 0xcccccccc ), UINT32_C( 0xcccccccd ) );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );

    TESTCASE( _PDCLIB_long_double_split( -24.789l, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x4003 );
    _PDCLIB_bigint64( &expected, UINT32_C( 0xc64fdf3b ), UINT32_C( 0x645a1cac ) );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );

#elif defined( _PDCLIB_LDBL_128 )

    _PDCLIB_bigint_t expect_2;

    TESTCASE( _PDCLIB_long_double_split( 0.8l, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x3ffe );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x00009999 ), UINT32_C( 0x99999999 ) );
    _PDCLIB_bigint64( &expect_2, UINT32_C( 0x99999999 ), UINT32_C( 0x9999999a ) );
    _PDCLIB_bigint_shl( &expected, 64 );
    _PDCLIB_bigint_add( &expected, &expect_2 );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );

    TESTCASE( _PDCLIB_long_double_split( -24.789l, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x4003 );
    _PDCLIB_bigint64( &expected, UINT32_C( 0x00008c9f ), UINT32_C( 0xbe76c8b4 ) );
    _PDCLIB_bigint64( &expect_2, UINT32_C( 0x39581062 ), UINT32_C( 0x4dd2f1aa ) );
    _PDCLIB_bigint_shl( &expected, 64 );
    _PDCLIB_bigint_add( &expected, &expect_2 );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );

#else
#error Unsupported long double encoding.
#endif

#endif

    return TEST_RESULTS;
}

#endif
