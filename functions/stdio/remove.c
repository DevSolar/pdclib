/* remove( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of remove() fit for use with POSIX kernels.
*/

#include <stdio.h>

#ifndef REGTEST

#include <string.h>

#include "/usr/include/errno.h"

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

#ifdef __cplusplus
extern "C" {
#endif

extern int unlink( const char * pathname );

#ifdef __cplusplus
}
#endif

int remove( const char * pathname )
{
    int rc;
    struct _PDCLIB_file_t * current = _PDCLIB_filelist;

    while ( current != NULL )
    {
        if ( ( current->filename != NULL ) && ( strcmp( current->filename, pathname ) == 0 ) )
        {
            return EOF;
        }

        current = current->next;
    }

    if ( ( rc = unlink( pathname ) ) == -1 )
    {
        /* The 1:1 mapping in _PDCLIB_config.h ensures this works. */
        *_PDCLIB_errno_func() = errno;
    }

    return rc;
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
