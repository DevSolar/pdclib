// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>

char * strncat( char * restrict dest, const char * restrict src, size_t n )
{
    char * tmp = dest;
    while ( *dest != '\0' )
    {
        ++dest;
    }
    while ( ( n-- > 0 ) && ( *src != '\0' ) )
    {
        *dest++ = *src++;
    }
    return tmp;
}
