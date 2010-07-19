/* $Id$ */

/* vprintf( const char *, va_list arg )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int vprintf( const char * _PDCLIB_restrict format, _PDCLIB_va_list arg )
{
    return vfprintf( stdout, format, arg );
}

#endif

#ifdef TEST
#include <limits.h>
#include <string.h>
#include <_PDCLIB_test.h>

static int testprintf( FILE * stream, size_t n, const char * format, ... )
{
    int i;
    va_list arg;
    va_start( arg, format );
    i = vprintf( format, arg );
    va_end( arg );
    return i;
}

int main( void )
{
    FILE * buffer;
    TESTCASE( ( buffer = freopen( testfile, "wb", stdout ) ) != NULL );
#include "printf_testcases.incl"
    TESTCASE( fclose( buffer ) == 0 );
#include "fprintf_reftest.incl"
    TESTCASE( remove( testfile ) == 0 );
    return TEST_RESULTS;
}

#endif
