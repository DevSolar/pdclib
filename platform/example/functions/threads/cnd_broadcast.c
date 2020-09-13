/* cnd_broadcast( cnd_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the parameter. */
extern int pthread_cond_broadcast( cnd_t * );

#ifdef __cplusplus
}
#endif

int cnd_broadcast( cnd_t * cond )
{
    if ( pthread_cond_broadcast( cond ) == 0 )
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
