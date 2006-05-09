/* $Id$ */

/* system( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

/* This is an example implementation of system() fit for use with POSIX kernels.
*/

#include <unistd.h>
#include <sys/wait.h>

int system( const char * string )
{
    char const * const argv[] = { "sh", "-c", (char const * const)string, NULL };
    if ( string != NULL )
    {
        int pid = fork();
        if ( pid == 0 )
        {
            execve( "/bin/sh", (char * * const)argv, NULL );
        }
        else if ( pid > 0 )
        {
            while( wait( NULL ) != pid );
        }
    }
    return -1;
}

#ifdef TEST
/* TODO: Work around the following undef */
#undef SEEK_SET
#include <_PDCLIB_test.h>

#define SHELLCOMMAND "echo 'SUCCESS testing system()'"

int main( void )
{
    TESTCASE( system( SHELLCOMMAND ) );
    return TEST_RESULTS;
}

#endif
