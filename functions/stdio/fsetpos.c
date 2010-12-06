/* $Id$ */

/* fsetpos( FILE *, const fpos_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

int fsetpos( struct _PDCLIB_file_t * stream, const struct _PDCLIB_fpos_t * pos )
{
    if ( stream->status & _PDCLIB_FWRITE )
    {
        if ( _PDCLIB_flushbuffer( stream ) == EOF )
        {
            return EOF;
        }
    }
    if ( _PDCLIB_seek( stream, pos->offset, SEEK_SET ) == EOF )
    {
        return EOF;
    }
    stream->pos.status = pos->status;
    /* TODO: Add mbstate. */
    return 0;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* fsetpos() tested together with fsetpos(). */
    return TEST_RESULTS;
}

#endif
