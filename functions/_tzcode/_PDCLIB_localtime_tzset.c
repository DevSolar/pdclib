/* _PDCLIB_localtime_tzset( time_t const *, struct tm *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_time_mtx;
#endif

#include <string.h>

struct tm * _PDCLIB_localtime_tzset( time_t const * timep, struct tm * tmp, bool setname )
{
    _PDCLIB_LOCK( _PDCLIB_time_mtx );

    if ( setname || ! lcl_is_set )
    {
        _PDCLIB_tzset_unlocked();
    }

    tmp = _PDCLIB_localsub( &_PDCLIB_lclmem, timep, setname, tmp );
    _PDCLIB_UNLOCK( _PDCLIB_time_mtx );
    return tmp;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
#endif

    return TEST_RESULTS;
}

#endif
