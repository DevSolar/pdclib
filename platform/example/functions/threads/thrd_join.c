/* thrd_join( thrd_t, int * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <stdint.h>
#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the first parameter. */
extern int pthread_join( thrd_t, void ** );

#ifdef __cplusplus
}
#endif

int thrd_join( thrd_t thr, int * res )
{
    void * result;
    int rc = pthread_join( thr, &result );

    if ( res != NULL )
    {
        *res = ( int )( uintptr_t )result;
    }

    if ( rc == 0 )
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
