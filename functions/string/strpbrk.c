// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__NULL.h>

char * strpbrk( const char *src_1, const char * src_2 )
{
    const char * p1 = src_1;
    const char * p2;
    while ( *p1 != '\0' )
    {
        p2 = src_2;
        while ( *p2 != '\0' )
        {
            if ( *p1 == *p2++ )
            {
                return (char *) p1;
            }
        }
        ++p1;
    }
    return NULL;
}
