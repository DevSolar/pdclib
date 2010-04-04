/* $Id$ */

/* _PDCLIB_prepread( struct _PDCLIB_file_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#define _PDCLIB_GLUE_H _PDCLIB_GLUE_H
#include <_PDCLIB_glue.h>

int _PDCLIB_prepread( struct _PDCLIB_file_t * stream )
{
    if ( ( stream->bufidx > stream->bufend ) ||
         ( stream->status & ( _PDCLIB_FWRITE | _PDCLIB_FAPPEND | _PDCLIB_ERRORFLAG | _PDCLIB_WIDESTREAM | _PDCLIB_EOFFLAG ) ) ||
         ! ( stream->status & ( _PDCLIB_FREAD | _PDCLIB_FRW ) ) )
    {
        _PDCLIB_errno = _PDCLIB_EIO;
        stream->status |= _PDCLIB_ERRORFLAG;
        return EOF;
    }
    stream->status |= _PDCLIB_FREAD | _PDCLIB_BYTESTREAM;
    if ( ( stream->bufidx == stream->bufend ) && ( stream->ungetidx == 0 ) )
    {
        return _PDCLIB_fillbuffer( stream );
    }
    else
    {
        return 0;
    }
}

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif

