/* mktime( struct tm * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_time_mtx;
#endif

time_t mktime( struct tm * timeptr )
{
    time_t t;
    _PDCLIB_LOCK( _PDCLIB_time_mtx );
    _PDCLIB_tzset_unlocked();
    t = _PDCLIB_mktime_tzname( &_PDCLIB_lclmem, timeptr, true );
    _PDCLIB_UNLOCK( _PDCLIB_time_mtx );
    return t;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <limits.h>

int main( void )
{
    /* System Clock DST */
    struct tm time;
    time_t t;

    MKTIME( time, 52, 45, 21, 13, 11, 1, 0, 0 );
    t = mktime( &time );
    TESTCASE( t == -2147483648l );

    MKTIME( time, 7, 14, 4, 19, 0, 138, 0, 0 );
    t = mktime( &time );
    TESTCASE( t == 2147483647l );

    return TEST_RESULTS;
}

#endif
