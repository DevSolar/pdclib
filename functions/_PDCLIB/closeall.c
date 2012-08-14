/* $Id$ */

/* _PDCLIB_closeall( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

void _PDCLIB_closeall( void )
{
    struct _PDCLIB_file_t * stream = _PDCLIB_filelist;
    struct _PDCLIB_file_t * next;
    while ( stream != NULL )
    {
        next = stream->next;
        fclose( stream );
        stream = next;
    }
}

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* No testdriver */
    return TEST_RESULTS;
}

#endif

