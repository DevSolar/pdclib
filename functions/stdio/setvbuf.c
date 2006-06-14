/* $Id$ */

/* setvbuf( FILE *, char *, int, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST

int setvbuf( struct _PDCLIB_file_t * _PDCLIB_restrict stream, char * _PDCLIB_restrict buf, int mode, size_t size )
{
    /* TODO: Honor user-provided buffer / buffer size. (Not actually required
       by the standard...) */
    stream->status &= ~( _IOFBF | _IOLBF | _IONBF );
    stream->status |= mode; /* TODO: Unchecked use of mode -> vulnerable. */
    return 0;

#if 0
    /* Only allowed on "virgin" streams (i.e., before first I/O occurs), a
       valid value for mode, and only once per stream (i.e., the buffer
       attached to the stream should always be the one allocated by fopen().
    */
    if ( ( ! stream->status & _PDCLIB_VIRGINSTR ) ||
         ( ( mode != _IOFBF ) && ( mode != _IOLBF ) && ( mode != _IONBF ) ) ||
         ! ( stream->status & _PDCLIB_LIBBUFFER ) )
    {
        return -1;
    }
    if ( mode == _IONBF )
    {
        /* When unbuffered I/O is requested, we don't need a buffer. */
        buf = NULL;
        size = 0;
    }
    else
    {
        /* The standard does not really require this - only BUFSIZ is required
           to be no smaller than 256 - but it makes sense not to make buffers
           too small anyway.
        */
        if ( size < 256 )
        {
            buf = NULL; /* do not use too-small user buffer */
            size = 256;
        }
    }
    /* If a suitable buffer is provided by user... */
    if ( buf != NULL )
    {
        /* ...do not free it in library functions like fclose(), freopen(). */
        stream->status &= ~_PDCLIB_LIBBUFFER;
    }
    /* If we cannot allocate enough memory, that is not a reason for failure -
       the standard does not actually *require* that setvbuf() honors user-
       supplied buffer and buffer size, so we can quietly ignore this.
    */
    /* FIXME: Logic stops here. Handle _IONBF, new buf value etc. correctly. */
    puts("foo");
    if ( ( ( buf = malloc( size ) ) != NULL ) || ( mode == _IONBF ) )
    {
        free( stream->buffer );
    }
    puts("bar");
    /* Applying new settings to stream. */
    stream->status &= ~( _IOFBF | _IOLBF | _IONBF );
    stream->status |= mode;
    stream->bufsize = size;
    stream->status &= ~_PDCLIB_VIRGINSTR;
    return 0;
#endif
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#define BUFFERSIZE 500

int main( void )
{
#ifndef REGTEST
    char const * const filename = "testfile";
    char buffer[ BUFFERSIZE ];
    struct _PDCLIB_file_t * fh;
    /* full buffered, user-supplied buffer */
    TESTCASE( ( fh = fopen( filename, "w" ) ) != NULL );
    TESTCASE( fh->status & _PDCLIB_LIBBUFFER );
    TESTCASE( fh->bufsize == BUFSIZ );
    TESTCASE( setvbuf( fh, buffer, _IOFBF, BUFFERSIZE ) == 0 );
#if 0
    TESTCASE( fh->buffer == buffer );
    TESTCASE( fh->bufsize == BUFFERSIZE );
#endif
    TESTCASE( ( fh->status & ( _IOFBF | _IONBF | _IOLBF ) ) == _IOFBF );
    TESTCASE( fclose( fh ) == 0 );
    /* line buffered, lib-supplied buffer */
    TESTCASE( ( fh = fopen( filename, "w" ) ) != NULL );
    TESTCASE( setvbuf( fh, NULL, _IOLBF, BUFFERSIZE ) == 0 );
#if 0
    TESTCASE( fh->buffer != buffer );
    TESTCASE( fh->buffer != NULL );
    TESTCASE( fh->bufsize == BUFFERSIZE );
#endif
    TESTCASE( ( fh->status & ( _IOFBF | _IONBF | _IOLBF ) ) == _IOLBF );
    TESTCASE( fclose( fh ) == 0 );
    /* not buffered, user-supplied buffer */
    TESTCASE( ( fh = fopen( filename, "w" ) ) != NULL );
    TESTCASE( setvbuf( fh, buffer, _IONBF, BUFFERSIZE ) == 0 );
#if 0
    TESTCASE( fh->buffer == NULL );
    TESTCASE( fh->bufsize == 0 );
#endif
    TESTCASE( ( fh->status & ( _IOFBF | _IONBF | _IOLBF ) ) == _IONBF );
    TESTCASE( fclose( fh ) == 0 );
#else
    puts( " NOTEST setvbuf() test driver is PDCLib-specific." );
#endif
    return TEST_RESULTS;
}

#endif
