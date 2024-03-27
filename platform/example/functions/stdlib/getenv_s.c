/* getenv_s( size_t *, char *, rsize_t, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of getenv() fit for use with POSIX kernels.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef REGTEST

extern char ** environ;

/* The standard states (7.22.4.6 (3), "the implementation shall behave
   as if no library function calls the getenv function." That is,
   however, in context of the previous paragraph stating that getenv
   "need not avoid data races with other threads of execution that
   modify the environment list".
   PDCLib does not provide means of modifying the environment list.
*/
errno_t getenv_s( size_t * _PDCLIB_restrict len, char * _PDCLIB_restrict value, rsize_t maxsize, const char * _PDCLIB_restrict name )
{
    size_t nlen;
    size_t index = 0;
    size_t vlen = 0;
    char const * environ_value = "";
    errno_t rc = -1;

    if ( name == NULL || maxsize == 0 || maxsize > RSIZE_MAX || value == NULL )
    {
        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return _PDCLIB_EINVAL;
    }

    nlen = strlen( name );

    while ( environ[ index ] != NULL )
    {
        if ( strncmp( environ[ index ], name, nlen ) == 0 )
        {
            environ_value = environ[ index ] + nlen + 1;
            vlen = strlen( environ_value );
            rc = 0;
            break;
        }

        index++;
    }

    if ( len != NULL )
    {
        *len = vlen;
    }

    if ( vlen < maxsize )
    {
        strcpy( value, environ_value );
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )

static int HANDLER_CALLS = 0;

static void test_handler( const char * _PDCLIB_restrict msg, void * _PDCLIB_restrict ptr, errno_t error )
{
    ++HANDLER_CALLS;
}

#endif

int main( void )
{
#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )
    size_t len;
    char value[100];
    set_constraint_handler_s( test_handler );

    TESTCASE( getenv_s( &len, value, 100, "SHELL" ) == 0 );
    TESTCASE( strcmp( value + ( len - 2 ), "sh" ) == 0 );
    /* TESTCASE( strcmp( value, "/bin/sh" ) == 0 ); */

    /* constraint violations */
    TESTCASE( getenv_s( &len, NULL, 100, "SHELL" ) != 0 );
    TESTCASE( getenv_s( &len, value, 0, "SHELL" ) != 0 );
    TESTCASE( getenv_s( &len, value, RSIZE_MAX + 1, "SHELL" ) != 0 );
    TESTCASE( getenv_s( &len, value, 100, NULL ) != 0 );

    /* non-existing (hopefully), != 0 but not constraint violation */
    TESTCASE( getenv_s( &len, value, 100, "supercalifragilisticexpialidocius" ) != 0 );

    TESTCASE( HANDLER_CALLS == 4 );
#endif
    return TEST_RESULTS;
}

#endif
