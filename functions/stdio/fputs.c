/* $Id$ */

/* fputs( const char *, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

int fputs( const char * _PDCLIB_restrict s, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    if ( _PDCLIB_prepwrite( stream ) == EOF )
    {
        return EOF;
    }
    while ( *s != '\0' )
    {
        /* Unbuffered and line buffered streams get flushed when fputs() does
           write the terminating end-of-line. All streams get flushed if the
           buffer runs full.
        */
        stream->buffer[ stream->bufidx++ ] = *s;
        if ( ( stream->bufidx == stream->bufsize ) ||
             ( ( stream->status & _IOLBF ) && *s == '\n' )
           )
        {
            if ( _PDCLIB_flushbuffer( stream ) == EOF )
            {
                return EOF;
            }
        }
        ++s;
    }
    if ( stream->status & _IONBF )
    {
        if ( _PDCLIB_flushbuffer( stream ) == EOF )
        {
            return EOF;
        }
    }
    return 0;
}

#endif
#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    char const * const message = "SUCCESS testing fputs()";
    FILE * fh;
    TESTCASE( ( fh = tmpfile() ) != NULL );
    TESTCASE( fputs( message, fh ) >= 0 );
    rewind( fh );
    for ( size_t i = 0; i < 23; ++i )
    {
        TESTCASE( fgetc( fh ) == message[i] );
    }
    TESTCASE( fclose( fh ) == 0 );
    return TEST_RESULTS;
}

#endif

