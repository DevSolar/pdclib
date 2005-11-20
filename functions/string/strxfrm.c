/* $Id$ */

/* Release $Name$ */

/* strxfrm( char *, const char *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_aux.h>
#include <string.h>

/* TODO: Dummy function, no locale support yet. */

size_t strxfrm( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2, size_t n )
{
    size_t len = strlen( s2 );
    if ( len < n )
    {
        /* Cannot use strncpy() here as the filling of s1 with '\0' is not part
           of the spec.
        */
        while ( n-- && ( *s1++ = *s2++ ) );
    }
    return len;
}

#warning Test driver missing.
