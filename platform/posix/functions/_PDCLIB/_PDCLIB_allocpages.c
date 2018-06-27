/* _PDCLIB_allocpages( size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#ifdef __linux__
#define _GNU_SOURCE
#endif
#include <stdint.h>
#include <stddef.h>
#include <sys/mman.h>
#include "_PDCLIB_glue.h"

#ifndef MAP_ANON
#define MAP_ANON MAP_ANOYNMOUS
#endif

void * _PDCLIB_allocpages( size_t n )
{
    void *addr = mmap(
        NULL, n * _PDCLIB_MALLOC_PAGESIZE, PROT_READ | PROT_WRITE,
        MAP_ANON | MAP_PRIVATE, -1, 0);

    if(addr != MAP_FAILED) {
        return addr;
    } else {
        return NULL;
    }
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
