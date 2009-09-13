/* $Id$ */

/* void * malloc( size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef REGTEST

#ifndef _PDCLIB_GLUE_H
#define _PDCLIB_GLUE_H _PDLIB_GLUE_H
#include <_PDCLIB_glue.h>
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
        bool node_split = false;
        if ( ( firstfit->size - size ) > ( _PDCLIB_MINALLOC + sizeof( struct _PDCLIB_memnode_t ) ) )
        {
            /* Oversized - split into two nodes */
            struct _PDCLIB_memnode_t * newnode = (struct _PDCLIB_memnode_t *)( (char *)firstfit + sizeof( struct _PDCLIB_memnode_t ) + size );
            newnode->size = firstfit->size - size - sizeof( struct _PDCLIB_memnode_t );
            newnode->next = firstfit->next;
            firstfit->next = newnode;
            firstfit->size = firstfit->size - newnode->size - sizeof( struct _PDCLIB_memnode_t );
            node_split = true;
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
            if ( node_split )
            {
                _PDCLIB_memlist.last = firstfit->next;
            }
            else
            {
                _PDCLIB_memlist.last = firstfit_previous;
            }
        }
        return (char *)firstfit + sizeof( struct _PDCLIB_memnode_t );
    }
    }
    {
    /* No fit possible; how many additional pages do we need? */
    size_t pages = ( ( size + sizeof( struct _PDCLIB_memnode_t ) - 1 ) / _PDCLIB_PAGESIZE ) + 1;
    /* Allocate more pages */
    struct _PDCLIB_memnode_t * newnode = (struct _PDCLIB_memnode_t *)_PDCLIB_allocpages( (int)pages );
    if ( newnode != NULL )
    {
        newnode->next = NULL;
        newnode->size = pages * _PDCLIB_PAGESIZE - sizeof( struct _PDCLIB_memnode_t );
        if ( ( newnode->size - size ) > ( _PDCLIB_MINALLOC + sizeof( struct _PDCLIB_memnode_t ) ) )
        {
            /* Oversized - split into two nodes */
            struct _PDCLIB_memnode_t * splitnode = (struct _PDCLIB_memnode_t *)( (char *)newnode + sizeof( struct _PDCLIB_memnode_t ) + size );
            splitnode->size = newnode->size - size - sizeof( struct _PDCLIB_memnode_t );
            newnode->size = size;
            /* Add splitted node as last element to free node list */
            if ( _PDCLIB_memlist.last == NULL )
            {
                _PDCLIB_memlist.first = splitnode;
            }
            else
            {
                _PDCLIB_memlist.last->next = splitnode;
            }
            splitnode->next = NULL; /* TODO: This is bug #7, uncovered by testdriver yet. */
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
#include <stdarg.h>
#include <stdio.h>


#ifndef REGTEST

/* Effective page size, i.e. how many bytes can be allocated and still be on
   one page of memory.
*/
#define EFFECTIVE _PDCLIB_PAGESIZE - sizeof( struct _PDCLIB_memnode_t )
#define MEMTEST( ptr, size ) ( ( ptr = malloc( size ) ) != NULL ) && ( memset( ptr, 0, size ) == ptr )

char * pages_start = 0;
int test_nodes( char const * const, int, ... );
void PRINT( char const * const, ... );

/* This can be enabled to give a dump of node information */
#if 0
void PRINT( char const * const format, ... )
{
    va_list( ap );
    va_start( ap, format );
    vprintf( format, ap );
}
#else
void PRINT( char const * const format, ... )
{
    /* EMPTY */
}
#endif

/* Helper function checking number of allocated memory pages and the nodes
   in the free memory list against expectations.
*/
int test_nodes( char const * const action, int expected_pages, ... )
{
    static int count = 1;
    int result = 1;
    PRINT( action );
    /* Determining the amount of allocated pages */
    int allocated_pages = ( (intptr_t)_PDCLIB_allocpages( 0 ) - (intptr_t)pages_start ) / _PDCLIB_PAGESIZE;
    PRINT( "Test #%2d, %d allocated pages", count++, allocated_pages );
    if ( allocated_pages != expected_pages )
    {
        PRINT( " - MISMATCH, expected\n          %d pages\n", expected_pages );
        result = 0;
    }
    else
    {
        PRINT( "\n" );
    }
    /* Now moving through the free nodes list */
    va_list( ap );
    va_start( ap, expected_pages );
    struct _PDCLIB_memnode_t * tracer = _PDCLIB_memlist.first;
    int firstnode = 0;
    int lastnode = 0;
    while ( tracer != NULL )
    {
        /* Data from node */
        size_t node_location = (char *)tracer - (char *)pages_start;
        PRINT( "   - node %.4p, size %#.4x", node_location, tracer->size );
        /* Expected data */
        size_t expected_location = va_arg( ap, size_t );
        if ( expected_location == 0 )
        {
            PRINT( " - UNEXPECTED NODE\n" );
            result = 0;
            continue;
        }
        /* Memorizing first and last expected node for later comparison. */
        if ( firstnode == 0 )
        {
            firstnode = expected_location;
        }
        lastnode = expected_location;
        /* Comparing expected node against current node */
        size_t expected_size = va_arg( ap, size_t );
        if ( ( node_location != expected_location ) || ( tracer->size != expected_size ) )
        {
            PRINT( " - MISMATCH, expected values\n          %.4p       %#.4p\n", expected_location, expected_size );
            result = 0;
        }
        else
        {
            PRINT( "\n" );
        }
        tracer = tracer->next;
    }
    /* Comparing first and last node in memlist against expectations. */
    PRINT( "   - memlist first: %#.4x - last: %#.4x",
            ( _PDCLIB_memlist.first == NULL ) ? NULL : (char *)_PDCLIB_memlist.first - (char *)pages_start,
            ( _PDCLIB_memlist.last == NULL ) ? NULL : (char *)_PDCLIB_memlist.last - (char *)pages_start );
    if ( ( firstnode != 0 ) && 
         ( ( ( (char *)_PDCLIB_memlist.first - (char *)pages_start ) != firstnode )
         || ( ( (char *)_PDCLIB_memlist.last  - (char *)pages_start ) != lastnode ) ) )
    {
        PRINT( " - MISMATCH, expected values\n                    %#.4x - last: %#.4x\n", firstnode, lastnode );
        result = 0;
    }
    else
    {
        PRINT( "\n" );
    }
    PRINT( "\n" );
    return result;
}

#endif 

/* Note that this test driver heavily tests *internals* of the implementation
   above (and of free() and realloc(), too). That means that changes in the
   implementation must be accompanied with appropriate changes of the test
   driver. It does *not* make a good regression tester for the implementation,
   I am afraid, and thus there is no REGTEST equivalent.
*/

int main( void )
{
#ifndef REGTEST
    void * ptr1, * ptr2, * ptr3, * ptr4, * ptr5, * ptr6, * ptr7, * ptr8, * ptr9, * ptrA, * ptrB, * ptrC;

    pages_start = _PDCLIB_allocpages( 0 );
    PRINT( "\nEffective is: %#.4x\nsizeof( memnode ) is: %#.2x\n\n", EFFECTIVE, sizeof( struct _PDCLIB_memnode_t ) ); 

    /* Allocating 10 bytes; expecting one page allocation and a node split */
    TESTCASE( MEMTEST( ptr1, 10 ) );
    TESTCASE( test_nodes( "Allocating 10 bytes.", 1,
               sizeof( struct _PDCLIB_memnode_t ) + 10, EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - 10,
               0 ) );

    /* Allocating the rest of the page; expecting no page allocation and assignment of the remaining node */
    TESTCASE( MEMTEST( ptr2, EFFECTIVE - 10 - sizeof( struct _PDCLIB_memnode_t ) ) );
    TESTCASE( test_nodes( "Allocating the rest of the page.", 1,
               0 ) );

    /* Allocating a full page; expecting one page allocation, no node split */
    TESTCASE( MEMTEST( ptr3, EFFECTIVE ) );
    TESTCASE( test_nodes( "Allocating a full page.", 2,
               0 ) );

    /* Allocating *almost* a full page; expecting one page allocation, no node split */
    TESTCASE( MEMTEST( ptr4, EFFECTIVE - 4 ) );
    TESTCASE( test_nodes( "Allocating *almost* a full page.", 3,
               0 ) );

    /* Freeing and re-allocating the "almost" full page; expecting no page allocation, no node split */
    free( ptr4 );
    TESTCASE( MEMTEST( ptr5, EFFECTIVE - 4 ) );
    TESTCASE( ptr4 == ptr5 );
    TESTCASE( test_nodes( "Freeing and re-allocating the \"almost\" full page.", 3 ) );

    /* Freeing the full page from test #3; expecting a full-sized free node. */
    free( ptr3 );
    TESTCASE( test_nodes( "Freeing the full page from test #3.", 3,
               _PDCLIB_PAGESIZE * 1, EFFECTIVE,
               0 ) );

    /* Allocating two full pages; expecting two page allocations, no node split */
    TESTCASE( MEMTEST( ptr3, EFFECTIVE + _PDCLIB_PAGESIZE ) );
    TESTCASE( test_nodes( "Allocating two full pages.", 5,
               _PDCLIB_PAGESIZE * 1, EFFECTIVE,
               0 ) );

    /* Re-allocating to size of 10 bytes; expecting no page allocation, no node split */
    /* TODO: Shouldn't realloc() split the now much-too-large node? */
    TESTCASE( realloc( ptr3, 10 ) == ptr3 );
    TESTCASE( test_nodes( "Re-allocating to size of 10 bytes.", 5,
               _PDCLIB_PAGESIZE * 1, EFFECTIVE,
               0 ) );

    /* Re-allocating to size of two full pages; expecting no page allocation, no node split */
    TESTCASE( realloc( ptr3, EFFECTIVE + _PDCLIB_PAGESIZE ) == ptr3 );
    TESTCASE( test_nodes( "Re-allocating to size of two full pages.", 5,
               _PDCLIB_PAGESIZE * 1, EFFECTIVE,
               0 ) );

    /* Re-allocating to size of three full pages; expecting three page allocation, freeing of two-page node */
    TESTCASE( realloc( ptr3, EFFECTIVE + _PDCLIB_PAGESIZE * 2 ) != ptr3 );
    TESTCASE( test_nodes( "Re-allocating to size of three full pages.", 8,
               _PDCLIB_PAGESIZE * 1, EFFECTIVE,
               _PDCLIB_PAGESIZE * 3, EFFECTIVE + _PDCLIB_PAGESIZE,
               0 ) );

    /* Allocating two full pages; expecting allocation of the available two-page node */
    TESTCASE( MEMTEST( ptr4, EFFECTIVE + _PDCLIB_PAGESIZE ) );
    TESTCASE( test_nodes( "Allocating two full pages.", 8,
               _PDCLIB_PAGESIZE * 1, EFFECTIVE,
               0 ) );

    /* Allocating zero bytes; expecting no change */
    TESTCASE( ! MEMTEST( ptr6, 0 ) );
    TESTCASE( test_nodes( "Allocating zero bytes.", 8,
               _PDCLIB_PAGESIZE * 1, EFFECTIVE,
               0 ) );

    /* Allocating 4 bytes; expecting upsizing of requestupsizing of size, node split */
    TESTCASE( MEMTEST( ptr7, 4 ) );
    TESTCASE( test_nodes( "Allocating 4 bytes.", 8,
               _PDCLIB_PAGESIZE * 1 + _PDCLIB_MINALLOC + sizeof( struct _PDCLIB_memnode_t ),
               EFFECTIVE - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ),
               0 ) );

    /* Allocating the rest of the page; expecting no page allocation and assignment of the remaining node */
    TESTCASE( MEMTEST( ptr8, EFFECTIVE - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ) ) );
    TESTCASE( test_nodes( "Allocating the rest of the page.", 8, 0 ) );

    /* Freeing the node from the previous test; expecting node to re-appear in free list */
    free( ptr8 );
    TESTCASE( test_nodes( "Freeing the node from the previous test.", 8,
               _PDCLIB_PAGESIZE * 1 + _PDCLIB_MINALLOC + sizeof( struct _PDCLIB_memnode_t ),
               EFFECTIVE - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ),
               0 ) );

    /* Allocating one byte more than available in free node; expecting page allocation */
    TESTCASE( MEMTEST( ptr8, EFFECTIVE + 1 - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ) ) );
    TESTCASE( test_nodes( "Allocating one byte more than available in free node.", 9,
               _PDCLIB_PAGESIZE * 1 + _PDCLIB_MINALLOC + sizeof( struct _PDCLIB_memnode_t ),
               EFFECTIVE - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ),
               0 ) );

    /* Re-allocating with NULL pointer; expecting no page allocation, no node split */
    ptr9 = realloc( NULL, EFFECTIVE - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ) );
    TESTCASE( ptr9 != NULL );
    TESTCASE( memset( ptr9, 0, EFFECTIVE - _PDCLIB_MINALLOC - sizeof( struct _PDCLIB_memnode_t ) ) == ptr9 );
    TESTCASE( test_nodes( "Re-allocating with NULL pointer.", 9, 0 ) );

    /* Allocating a bit more than half a page; expecting page allocation, node split */
#define TESTSIZE 3000
    TESTCASE( MEMTEST( ptrA, TESTSIZE ) );
    TESTCASE( test_nodes( "Allocating a bit more than half a page.", 10,
               _PDCLIB_PAGESIZE * 9 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               0 ) );

    /* Allocating a bit more than half a page; expecting page allocation, node split */
    TESTCASE( MEMTEST( ptrB, TESTSIZE ) );
    TESTCASE( test_nodes( "Allocating a bit more than half a page.", 11,
               _PDCLIB_PAGESIZE * 9 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               _PDCLIB_PAGESIZE * 10 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               0 ) );

    /* Allocating a bit more than half a page; expecting page allocation, node split */
    TESTCASE( MEMTEST( ptrC, TESTSIZE ) );
    TESTCASE( test_nodes( "Allocating a bit more than half a page.", 12,
               _PDCLIB_PAGESIZE * 9 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               _PDCLIB_PAGESIZE * 10 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               _PDCLIB_PAGESIZE * 11 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               0 ) );

    /* Freeing the middle node */
    free( ptrB );
    TESTCASE( test_nodes( "Freeing the middle node.", 12,
               _PDCLIB_PAGESIZE * 9 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               _PDCLIB_PAGESIZE * 10 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               _PDCLIB_PAGESIZE * 11 + sizeof( struct _PDCLIB_memnode_t ) + TESTSIZE,
               EFFECTIVE - sizeof( struct _PDCLIB_memnode_t ) - TESTSIZE,
               _PDCLIB_PAGESIZE * 10,
               TESTSIZE,
               0 ) );

#else
    puts( " NOTEST malloc() test driver is PDCLib-specific." );
#endif
    return TEST_RESULTS;
}

#endif
