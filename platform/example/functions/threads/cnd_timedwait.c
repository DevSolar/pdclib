/* cnd_timedwait( cnd_t *, mtx_t, const struct timespec * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#include "/usr/include/errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casing the parameters. */
extern int pthread_cond_timedwait( cnd_t *, mtx_t *, const struct timespec * );

#ifdef __cplusplus
}
#endif

int cnd_timedwait( cnd_t * _PDCLIB_restrict cond, mtx_t * _PDCLIB_restrict mtx, const struct timespec * _PDCLIB_restrict ts )
{
    switch ( pthread_cond_timedwait( cond, mtx, ts ) )
    {
        case 0:
            return thrd_success;

        case ETIMEDOUT:
            return thrd_timedout;

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
