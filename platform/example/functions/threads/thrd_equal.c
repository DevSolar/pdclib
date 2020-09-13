/* thrd_equal( thrd_t, thrd_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the parameters. */
extern int pthread_equal( thrd_t, thrd_t );

#ifdef __cplusplus
}
#endif

int thrd_equal( thrd_t thr0, thrd_t thr1 )
{
    return pthread_equal( thr0, thr1 );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Tested by thrd_current test driver. */
    return TEST_RESULTS;
}

#endif
