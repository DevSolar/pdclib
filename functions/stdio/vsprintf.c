/* $Id$ */

/* vsprintf( char *, const char *, va_list ap )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef REGTEST

int foo = SIZE_MAX;

int vsprintf( char * str, const char * format, va_list arg )
{
    return vsnprintf( str, SIZE_MAX, format, arg ); /* TODO: Replace with a non-checking call */
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
