// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>

size_t strlen( const char * src )
{
    size_t len = 0;
    while ( src[len] != '\0' )
    {
        ++len;
    }
    return len;
}
