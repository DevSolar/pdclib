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
    void * newptr = NULL;
    if ( ptr == NULL )
    {
        return malloc( size );
    }
    if ( size > 0 )
    {
        struct _PDCLIB_memnode_t * baseptr = (struct _PDCLIB_memnode_t *)( (char *)ptr - sizeof( struct _PDCLIB_memnode_t ) );
        if ( baseptr->size >= size )
        {
            /* Current memnode is large enough; nothing to do. */
            return ptr;
        }
        else
        {
            /* Get larger memnode and copy over contents. */
            if ( ( newptr = malloc( size ) ) == NULL )
            {
                return NULL;
            }
            memcpy( newptr, ptr, baseptr->size );
        }
    }
    free( ptr );
    return newptr;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* tests covered in malloc test driver */
    return TEST_RESULTS;
}

#endif

