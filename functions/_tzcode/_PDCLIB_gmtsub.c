/* _PDCLIB_gmtsub( struct state const *, time_t const *, int_fast32_t, struct tm * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

/* gmtsub is to gmtime as localsub is to localtime. */
struct tm * _PDCLIB_gmtsub( struct state const * sp, time_t const * timep, int_fast32_t offset, struct tm * tmp )
{
    struct tm * result;

    result = _PDCLIB_timesub( timep, offset, &_PDCLIB_gmtmem, tmp );

#ifdef TM_ZONE
    /* Could get fancy here and deliver something such as
       "+xx" or "-xx" if offset is non-zero,
       but this is no time for a treasure hunt.
    */
    tmp->TM_ZONE = ( (char *)( offset ? wildabbr : &_PDCLIB_gmtmem ? _PDCLIB_gmtptr.chars : gmt ) );
#endif

    return result;
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
