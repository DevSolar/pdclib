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
    significand->data[0] = ( ( (unsigned)flt.byte[2] & 0x7F ) << 16 ) | ( (unsigned)flt.byte[1] << 8 ) | (unsigned)flt.byte[0];
    significand->size    = 1;
    return flt.byte[3] >> 7;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t significand;
    unsigned exponent;

    TESTCASE( _PDCLIB_float_split( 0.8f, &exponent, &significand ) == 0 );
    TESTCASE( exponent == 0x007e );
    TESTCASE( significand.size == 1 );
    TESTCASE( significand.data[0] == 0x004ccccd );

    TESTCASE( _PDCLIB_float_split( -24.789f, &exponent, &significand ) == 1 );
    TESTCASE( exponent == 0x0083 );
    TESTCASE( significand.size == 1 );
    TESTCASE( significand.data[0] == 0x00464fdf );
#endif

    return TEST_RESULTS;
}

#endif
