/* _PDCLIB_update_tzname_etc( struct state const *, struct ttinfo const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

void _PDCLIB_update_tzname_etc( struct state const * sp, struct ttinfo const * ttisp )
{
#if HAVE_TZNAME
    tzname[ ttisp->isdst ] = (char *) &sp->chars[ ttisp->desigidx ];
#endif
#if USG_COMPAT
    if ( ! ttisp->isdst )
    {
        timezone = - ttisp->utoff;
    }
#endif
#if ALTZONE
    if ( ttisp->isdst )
    {
        altzone = - ttisp->utoff;
    }
#endif
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
