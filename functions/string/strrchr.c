// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// C++

const char * strrchr( const char * s, int c ) { /* TODO */ };
char * strrchr( char * s, int c ) { /* TODO */ };

// ----------------------------------------------------------------------------
// Standard C

char * strrchr( const char * s, int c ) { /* TODO */ };

/* PDPC code - unreviewed
{
    const char *p;
    
    p = s + strlen(s);
    while (p >= s)
    {
        if (*p == (char)c) return ((char *)p);
        p--;
    }
    return (NULL);
}
*/
