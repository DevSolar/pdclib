// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * tmpnam( char * s ) { /* TODO */ };

/* PDPC code - unreviewed
{
    static char buf[] = "ZZZZZZZA.$$$";

    buf[7]++;
    if (s == NULL)
    {
        return (buf);
    }
    strcpy(s, buf);
    return (s);
}
*/
