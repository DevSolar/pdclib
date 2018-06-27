/* remove( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of remove() fit for use with POSIX kernels.
*/

#include <stdio.h>

#ifndef REGTEST

#include <string.h>
#include <errno.h>
#include <wchar.h> // Watcom bug: winnt.h assumes string.h defines wchar_t
#include <windows.h>

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

extern void _PDCLIB_w32errno( void );
int remove( const char * pathname )
{
    BOOL ok = DeleteFileA( pathname );
    if(!ok) {
        _PDCLIB_w32errno();
        return -1;
    } else return 0;
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

