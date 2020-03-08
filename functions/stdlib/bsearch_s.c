/* bsearch( const void *, const void *, size_t, size_t, int(*)( const void *, const void * ) )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>
#include <stdint.h>

#ifndef REGTEST

void * bsearch_s( const void * key, const void * base, rsize_t nmemb, rsize_t size, int ( *compar )( const void *, const void *, void * ), void * context )
{
    const void * pivot;
    int rc;
    size_t corr;

    if ( nmemb > RSIZE_MAX || size > RSIZE_MAX || ( nmemb > 0 && ( key == NULL || base == NULL || compar == NULL ) ) )
    {
        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return NULL;
    }

    while ( nmemb )
    {
        /* algorithm needs -1 correction if remaining elements are an even number. */
        corr = nmemb % 2;
        nmemb /= 2;
        pivot = ( const char * )base + ( nmemb * size );
        rc = compar( key, pivot, context );

        if ( rc > 0 )
        {
            base = ( const char * )pivot + size;
            /* applying correction */
            nmemb -= ( 1 - corr );
        }
        else if ( rc == 0 )
        {
            return ( void * )pivot;
        }
    }

    return NULL;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )

static int compare( const void * left, const void * right, void * context )
{
    return *( ( unsigned char * )left ) - *( ( unsigned char * )right );
}

#endif

int main( void )
{
#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )
    TESTCASE( bsearch_s( "e", abcde, 4, 1, compare, NULL ) == NULL );
    TESTCASE( bsearch_s( "e", abcde, 5, 1, compare, NULL ) == &abcde[4] );
    TESTCASE( bsearch_s( "a", abcde + 1, 4, 1, compare, NULL ) == NULL );
    TESTCASE( bsearch_s( "0", abcde, 1, 1, compare, NULL ) == NULL );
    TESTCASE( bsearch_s( "a", abcde, 1, 1, compare, NULL ) == &abcde[0] );
    TESTCASE( bsearch_s( "a", abcde, 0, 1, compare, NULL ) == NULL );
    TESTCASE( bsearch_s( "e", abcde, 3, 2, compare, NULL ) == &abcde[4] );
    TESTCASE( bsearch_s( "b", abcde, 3, 2, compare, NULL ) == NULL );
#endif
    return TEST_RESULTS;
}

#endif
