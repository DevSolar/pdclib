// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>

void * memset( void * dest, int c, size_t n )
{
    unsigned char ch = (unsigned char) c;
    unsigned char * dest_p = (unsigned char *) dest;
    while ( n-- )
    {
        *dest_p++ = ch;
    }
    return dest;
}
