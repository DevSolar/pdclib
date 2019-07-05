/* strerror_s( char *, rsize_t, errno_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST

#include <locale.h>

errno_t strerror_s( char * s, rsize_t maxsize, errno_t errnum )
{
    size_t len = strerrorlen_s( errnum );

    if ( s == NULL || maxsize > RSIZE_MAX || maxsize == 0 )
    {
        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return _PDCLIB_EINVAL;
    }

    if ( len < maxsize )
    {
        strcpy( s, strerror( errnum ) );
    }
    else
    {
        strncpy( s, strerror( errnum ), maxsize - 1 );

        if ( maxsize > 3 )
        {
            strcpy( &s[ maxsize - 4 ], "..." );
        }
        else
        {
            s[ maxsize - 1 ] = '\0';
        }
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdio.h>
#include <errno.h>

int main( void )
{
#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )
    char s[14];
    TESTCASE( strerror_s( s, 14, _PDCLIB_ERRNO_MAX ) == 0 );
    TESTCASE( strcmp( s, "unknown error" ) == 0 );
    TESTCASE( strerror_s( s, 13, _PDCLIB_ERRNO_MAX ) == 0 );
    TESTCASE( strcmp( s, "unknown e..." ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
