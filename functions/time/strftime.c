/* strftime( char * restrict, size_t, const char * restrict, const struct tm * restrict )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

size_t strftime( char * restrict s, size_t maxsize, const char * restrict format, const struct tm * restrict timeptr )
{
    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    return NO_TESTDRIVER;
}

#endif
