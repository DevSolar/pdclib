/* _PDCLIB_errno

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#if __STDC_VERSION__ >= 201112L
_Thread_local int _PDCLIB_errno = 0;
#else
static int _PDCLIB_errno = 0;
#endif

int * _PDCLIB_errno_func()
{
    return &_PDCLIB_errno;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <errno.h>

#if ! defined( REGTEST ) && __STDC_VERSION__ >= 201112L

#include <threads.h>

static int thread_func( void * arg )
{
    TESTCASE( errno == 0 );
    *_PDCLIB_errno_func() = 1;
    TESTCASE( errno == 1 );
    thrd_exit( 0 );
}

#endif

int main( void )
{
    errno = 0;
    TESTCASE( errno == 0 );
    errno = EDOM;
    TESTCASE( errno == EDOM );
    errno = ERANGE;
    TESTCASE( errno == ERANGE );

#if ! defined( REGTEST ) && __STDC_VERSION__ >= 201112L
    {
        thrd_t t;
        struct timespec spec = { 1, 0 };
        int rc;

        TESTCASE( thrd_create( &t, thread_func, NULL ) == thrd_success );

        TESTCASE( thrd_sleep( &spec, NULL ) == 0 );
        TESTCASE( errno == ERANGE );
        TESTCASE( thrd_join( t, &rc ) == thrd_success );
        TESTCASE( rc == 0 );
    }
#endif

    return TEST_RESULTS;
}

#endif
