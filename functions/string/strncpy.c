// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>

char * strncpy( char * restrict dest, const char * restrict src, size_t n )
{
    char * tmp = dest;
    while ( ( n-- != 0 ) && ( ( *dest++ = *src++ ) != '\0' ) )
    {
        // EMPTY
    }
    while ( n-- != 0 )
    {
        *dest++ = '\0';
    }
    return tmp;
}
