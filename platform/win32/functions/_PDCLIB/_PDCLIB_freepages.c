/* _PDCLIB_allocpages( int const )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub implementation of _PDCLIB_freepages.
*/

#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#ifndef REGTEST
#include "_PDCLIB_glue.h"

void _PDCLIB_freepages( void * p, size_t n )
{
    return;
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
