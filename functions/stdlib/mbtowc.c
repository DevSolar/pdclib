// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int mbtowc( wchar_t * restrict pwc, const char * restrict s, size_t n ) { /* TODO */ };

/* PDPC code - unreviewed
{
    if (s == NULL)
    {
        return (0);
    }
    if (n == 1)
    {
        if (pwc != NULL)
        {
            *pwc = *s;
        }
        return (1);
    }
    else
    {
        return (-1);
    }
}
*/