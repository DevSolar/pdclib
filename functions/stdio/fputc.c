/* fputc( int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

int fputc( int c, struct _PDCLIB_file_t * stream )
{
    _PDCLIB_LOCK( stream->mtx );

    if ( _PDCLIB_prepwrite( stream ) == EOF )
    {
        _PDCLIB_UNLOCK( stream->mtx );
        return EOF;
    }

    stream->buffer[stream->bufidx++] = ( char )c;

    if ( ( stream->bufidx == stream->bufsize )                   /* _IOFBF */
           || ( ( stream->status & _IOLBF ) && ( ( char )c == '\n' ) ) /* _IOLBF */
           || ( stream->status & _IONBF )                        /* _IONBF */
       )
    {
        /* buffer filled, unbuffered stream, or end-of-line. */
        c = ( _PDCLIB_flushbuffer( stream ) == 0 ) ? c : EOF;
    }

    _PDCLIB_UNLOCK( stream->mtx );

    return c;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif
