// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>

size_t strspn( const char * src_1, const char * src_2 )
{
    size_t len = 0;
    const char * p;
    while ( src_1[ len ] != '\0' )
    {
        p = src_2;
        while ( *p != '\0' )
        {
            if ( *src_1 == *p )
            {
                break;
            }
            ++p;
        }
        if ( *p == '\0' )
        {
            return len;
        }
        ++len;
    }
    return len;
}
