/* tss_set( tss_t, void * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the first parameter. */
extern int pthread_setspecific( tss_t, const void * );

#ifdef __cplusplus
}
#endif

int tss_set( tss_t key, void * val )
{
    if ( pthread_setspecific( key, val ) == 0 )
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
