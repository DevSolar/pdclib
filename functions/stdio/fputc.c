// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int fputc( int c, FILE * stream ) { /* TODO */ };

/* PDPC code - unreviewed
{
    char buf[1];

#ifndef __MVS__
    stream->quickBin = 0;
    if ((stream->upto < (stream->endbuf - 2))
        && (stream->bufTech != _IONBF))
    {
        if (stream->textMode)
        {
            if (c == '\n')
            {
                if (stream->bufTech == _IOFBF)
                {
                    *stream->upto++ = '\r';
                    *stream->upto++ = '\n';
                }
                else
                {
                    buf[0] = (char)c;
                    if (fwrite(buf, 1, 1, stream) != 1)
                    {
                        return (EOF);
                    }
                }
            }
            else
            {
                *stream->upto++ = (char)c;
            }
        }
        else
        {
            *stream->upto++ = (char)c;
        }
    }
    else
#endif
    {
        buf[0] = (char)c;
        if (fwrite(buf, 1, 1, stream) != 1)
        {
            return (EOF);
        }
    }
    return (c);
}
*/
