/* $Id$ */

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

extern void _exit( int status ) _PDCLIB_NORETURN;

void _PDCLIB_Exit( int status )
{
    _exit( status );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    int UNEXPECTED_RETURN = 0;
    _PDCLIB_Exit( 0 );
    TESTCASE( UNEXPECTED_RETURN );
    return TEST_RESULTS;
}

#endif
