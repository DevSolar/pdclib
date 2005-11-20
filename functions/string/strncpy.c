/* $Id$ */

/* Release $Name$ */

/* strncpy( char *, const char *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_aux.h>
#include <string.h>

char * strncpy( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2, size_t n )
{
    char * rc = s1;
    while ( ( n > 0 ) && ( *s1++ = *s2++ ) )
    {
        /* Cannot do "n--" in the conditional as size_t is unsigned and we have
           to check it again for >0 in the next loop.
        */
        --n;
    }
    while ( n-- )
    {
        *s1++ = '\0';
    }
    return rc;
}

#warning Test driver missing.
