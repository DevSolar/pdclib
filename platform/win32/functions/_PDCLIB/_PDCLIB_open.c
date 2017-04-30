/* _PDCLIB_open( char const * const, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <errno.h>

#ifndef REGTEST
#include "_PDCLIB_glue.h"
#include <windows.h>

extern const _PDCLIB_fileops_t _PDCLIB_fileops;

void _PDCLIB_w32errno(void);
bool _PDCLIB_open( _PDCLIB_fd_t * pFd, const _PDCLIB_fileops_t ** pOps,
                   char const * const filename, unsigned int mode )
{
    DWORD desiredAccess;
    DWORD creationDisposition;

    switch(mode & ( _PDCLIB_FREAD | _PDCLIB_FWRITE | _PDCLIB_FAPPEND 
                    | _PDCLIB_FRW ))
    {
    case _PDCLIB_FREAD: /* "r" */
        desiredAccess = GENERIC_READ;
        creationDisposition = OPEN_EXISTING;
        break;
    case _PDCLIB_FWRITE: /* "w" */
        desiredAccess = GENERIC_WRITE;
        creationDisposition = CREATE_ALWAYS;
        break;
    case _PDCLIB_FAPPEND: /* "a" */
        desiredAccess = GENERIC_WRITE;
        creationDisposition = OPEN_ALWAYS;
        break;
    case _PDCLIB_FREAD | _PDCLIB_FRW: /* "r+" */
        desiredAccess = GENERIC_READ | GENERIC_WRITE;
        creationDisposition = OPEN_EXISTING;
        break;
    case _PDCLIB_FWRITE | _PDCLIB_FRW: /* "w+" */
        desiredAccess = GENERIC_WRITE | GENERIC_READ;
        creationDisposition = CREATE_ALWAYS;
        break;
    case _PDCLIB_FAPPEND | _PDCLIB_FRW: /* "a+" */
        desiredAccess = GENERIC_WRITE | GENERIC_READ;
        creationDisposition = OPEN_ALWAYS;
        break;
    default: /* Invalid mode */
        errno = EINVAL;
        return false;
    }

    HANDLE fd = CreateFileA(filename, desiredAccess, 
        FILE_SHARE_READ | FILE_SHARE_DELETE,
        NULL, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);

    if(fd == INVALID_HANDLE_VALUE) {
#if 0
        DWORD dw = GetLastError();
        char* msgBuf;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR) &msgBuf,
            0, NULL );

        fprintf(stderr, "Error: %s\n", msgBuf);
#endif
        _PDCLIB_w32errno();
        return false;
    }

    if(mode & _PDCLIB_FAPPEND) {
        LARGE_INTEGER offs;
        offs.QuadPart = 0;
        BOOL ok = SetFilePointerEx(fd, offs, NULL, FILE_END);
        if(!ok) {
            _PDCLIB_w32errno();
            CloseHandle(fd);
            return false;
        }
    }

    pFd->pointer = fd;
    *pOps = &_PDCLIB_fileops;
    return true;
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

#include <stdlib.h>
#include <string.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif

