/* thrd_exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <stdint.h>
#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

extern _PDCLIB_Noreturn void pthread_exit( void * ) _PDCLIB_NORETURN;

#ifdef __cplusplus
}
#endif

void thrd_exit( int res )
{
    pthread_exit( ( void * )( uintptr_t )res );
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
