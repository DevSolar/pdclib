// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * strcpy( char * restrict dest, const char * restrict src )
{
    char * tmp = dest;
    while ( ( *dest++ = *src++ ) != '\0' )
    {
        // EMPTY
    }
    return tmp;
}
