// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * gets( char * s ) { /* TODO */ };

/* PDPC code - unreviewed
{
    char *ret;

    stdin->quickText = 0;
    stdin->noNl = 1;
    ret = fgets(s, INT_MAX, stdin);
    stdin->noNl = 0;
    stdin->quickText = 1;
    return (ret);
}
*/
