/* $Id$ */

/* void free( void * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>
#endif

/* TODO: Primitive placeholder. Much room for improvement. */

/* structure holding first and last element of free node list */
extern struct _PDCLIB_headnode_t _PDCLIB_memlist;

void free( void * ptr )
{
    ptr = (void *)( (char *)ptr - sizeof( struct _PDCLIB_memnode_t ) );
    ( (struct _PDCLIB_memnode_t *)ptr )->next = NULL;
    if ( _PDCLIB_memlist.last != NULL )
    {
        _PDCLIB_memlist.last->next = ptr;
    }
    else
    {
        _PDCLIB_memlist.first = ptr;
    }
    _PDCLIB_memlist.last = ptr;
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
