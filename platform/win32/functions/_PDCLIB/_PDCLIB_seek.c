/* $Id$ */

/* int64_t _PDCLIB_seek( FILE *, int64_t, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <errno.h>
#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <windows.h>

#if _PDCLIB_C_MIN(2011)
_Static_assert(SEEK_SET == FILE_BEGIN, "SEEK_SET is incorrect");
_Static_assert(SEEK_CUR == FILE_CURRENT, "SEEK_CUR is incorrect");
_Static_assert(SEEK_END == FILE_END, "SEEK_END is incorrect");
#endif

extern void _PDCLIB_w32errno( void );
_PDCLIB_int64_t _PDCLIB_seek( struct _PDCLIB_file_t * stream, _PDCLIB_int64_t offset, int whence )
{
    LARGE_INTEGER liOffset;
    liOffset.QuadPart = offset;
    BOOL rv = SetFilePointerEx( stream->handle, liOffset, &liOffset, whence );
    if(!rv) {
        _PDCLIB_w32errno();
        return EOF;
    }

    stream->ungetidx = 0;
    stream->bufidx = 0;
    stream->bufend = 0;
    stream->pos.offset = liOffset.QuadPart;
    return liOffset.QuadPart;
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

