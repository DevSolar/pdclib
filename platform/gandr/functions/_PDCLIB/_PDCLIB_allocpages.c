/* _PDCLIB_allocpages( int const )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdint.h>
#include <stddef.h>
#include "_PDCLIB_glue.h"
#include <errno.h>
#include <gd_bal.h>

void * _PDCLIB_allocpages( size_t n )
{
    void *p = NULL;
    int rv = gd_alloc_pages( gd_loader_data, &p, n );

    if (rv) {
        errno = rv;
        return NULL;
    } else {
        return p;
    }
}

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
