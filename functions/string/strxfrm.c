// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

size_t strxfrm( char * restrict s1, const char * restrict s2, size_t n ) { /* TODO */ };

/* PDPC code - unreviewed
{
    size_t oldlen;
    
    oldlen = strlen(s2);
    if (oldlen < n)
    {
        memcpy(s1, s2, oldlen);
        s1[oldlen] = '\0';
    }
    return (oldlen);
}
*/
