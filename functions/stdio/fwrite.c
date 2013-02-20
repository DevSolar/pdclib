/* $Id$ */

/* fwrite( const void *, size_t, size_t, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_io.h>
#include <_PDCLIB_glue.h>

#include <stdbool.h>
#include <string.h>

//TODO OS(2012-08-01): Ascertain purpose of lineend & potentially remove

size_t _PDCLIB_fwrite_unlocked( const void * _PDCLIB_restrict ptr, 
               size_t size, size_t nmemb, 
               FILE * _PDCLIB_restrict stream )
{
    if ( _PDCLIB_prepwrite( stream ) == EOF )
    {
        return 0;
    }
    _PDCLIB_size_t offset = 0;
    //bool lineend = false;
    size_t nmemb_i;
    for ( nmemb_i = 0; nmemb_i < nmemb; ++nmemb_i )
    {
        for ( size_t size_i = 0; size_i < size; ++size_i )
        {
            if ( ( stream->buffer[ stream->bufidx++ ] = ((char*)ptr)[ nmemb_i * size + size_i ] ) == '\n' )
            {
                /* Remember last newline, in case we have to do a partial line-buffered flush */
                offset = stream->bufidx;
                //lineend = true;
            }
            if ( stream->bufidx == stream->bufsize )
            {
                if ( _PDCLIB_flushbuffer( stream ) == EOF )
                {
                    /* Returning number of objects completely buffered */
                    return nmemb_i;
                }
                //lineend = false;
                /*
                 * The entire buffer has been flushed; this means we have to
                 * reset our newline position as we have already written
                 * that part of the stream.
                 */
                offset = 0;
            }
        }
    }
    /* Fully-buffered streams are OK. Non-buffered streams must be flushed,
       line-buffered streams only if there's a newline in the buffer.
    */
    switch ( stream->status & ( _IONBF | _IOLBF ) )
    {
        case _IONBF:
            if ( _PDCLIB_flushbuffer( stream ) == EOF )
            {
                /* We are in a pinch here. We have an error, which requires a
                   return value < nmemb. On the other hand, all objects have
                   been written to buffer, which means all the caller had to
                   do was removing the error cause, and re-flush the stream...
                   Catch 22. We'll return a value one short, to indicate the
                   error, and can't really do anything about the inconsistency.
                */
                return nmemb_i - 1;
            }
            break;
        case _IOLBF:
            {
            size_t bufidx = stream->bufidx;
            stream->bufidx = offset;
            if ( _PDCLIB_flushbuffer( stream ) == EOF )
            {
                /* See comment above. */
                stream->bufidx = bufidx;
                return nmemb_i - 1;
            }
            stream->bufidx = bufidx - offset;
            memmove( stream->buffer, stream->buffer + offset, stream->bufidx );
            }
    }
    return nmemb_i;
}

size_t fwrite( const void * _PDCLIB_restrict ptr, 
               size_t size, size_t nmemb, 
               FILE * _PDCLIB_restrict stream )
{
    _PDCLIB_flockfile( stream );
    size_t r = _PDCLIB_fwrite_unlocked( ptr, size, nmemb, stream );
    _PDCLIB_funlockfile( stream );
    return r;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by fread(). */
    return TEST_RESULTS;
}

#endif

