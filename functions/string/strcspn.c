/* $Id$ */

/* Release $Name$ */

/* strcspn( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>

size_t strcspn( const char * src_1, const char * src_2 )
{
    size_t len = 0;
    const char * src_p;
    while ( src_1[len] != '\0' )
    {
        src_p = src_2;
        while ( *src_p != '\0' )
        {
            if ( src_1[len] == *src_p++ )
            {
                return len;
            }
        }
        ++len;
    }
    return len;
}
