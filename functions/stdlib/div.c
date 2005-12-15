/* $Id$ */

/* Release $Name$ */

/* div( int, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

div_t div( int numer, int denom )
{
    div_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    /* TODO: pre-C99 compilers might require modulus corrections */
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#ifndef _PDCLIB_CONFIG_H
#include <_PDCLIB_config.h>
#endif

int main()
{
    div_t idiv;
    BEGIN_TESTS;
    idiv = div( 5, 2 );
    TESTCASE( idiv.quot == 2 && idiv.rem == 1 );
    idiv = div( -5, 2 );
    TESTCASE( idiv.quot == -2 && idiv.rem == -1 );
    idiv = div( 5, -2 );
    TESTCASE( idiv.quot == -2 && idiv.rem == 1 );
    TESTCASE( sizeof( idiv.quot ) == _PDCLIB_INT_BYTES );
    TESTCASE( sizeof( idiv.rem )  == _PDCLIB_INT_BYTES );
    return TEST_RESULTS;
}

#endif
