/* fflush( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_filelist_mtx;
#endif

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

int fflush( struct _PDCLIB_file_t * stream )
{
    int rc = 0;

    if ( stream == NULL )
    {
        _PDCLIB_LOCK( _PDCLIB_filelist_mtx );
        stream = _PDCLIB_filelist;

        /* TODO: Check what happens when fflush( NULL ) encounters write errors, in other libs */
        while ( stream != NULL )
        {
            _PDCLIB_LOCK( stream->mtx );

            if ( stream->status & _PDCLIB_FWRITE )
            {
                if ( _PDCLIB_flushbuffer( stream ) == EOF )
                {
                    rc = EOF;
                }
            }

            _PDCLIB_UNLOCK( stream->mtx );

            stream = stream->next;
        }

        _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
    }
    else
    {
        _PDCLIB_LOCK( stream->mtx );
        rc = _PDCLIB_flushbuffer( stream );
        _PDCLIB_UNLOCK( stream->mtx );
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif
