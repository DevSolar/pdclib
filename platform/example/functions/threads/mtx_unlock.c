/* mtx_unlock( mtx_t * mtx )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicity casting the parameter. */
extern int pthread_mutex_unlock( mtx_t * );

#ifdef __cplusplus
}
#endif

int mtx_unlock( mtx_t * mtx )
{
    if ( pthread_mutex_unlock( mtx ) == 0 )
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
    /* Tested by the mtx_lock test driver. */
    return TEST_RESULTS;
}

#endif
