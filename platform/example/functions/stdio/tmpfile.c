/* $Id$ */

/* tmpfile( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <_PDCLIB_int.h>

struct _PDCLIB_file_t * tmpfile( void )
{
    /* TODO: Implement */
    return NULL;
}

#endif REGTEST

#ifdef TEST
#include <_PDCLIB_test.h>

int main()
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
