// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__NULL.h>

char * strchr( const char * src, int c )
{
    while ( *src != '\0' )
    {
        if ( *src == (const char) c )
        {
            return (char *) src;
        }
        ++src;
    }
    return NULL;
}
