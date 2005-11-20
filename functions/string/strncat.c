/* $Id$ */

/* Release $Name$ */

/* strncat( char *, const char *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_aux.h>
#include <string.h>

char * strncat( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2, size_t n )
{
    char * rc = s1;
    while ( *s1 )
    {
        ++s1;
    }
    while ( n && ( *s1++ = *s2++ ) )
    {
        --n;
    }
    if ( n == 0 )
    {
        *s1 = '\0';
    }
    return rc;
}

#warning Test driver missing.

#ifdef TEST
int main()
{
    return 0;
}
#endif
