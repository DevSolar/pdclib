/* thrd_yield( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int sched_yield( void );

#ifdef __cplusplus
}
#endif

void thrd_yield( void )
{
    sched_yield();
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
