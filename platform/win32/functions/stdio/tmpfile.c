/* tmpfile( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <errno.h>
#include "_PDCLIB_glue.h"
#include <windows.h>
#include <string.h>

static char tmpname_prefix[4] = {0, 0, 0, 0};

extern const _PDCLIB_fileops_t _PDCLIB_fileops;
extern void _PDCLIB_w32errno( void );

FILE* tmpfile( void )
{
    if(!tmpname_prefix[0]) {
        char namebuf[MAX_PATH+1];
        DWORD res = GetModuleFileNameA(NULL, namebuf, MAX_PATH+1);
        if(res) {
            char * basename = strrchr(namebuf, '\\');
            if(basename) {
                basename += 1;
            } else basename = namebuf;

            char* dot = strchr(basename, '.');
            if(dot) *dot = 0;

            strncpy(tmpname_prefix, basename, 3);
        } else {
            // Error getting file name
            strcpy(tmpname_prefix, "PDU");
        }
    }

    char tmpdir[MAX_PATH + 1];
    DWORD rv = GetTempPathA(MAX_PATH + 1, tmpdir);
    if(rv == 0) {
        _PDCLIB_w32errno();
        return NULL;
    }

    char name[MAX_PATH + 1];
    rv = GetTempFileNameA(tmpdir, tmpname_prefix, 0, name);
    if(rv == 0) {
        _PDCLIB_w32errno();
        return NULL;
    }

    /* OPEN_EXISTING as CreateTempFileName creates the file then closes the
       handle to it (to avoid race conditions as associated with e.g. tmpnam)
     */
    HANDLE fd = CreateFileA(name, GENERIC_READ | GENERIC_WRITE, 
        FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_TEMPORARY, NULL);

    if(fd == INVALID_HANDLE_VALUE) {
        _PDCLIB_w32errno();
        return NULL;
    }

    /* Set the file to delete on close */
    DeleteFile(name);

    FILE* fs = _PDCLIB_fvopen(((_PDCLIB_fd_t){fd}), &_PDCLIB_fileops, _PDCLIB_FWRITE | _PDCLIB_FRW, name);
    if(!fs) {
        CloseHandle(fd);
    }
    return fs;
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"
#include <string.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif

