/* thrd_yield( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ANDROID__
extern int pthread_yield( void );
#define yield pthread_yield
#else
extern int sched_yield( void );
#define yield sched_yield
#endif

#ifdef __cplusplus
}
#endif

void thrd_yield( void )
{
    yield();
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
