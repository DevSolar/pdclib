/* quick_exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

/* TODO - "...except that a function is called after any previously registered
   functions that had already been called at the time it was registered."
*/

void ( *_PDCLIB_quickexitstack[ _PDCLIB_ATEXIT_SLOTS ] )( void );
size_t _PDCLIB_quickexitptr = 0;

void quick_exit( int status )
{
    while ( _PDCLIB_quickexitptr != 0 )
    {
        _PDCLIB_quickexitstack[ --_PDCLIB_quickexitptr ]();
    }

    _Exit( status );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Unwinding of regstack tested in at_quick_exit(). */
    return TEST_RESULTS;
}

#endif
