// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// C++

const void * memchr( const void * s, int c, size_t n ) { /* TODO */ };
void * memchr( void * s, int c, size_t n ) { /* TODO */ };

// ----------------------------------------------------------------------------
// Standard C

void * memchr( const void * s, int c, size_t n ) { /* TODO */ };

/* PDPC code - unreviewed
{
    const unsigned char *p;
    size_t x = 0;
    
    p = (const unsigned char *)s;
    while (x < n)
    {
        if (*p == (unsigned char)c) return ((void *)p);
        p++;
        x++;
    }
    return (NULL);
}
*/
