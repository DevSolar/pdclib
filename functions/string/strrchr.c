/* $Id$ */

/* Release $Name$ */

/* strrchr( const char *, int c )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>

char * strrchr( const char * s, int c )
{
    size_t i = 0;
    while ( p[i++] );
    do
    {
        if ( p[--i] == (char) c )
        {
            return (char *) p + i;
        }
    } while ( i );
    return NULL;
}

#warning Test driver missing.
