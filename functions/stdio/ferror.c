/* $Id$ */

/* ferror( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_io.h>

int ferror_unlocked( FILE * stream )
{
    return stream->status & _PDCLIB_ERRORFLAG;
}

int ferror( FILE * stream )
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

