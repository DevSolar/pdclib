// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * strncat( char * restrict s1, const char * restrict s2, size_t n ) { /* TODO */ };

/* PDPC code - unreviewed
{
    char *p = s1;
    size_t x = 0;
    
    while (*p != '\0') p++;
    while ((*s2 != '\0') && (x < n))
    {
        *p = *s2;
        p++;
        s2++;
        x++;
    }
    *p = '\0';
    return (s1);
}
*/
