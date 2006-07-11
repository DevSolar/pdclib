/* $Id$ */

/* fgets( char *, int, FILE * );

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

char * fgets( char * _PDCLIB_restrict s, int n, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    /* TODO: Implement. */
    return NULL;
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
