/* $Id$ */

/* fwrite( void *, size_t, size_t, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <_PDCLIB_glue.h>

#ifndef REGTEST

#include <stdbool.h>
#include <string.h>

size_t fread( void * _PDCLIB_restrict ptr, size_t size, size_t nmemb, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    if ( _PDCLIB_prepread( stream ) == EOF )
    {
        return 0;
    }
    char * dest = (char *)ptr;
    size_t nmemb_i;
    for ( nmemb_i = 0; nmemb_i < nmemb; ++nmemb_i )
    {
        for ( size_t size_i = 0; size_i < size; ++size_i )
        {
            if ( stream->bufidx == stream->bufend )
            {
                if ( _PDCLIB_fillbuffer( stream ) == EOF )
                {
                    /* Could not read requested data */
                    return nmemb_i;
                }
            }
            dest[ nmemb_i * size + size_i ] = stream->buffer[ stream->bufidx++ ];
        }
    }
    return nmemb_i;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    FILE * fh;
    remove( "testfile" );
    TESTCASE( ( fh = fopen( "testfile", "w" ) ) != NULL );
    TESTCASE( fwrite( "SUCCESS testing fwrite()\n", 1, 25, fh ) == 25 );
    TESTCASE( fclose( fh ) == 0 );
    /* TODO: Add readback test. */
    TESTCASE( remove( "testfile" ) == 0 );
    return TEST_RESULTS;
}

#endif

