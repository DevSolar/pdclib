/* mtx_init( mtx_t *, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

int mtx_init( mtx_t * mtx, int type )
{
    /* As far as I could figure out from Pthread documentation, there is
       no special requirement for a Pthread mutex to support timeout (the
       default "fast" mutex already supports that). So the only thing we
       check for in type is whether the mutex shall be recursive or not.
    */
    if ( type & mtx_recursive )
    {
        _PDCLIB_mtx_t recursive_mutex = _PDCLIB_MTX_RECURSIVE_INIT;
        *mtx = recursive_mutex;
    }
    else
    {
        _PDCLIB_mtx_t plain_mutex = _PDCLIB_MTX_PLAIN_INIT;
        *mtx = plain_mutex;
    }

    return thrd_success;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <string.h>

int main( void )
{
#ifndef REGTEST
    mtx_t plain;
    mtx_t plain_test = _PDCLIB_MTX_PLAIN_INIT;

    mtx_t recursive;
    mtx_t recursive_test = _PDCLIB_MTX_RECURSIVE_INIT;

    TESTCASE( mtx_init( &plain, mtx_plain ) == thrd_success );
    TESTCASE( memcmp( &plain, &plain_test, sizeof( mtx_t ) ) == 0 );

    TESTCASE( mtx_init( &recursive, mtx_recursive ) == thrd_success );
    TESTCASE( memcmp( &recursive, &recursive_test, sizeof( mtx_t ) ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
