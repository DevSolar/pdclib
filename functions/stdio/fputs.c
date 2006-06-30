/* $Id$ */

/* fputs( const char *, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int fputs( const char * _PDCLIB_restrict s, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    /* FIXME: This is devoid of any error checking (file writeable? r/w
       constraints honored?)
    */
    /* FIXME: Proper buffering handling. */
    while ( stream->bufidx < stream->bufsize )
    {
        if ( ( stream->buffer[stream->bufidx++] = *(s++) ) == '\0' )
        {
            break;
        }
    }
    fflush( stream );
    if ( *(s-1) != '\0' )
    {
        return fputs( s, stream );
    }
    else
    {
        return 1;
    }
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <string.h>

int main( void )
{
    FILE * fh;
    char buffer[100];
    char text[] = "SUCCESS testing fputs().";
    TESTCASE( ( fh = fopen( "testfile", "w" ) ) != NULL );
    TESTCASE( fputs( text, fh ) != EOF );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( ( fh = fopen( "testfile", "r" ) ) != NULL );
    TESTCASE( fread( buffer, 1, strlen( text ), fh ) == strlen( text ) );
    TESTCASE( memcmp( buffer, text, strlen( text ) ) == 0 );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( "testfile" ) == 0 );
    return TEST_RESULTS;
}

#endif
