// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// C++

const char * strstr( const char * s1, const char * s2 ) { /* TODO */ };
char * strstr( char * s1, const char * s2 ) { /* TODO */ };

// ----------------------------------------------------------------------------
// Standard C

char * strstr( const char * s1, const char * s2 ) { /* TODO */ };

/* PDPC code - unreviewed
{
    const char *p = s1, *p1, *p2 = s2;

    while (*p)
    {
        if (*p == *s2)
        {
            p1 = p;
            p2 = s2;
            while ((*p2 != '\0') && (*p1++ == *p2++)) ;
            if (*p2 == '\0')
            {
                return (char *)p;
            }
        }
        p++;
    }
    return NULL;
}
*/
