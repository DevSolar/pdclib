// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>
#include <__NULL.h>

void * memchr( const void * src, int c, size_t n )
{
    const unsigned char * p = (const unsigned char *) src;
    while ( n-- )
    {
        if ( *p == (unsigned char) c )
        {
            return (void *) p;
        }
        ++p;
    }
    return NULL;
}
