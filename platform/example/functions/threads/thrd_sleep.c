/* thrd_sleep( const struct timespec *, struct timespec * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#include "/usr/include/errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the parameters. */
extern int nanosleep( const struct timespec *, struct timespec * );

#ifdef __cplusplus
}
#endif

int thrd_sleep( const struct timespec * duration, struct timespec * remaining )
{
    errno = 0;

    if ( nanosleep( duration, remaining ) == 0 )
    {
        return 0;
    }

    if ( errno == EINTR )
    {
        return -1;
    }

    return -2;
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
