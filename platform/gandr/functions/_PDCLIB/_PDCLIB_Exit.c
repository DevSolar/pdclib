/* _PDCLIB_Exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub implementation of _PDCLIB_Exit
*/

#include <stdlib.h>

#ifndef REGTEST
#include "_PDCLIB_glue.h"
#include <errno.h>

void _PDCLIB_Exit( int status )
{
    for(;;);
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    int UNEXPECTED_RETURN = 0;
    _PDCLIB_Exit( 0 );
    TESTCASE( UNEXPECTED_RETURN );
    return TEST_RESULTS;
}

#endif
