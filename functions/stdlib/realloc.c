// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

void * realloc( void * ptr, size_t size ) { /* TODO */ };

/* PDPC code - unreviewed
{
    char *newptr;
    size_t oldsize;
    
    newptr = malloc(size);
    if (newptr == NULL)
    {
        return (NULL);
    }
    if (ptr != NULL)
    {
        oldsize = *(size_t *)((char *)ptr - 4);
        if (oldsize < size)
        {
            size = oldsize;
        }
        memcpy(newptr, ptr, size);
        free(ptr);
    }
    return (newptr);
}
*/
