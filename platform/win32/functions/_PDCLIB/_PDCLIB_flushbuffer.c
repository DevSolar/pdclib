/* $Id$ */

/* _PDCLIB_flushbuffer( struct _PDCLIB_file_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub implementation of _PDCLIB_flushbuffer
*/

#include <stdio.h>
#include <string.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <errno.h>
#include <windows.h>

int _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream )
{
    if ( ! ( stream->status & _PDCLIB_FBIN ) )
    {
        /* TODO: Text stream conversion here */
    }

    DWORD written = 0;


    while(written != stream->bufidx) {
        DWORD justWrote;
        DWORD toWrite = stream->bufidx - written;
        BOOL res = WriteFile( stream->handle, stream->buffer + written, 
                              toWrite, &justWrote, NULL);
        written += justWrote;

        if(!res) {
            stream->status |=_PDCLIB_ERRORFLAG;
            stream->bufidx -= written;
            memmove( stream->buffer, stream->buffer + written, stream->bufidx );
            _PDCLIB_w32errno();
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

