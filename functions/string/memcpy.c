// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

void * memcpy( void * restrict s1, const void * restrict s2, size_t n ) { /* TODO */ };

/* Therx code
{
    void * ret = s1;
    const char * src = (const char *) s2;
    char * dst = (char *) s1;
    for( ; n != 0; n-- )
    {
        *dst++ = *src++;
    }
    return ret;
}
*/

/* PDPC code - unreviewed
void *memcpy(void *s1, const void *s2, size_t n)
{
    register const unsigned char *f = s2;
    register const unsigned char *fe;
    register unsigned char *t = s1;
    
    fe = f + n;
    while (f != fe)
    {
        *t++ = *f++;
    }
    return (s1);
}
#else
void *memcpy(void *s1, const void *s2, size_t n)
{
    register unsigned int *p = (unsigned int *)s1;
    register unsigned int *cs2 = (unsigned int *)s2;
    register unsigned int *endi;
    
    endi = (unsigned int *)((char *)p + (n & ~0x03));
    while (p != endi)
    {
        *p++ = *cs2++;
    }
    switch (n & 0x03)
    {
        case 0:
            break;
        case 1:
            *(char *)p = *(char *)cs2;
            break;
        case 2:
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            break;
        case 3:
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            break;
    }
    return (s1);
}
*/
