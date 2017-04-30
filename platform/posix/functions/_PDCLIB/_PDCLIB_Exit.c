/* _PDCLIB_Exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST
#include "_PDCLIB_glue.h"

extern void _exit( int status ) _PDCLIB_noreturn;

void _PDCLIB_Exit( int status )
{
    _exit( status );
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    int UNEXPECTED_RETURN = 0;
    _PDCLIB_Exit( 0 );
    TESTCASE( UNEXPECTED_RETURN );
#endif
    return TEST_RESULTS;
}

#endif
