/* _PDCLIB_fileops

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <stdio.h>
#include <stdint.h>
#include "_PDCLIB_glue.h"
#include <errno.h>
#include <windows.h>

#if _PDCLIB_C_MIN(2011)
_Static_assert(SEEK_SET == FILE_BEGIN, "SEEK_SET is incorrect");
_Static_assert(SEEK_CUR == FILE_CURRENT, "SEEK_CUR is incorrect");
_Static_assert(SEEK_END == FILE_END, "SEEK_END is incorrect");
#endif

void _PDCLIB_w32errno(void);

static bool readf( _PDCLIB_fd_t self, void * buf, size_t length, 
                   size_t * numBytesRead )
{
    DWORD dwLen = length > INT32_MAX ? INT32_MAX : length;
    DWORD dwBytesRead;
    if(ReadFile(self.pointer, buf, dwLen, &dwBytesRead, NULL)) {
        *numBytesRead = dwBytesRead;
        return true;
    } else {
        _PDCLIB_w32errno();
        return false;
    }
}

static bool writef( _PDCLIB_fd_t self, const void * buf, size_t length, 
                   size_t * numBytesWritten )
{
    DWORD dwLen = length > INT32_MAX ? INT32_MAX : length;
    DWORD dwBytesWritten;

    if(WriteFile(self.pointer, buf, dwLen, &dwBytesWritten, NULL)) {
        *numBytesWritten = dwBytesWritten;
        return true;
    } else {
        _PDCLIB_w32errno();
        return false;
    }
}
static bool seekf( _PDCLIB_fd_t self, int_fast64_t offset, int whence,
    int_fast64_t* newPos )
{
    LARGE_INTEGER liOffset;
    liOffset.QuadPart = offset;
    if(!SetFilePointerEx( self.pointer, liOffset, &liOffset, whence )) {
        _PDCLIB_w32errno();
        return false;
    }

    *newPos = liOffset.QuadPart;
    return true;
}

static void closef( _PDCLIB_fd_t self )
{
    CloseHandle( self.pointer );
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
