/* _PDCLIB_isstream( FILE *, FILE ** )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

int _PDCLIB_isstream( struct _PDCLIB_file_t * stream, struct _PDCLIB_file_t ** previous )
{
    struct _PDCLIB_file_t * current = _PDCLIB_filelist;

    if ( previous != NULL )
    {
        *previous = NULL;
    }

    while ( ( current != NULL ) && ( current != stream ) )
    {
        if ( previous != NULL )
        {
            *previous = current;
        }

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
