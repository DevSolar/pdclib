/* _PDCLIB_flushbuffer( struct _PDCLIB_file_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <string.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <_PDCLIB_io.h>

int _PDCLIB_flushbuffer( FILE * stream )
{
    if ( ! ( stream->status & _PDCLIB_FBIN ) )
    {
        /* TODO: Text stream conversion here */
    }

    size_t written = 0;


    while(written != stream->bufidx) {
        size_t justWrote;
        size_t toWrite = stream->bufidx - written;
        bool res = stream->ops->write( stream->handle, stream->buffer + written, 
                              toWrite, &justWrote);
        written += justWrote;
        stream->pos.offset += justWrote;

        if(!res) {
            stream->status |=_PDCLIB_ERRORFLAG;
            stream->bufidx -= written;
            memmove( stream->buffer, stream->buffer + written, stream->bufidx );
            return EOF;
        }
    }

    stream->bufidx = 0;
    return 0;
}

#endif


#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif

