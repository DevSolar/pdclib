// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

FILE * freopen( const char * restrict filename, const char * restrict mode, FILE * stream ) { /* TODO */ };

/* PDPC code - unreviewed
{
    fclose(stream);
    return (fopen(filename, mode));
}
*/
