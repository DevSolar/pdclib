/* $Id$ */

/* gets( char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#define _PDCLIB_GLUE_H _PDCLIB_GLUE_H
#include <_PDCLIB_glue.h>

char * gets( char * s )
{
    if ( _PDCLIB_prepread( stdin ) == EOF )
    {
        return NULL;
    }
    char * dest = s;
    while ( ( *dest = stdin->buffer[stdin->bufidx++] ) != '\n' )
    {
        if ( stdin->bufidx == stdin->bufend )
        {
            if ( _PDCLIB_fillbuffer( stdin ) == EOF )
            {
                return NULL;
            }
        }
        ++dest;
    }
    *dest = '\n';
    return s;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif

