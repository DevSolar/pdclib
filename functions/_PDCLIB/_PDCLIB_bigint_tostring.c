/* _PDCLIB_bigint_tostring( _PDCLIB_bigint_t const *, char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

char * _PDCLIB_bigint_tostring( _PDCLIB_bigint_t const * _PDCLIB_restrict value, char * _PDCLIB_restrict buffer )
{
    char * rc = buffer;
    char prefix[3] = "0x";
    int hexdigits = _PDCLIB_BIGINT_DIGIT_BITS / 4;

    if ( value->size > 0 )
    {
        unsigned i;

        for ( i = value->size; i > 0; --i )
        {
            sprintf( buffer, "%s%0*" PRIxLEAST32, prefix, hexdigits, value->data[i - 1] );
            buffer += hexdigits + strlen( prefix );
            prefix[0] = '.';
            prefix[1] = '\0';
        }
    }
    else
    {
        sprintf( buffer, "0x%0*x", hexdigits, 0 );
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t value;
    char buffer[ _PDCLIB_BIGINT_CHARS ];
#if _PDCLIB_BIGINT_DIGIT_BITS == 8
    char const * expected[] = { "0x00", "0x12.34.56.78", "0x90.ab.cd.ef.12.34.56.78" };
#elif _PDCLIB_BIGINT_DIGIT_BITS == 16
    char const * expected[] = { "0x0000", "0x1234.5678", "0x90ab.cdef.1234.5678" };
#else
    char const * expected[] = { "0x00000000", "0x12345678", "0x90abcdef.12345678" };
#endif
    _PDCLIB_bigint32( &value, 0 );
    TESTCASE( strcmp( _PDCLIB_bigint_tostring( &value, buffer ), expected[0] ) == 0 );
    _PDCLIB_bigint32( &value, UINT32_C( 0x12345678 ) );
    TESTCASE( strcmp( _PDCLIB_bigint_tostring( &value, buffer ), expected[1] ) == 0 );
    _PDCLIB_bigint64( &value, UINT32_C( 0x90abcdef ), UINT32_C( 0x12345678 ) );
    TESTCASE( strcmp( _PDCLIB_bigint_tostring( &value, buffer ), expected[2] ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
