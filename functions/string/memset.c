// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

void * memset( void * s, int c, size_t n ) { /* TODO */ };

/* Therx code
{
    unsigned short * tmp = (unsigned short *) s; // TODO: unsigned short?
    for( ; n != 0; n-- )
    {
        *tmp++ = c;
    }
    return s;
}
*/

/* PDPC code - unreviewed
{
    size_t x = 0;
    
    for (x = 0; x < n; x++)
    {
        *((char *)s + x) = (unsigned char)c;
    }
    return (s);
}
*/
