/* $Id$ */

/* _PDCLIB_digits

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>
#endif

char _PDCLIB_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

#ifdef TEST
#include <_PDCLIB_test.h>

#include <string.h>

int main( void )
{
    TESTCASE( strcmp( _PDCLIB_digits, "0123456789abcdefghijklmnopqrstuvwxyz" ) == 0 );
    return TEST_RESULTS;
}

#endif
