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

int main()
{
    int NO_TESTDRIVER = 0;
    BEGIN_TESTS;
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
