// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int fgetpos( FILE * restrict stream, fpos_t * restrict pos ) { /* TODO */ };

/* PDPC code - unreviewed
{
    *pos = ftell(stream);
    return (0);
}
*/
