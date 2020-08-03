/* _PDCLIB_gmtime_r( const time_t *, struct tm * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

/* Re-entrant version of gmtime. */
struct tm * _PDCLIB_gmtime_r( const time_t * timep, struct tm * tmp )
{
    _PDCLIB_gmtcheck();
    return _PDCLIB_gmtsub( _PDCLIB_gmtptr, timep, 0, tmp );
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
