// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * strcat( char * restrict s1, const char * restrict s2 ) { /* TODO */ };

/* Therx code
{
    while (*s1)
    {
        s1++;
    }
    while (*s1++ = *s2++)
    {
        // EMPTY
    }
    return s1;
}
*/

/* PDPC code - unreviewed
{
    char *p = s1;
    
    while (*p != '\0') p++;
    while ((*p = *s2) != '\0')
    {
        p++;
        s2++;
    }
    return (s1);
}
*/
