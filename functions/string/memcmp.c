// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <string.h>

int memcmp( const void * src_1, const void * src_2, size_t n )
{
    const unsigned char * p1 = (const unsigned char *) src_1;
    const unsigned char * p2 = (const unsigned char *) src_2;
    while ( n-- )
    {
        if ( *p1 != *p2 )
        {
            return *p2 - *p1;
        }
        ++p1;
        ++p2;
    }
    return 0;
}
