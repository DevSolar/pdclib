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
#if __GCC__
/* POSIX requires an EOVERFLOW failure for bounds > INT_MAX, which is in
   conflict with the C standard. We explicitly disable the warning GCC
   emits about SIZE_MAX > INT_MAX.
*/
#pragma GCC diagnostics push
#pragma GCC diagnostics ignored "-Wformat-truncation="
#endif
    rc = vsnprintf( s, SIZE_MAX, format, ap ); /* TODO: replace with non-checking call */
#if __GCC__
#pragma GCC diagnostics pop
#endif
    va_end( ap );
    return rc;
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "stdio/sprintf.c"
#define _PDCLIB_STRINGIO
#include <stddef.h>

#include "_PDCLIB_test.h"

#define testprintf( s, ... ) sprintf( s, __VA_ARGS__ )

int main( void )
{
    char target[100];
#include "printf_testcases.h"
    return TEST_RESULTS;
}

#endif
