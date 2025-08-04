/* int_least64_t _PDCLIB_seek( FILE *, int_least64_t, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_seek() fit for use with POSIX
   kernels.
 */

#ifndef REGTEST

#include <stdio.h>
#include <stdint.h>

#include "pdclib/_PDCLIB_glue.h"

#include "pdclib/_PDCLIB_platform_errno.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int64_t lseek64( int fd, _PDCLIB_int_least64_t offset, int whence );
extern long lseek( int fd, long offset, int whence );

#ifdef __cplusplus
}
#endif

_PDCLIB_int_least64_t _PDCLIB_seek( struct _PDCLIB_file_t * stream, _PDCLIB_int_least64_t offset, int whence )
{
    _PDCLIB_int_least64_t rc;

    switch ( whence )
    {
        case SEEK_SET:
        case SEEK_CUR:
        case SEEK_END:
            /* EMPTY - OK */
            break;

        default:
            *_PDCLIB_errno_func() = _PDCLIB_EINVAL;
            return EOF;
            break;
    }

#ifdef __CYGWIN__
    rc = lseek( stream->handle, offset, whence );
#else
    rc = lseek64( stream->handle, offset, whence );
#endif

    if ( rc != EOF )
    {
        stream->ungetidx = 0;
        stream->bufidx = 0;
        stream->bufend = 0;
        stream->pos.offset = rc;
        return rc;
    }

    /* The 1:1 mapping in _PDCLIB_config.h ensures that this works. */
    *_PDCLIB_errno_func() = errno;
    return EOF;
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
