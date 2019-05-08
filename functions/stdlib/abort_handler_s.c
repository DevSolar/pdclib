/* abort_handler_s( const char *, void *, errno_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>

#ifndef REGTEST

#include <stdio.h>

void abort_handler_s( const char * _PDCLIB_restrict msg, void * _PDCLIB_restrict ptr, errno_t errno )
{
    fprintf( stderr, "abort handler called:\n%s\n", msg );
    abort();
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
