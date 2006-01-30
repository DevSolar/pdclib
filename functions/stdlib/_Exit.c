/* $Id$ */

/* Release $Name$ */

/* _Exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H
#include <_PDCLIB_config.h>

#ifndef REGTEST

void _Exit( int status )
{
    _PDCLIB_Exit( status );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
