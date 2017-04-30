/* _PDCLIB_allocpages( size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <stdint.h>
#include <stddef.h>
#include "_PDCLIB_glue.h"
#include <errno.h>
#include <windows.h>

void _PDCLIB_w32errno(void);

void * _PDCLIB_allocpages( size_t n )
{
    void * rv = VirtualAlloc(NULL, n * _PDCLIB_MALLOC_PAGESIZE, MEM_COMMIT,
        PAGE_READWRITE);
    if(!rv) {
        _PDCLIB_w32errno();
    }
    return rv;
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
