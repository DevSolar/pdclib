/* remove( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of remove() fit for use with POSIX kernels.
*/

#include <stdio.h>

#ifndef REGTEST
#include "_PDCLIB_io.h"
#include <string.h>

extern FILE * _PDCLIB_filelist;

extern int unlink( const char * pathname );

int remove( const char * pathname )
{
    FILE * current = _PDCLIB_filelist;
    while ( current != NULL )
    {
        if ( ( current->filename != NULL ) && ( strcmp( current->filename, pathname ) == 0 ) )
        {
            return EOF;
        }
        current = current->next;
    }
    return unlink( pathname );
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    /* Testing covered by ftell.c (and several others) */
    return TEST_RESULTS;
}

#endif

