/* $Id$ */

/* vsprintf( char *, const char *, va_list ap )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef REGTEST

int vsprintf( char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, va_list arg )
{
    return vsnprintf( s, SIZE_MAX, format, arg ); /* TODO: Replace with a non-checking call */
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <limits.h>
#include <stdint.h>
#include <string.h>

static int testprintf( char * s, size_t n, const char * format, ... )
{
    int i;
    va_list arg;
    va_start( arg, format );
    i = vsprintf( s, format, arg );
    va_end( arg );
    return i;
}

#define TESTCASE_SPRINTF( x ) if ( strcmp( buffer, x ) == 0 ) {} \
                              else { TEST_RESULTS += 1; printf( "FAILED: " __FILE__ ", line %d - \"%s\" != %s\n", __LINE__, buffer, #x ); }

int main( void )
{
    char buffer[100];
#include "printf_testcases.incl"
    return TEST_RESULTS;
}

#endif
