// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

size_t strspn( const char * s1, const char * s2 ) { /* TODO */ };

/* PDPC code - unreviewed
{
    const char *p1;
    const char *p2;
    
    p1 = s1;
    while (*p1 != '\0')
    {
        p2 = s2;
        while (*p2 != '\0')
        {
            if (*p1 == *p2) break;
            p2++;
        }
        if (*p2 == '\0') return ((size_t)(p1 - s1));
        p1++;
    }
    return ((size_t)(p1 - s1));
}
*/
