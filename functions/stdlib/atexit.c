/* $Id$ */

/* Release $Name$ */

/* atexit( void (*)( void ) )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

extern void (*_PDCLIB_regstack[])( void );
extern size_t _PDCLIB_regptr;

int atexit( void (*func)( void ) )
{
    if ( _PDCLIB_regptr == 0 )
    {
        return -1;
    }
    else
    {
        _PDCLIB_regstack[ --_PDCLIB_regptr ] = func;
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
