/* difftime( time_t, time_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

double difftime( time_t time1, time_t time0 )
{
    return 0.0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    return NO_TESTDRIVER;
}

#endif
