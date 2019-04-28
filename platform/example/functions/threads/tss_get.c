/* tss_get( tss_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

/* Implicitly casting the parameter. */
extern void * pthread_getspecific( tss_t );

void * tss_get( tss_t key )
{
    return pthread_getspecific( key );
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
