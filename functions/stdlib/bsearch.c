// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// TODO: C/C++ linkage
void * bsearch( const void * key, const void * base, size_t nelem, size_t size, int (*cmp) ( const void * ck, const void * ce) ) { /* TODO */ };

/* PDPC code - unreviewed
{
    size_t try;
    int res;
    const void *ptr;
    
    while (nmemb > 0)
    {
        try = nmemb / 2;    
        ptr = (void *)((char *)base + try * size);
        res = compar(ptr, key);
        if (res == 0)
        {
            return ((void *)ptr);
        }
        else if (res < 0)
        {
            nmemb = nmemb - try - 1;
            base = (const void *)((const char *)ptr + size);
        }
        else
        {
            nmemb = try;
        }
    }
    return (NULL);
}
*/
