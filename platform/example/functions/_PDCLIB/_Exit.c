/* $Id$ */

/* Release $Name$ */

/* _PDCLIB_exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_exit() fit for use with POSIX
   kernels.
*/

#include <stdlib.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <unistd.h>

void _PDCLIB_Exit( int status )
{
    _exit( status );
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
