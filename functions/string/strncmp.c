// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>

int strncmp( const char * src_1, const char * src_2, size_t n )
{
    while ( ( n-- != 0 ) && ( *src_1 == *src_2 ) )
    {
        ++src_1;
        ++src_2;
    }
    if ( ( n == 0 ) )
    {
        return 0;
    }
    return ( *src_1 - *src_2 );
}
