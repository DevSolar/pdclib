/* $Id$ */

/* strerror( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>

#ifndef REGTEST

/* TODO: Doing this via a static array is not the way to do it. */
char * strerror( int errnum )
{
    return (char *)_PDCLIB_errno_texts[ errnum ];
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <stdio.h>
#include <errno.h>

int main( void )
{
    TESTCASE( strerror( ERANGE ) != strerror( EDOM ) );
    return TEST_RESULTS;
}
#endif
