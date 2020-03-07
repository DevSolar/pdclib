/* _PDCLIB_init_file_t( _PDCLIB_file_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

struct _PDCLIB_file_t * _PDCLIB_init_file_t( struct _PDCLIB_file_t * stream )
{
    struct _PDCLIB_file_t * rc = stream;

    if ( rc == NULL )
    {
        if ( ( rc = malloc( sizeof( struct _PDCLIB_file_t ) ) ) == NULL )
        {
            /* No memory */
            return NULL;
        }
    }

    if ( ( rc->buffer = malloc( BUFSIZ ) ) == NULL )
    {
        /* No memory */
        free( rc );
        return NULL;
    }

    rc->bufsize = BUFSIZ;
    rc->bufidx = 0;
    rc->bufend = 0;
    rc->pos.offset = 0;
    rc->pos.status = 0;
    rc->ungetidx = 0;
    rc->status = _PDCLIB_FREEBUFFER;

#ifndef __STDC_NO_THREADS
    if ( stream == NULL )
    {
        /* If called by freopen() (stream not NULL), mutex is already
           initialized.
        */
        if ( mtx_init( &rc->mtx, mtx_plain | mtx_recursive ) != thrd_success )
        {
            /* could not initialize stream mutex */
            free( rc->buffer );
            free( rc );
            return NULL;
        }
    }
#endif

    /* TODO: Setting mbstate */

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    FILE * source;
    int i;
    char buffer[100];

    TESTCASE( ( source = freopen( testfile, "wb+", stdin ) ) != NULL );

    source = freopen( NULL, "wb+", source );
    fwrite( "foo", 1, 3, source );
    rewind( source );
    TESTCASE( scanf( "%3c", buffer ) == 1 );

    source = freopen( NULL, "wb+", source );
    fwrite( "%x", 1, 2, source );
    rewind( source );
    TESTCASE( scanf( "%%%c%n", buffer, &i ) == 1 );
    TESTCASE( i == 2 );
    TESTCASE( buffer[0] == 'x' );

#ifndef REGTEST
    TESTCASE( NO_TESTDRIVER );
#endif
    return TEST_RESULTS;
}

#endif
