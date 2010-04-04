/* $Id$ */

/* fgetc( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#include <_PDCLIB_glue.h>

#ifndef REGTEST

int fgetc( struct _PDCLIB_file_t * stream )
{
    if ( _PDCLIB_prepread( stream ) == EOF )
    {
        return EOF;
    }
    if ( stream->ungetidx > 0 )
    {
        return stream->ungetbuf[ stream->ungetidx-- ];
    }
    return stream->buffer[stream->bufidx++];
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
