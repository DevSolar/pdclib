/* $Id$ */

/* Release $Name$ */

/* exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

struct _PDCLIB_exitfunc_t * regstack = NULL;

void exit( int status )
{
    struct _PDCLIB_exitfunc_t * next = regstack;
    while ( next != NULL )
    {
        next->func();
        regstack = next->next;
        free( next );
        next = regstack;
    }
    /* TODO: Flush and close open streams. Remove tmpfile() files. */
    _Exit( status );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main()
{
    int NO_TESTDRIVER = 0;
    BEGIN_TESTS;
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
