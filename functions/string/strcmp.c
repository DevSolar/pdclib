// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int strcmp( const char * s1, const char * s2 ) { /* TODO */ };

/* Therx code
{
    while ((*s1 != '\0') && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *) s1) - (*(unsigned char *) s2);
}
*/

/* PDPC code - unreviewed
{
    const unsigned char *p1;
    const unsigned char *p2;
    
    p1 = (const unsigned char *)s1;
    p2 = (const unsigned char *)s2;
    while (*p1 != '\0')
    {
        if (*p1 < *p2) return (-1);
        else if (*p1 > *p2) return (1);
        p1++;
        p2++;
    }
    if (*p2 == '\0') return (0);
    else return (-1);
}
*/
