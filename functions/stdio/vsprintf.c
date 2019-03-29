/* vsprintf( char *, const char *, va_list )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef REGTEST

int vsprintf( char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, va_list arg )
{
#if __GCC__
/* POSIX requires an EOVERFLOW failure for bounds > INT_MAX, which is in
   conflict with the C standard. We explicitly disable the warning GCC
   emits about SIZE_MAX > INT_MAX.
*/
#pragma GCC diagnostics push
#pragma GCC diagnostics ignored "-Wformat-truncation="
#endif
    return vsnprintf( s, SIZE_MAX, format, arg ); /* TODO: Replace with a non-checking call */
#if __GCC__
#pragma GCC diagnostics pop
#endif
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "stdio/vsprintf.c"
#define _PDCLIB_STRINGIO
#include <stdint.h>
#include <stddef.h>
#include "_PDCLIB_test.h"

static int testprintf( char * s, const char * format, ... )
{
    int i;
    va_list arg;
    va_start( arg, format );
    i = vsprintf( s, format, arg );
    va_end( arg );
    return i;
}

int main( void )
{
    char target[100];
#include "printf_testcases.h"
    return TEST_RESULTS;
}

#endif
