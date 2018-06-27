/* asctime( const struct tm * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

char * asctime( const struct tm * timeptr )
{
    return NULL;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
