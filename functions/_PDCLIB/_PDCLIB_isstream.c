/* _PDCLIB_getstream( FILE * )

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

int _PDCLIB_isstream( struct _PDCLIB_file_t * stream, struct _PDCLIB_file_t ** previous )
{
    struct _PDCLIB_file_t * current = _PDCLIB_filelist;
    *previous = NULL;

    while ( ( current != NULL ) && ( current != stream ) )
    {
        *previous = current;
        current = current->next;
    }

    return current != NULL;
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
