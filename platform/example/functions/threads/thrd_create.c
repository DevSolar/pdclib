/* thrd_create( thrd_t *, thrd_start_t, void * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the first parameters. */
extern int pthread_create( thrd_t *, const _PDCLIB_thrd_attr_t *, thrd_start_t, void * );

#ifdef __cplusplus
}
#endif

int thrd_create( thrd_t * thr, thrd_start_t func, void * arg )
{
    if ( pthread_create( thr, NULL, func, arg ) == 0 )
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
thrd_t g_thread[ COUNT ] = {0};
int g_count = 0;

static int func( void * arg )
{
    ++g_count;
    return 0;
}

#endif

int main( void )
{
#ifndef REGTEST

    for ( unsigned i = 0; i < COUNT; ++i )
    {
        TESTCASE( thrd_create( &g_thread[i], func, NULL ) == thrd_success );
    }

    for ( unsigned i = 0; i < COUNT; ++i )
    {
        TESTCASE( thrd_join( g_thread[i], NULL ) == thrd_success );
    }

    TESTCASE( g_count == COUNT );
#endif
    return TEST_RESULTS;
}

#endif
