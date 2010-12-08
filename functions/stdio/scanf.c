/* $Id$ */

/* scanf( const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int scanf( const char * _PDCLIB_restrict format, ... )
{
    va_list ap;
    va_start( ap, format );
    return vfscanf( stdin, format, ap );
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "stdio/scanf.c"
#define _PDCLIB_FILEIO

#include <_PDCLIB_test.h>

#define testscanf( stream, format, ... ) scanf( format, __VA_ARGS__ )

int main( void )
{
    FILE * source;
    TESTCASE( ( source = freopen( testfile, "wb+", stdin ) ) != NULL );
#include "scanf_testcases.h"
    TESTCASE( fclose( source ) == 0 );
    TESTCASE( remove( testfile ) == 0 );
    return TEST_RESULTS;
}

#endif
