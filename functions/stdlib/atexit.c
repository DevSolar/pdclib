/* $Id$ */

/* Release $Name$ */

/* atexit( void (*)( void ) )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

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
#include <assert.h>

static int flags[ 32 ];

static void counthandler()
{
    static int rc = 0;
    flags[ rc ] = rc;
    ++rc;
}

static void checkhandler()
{
    for ( int i = 0; i < 31; ++i )
    {
        assert( flags[ i ] == i );
    }
}

int main()
{
    BEGIN_TESTS;
    TESTCASE( atexit( &checkhandler ) == 0 );
    for ( int i = 0; i < 31; ++i )
    {
        TESTCASE( atexit( &counthandler ) == 0 );
    }
    return TEST_RESULTS;
}

#endif
