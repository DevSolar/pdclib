// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * strcat( char * restrict dest, const char * restrict src )
{
    char * dest_p = dest;
    if ( *dest_p != '\0' )
    {
        while ( *++dest_p != '\0' )
        {
            // EMPTY
        }
    }
    while ( (*dest_p++ = *src++) != '\0' )
    {
        // EMPTY
    }
    return dest;
}
