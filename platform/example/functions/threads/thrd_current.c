/* thrd_current( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the return type. */
extern thrd_t pthread_self( void );

#ifdef __cplusplus
}
#endif

thrd_t thrd_current( void )
{
    return ( thrd_t )pthread_self();
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#ifndef REGTEST

#define COUNT 10
thrd_t   g_thread[COUNT];
unsigned g_index[COUNT] = { 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u };

static int func( void * arg )
{
    TESTCASE( thrd_equal( g_thread[ *( unsigned * )arg ], thrd_current() ) != 0 );
    return 0;
}

#endif

int main( void )
{
#ifndef REGTEST

    for ( unsigned i = 0; i < COUNT; ++i )
    {
        TESTCASE( thrd_create( &g_thread[i], func, &g_index[i] ) == thrd_success );
    }

    for ( unsigned i = 0; i < COUNT; ++i )
    {
        TESTCASE( thrd_join( g_thread[i], NULL ) == thrd_success );
    }

#endif
    return TEST_RESULTS;
}

#endif
