// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>

void * memmove( void * dest, const void * src, size_t n )
{
    const char * src_p = (const char *) src;
    char * dest_p = (char *) dest;
    if ( dest_p < src_p )
    {
        while ( n-- )
        {
            *dest_p++ = *src_p++;
        }
    }
    else
    {
        src_p += n;
        dest_p += n;
        while ( n-- )
        {
            *dest_p-- = *src_p--;
        }
    }
    return dest;
}
