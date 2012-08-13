/* $Id$ */

/* _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub version of _PDCLIB_fillbuffer
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <errno.h>
#include <windows.h>

void _PDCLIB_w32errno(void);
int _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream )
{
    DWORD nBytesRead;
    BOOL ok = ReadFile( stream->handle, stream->buffer, stream->bufsize,
                        &nBytesRead, NULL );

    if( ok ) {
        if( nBytesRead == 0 ) {
            stream->status |= _PDCLIB_EOFFLAG;
            return EOF;
        }
        stream->pos.offset += nBytesRead;
        stream->bufend = nBytesRead;
        stream->bufidx = 0;
        return 0;
    } else {
        _PDCLIB_w32errno();
        stream->status |= _PDCLIB_ERRORFLAG;
        return EOF;
    }
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

