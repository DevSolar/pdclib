/* _PDCLIB_fileops

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdint.h>
#include "_PDCLIB_glue.h"
#include <errno.h>
#include <unistd.h>
typedef int64_t off_t;

static bool readf( _PDCLIB_fd_t fd, void * buf, size_t length,
                   size_t * numBytesRead )
{
    ssize_t res = read(fd.sval, buf, length);
    if(res == -1) {
        return false;
    } else {
        *numBytesRead = res;
        return true;
    }
}

static bool writef( _PDCLIB_fd_t fd, const void * buf, size_t length,
                   size_t * numBytesWritten )
{
    ssize_t res = write(fd.sval, buf, length);
    if(res == -1) {
        return false;
    } else {
        *numBytesWritten = res;
        return true;
    }
}

/* Note: Assumes being compiled with an OFF64 programming model */

static bool seekf( _PDCLIB_fd_t fd, int_fast64_t offset, int whence,
    int_fast64_t* newPos )
{
    off_t npos = lseek( fd.sval, offset, whence );
    if( npos == -1 ) {
        return false;
    } else {
        *newPos = npos;
        return true;
    }
}

static void closef( _PDCLIB_fd_t self )
{
    close( self.sval );
}

const _PDCLIB_fileops_t _PDCLIB_fileops = {
    .read  = readf,
    .write = writef,
    .seek  = seekf,
    .close = closef,
};

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    // Tested by stdio test cases
    return TEST_RESULTS;
}

#endif
