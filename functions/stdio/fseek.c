// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int fseek( FILE * stream, long offset, int mode ) { /* TODO */ };

/* PDPC code - unreviewed
Read the note in fopen.c.
{
    long newpos;
#ifdef __OS2__
    ULONG retpos;
    APIRET rc;
#endif

    if (stream->mode == __WRITE_MODE)
    {
        fflush(stream);
    }
    if (whence == SEEK_SET)
    {
        newpos = offset;
    }
    else if (whence == SEEK_CUR)
    {
        newpos = offset + stream->bufStartR + (stream->upto - stream->fbuf);
    }
    if ((newpos > stream->bufStartR)
        && (newpos < (stream->bufStartR + (stream->endbuf - stream->fbuf)))
        && stream->update)
    {
        stream->upto = stream->fbuf + (size_t)(newpos - stream->bufStartR);
    }
    else
    {
#ifdef __OS2__
        rc = DosSetFilePtr(stream->hfile, newpos, FILE_BEGIN, &retpos);
        if ((rc != 0) || (retpos != newpos))
        {
            errno = rc;
            return (-1);
        }
        else
        {
            stream->endbuf = stream->fbuf + stream->szfbuf;
            stream->upto = stream->endbuf;
            stream->bufStartR = newpos - stream->szfbuf;
        }
#endif
#ifdef __MSDOS
        __seek(stream->hfile, newpos, whence);
        stream->endbuf = stream->fbuf + stream->szfbuf;
        stream->upto = stream->endbuf;
        stream->bufStartR = newpos - stream->szfbuf;
#endif
    }
    stream->quickBin = 0;
    stream->quickText = 0;
    stream->ungetCh = -1;
    return (0);
}
*/
