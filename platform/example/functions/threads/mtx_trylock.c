/* mtx_trylock( mtx_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#include "/usr/include/errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Implicity casting the parameter. */
extern int pthread_mutex_trylock( mtx_t * );

#ifdef __cplusplus
}
#endif

int mtx_trylock( mtx_t * mtx )
{
    switch ( pthread_mutex_trylock( mtx ) )
    {
        case 0:
            return thrd_success;

        case EBUSY:
            return thrd_busy;

        default:
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
