/* $Id$ */

/* gets( char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#define _PDCLIB_GLUE_H _PDCLIB_GLUE_H
#include <_PDCLIB_glue.h>

char * gets( char * s )
{
    if ( _PDCLIB_prepread( stdin ) == EOF )
    {
        return NULL;
    }
    char * dest = s;
    while ( ( *dest = stdin->buffer[stdin->bufidx++] ) != '\n' )
    {
        ++dest;
        if ( stdin->bufidx == stdin->bufend )
        {
            if ( _PDCLIB_fillbuffer( stdin ) == EOF )
            {
                break;
            }
        }
    }
    *dest = '\0';
    return ( dest == s ) ? NULL : s;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>
#include <string.h>

int main( void )
{
    FILE * fh;
    char buffer[10];
    char const * gets_test = "foo\nbar\0baz\nweenie";
    TESTCASE( ( fh = fopen( testfile, "wb" ) ) != NULL );
    TESTCASE( fwrite( gets_test, 1, 18, fh ) == 18 );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( ( fh = freopen( testfile, "rb", stdin ) ) != NULL );
    TESTCASE( gets( buffer ) == buffer );
    TESTCASE( strcmp( buffer, "foo" ) == 0 );
    TESTCASE( gets( buffer ) == buffer );
    TESTCASE( memcmp( buffer, "bar\0baz\0", 8 ) == 0 );
    TESTCASE( gets( buffer ) == buffer );
    TESTCASE( strcmp( buffer, "weenie" ) == 0 );
    TESTCASE( feof( fh ) );
    TESTCASE( fseek( fh, -1, SEEK_END ) == 0 );
    TESTCASE( gets( buffer ) == buffer );
    TESTCASE( strcmp( buffer, "e" ) == 0 );
    TESTCASE( feof( fh ) );
    TESTCASE( fseek( fh, 0, SEEK_END ) == 0 );
    TESTCASE( gets( buffer ) == NULL );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( testfile ) == 0 );
    return TEST_RESULTS;
}

#endif

