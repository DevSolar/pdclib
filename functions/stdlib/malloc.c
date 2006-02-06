/* $Id$ */

/* Release $Name$ */

/* void * malloc( size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

#include <stdint.h>

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDLIB_INT_H
#include <_PDCLIB_int.h>
#endif

/* TODO: Primitive placeholder. Much room for improvement. */

/* Keeping pointers to the first and the last element of the free list. */
struct _PDCLIB_headnode_t _PDCLIB_memlist = { NULL, NULL };

void * malloc( size_t size )
{
    if ( size == 0 )
    {
        return NULL;
    }
    if ( size < _PDCLIB_MINALLOC )
    {
        size = _PDCLIB_MINALLOC;
    }
    {
    struct _PDCLIB_memnode_t * current = _PDCLIB_memlist.first;
    struct _PDCLIB_memnode_t * previous = NULL;
    struct _PDCLIB_memnode_t * firstfit = NULL;
    struct _PDCLIB_memnode_t * firstfit_previous = NULL;
    /* Trying exact fit */
    while ( current != NULL )
    {
        if ( current->size == size )
        {
            /* Found exact fit, allocate node */
            if ( previous != NULL )
            {
                /* Node in the middle of the list */
                previous->next = current->next;
            }
            else
            {
                /* Node is first in list */
                _PDCLIB_memlist.first = current->next;
            }
            if ( _PDCLIB_memlist.last == current )
            {
                /* Node is last in list */
                _PDCLIB_memlist.last = previous;
            }
            return (char *)current + sizeof( struct _PDCLIB_memnode_t );
        }
        else if ( current->size > size && ( firstfit == NULL || current->size < firstfit->size ) )
        {
            /* Remember previous node in case we do not get an exact fit.
               Note that this is the node *pointing to* the first fit,
               as we need that for allocating (i.e., changing next pointer).
            */
            firstfit_previous = previous;
            firstfit = current;
        }
        /* Skip to next node */
        previous = current;
        current = current->next;
    }
    /* No exact fit; go for first fit */
    if ( firstfit != NULL )
    {
        if ( ( firstfit->size - size ) > _PDCLIB_MINALLOC )
        {
            /* Oversized - split into two nodes */
            struct _PDCLIB_memnode_t * newnode = (struct _PDCLIB_memnode_t *)( (char *)firstfit + sizeof( struct _PDCLIB_memnode_t ) + size );
            newnode->size = firstfit->size - size - sizeof( struct _PDCLIB_memnode_t );
            newnode->next = firstfit->next;
            firstfit->next = newnode;
            firstfit->size = firstfit->size - newnode->size - sizeof( struct _PDCLIB_memnode_t );
        }
        if ( firstfit_previous != NULL )
        {
            /* Node in the middle of the list */
            firstfit_previous->next = firstfit->next;
        }
        else
        {
            /* Node is first in list */
            _PDCLIB_memlist.first = firstfit->next;
        }
        if ( _PDCLIB_memlist.last == firstfit )
        {
            /* Node is last in list */
            _PDCLIB_memlist.last = firstfit_previous;
        }
        return (char *)firstfit + sizeof( struct _PDCLIB_memnode_t );
    }
    }
    {
    /* No fit possible; how many additional pages do we need? */
    uintmax_t pages = ( ( size + sizeof( struct _PDCLIB_memnode_t ) - 1 ) / _PDCLIB_PAGESIZE ) + 1;
    /* Allocate more pages */
    struct _PDCLIB_memnode_t * newnode = (struct _PDCLIB_memnode_t *)_PDCLIB_allocpages( pages );
    if ( newnode != NULL )
    {
        newnode->next = NULL;
        newnode->size = pages * _PDCLIB_PAGESIZE - sizeof( struct _PDCLIB_memnode_t );
        if ( ( newnode->size - size ) > _PDCLIB_MINALLOC )
        {
            /* Oversized - split into two nodes */
            struct _PDCLIB_memnode_t * splitnode = (struct _PDCLIB_memnode_t *)( (char *)newnode + sizeof( struct _PDCLIB_memnode_t ) + size );
            splitnode->size = newnode->size - size - sizeof( struct _PDCLIB_memnode_t );
            newnode->size = size;
            /* Add splitted node as last element to free node list */
            if ( _PDCLIB_memlist.last == NULL )
            {
                _PDCLIB_memlist.first = splitnode;
                splitnode->next = NULL;
            }
            else
            {
                _PDCLIB_memlist.last->next = splitnode;
            }
            _PDCLIB_memlist.last = splitnode;
        }
        return (char *)newnode + sizeof( struct _PDCLIB_memnode_t );
    }
    }
    /* No fit, heap extension not possible - out of memory */
    return NULL;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>
#include <string.h>

#define MEMTEST( ptr, size ) ( ( ptr = malloc( size ) ) != NULL ) && ( memset( ptr, 0, size ) == ptr )
#define PAGETEST( x ) ( pages_start + x * _PDCLIB_PAGESIZE ) == sbrk( 0 )
#define EFFECTIVE _PDCLIB_PAGESIZE - sizeof( struct _PDCLIB_memnode_t )

/* Note that this test driver heavily tests *internals* of the implementation
   above (and of free() and realloc(), too). That means that changes in the
   implementation must be accompanied with appropriate changes of the test
   driver. It does *not* make a good regression tester for the implementation,
   I am afraid, and thus there is no REGTEST equivalent.
*/

#include <unistd.h>

int main( int argc, char * argv[] )
{
    BEGIN_TESTS;
#ifndef REGTEST
    {
    void * ptr1, * ptr2, * ptr3, * ptr4, * ptr5, * ptr6, * ptr7, * ptr8;
    char * pages_start = _PDCLIB_allocpages( 0 );
    /* allocating 10 byte; expected: 1 page allocation, node split */
    TESTCASE( MEMTEST( ptr1, 10 ) );
    TESTCASE( PAGETEST( 1 ) );
    /* allocating EFFECTIVE - 10 byte; expected: no page allocation, receiving split node */
    TESTCASE( MEMTEST( ptr2, EFFECTIVE - 10 - sizeof( struct _PDCLIB_memnode_t ) ) );
    TESTCASE( PAGETEST( 1 ) );
    /* allocating EFFECTIVE; expected: 1 page allocation, no node split */
    TESTCASE( MEMTEST( ptr3, EFFECTIVE ) );
    TESTCASE( PAGETEST( 2 ) );
    /* allocating EFFECTIVE - 4; expected: 1 page allocation, no node split */
    TESTCASE( MEMTEST( ptr4, EFFECTIVE - 4 ) );
    TESTCASE( PAGETEST( 3 ) );
    /* freeing and re-allocating EFFECTIVE - 4; expected: no page allocation, no node split */
    free( ptr4 );
    TESTCASE( MEMTEST( ptr5, EFFECTIVE - 4 ) );
    TESTCASE( ptr4 == ptr5 );
    TESTCASE( PAGETEST( 3 ) );
    /* releasing EFFECTIVE; expected: no page release */
    free( ptr3 );
    TESTCASE( PAGETEST( 3 ) );
    /* allocating EFFECTIVE + _PDCLIB_PAGESIZE; expected: 2 page allocation, no node split */
    TESTCASE( MEMTEST( ptr3, EFFECTIVE + _PDCLIB_PAGESIZE ) );
    TESTCASE( PAGETEST( 5 ) );
    /* reallocating to 10 byte; expected: no page allocation, no node split */
    TESTCASE( realloc( ptr3, 10 ) == ptr3 );
    TESTCASE( PAGETEST( 5 ) );
    /* reallocating to EFFECTIVE + _PDCLIB_PAGESIZE; expected: no page allocation, no node split */
    TESTCASE( realloc( ptr3, EFFECTIVE + _PDCLIB_PAGESIZE ) == ptr3 );
    TESTCASE( PAGETEST( 5 ) );
    /* reallocating to EFFECTIVE + _PDCLIB_PAGESIZE * 2; expected: 3 page allocations, no node split */
    TESTCASE( realloc( ptr3, EFFECTIVE + _PDCLIB_PAGESIZE * 2 ) != ptr3 );
    TESTCASE( PAGETEST( 8 ) );
    /* allocating EFFECTIVE + _PDCLIB_PAGESIZE; expected: no page allocation, no node split */
    TESTCASE( MEMTEST( ptr4, EFFECTIVE + _PDCLIB_PAGESIZE ) );
    TESTCASE( PAGETEST( 8 ) );
    /* allocating zero size; expected: no page allocation, no node split */
    TESTCASE( ! MEMTEST( ptr6, 0 ) );
    TESTCASE( PAGETEST( 8 ) );
    /* allocating 4 byte; expected: no page allocation, upsizing of size, node split */
    TESTCASE( MEMTEST( ptr7, 4 ) );
    TESTCASE( PAGETEST( 8 ) );
    /* allocating rest of page; expected: no page allocation, no node split */
    TESTCASE( MEMTEST( ptr8, EFFECTIVE - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ) ) );
    TESTCASE( PAGETEST( 8 ) );
    /* freeing, and allocating one byte more; expected: 1 page allocation, node split */
    free( ptr8 );
    TESTCASE( MEMTEST( ptr8, EFFECTIVE + 1 - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ) ) );
    TESTCASE( PAGETEST( 9 ) );
    }
#endif
    return TEST_RESULTS;
}

#endif
