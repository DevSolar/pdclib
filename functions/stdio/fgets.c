/* $Id$ */

/* fgets( char *, int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#define _PDCLIB_GLUE_H _PDCLIB_GLUE_H
#include <_PDCLIB_glue.h>

char * fgets( char * s, int size, struct _PDCLIB_file_t * stream )
{
    if ( size <= 1 )
    {
        /* TODO: This is the letter of the standard, but is it the right thing to do? */
        *s = '\0';
        return s;
    }
    if ( _PDCLIB_prepread( stdin ) == EOF )
    {
        return NULL;
    }
    char * dest = s;
    while ( ( ( *dest = stdin->buffer[stdin->bufidx++] ) != '\n' ) && --size > 0 )
    {
        if ( stdin->bufidx == stdin->bufend )
        {
            if ( _PDCLIB_fillbuffer( stdin ) == EOF )
            {
                /* EOF adds \0, error leaves target indeterminate, so we can
                   just add the \0 anyway.
                */
                *dest = '\0';
                return NULL;
            }
        }
        ++dest;
    }
    *dest = '\0';
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

