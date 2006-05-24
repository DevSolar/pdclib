/* $Id$ */

/* _PDCLIB_Xdigits

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>
#endif

char _PDCLIB_Xdigits[] = "0123456789ABCDEF";

#ifdef TEST
#include <_PDCLIB_test.h>

#include <string.h>

int main( void )
{
    TESTCASE( strcmp( _PDCLIB_Xdigits, "0123456789ABCDEF" ) == 0 );
    return TEST_RESULTS;
}

#endif
