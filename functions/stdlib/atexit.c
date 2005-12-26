/* $Id$ */

/* Release $Name$ */

/* atexit( void (*)( void ) )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

/* TODO: Required by both atexit() and exit(). */
struct _PDCLIB_exitfunc_t
{
    struct _PDCLIB_exitfunc_t * next;
    void (*func)( void );
};

extern struct _PDCLIB_exitfunc_t * regstack;

int atexit( void (*func)( void ) )
{
    struct _PDCLIB_exitfunc_t * regfunc = (struct _PDCLIB_exitfunc_t *)malloc( sizeof( struct _PDCLIB_exitfunc_t ) );
    if ( regfunc == NULL )
    {
        return -1;
    }
    else
    {
        regfunc->func = func;
	regfunc->next = regstack;
	regstack = regfunc;
	return 0;
    }
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
