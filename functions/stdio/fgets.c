/* $Id$ */

/* fgets( char *, int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#define _PDCLIB_GLUE_H _PDCLIB_GLUE_H
#include <_PDCLIB_glue.h>

char * fgets( char * _PDCLIB_restrict s, int size, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    if ( size <= 1 )
    {
        /* TODO: This is the letter of the standard, but is it the right thing to do? */
        *s = '\0';
        return s;
    }
    if ( _PDCLIB_prepread( stream ) == EOF )
    {
        return NULL;
    }
    char * dest = s;
    while ( ( ( *dest = stream->buffer[stream->bufidx++] ) != '\n' ) && --size > 0 )
    {
        if ( stream->bufidx == stream->bufend )
        {
            if ( _PDCLIB_fillbuffer( stream ) == EOF )
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

