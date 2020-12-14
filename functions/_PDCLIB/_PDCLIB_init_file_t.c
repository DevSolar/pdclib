/* _PDCLIB_init_file_t( _PDCLIB_file_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

struct _PDCLIB_file_t * _PDCLIB_init_file_t( struct _PDCLIB_file_t * stream )
{
    struct _PDCLIB_file_t * rc = stream;

    if ( rc == NULL )
    {
        if ( ( rc = (struct _PDCLIB_file_t *)malloc( sizeof( struct _PDCLIB_file_t ) ) ) == NULL )
        {
            /* No memory */
            return NULL;
        }
    }

    if ( ( rc->buffer = (char *)malloc( BUFSIZ ) ) == NULL )
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

#ifndef __STDC_NO_THREADS__

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
#ifndef REGTEST
    TESTCASE( NO_TESTDRIVER );
#endif
    return TEST_RESULTS;
}

#endif
