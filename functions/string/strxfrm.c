// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <__size_t.h>

// TODO: Dummy function, no locale support yet.

size_t strlen( const char * src );
char * strncpy( char * restrict dest, const char * restrict src, size_t n );

size_t strxfrm( char * restrict dest, const char * restrict src, size_t n )
{
    size_t len = strlen( src );
    if ( len < n )
    {
        strncpy( dest, src, len );
    }
    return len;
}
