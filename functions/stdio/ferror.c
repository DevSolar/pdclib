/* $Id$ */

/* ferror( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int ferror_unlocked( struct _PDCLIB_file_t * stream )
{
    return stream->status & _PDCLIB_ERRORFLAG;
}

int ferror( struct _PDCLIB_file_t * stream )
{
    flockfile( stream );
    int error = ferror_unlocked( stream );
    funlockfile( stream );
    return error;
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

