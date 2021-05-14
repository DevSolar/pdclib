/* _PDCLIB_float_split( float, unsigned *, _PDCLIB_bigint_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

int _PDCLIB_float_split( float value, unsigned * exponent, _PDCLIB_bigint_t * significand )
{
    union
    {
        float value;
        unsigned char byte[ sizeof( float ) ];
    } flt = { value };

    *exponent            = ( ( (unsigned)flt.byte[3] & 0x7F ) <<  1 ) | ( (unsigned)flt.byte[2] >> 7 );

#if _PDCLIB_BIGINT_DIGIT_BITS == 32
    significand->data[0] = ( ( (unsigned)flt.byte[2] & 0x7F ) << 16 ) | ( (unsigned)flt.byte[1] << 8 ) | (unsigned)flt.byte[0];
    significand->size    = 1;
#elif _PDCLIB_BIGINT_DIGIT_BITS == 16
    significand->data[1] =   (unsigned)flt.byte[2] & 0x7F;
    significand->data[0] = ( (unsigned)flt.byte[1] << 8 ) | (unsigned)flt.byte[0];
    significand->size    = 2;
#else
    significand->data[2] = (unsigned)flt.byte[2] & 0x7F;
    significand->data[1] = (unsigned)flt.byte[1];
    significand->data[0] = (unsigned)flt.byte[0];
    significand->size    = 3;
#endif

    return flt.byte[3] >> 7;
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

    TESTCASE( _PDCLIB_float_split( 0.8f, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x007e );
    _PDCLIB_bigint32( &expected, UINT32_C( 0x004ccccd ) );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );

    TESTCASE( _PDCLIB_float_split( -24.789f, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x0083 );
    _PDCLIB_bigint32( &expected, UINT32_C( 0x00464fdf ) );
    TESTCASE( _PDCLIB_bigint_cmp( &significand, &expected ) == 0 );
#endif

    return TEST_RESULTS;
}

#endif
