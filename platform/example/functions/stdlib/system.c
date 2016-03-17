/* system( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

/* This is an example implementation of system() fit for use with POSIX kernels.
*/

extern int fork( void );
extern int execve( const char * filename, char * const argv[], char * const envp[] );
extern int wait( int * status );

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
#include "_PDCLIB_test.h"

#define SHELLCOMMAND "echo 'SUCCESS testing system()'"

int main( void )
{
    FILE * fh;
    char buffer[25];
    buffer[24] = 'x';
    TESTCASE( ( fh = freopen( testfile, "wb+", stdout ) ) != NULL );
    TESTCASE( system( SHELLCOMMAND ) );
    rewind( fh );
    TESTCASE( fread( buffer, 1, 24, fh ) == 24 );
    TESTCASE( memcmp( buffer, "SUCCESS testing system()", 24 ) == 0 );
    TESTCASE( buffer[24] == 'x' );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( testfile ) == 0 );
    return TEST_RESULTS;
}

#endif
