// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * strncpy( char * restrict s1, const char * restrict s2, size_t n ) { /* TODO */ };

/* PDPC code - unreviewed
char *strncpy(char *s1, const char *s2, size_t n)
{
    char *p = s1;
    size_t x;
    
    for (x=0; x < n; x++)
    {
        *p = *s2;
        if (*s2 == '\0') break;
        p++;
        s2++;
    }
    for (; x < n; x++)
    {
        *p++ = '\0';
    }
    return (s1);
}
*/