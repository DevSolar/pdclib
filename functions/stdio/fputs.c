// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int fputs( const char * restrict s, FILE * restrict stream ) { /* TODO */ };

/* PDPC code - unreviewed
#ifndef __MVS__
int fputs(const char *s, FILE *stream)
{
    size_t len;

    len = strlen(s);
    fwrite(s, len, 1, stream);
    return (0);
}
#endif
*/
