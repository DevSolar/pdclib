// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * strcpy( char * restrict s1, const char * restrict s2 ) { /* TODO */ };

/* Therx code - unreviewed
{
    while (*s1++ = *s2++)
    {
        // EMPTY
    }
    return s1;
}
*/

/* PDPC code - unreviewed
char *strcpy(char *s1, const char *s2)
{
    char *p = s1;
    
    while ((*p++ = *s2++) != '\0') ;
    return (s1);
}
*/