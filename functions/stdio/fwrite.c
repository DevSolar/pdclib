// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

size_t fwrite( const void * restrict ptr, size_t size, size_t nelem, FILE * restrict stream ) { /* TODO */ };

/* PDPC code - unreviewed, verbatim.
Read the note in fopen.c.
#ifndef __MVS__
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t towrite;
    size_t elemWritten;
#ifdef __OS2__
    ULONG actualWritten;
    APIRET rc;
#endif
#ifdef __MSDOS__
    size_t actualWritten;
    int errind;
#endif

    if (nmemb == 1)
    {
        towrite = size;
    }
    else if (size == 1)
    {
        towrite = nmemb;
    }
    else
    {
        towrite = size * nmemb;
    }
    if (towrite < stream->szfbuf)
    {
        stream->quickBin = 0;
        if ((stream->bufTech == _IONBF) && !stream->textMode)
        {
            stream->quickBin = 1;
        }
    }
    if (!stream->quickBin)
    {
        fwriteSlow(ptr, size, nmemb, stream, towrite, &elemWritten);
        return (elemWritten);
    }
    else
    {
#ifdef __OS2__
        rc = DosWrite(stream->hfile, (VOID *)ptr, towrite, &actualWritten);
        if (rc != 0)
        {
            stream->errorInd = 1;
            actualWritten = 0;
            errno = rc;
        }
#endif
#ifdef __MSDOS__
        actualWritten = __write(stream->hfile,
                                ptr,
                                towrite,
                                &errind);
        if (errind)
        {
            stream->errorInd = 1;
            actualWritten = 0;
            errno = actualWritten;
        }
#endif
        if (nmemb == 1)
        {
            if (actualWritten == size)
            {
                elemWritten = 1;
            }
            else
            {
                elemWritten = 0;
            }
        }
        else if (size == 1)
        {
            elemWritten = actualWritten;
        }
        else
        {
            elemWritten = actualWritten / size;
        }
        stream->bufStartR += actualWritten;
        return (elemWritten);
    }
}

static void fwriteSlow(const void *ptr,
                       size_t size,
                       size_t nmemb,
                       FILE *stream,
                       size_t towrite,
                       size_t *elemWritten)
{
    size_t actualWritten;

    /* Normally, on output, there will never be a situation where
       the write buffer is full, but it hasn't been written out.
       If we find this to be the case, then it is because we have
       done an fseek, and didn't know whether we were going to do
       a read or a write after it, so now that we know, we switch
       the buffer to being set up for write.  We could use a flag,
       but I thought it would be better to just put some magic
       code in with a comment */
    if (stream->upto == stream->endbuf)
    {
        stream->bufStartR += (stream->endbuf - stream->fbuf);
        stream->upto = stream->fbuf;
        stream->mode = __WRITE_MODE;
    }
    if ((stream->textMode) || (stream->bufTech == _IOLBF))
    {
        fwriteSlowT(ptr, stream, towrite, &actualWritten);
    }
    else
    {
        fwriteSlowB(ptr, stream, towrite, &actualWritten);
    }
    if (nmemb == 1)
    {
        if (actualWritten == size)
        {
            *elemWritten = 1;
        }
        else
        {
            *elemWritten = 0;
        }
    }
    else if (size == 1)
    {
        *elemWritten = actualWritten;
    }
    else
    {
        *elemWritten = actualWritten / size;
    }
    return;
}


/* can still be called on binary files, if the binary file is
   line buffered  */

static void fwriteSlowT(const void *ptr,
                        FILE *stream,
                        size_t towrite,
                        size_t *actualWritten)
{
    char *p;
    char *tptr;
    char *oldp;
    size_t diffp;
    size_t rem;
    int fin;
#ifdef __OS2__
    ULONG tempWritten;
    APIRET rc;
#endif
#ifdef __MSDOS__
    size_t tempWritten;
    int errind;
#endif

    *actualWritten = 0;
    tptr = (char *)ptr;
    p = tptr;
    oldp = p;
    p = (char *)memchr(oldp, '\n', towrite - (size_t)(oldp - tptr));
    while (p != NULL)
    {
        diffp = (size_t)(p - oldp);
        fin = 0;
        while (!fin)
        {
            rem = (size_t)(stream->endbuf - stream->upto);
            if (diffp < rem)
            {
                memcpy(stream->upto, oldp, diffp);
                stream->upto += diffp;
                *actualWritten += diffp;
                fin = 1;
            }
            else
            {
                memcpy(stream->upto, oldp, rem);
                oldp += rem;
                diffp -= rem;
#ifdef __OS2__
                rc = DosWrite(stream->hfile,
                              stream->fbuf,
                              stream->szfbuf,
                              &tempWritten);
                if (rc != 0)
                {
                    stream->errorInd = 1;
                    return;
                }
#endif
#ifdef __MSDOS__
                tempWritten = __write(stream->hfile,
                                      stream->fbuf,
                                      stream->szfbuf,
                                      &errind);
                if (errind)
                {
                    stream->errorInd = 1;
                    return;
                }
#endif
                else
                {
                    *actualWritten += rem;
                    stream->upto = stream->fbuf;
                    stream->bufStartR += tempWritten;
                }
            }
        }
        rem = (size_t)(stream->endbuf - stream->upto);
        if (rem < 2)
        {
#ifdef __OS2__
            rc = DosWrite(stream->hfile,
                          stream->fbuf,
                          (size_t)(stream->upto - stream->fbuf),
                          &tempWritten);
            if (rc != 0)
            {
                stream->errorInd = 1;
                errno = rc;
                return;
            }
#endif
#ifdef __MSDOS__
            tempWritten = __write(stream->hfile,
                                  stream->fbuf,
                                  (size_t)(stream->upto - stream->fbuf),
                                  &errind);
            if (errind)
            {
                stream->errorInd = 1;
                errno = tempWritten;
                return;
            }
#endif
            stream->upto = stream->fbuf;
            stream->bufStartR += tempWritten;
        }
        if (stream->textMode)
        {
            memcpy(stream->upto, "\r\n", 2);
            stream->upto += 2;
        }
        else
        {
            memcpy(stream->upto, "\n", 1);
            stream->upto += 1;
        }
        *actualWritten += 1;
        oldp = p + 1;
        p = (char *)memchr(oldp, '\n', towrite - (size_t)(oldp - tptr));
    }

    if ((stream->bufTech == _IOLBF)
        && (stream->upto != stream->fbuf)
        && (oldp != tptr))
    {
#ifdef __OS2__
        rc = DosWrite(stream->hfile,
                      stream->fbuf,
                      (size_t)(stream->upto - stream->fbuf),
                      &tempWritten);
        if (rc != 0)
        {
            stream->errorInd = 1;
            errno = rc;
            return;
        }
#endif
#ifdef __MSDOS__
        tempWritten = __write(stream->hfile,
                              stream->fbuf,
                              (size_t)(stream->upto - stream->fbuf),
                              &errind);
        if (errind)
        {
            stream->errorInd = 1;
            errno = tempWritten;
            return;
        }
#endif
        stream->upto = stream->fbuf;
        stream->bufStartR += tempWritten;
    }

    diffp = towrite - *actualWritten;
    while (diffp != 0)
    {
        rem = (size_t)(stream->endbuf - stream->upto);
        if (diffp < rem)
        {
            memcpy(stream->upto, oldp, diffp);
            stream->upto += diffp;
            *actualWritten += diffp;
        }
        else
        {
            memcpy(stream->upto, oldp, rem);
#ifdef __OS2__
            rc = DosWrite(stream->hfile,
                          stream->fbuf,
                          stream->szfbuf,
                          &tempWritten);
            if (rc != 0)
            {
                stream->errorInd = 1;
                errno = rc;
                return;
            }
#endif
#ifdef __MSDOS__
            tempWritten = __write(stream->hfile,
                                  stream->fbuf,
                                  stream->szfbuf,
                                  &errind);
            if (errind)
            {
                stream->errorInd = 1;
                errno = tempWritten;
                return;
            }
#endif
            else
            {
                *actualWritten += rem;
                stream->upto = stream->fbuf;
            }
            stream->bufStartR += tempWritten;
            oldp += rem;
        }
        diffp = towrite - *actualWritten;
    }
    if ((stream->bufTech == _IONBF)
        && (stream->upto != stream->fbuf))
    {
#ifdef __OS2__
        rc = DosWrite(stream->hfile,
                      stream->fbuf,
                      (size_t)(stream->upto - stream->fbuf),
                      &tempWritten);
        if (rc != 0)
        {
            stream->errorInd = 1;
            errno = rc;
            return;
        }
#endif
#ifdef __MSDOS__
        tempWritten = __write(stream->hfile,
                              stream->fbuf,
                              (size_t)(stream->upto - stream->fbuf),
                              &errind);
        if (errind)
        {
            stream->errorInd = 1;
            errno = tempWritten;
            return;
        }
#endif
        stream->upto = stream->fbuf;
        stream->bufStartR += tempWritten;
    }
    return;
}

/* whilst write requests are smaller than a buffer, we do not turn
   on quickbin */

static void fwriteSlowB(const void *ptr,
                        FILE *stream,
                        size_t towrite,
                        size_t *actualWritten)
{
    size_t spare;
#ifdef __OS2__
    ULONG tempWritten;
    APIRET rc;
#endif
#ifdef __MSDOS__
    size_t tempWritten;
    int errind;
#endif

    spare = (size_t)(stream->endbuf - stream->upto);
    if (towrite < spare)
    {
        memcpy(stream->upto, ptr, towrite);
        *actualWritten = towrite;
        stream->upto += towrite;
        return;
    }
    memcpy(stream->upto, ptr, spare);
#ifdef __OS2__
    rc = DosWrite(stream->hfile,
                  stream->fbuf,
                  stream->szfbuf,
                  &tempWritten);
    if (rc != 0)
    {
        stream->errorInd = 1;
        errno = rc;
        return;
    }
#endif
#ifdef __MSDOS__
    tempWritten = __write(stream->hfile,
                          stream->fbuf,
                          stream->szfbuf,
                          &errind);
    if (errind)
    {
        stream->errorInd = 1;
        errno = tempWritten;
        return;
    }
#endif
    *actualWritten = spare;
    stream->upto = stream->fbuf;
    stream->bufStartR += tempWritten;
    if (towrite > stream->szfbuf)
    {
        stream->quickBin = 1;
#ifdef __OS2__
        rc = DosWrite(stream->hfile,
                      (char *)ptr + *actualWritten,
                      towrite - *actualWritten,
                      &tempWritten);
        if (rc != 0)
        {
            stream->errorInd = 1;
            errno = rc;
            return;
        }
#endif
#ifdef __MSDOS__
        tempWritten = __write(stream->hfile,
                              (char *)ptr + *actualWritten,
                              towrite - *actualWritten,
                              &errind);
        if (errind)
        {
            stream->errorInd = 1;
            errno = tempWritten;
            return;
        }
#endif
        *actualWritten += tempWritten;
        stream->bufStartR += tempWritten;
    }
    else
    {
        memcpy(stream->fbuf,
               (char *)ptr + *actualWritten,
               towrite - *actualWritten);
        stream->upto += (towrite - *actualWritten);
        *actualWritten = towrite;
    }
    stream->bufStartR += *actualWritten;
    return;
}
#endif
*/
