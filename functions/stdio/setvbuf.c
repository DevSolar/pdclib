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
    /* Only allowed on "virgin" streams (i.e., before first I/O occurs), and
       a valid value for mode.
    */
    if ( ( ! stream->status & _PDCLIB_VIRGINSTR ) ||
         ( ( mode != _IOFBF ) && ( mode != _IOLBF ) && ( mode != _IONBF ) ) )
    {
        return -1;
    }
    /* If a buffer is provided by user... */
    if ( buf != NULL )
    {
        /* ...do not free it in library functions like fclose(), freopen(). */
        stream->status &= ~_PDCLIB_LIBBUFFER;
    }
    /* If no buffer is provided by user, but required... */
    else if ( mode != _IONBF )
    {
        /* Since setvbuf() may be called (successfully) on a stream only once,
           the stream's buffer at this point should *always* be that allocated
           by fopen(), but better make sure.
        */
        if ( ! ( stream->status & _PDCLIB_LIBBUFFER ) )
        {
            return -1;
        }
        /* Drop old buffer, allocate new one of requested size (unless that is
           equal to BUFSIZ, in which case we can use the one already allocated
           by fopen().)
        */
        if ( size != BUFSIZ )
        {
            if ( ( buf = malloc( size ) ) == NULL )
            {
                return -1;
            }
            free( stream->buffer );
        }
    }
    /* Applying new settings to stream. */
    stream->status &= ~( _IOFBF | _IOLBF | _IONBF );
    stream->status |= mode;
    stream->buffer = buf;
    stream->bufsize = size;
    stream->status &= ~_PDCLIB_VIRGINSTR;
    return 0;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
#ifndef REGTEST
    TESTCASE( NO_TESTDRIVER );
#else
    puts( " NOTEST setvbuf() test driver is PDCLib-specific." );
#endif
    return TEST_RESULTS;
}

#endif
