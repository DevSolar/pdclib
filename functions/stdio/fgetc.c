/* fgetc( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

int fgetc( struct _PDCLIB_file_t * stream )
{
    int rc = EOF;

    _PDCLIB_LOCK( stream->mtx );

    if ( _PDCLIB_prepread( stream ) != EOF )
    {
        if ( _PDCLIB_CHECKBUFFER( stream ) != EOF )
        {
            rc = _PDCLIB_GETC( stream );
        }
    }

    _PDCLIB_UNLOCK( stream->mtx );

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
