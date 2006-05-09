/* $Id$ */

/* gets( char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <limits.h>

#ifndef REGTEST

char * gets( char * s )
{
    return fgets( s, INT_MAX, stdin ); /* TODO: Replace with an unchecking call. */
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
