/* call_once( once_flag *, void (*)( void ) )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

/* Implicitly casting the parameter. */
extern int pthread_once( once_flag *, void (*)( void ) );

void call_once( once_flag * flag, void (*func)( void ) )
{
    pthread_once( flag, func );
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
