/* getenv( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of getenv() fit for use with POSIX kernels.
*/

#include <string.h>
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
char * getenv( const char * name )
{
    size_t len = strlen( name );
    size_t index = 0;

    while ( environ[ index ] != NULL )
    {
        if ( strncmp( environ[ index ], name, len ) == 0 )
        {
            return environ[ index ] + len + 1;
        }

        index++;
    }

    return NULL;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    char * env = getenv( "SHELL" );
    size_t len = strlen( env );
    TESTCASE( strcmp( env + ( len - 2 ), "sh" ) == 0 );
    return TEST_RESULTS;
}

#endif
