/* $Id$ */

/* Release $Name$ */

/* lldiv( long long int, long long int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

lldiv_t lldiv( long long int numer, long long int denom )
{
    lldiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    /* TODO */
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main()
{
    int NO_TESTDRIVER = 0;
    BEGIN_TESTS;
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
