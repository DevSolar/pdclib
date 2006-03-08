/* $Id$ */

/* vscanf( const char *, va_list arg )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int vscanf( const char * _PDCLIB_restrict format, _PDCLIB_va_list arg )
{
    return vfscanf( stdin, format, arg );
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
