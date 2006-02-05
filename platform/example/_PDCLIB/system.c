/* $Id$ */

/* Release $Name$ */

/* system( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of system() fit for use with POSIX kernels.
*/

#include <unistd.h>
#include <sys/wait.h>

int system( const char * string )
{
    char * const argv[] = { "sh", "-c", (char * const)string, NULL };
    if ( string != NULL )
    {
        int pid = fork();
        if ( pid == 0 )
        {
            execve( "/bin/sh", argv, NULL );
        }
        else if ( pid > 0 )
        {
            while( wait( NULL ) != pid );
        }
    }
    return -1;
}

#ifdef TEST
#include <_PDCLIB_test.h>
#include <_PDCLIB_config.h>

#define SHELLCOMMAND "echo 'SUCCESS testing system()'"

int main()
{
    BEGIN_TESTS;
    TESTCASE( system( SHELLCOMMAND ) );
    return TEST_RESULTS;
}

#endif
