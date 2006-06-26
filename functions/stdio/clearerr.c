/* $Id$ */

/* clearerr( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

void clearerr( struct _PDCLIB_file_t * stream )
{
    stream->status &= ~( _PDCLIB_ERRORFLAG | _PDCLIB_EOFFLAG );
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
