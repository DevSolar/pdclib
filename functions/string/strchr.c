// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// C++

const char * strchr( const char * s, int c ) { /* TODO */ };
char * strchr( char * s, int c ) { /* TODO */ };

// ----------------------------------------------------------------------------
// Standard C

char * strchr( const char * s, int c ) { /* TODO */ };

/* PDPC code - unreviewed
{
    while (*s != '\0')
    {
        if (*s == (char)c) return ((char *)s);
        s++;
    }
    return (NULL);
}
*/
