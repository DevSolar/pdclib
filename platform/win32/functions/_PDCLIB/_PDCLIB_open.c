/* $Id$ */

/* _PDCLIB_open( char const * const, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub implementation of open.
*/

#include <stdio.h>
#include <errno.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <windows.h>

void _PDCLIB_w32errno(void);
HANDLE _PDCLIB_open( char const * const filename, unsigned int mode )
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
        return NULL;
    }

    HANDLE fd = CreateFileA(filename, desiredAccess, 
        FILE_SHARE_READ | FILE_SHARE_DELETE,
        NULL, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);

    if(fd == INVALID_HANDLE_VALUE) {
        _PDCLIB_w32errno();
        return NULL;
    }

    if(mode & _PDCLIB_FAPPEND) {
        LARGE_INTEGER offs;
        offs.QuadPart = 0;
        BOOL ok = SetFilePointerEx(fd, offs, NULL, FILE_END);
        if(!ok) {
            _PDCLIB_w32errno();
            CloseHandle(fd);
            return NULL;
        }
    }

    return fd;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <stdlib.h>
#include <string.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif

