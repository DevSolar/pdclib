// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

size_t strlen( const char * s ) { /* TODO */ };

/* Therx code
{
    const char * start = s1;
    while (*s1)
    {
        s1++;
    }
    return s1 - start;
}
*/

/* PDPC code - unreviewed
{
    const char *p;
    
    p = s;
    while (*p != '\0') p++;
    return ((size_t)(p - s));
}
*/
