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
    strcpy( buffer, "0x" );
    buffer += 2;

    if ( value->size > 0 )
    {
        int i;

        for ( i = value->size - 1; i >= 0; --i )
        {
            sprintf( buffer, "%08" PRIxLEAST32, value->data[i] );
            buffer += 8;
        }
    }
    else
    {
        strcpy( buffer, "00000000" );
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
    _PDCLIB_bigint32( &value, 0 );
    TESTCASE( strcmp( _PDCLIB_bigint_tostring( &value, buffer ), "0x00000000" ) == 0 );
    _PDCLIB_bigint32( &value, UINT32_C( 0x12345678 ) );
    TESTCASE( strcmp( _PDCLIB_bigint_tostring( &value, buffer ), "0x12345678" ) == 0 );
    _PDCLIB_bigint64( &value, UINT64_C( 0x90abcdef12345678 ) );
    TESTCASE( strcmp( _PDCLIB_bigint_tostring( &value, buffer ), "0x90abcdef12345678" ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
