/* fgets( char *, int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

char * fgets( char * _PDCLIB_restrict s, int size, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    char * dest = s;

    if ( size == 0 )
    {
        return NULL;
    }

    if ( size == 1 )
    {
        *s = '\0';
        return s;
    }

    _PDCLIB_LOCK( stream->mtx );

    if ( _PDCLIB_prepread( stream ) != EOF )
    {
        do
        {
            if ( _PDCLIB_CHECKBUFFER( stream ) == EOF )
            {
                /* In case of error / EOF before a character is read, this
                   will lead to a \0 be written anyway. Since the results
                   are "indeterminate" by definition, this does not hurt.
                */
                break;
            }
        }
        while ( ( ( *dest++ = _PDCLIB_GETC( stream ) ) != '\n' ) && ( --size > 0 ) );
    }

    _PDCLIB_UNLOCK( stream->mtx );

    *dest = '\0';
    return ( dest == s ) ? NULL : s;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <string.h>

int main( void )
{
    FILE * fh;
    char buffer[10];
    const char * fgets_test = "foo\nbar\0baz\nweenie";
    TESTCASE( ( fh = fopen( testfile, "wb+" ) ) != NULL );
    TESTCASE( fwrite( fgets_test, 1, 18, fh ) == 18 );
    rewind( fh );
    TESTCASE( fgets( buffer, 10, fh ) == buffer );
    TESTCASE( strcmp( buffer, "foo\n" ) == 0 );
    TESTCASE( fgets( buffer, 10, fh ) == buffer );
    TESTCASE( memcmp( buffer, "bar\0baz\n", 8 ) == 0 );
    TESTCASE( fgets( buffer, 10, fh ) == buffer );
    TESTCASE( strcmp( buffer, "weenie" ) == 0 );
    TESTCASE( feof( fh ) );
    TESTCASE( fseek( fh, -1, SEEK_END ) == 0 );
    /* newlib returns NULL on any n < 2, so we _NOREG these tests. */
    TESTCASE_NOREG( fgets( buffer, 1, fh ) == buffer );
    TESTCASE_NOREG( strcmp( buffer, "" ) == 0 );
    TESTCASE( fgets( buffer, 0, fh ) == NULL );
    TESTCASE( ! feof( fh ) );
    TESTCASE_NOREG( fgets( buffer, 1, fh ) == buffer );
    TESTCASE_NOREG( strcmp( buffer, "" ) == 0 );
    TESTCASE( ! feof( fh ) );
    TESTCASE( fgets( buffer, 2, fh ) == buffer );
    TESTCASE( strcmp( buffer, "e" ) == 0 );
    TESTCASE( fseek( fh, 0, SEEK_END ) == 0 );
    TESTCASE( fgets( buffer, 2, fh ) == NULL );
    TESTCASE( feof( fh ) );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( testfile ) == 0 );
    return TEST_RESULTS;
}

#endif
