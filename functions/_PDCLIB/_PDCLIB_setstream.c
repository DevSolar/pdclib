/* _PDCLIB_setstream( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_int.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_filelist_mtx;
#endif

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

void _PDCLIB_setstream( struct _PDCLIB_file_t * stream )
{
    _PDCLIB_LOCK( _PDCLIB_filelist_mtx );
    stream->next = _PDCLIB_filelist;
    _PDCLIB_filelist = stream;
    _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* No testdriver */
    return TEST_RESULTS;
}

#endif
