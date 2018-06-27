/* _PDCLIB_freepages( void *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub implementation of _PDCLIB_allocpages
*/

#include <stdint.h>
#include <stddef.h>
#include "_PDCLIB_glue.h"
#include <errno.h>
#include <gd_bal.h>

void _PDCLIB_freepages( void * p, size_t n )
{
    int rv = 0;
    if((rv = gd_free_pages( p, n ))) {
        perror("_PDCLIB_freepages");
        abort();
    }
}

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
