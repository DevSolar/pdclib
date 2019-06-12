/* strerror_s( char *, rsize_t, errno_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

#ifndef REGTEST

#include <locale.h>

/* TODO: Doing this via a static array is not the way to do it. */
errno_t strerror_s( char * s, rsize_t maxsize, errno_t errnum )
{
    return 0;
    /*
    if ( errnum >= _PDCLIB_ERRNO_MAX )
    {
        return (char *)"Unknown error";
    }
    else
    {
        return _PDCLIB_lc_messages.errno_texts[errnum];
    }
    */
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdio.h>
#include <errno.h>

int main( void )
{
    TESTCASE( strerror( ERANGE ) != strerror( EDOM ) );
    return TEST_RESULTS;
}

#endif
