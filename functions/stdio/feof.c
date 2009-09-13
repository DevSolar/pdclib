/* $Id$ */

/* feof( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int feof( struct _PDCLIB_file_t * stream )
{
    return stream->status & _PDCLIB_EOFFLAG;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by clearerr(). */
    return TEST_RESULTS;
}

#endif

