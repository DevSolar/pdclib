/* fread( void *, size_t, size_t, struct * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <string.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

size_t fread( void * _PDCLIB_restrict ptr, size_t size, size_t nmemb, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    char * dest = ( char * )ptr;
    size_t nmemb_i = 0;

    _PDCLIB_LOCK( stream->mtx );

    if ( _PDCLIB_prepread( stream ) != EOF )
    {
        for ( nmemb_i = 0; nmemb_i < nmemb; ++nmemb_i )
        {
            size_t size_i;

            /* TODO: For better performance, move from stream buffer
               to destination block-wise, not byte-wise.
            */
            for ( size_i = 0; size_i < size; ++size_i )
            {
                if ( _PDCLIB_CHECKBUFFER( stream ) == EOF )
                {
                    /* Could not read requested data */
                    _PDCLIB_UNLOCK( stream->mtx );
                    return nmemb_i;
                }

                dest[ nmemb_i * size + size_i ] = _PDCLIB_GETC( stream );
            }
        }
    }

    _PDCLIB_UNLOCK( stream->mtx );

    return nmemb_i;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    FILE * fh;
    const char * message = "Testing fwrite()...\n";
    char buffer[21];
    buffer[20] = 'x';
    TESTCASE( ( fh = tmpfile() ) != NULL );
    /* fwrite() / readback */
    TESTCASE( fwrite( message, 1, 20, fh ) == 20 );
    rewind( fh );
    TESTCASE( fread( buffer, 1, 20, fh ) == 20 );
    TESTCASE( memcmp( buffer, message, 20 ) == 0 );
    TESTCASE( buffer[20] == 'x' );
    /* same, different nmemb / size settings */
    rewind( fh );
    TESTCASE( memset( buffer, '\0', 20 ) == buffer );
    TESTCASE( fwrite( message, 5, 4, fh ) == 4 );
    rewind( fh );
    TESTCASE( fread( buffer, 5, 4, fh ) == 4 );
    TESTCASE( memcmp( buffer, message, 20 ) == 0 );
    TESTCASE( buffer[20] == 'x' );
    /* same... */
    rewind( fh );
    TESTCASE( memset( buffer, '\0', 20 ) == buffer );
    TESTCASE( fwrite( message, 20, 1, fh ) == 1 );
    rewind( fh );
    TESTCASE( fread( buffer, 20, 1, fh ) == 1 );
    TESTCASE( memcmp( buffer, message, 20 ) == 0 );
    TESTCASE( buffer[20] == 'x' );
    /* Done. */
    TESTCASE( fclose( fh ) == 0 );
    return TEST_RESULTS;
}

#endif
