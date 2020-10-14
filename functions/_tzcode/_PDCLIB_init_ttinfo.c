/* _PDCLIB_init_ttinfo( struct ttinfo *, int_fast32_t, bool, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

/* Initialize *S to a value based on UTOFF, ISDST, and DESIGIDX.  */
void _PDCLIB_init_ttinfo( struct ttinfo * s, int_fast32_t utoff, bool isdst, int desigidx )
{
    s->utoff = utoff;
    s->isdst = isdst;
    s->desigidx = desigidx;
    s->ttisstd = false;
    s->ttisut = false;
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
