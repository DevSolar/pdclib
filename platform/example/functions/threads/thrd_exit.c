/* thrd_exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

extern void pthread_exit( void * ) _PDCLIB_NORETURN;

void thrd_exit( int res )
{
    /* TODO: return value */
    pthread_exit( &res );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    TESTCASE( NO_TESTDRIVER );
#endif
    return TEST_RESULTS;
}

#endif
