// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

void * memmove( void * s1, const void * s2, size_t n ) { /* TODO */ };

/* PDPC code - unreviewed
{
    char *p = s1;
    const char *cs2 = s2;
    size_t x;
    
    if (p <= cs2)
    {
        for (x=0; x < n; x++)
        {
            *p = *cs2;
            p++;
            cs2++;
        }
    }
    else
    {
        if (n != 0)
        {
            for (x=n-1; x > 0; x--)
            {
                *(p+x) = *(cs2+x);
            }
        }
        *(p+x) = *(cs2+x);
    }
    return (s1);
}
*/