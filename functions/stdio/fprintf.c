/* $Id$ */

/* fprintf( FILE *, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int fprintf( struct _PDCLIB_file_t * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, ... )
{
    int rc;
    va_list ap;
    va_start( ap, format );
    rc = vfprintf( stream, format, ap );
    va_end( ap );
    return rc;
}

#endif

#ifdef TEST
#include <limits.h>
#include <string.h>
#include <_PDCLIB_test.h>

#define testprintf( stream, format, ... ) fprintf( stream, format, __VA_ARGS__ )

#define TESTCASE_SPRINTF( x )

int main( void )
{
    FILE * target;
    TESTCASE( ( target = fopen( "testing/testfile", "wb" ) ) != NULL );
#include "printf_testcases.incl"
    TESTCASE( fclose( target ) == 0 );
#include "fprintf_reftest.incl"
    TESTCASE( remove( "testing/testfile" ) == 0 );
    return TEST_RESULTS;
}

#endif
