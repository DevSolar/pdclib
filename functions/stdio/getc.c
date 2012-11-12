/* $Id$ */

/* getc( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int getc_unlocked( struct _PDCLIB_file_t * stream )
{
    return fgetc_unlocked( stream );
}

int getc( struct _PDCLIB_file_t * stream )
{
    return fgetc( stream );
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
