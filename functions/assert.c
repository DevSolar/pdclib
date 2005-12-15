/* _PDCLIB_assert( char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef _PDCLIB_AUX_H
#define _PDCLIB_AUX_H _PDCLIB_AUX_H
#include <_PDCLIB_aux.h>
#endif

#if _PDCLIB_C_VERSION == 99
void _PDCLIB_assert( char const * const message1, char const * const function, char const * const message2 )
{
    fputs( message1, stderr );
    fputs( function, stderr );
    fputs( message2, stderr );
    abort();
}
#else
void _PDCLIB_assert( char const * const message )
{
    fputs( message, stderr );
    abort();
}
#endif


#ifdef TEST
#include <_PDCLIB_test.h>
#include <signal.h>

static int rc = 0;
static int EXPECTED_ABORT = 0;

void aborthandler( int signal )
{
    TESTCASE( ! EXPECTED_ABORT );
    exit( rc );
}

#define NDEBUG
#include <assert.h>

int disabled_test()
{
    int i = 0;
    assert( i == 0 ); /* NDEBUG set, condition met */
    assert( i == 1 ); /* NDEBUG set, condition fails */
    return i;
}

#undef NDEBUG
#include <assert.h>

int main()
{
    int i = 0;
    BEGIN_TESTS;
    TESTCASE( signal( SIGABRT, &aborthandler ) != SIG_ERR );
    assert( i == 0 ); /* NDEBUG not set, condition met */
    puts( "Expecting failed assert() message here:" );
    assert( i == 1 ); /* NDEBUG not set, condition fails - should abort */
    return TEST_RESULTS;
}

#endif
