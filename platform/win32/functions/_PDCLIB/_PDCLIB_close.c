/* $Id$ */

/* _PDCLIB_close( _PDCLIB_fd_t fd )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub example implementation of _PDCLIB_close()
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <errno.h>
#include <windows.h>

void _PDCLIB_w32errno(void);
int _PDCLIB_close( HANDLE fd )
{
    if(CloseHandle((HANDLE) fd))
        return 0;
    _PDCLIB_w32errno();
    return 1;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* No testdriver; tested in driver for _PDCLIB_open(). */
    return TEST_RESULTS;
}

#endif
