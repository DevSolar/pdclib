/* thrd_join( thrd_t, int * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

/* Implicitly casting the first parameter. */
extern int pthread_join( thrd_t, void ** );

int thrd_join( thrd_t thr, int * res )
{
    /* TODO: return value */
    if ( pthread_join( thr, (void **)&res ) == 0 )
    {
        return thrd_success;
    }
    else
    {
        return thrd_error;
    }
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
