/* $Id$ */

/* puts( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

extern char * _PDCLIB_eol;

int puts( const char * s )
{
    if ( _PDCLIB_prepwrite( stdout ) == EOF )
    {
        return EOF;
    }
    while ( *s != '\0' )
    {
        stdout->buffer[ stdout->bufidx++ ] = *s++;
        if ( stdout->bufidx == stdout->bufsize )
        {
            if ( _PDCLIB_flushbuffer( stdout ) == EOF )
            {
                return EOF;
            }
        }
    }
    s = _PDCLIB_eol;
    while ( *s != '\0' )
    {
        stdout->buffer[ stdout->bufidx++ ] = *s++;
        if ( stdout->bufidx == stdout->bufsize )
        {
            if ( _PDCLIB_flushbuffer( stdout ) == EOF )
            {
                return EOF;
            }
        }
    }
    if ( stdout->status & ( _IOLBF | _IONBF ) )
    {
        return _PDCLIB_flushbuffer( stdout );
    }
    return 0;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( puts( "SUCCESS testing puts()" ) >= 0 );
    return TEST_RESULTS;
}

#endif

