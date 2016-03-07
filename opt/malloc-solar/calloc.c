/* void * calloc( size_t, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>
#include <string.h>

#ifndef REGTEST

void * calloc( size_t nmemb, size_t size )
{
    /* assign memory for nmemb elements of given size */
    void * rc = malloc( nmemb * size );
    if ( rc != NULL )
    {
        /* zero-initialize the memory */
        memset( rc, 0, nmemb * size );
    }
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    char * s;
    TESTCASE( ( s = calloc( 3, 2 ) ) != NULL );
    TESTCASE( s[0] == '\0' );
    TESTCASE( s[5] == '\0' );
    free( s );
    TESTCASE( ( s = calloc( 6, 1 ) ) != NULL );
    TESTCASE( s[0] == '\0' );
    TESTCASE( s[5] == '\0' );
    free( s );
    TESTCASE( ( s = calloc( 1, 6 ) ) != NULL );
    TESTCASE( s[0] == '\0' );
    TESTCASE( s[5] == '\0' );
    free( s );
    return TEST_RESULTS;
}

#endif
