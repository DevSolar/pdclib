/* $Id$ */

/* sprintf( char *, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef REGTEST

int sprintf( char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, ...)
{
    int rc;
    va_list ap;
    va_start( ap, format );
    rc = vsnprintf( s, SIZE_MAX, format, ap );
    va_end( ap );
    return rc;
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
