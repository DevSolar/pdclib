/* $Id$ */

/* fscanf( FILE *, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int fscanf( FILE * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, ... )
{
    int rc;
    va_list ap;
    va_start( ap, format );
    rc = vfscanf( stream, format, ap );
    va_end( ap );
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include "scan_test.h"

int main( void )
{
#define SCANFUNC( source, format, ... ) fscanf( source, format, __VA_ARGS__ )
#include "fscan_sources.incl"
#include "scanf_testcases.incl"
    return TEST_RESULTS;
}

#endif
