/* mtx_lock( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the parameter. */
extern int pthread_mutex_lock( mtx_t * );

#ifdef __cplusplus
}
#endif

int mtx_lock( mtx_t * mtx )
{
    if ( pthread_mutex_lock( mtx ) == 0 )
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

#ifndef REGTEST

#define COUNT 10
thrd_t g_thread[COUNT];
mtx_t g_mutex;

static int func( void * arg )
{
    TESTCASE( mtx_lock( &g_mutex ) == thrd_success );
    thrd_yield();
    TESTCASE( mtx_unlock( &g_mutex ) == thrd_success );
    return 0;
}

#endif

int main( void )
{
#ifndef REGTEST
    TESTCASE( mtx_init( &g_mutex, mtx_plain ) == thrd_success );

    for ( unsigned i = 0; i < COUNT; ++i )
    {
        TESTCASE( thrd_create( &g_thread[i], func, NULL ) == thrd_success );
    }

    for ( unsigned i = 0; i < COUNT; ++i )
    {
        TESTCASE( thrd_join( g_thread[i], NULL ) == thrd_success );
    }

#endif
    return TEST_RESULTS;
}

#endif
