/* $Id$ */

/* Release $Name$ */

/* void * realloc( void *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#ifndef REGTEST

/* TODO: Primitive placeholder. Improve. */

void * realloc( void * ptr, size_t size )
{
    struct _PDCLIB_memnode_t * baseptr = (struct _PDCLIB_memnode_t *)( (char *)ptr - sizeof( struct _PDCLIB_memnode_t ) );
    if ( baseptr->size >= size )
    {
        return ptr;
    }
    else
    {
        void * newptr = malloc( size );
        memcpy( newptr, ptr, baseptr->size );
        free( ptr );
        return newptr;
    }
    return NULL;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    /* tests covered in malloc test driver */
    return TEST_RESULTS;
}

#endif
