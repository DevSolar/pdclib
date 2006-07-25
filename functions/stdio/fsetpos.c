/* $Id$ */

/* fsetpos( FILE *, const fpos_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int fsetpos( struct _PDCLIB_file_t * stream, const _PDCLIB_fpos_t * pos )
{
    if ( stream->status & _PDCLIB_WROTELAST )
    {
        fflush( stream );
    }
    /* TODO: Implement. */
    return 0;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
