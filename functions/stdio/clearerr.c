// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

void clearerr( FILE * stream ) { /* TODO */ };

/* PDPC code - unreviewed
{
    stream->errorInd = 0;
    stream->eofInd = 0;
    return;
}
*/
