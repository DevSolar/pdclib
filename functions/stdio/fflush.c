// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int fflush( FILE * stream ) { /* TODO */ };

/* PDPC code - unreviewed
Read the note in fopen.c.
{
#ifdef __OS2__
    APIRET rc;
    ULONG actualWritten;
#endif
#ifdef __MSDOS__
    int errind;
    size_t actualWritten;
#endif

    if ((stream->upto != stream->fbuf) && (stream->mode == __WRITE_MODE))
    {
#ifdef __OS2__
        rc = DosWrite(stream->hfile,
                     (VOID *)stream->fbuf,
                     (size_t)(stream->upto - stream->fbuf),
                     &actualWritten);
        if (rc != 0)
        {
            stream->errorInd = 1;
            errno = rc;
            return (EOF);
        }
#endif
#ifdef __MSDOS__
        actualWritten = __write(stream->hfile,
                                stream->fbuf,
                                (size_t)(stream->upto - stream->fbuf),
                                &errind);
        if (errind)
        {
            stream->errorInd = 1;
            errno = actualWritten;
            return (EOF);
        }
#endif
#ifndef __MVS__
        stream->bufStartR += actualWritten;
        stream->upto = stream->fbuf;
#endif
    }
    return (0);
}
*/
