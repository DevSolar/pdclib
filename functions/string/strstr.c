// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__NULL.h>

char * strstr( const char * src_1, const char * src_2 )
{
    const char * p1 = src_1;
    const char * p2;
    while ( *src_1 != '\0' )
    {
        p2 = src_2;
        while ( ( *p2 != '\0' ) && ( *p1 == *p2 ) )
        {
            ++p1;
            ++p2;
        }
        if ( *p2 == '\0' )
        {
            return (char *) src_1;
        }
        ++src_1;
        p1 = src_1;
    }
    return NULL;
}
