/* $Id$ */

/* fputc( int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

/* Write the value c (cast to unsigned char) to the given stream.
   Returns c if successful, EOF otherwise.
   If a write error occurs, sets the error indicator of the stream is set.
*/
int fputc( int c, struct _PDCLIB_file_t * stream )
{
    /* FIXME: This is devoid of any error checking (file writeable? r/w
    constraints honored?) (Text format translations?)
    */
    stream->buffer[stream->bufidx++] = (char)c;
    if ( ( stream->bufidx == stream->bufsize )                   /* _IOFBF */
           || ( ( stream->status & _IOLBF ) && ( (char)c == '\n' ) ) /* _IOLBF */
           || ( stream->status & _IONBF )                        /* _IONBF */
    )
    {
        /* buffer filled, unbuffered stream, or end-of-line. */
        fflush( stream );
    }
    else
    {
        stream->status |= _PDCLIB_WROTELAST;
    }
    return c;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    FILE * fh;
    char buffer[100];
    TESTCASE( ( fh = fopen( "testfile", "w" ) ) != NULL );
    TESTCASE( fputc( '!', fh ) == '!' );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( ( fh = fopen( "testfile", "r" ) ) != NULL );
    TESTCASE( fread( buffer, 1, 1, fh ) == 1 );
    TESTCASE( buffer[0] == '!' );
    TESTCASE( fclose( fh ) == 0 );
    return TEST_RESULTS;
}

#endif
