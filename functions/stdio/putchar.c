/* $Id$ */

/* putchar( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int putchar_unlocked( int c )
{
    return fputc_unlocked( c, stdout );
}

int putchar( int c )
{
    return fputc( c, stdout );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif
