// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__NULL.h>

char * strrchr( const char * src, int c )
{
    const char * p = src;
    while ( *p != '\0' )
    {
        ++p;
    }
    while ( p >= src )
    {
        if ( *p == (char) c )
        {
            return (char *) p;
        }
        --p;
    }
    return NULL;
}
