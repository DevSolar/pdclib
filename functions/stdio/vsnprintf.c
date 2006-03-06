/* $Id$ */

/* Release $Name$ */

/* vsnprintf( char *, size_t, const char *, va_list ap )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

typedef char wchar_t;

int vsnprintf( char * str, size_t size, const char * format, _PDCLIB_va_list arg )
{
    /* TODO: This function should interpret format as multibyte characters. */
    /* TODO: Implement */
    return 0;
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
