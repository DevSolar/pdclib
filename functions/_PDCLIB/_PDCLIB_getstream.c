/* _PDCLIB_getstream( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

int _PDCLIB_getstream( struct _PDCLIB_file_t * stream )
{
    struct _PDCLIB_file_t * previous;

    if ( ! _PDCLIB_isstream( stream, &previous ) )
    {
        *_PDCLIB_errno_func() = _PDCLIB_EBADF;
        return EOF;
    }

    if ( previous != NULL )
    {
        previous->next = stream->next;
    }
    else
    {
        _PDCLIB_filelist = stream->next;
    }

    return 0;
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
