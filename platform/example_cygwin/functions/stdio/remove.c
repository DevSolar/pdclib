/* $Id$ */

/* remove( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of remove() fit for use with POSIX kernels.
*/

#include <stdio.h>

#ifndef REGTEST

#include "/usr/include/errno.h"

extern int unlink( const char * pathname );

int remove( const char * pathname )
{
    int rc;
    if ( ( rc = unlink( pathname ) ) == -1 )
    {
        switch ( errno )
        {
            /* See the comments on implementation-defined errno values in
               <_PDCLIB_config.h>.
            */
            case EACCES:
            case EFAULT:
            case EIO:
            case EISDIR:
            case ELOOP:
            case ENAMETOOLONG:
            case ENOENT:
            case ENOMEM:
            case ENOTDIR:
            case EPERM:
            case EROFS:
                _PDCLIB_errno = _PDCLIB_ERROR;
                break;
            default:
                /* This should be something like EUNKNOWN. */
                _PDCLIB_errno = _PDCLIB_ERROR;
                break;
        }
    }
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by ftell.c (and several others) */
    return TEST_RESULTS;
}

#endif

