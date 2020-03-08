/* exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

/* TODO - "...except that a function is called after any previously registered
   functions that had already been called at the time it was registered."
*/

void ( *_PDCLIB_exitstack[ _PDCLIB_ATEXIT_SLOTS ] )( void );
size_t _PDCLIB_exitptr = 0;

void exit( int status )
{
    while ( _PDCLIB_exitptr != 0 )
    {
        _PDCLIB_exitstack[ --_PDCLIB_exitptr ]();
    }

    _Exit( status );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Unwinding of regstack tested in atexit(). */
    return TEST_RESULTS;
}

#endif
