// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

long ftell( FILE * stream ) { /* TODO */ };

/* PDPC code - unreviewed
{
    return (stream->bufStartR + (stream->upto - stream->fbuf));
}
*/
