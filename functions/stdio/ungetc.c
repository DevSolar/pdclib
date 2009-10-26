/* $Id$ */

/* ungetc( int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int ungetc( int c, struct _PDCLIB_file_t * stream )
{
    if ( c == EOF || stream->ungetidx == _PDCLIB_UNGETCBUFSIZE )
    {
        return -1;
    }
    return stream->ungetbuf[stream->ungetidx++] = (unsigned char) c;
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
