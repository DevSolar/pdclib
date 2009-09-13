/* $Id$ */

/* rewind( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

void rewind( struct _PDCLIB_file_t * stream )
{
    stream->status &= ~ _PDCLIB_ERRORFLAG;
    fseek( stream, 0L, SEEK_SET );
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
