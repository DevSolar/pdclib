// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int fclose( FILE * stream ) { /* TODO */ };

/* PDPC code - unreviewed.
Read the note in fopen.c.
int fclose(FILE *stream)
{
#ifdef __OS2__
    APIRET rc;
#endif

    fflush(stream);
#ifdef __OS2__
    rc = DosClose(stream->hfile);
#endif
#ifdef __MSDOS__
    __close(stream->hfile);
#endif
#ifdef __MVS__
    __aclose(stream->hfile);
#endif
    __userFiles[stream->intFno] = NULL;
    if (!stream->theirBuffer)
    {
        free(stream->intBuffer);
    }
    free(stream);
#ifdef __OS2__
    if (rc != 0)
    {
        errno = rc;
        return (EOF);
    }
#endif
    return (0);
}
*/
