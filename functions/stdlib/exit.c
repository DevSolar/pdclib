/* $Id$ */

/* Release $Name$ */

/* exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

/* TODO - "except that a function is called after any previously registered
   functions that had already been called at the time it was registered.
*/

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
    _Exit( status );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    /* Unwinding of regstack tested in atexit(). */
    return TEST_RESULTS;
}

#endif
