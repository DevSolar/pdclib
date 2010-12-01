/* $Id$ */

/* snprintf( char *, size_t, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int snprintf( char * _PDCLIB_restrict s, size_t n, const char * _PDCLIB_restrict format, ...)
{
    int rc;
    va_list ap;
    va_start( ap, format );
    rc = vsnprintf( s, n, format, ap );
    va_end( ap );
    return rc;
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "stdio/snprintf.c"
#define SPRINTF_FUNCTION
#include <_PDCLIB_test.h>

#include <string.h>
#include <limits.h>

#define testprintf( s, format, ... ) snprintf( s, 100, format, __VA_ARGS__ )

int main( void )
{
    char target[100];
#include "printf_testcases.incl"
    return TEST_RESULTS;
}

#endif
