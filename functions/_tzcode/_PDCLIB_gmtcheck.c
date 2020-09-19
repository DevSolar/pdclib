/* _PDCLIB_gmtcheck( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_time_mtx;
#endif

static void gmtload( struct state * sp )
{
    if ( _PDCLIB_tzload( gmt, sp, true ) != 0 )
    {
        _PDCLIB_tzparse( gmt, sp, true );
    }
}

void _PDCLIB_gmtcheck( void )
{
    static bool gmt_is_set;

    _PDCLIB_LOCK( _PDCLIB_time_mtx );

    if ( ! gmt_is_set )
    {
        gmtload( &_PDCLIB_gmtmem );
        gmt_is_set = true;
    }

    _PDCLIB_UNLOCK( _PDCLIB_time_mtx );
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
