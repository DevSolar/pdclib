// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * strtok( char * restrict s1, const char * restrict s2 ) { /* TODO */ };

/* PDPC code - unreviewed
{
    static char *old = NULL;
    char *p;
    size_t len;
    size_t remain;
    
    if (s1 != NULL) old = s1;
    if (old == NULL) return (NULL);
    p = old;
    len = strspn(p, s2);
    remain = strlen(p);
    if (remain <= len) { old = NULL; return (NULL); }
    p += len;
    len = strcspn(p, s2);
    remain = strlen(p);
    if (remain <= len) { old = NULL; return (p); }
    *(p + len) = '\0';
    old = p + len + 1;
    return (p);
}
*/
