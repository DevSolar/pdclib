// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

void * calloc( size_t nelem, size_t size ) { /* TODO */ };

/* PDPC code - unreviewed
{
    void *ptr;
    size_t total;
    
    if (nmemb == 1)
    {
        total = size;
    }
    else if (size == 1)
    {
        total = nmemb;
    }
    else
    {
        total = nmemb * size;
    }
    ptr = malloc(total);
    if (ptr != NULL)
    {
        memset(ptr, '\0', total);
    }
    return (ptr);
}
*/