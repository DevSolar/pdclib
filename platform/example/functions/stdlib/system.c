/* system( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

/* This is an example implementation of system() fit for use with POSIX kernels.
*/

#ifdef __cplusplus
extern "C" {
#endif

extern int fork( void );
extern int execve( const char * filename, char * const argv[], char * const envp[] );
extern int wait( int * status );

#ifdef __cplusplus
}
#endif

extern char ** environ;

int system( const char * string )
{
    const char * argv[] = { "sh", "-c", NULL, NULL };
    argv[2] = string;

    if ( string != NULL )
    {
        int status;
        int pid = fork();

        if ( pid == 0 )
        {
#if defined( __ANDROID__ )
            execve( "/system/bin/sh", ( char * const *)argv, environ );
#else
            execve( "/bin/sh", ( char * const *)argv, environ );
#endif
        }
        else if ( pid > 0 )
        {
            while ( wait( &status ) != pid )
            {
                /* EMPTY */
            }

            return status;
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
#if !( defined( REGTEST ) && defined( __ANDROID__ ) )
    /* Bionic's system() is hardcoded to use
       execve( "/bin/sh", (char * const *)argv, NULL );
       which fails on non-rooted Termux.
    */
    TESTCASE( ( fh = freopen( testfile, "wb+", stdout ) ) != NULL );
    TESTCASE( system( SHELLCOMMAND ) == 0 );
    rewind( fh );
    TESTCASE( fread( buffer, 1, 24, fh ) == 24 );
    TESTCASE( memcmp( buffer, "SUCCESS testing system()", 24 ) == 0 );
    TESTCASE( buffer[24] == 'x' );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( testfile ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
