// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

size_t mbstowcs( wchar_t * restrict wcs, const char * restrict s, size_t n ) { /* TODO */ };

/* PDPC code - unreviewed
{
    strncpy((char *)pwcs, s, n);
    if (strlen(s) >= n)
    {
        return (n);
    }
    return (strlen((char *)pwcs));
}
*/
