/* tss_create( tss_t *, tss_dtor_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the parameters. */
extern int pthread_key_create( tss_t *, tss_dtor_t );

#ifdef __cplusplus
}
#endif

int tss_create( tss_t * key, tss_dtor_t dtor )
{
    if ( pthread_key_create( key, dtor ) == 0 )
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
