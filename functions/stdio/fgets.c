// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * fgets( char * restrict s, int n, FILE * restrict stream ) { /* TODO */ };

/* PDPC code - unreviewed
/*

In fgets, we have the following possibilites...

1. we found a genuine '\n' that terminated the search.
2. we hit the '\n' at the endbuf.
3. we hit the '\n' sentinel.

*/
#ifndef __MVS__
char *fgets(char *s, int n, FILE *stream)
{
    char *p;
    register char *t;
    register char *u = s;
    int c;
    int processed;
#ifdef __OS2__
    ULONG actualRead;
    APIRET rc;
#endif
#ifdef __MSDOS__
    size_t actualRead;
    int errind;
#endif

    if (stream->quickText)
    {
        p = stream->upto + n - 1;
        t = stream->upto;
        if (p < stream->endbuf)
        {
            c = *p;
            *p = '\n';
#ifdef __OS2__
            if (n < 8)
            {
#endif
                while ((*u++ = *t++) != '\n') ; /* tight inner loop */
#ifdef __OS2__
            }
            else
            {
                register unsigned int *i1;
                register unsigned int *i2;
                register unsigned int z;

                i1 = (unsigned int *)t;
                i2 = (unsigned int *)u;
                while (1)
                {
                    z = *i1;
                    if ((z & 0xffU) == '\n') break;
                    z >>= 8;
                    if ((z & 0xffU) == '\n') break;
                    z >>= 8;
                    if ((z & 0xffU) == '\n') break;
                    z >>= 8;
                    if ((z & 0xffU) == '\n') break;
                    *i2++ = *i1++;
                }
                t = (char *)i1;
                u = (char *)i2;
                while ((*u++ = *t++) != '\n') ;
            }
#endif
            *p = (char)c;
            if (t <= p)
            {
                if (*(t - 2) == '\r') /* t is protected, u isn't */
                {
                    *(u - 2) = '\n';
                    *(u - 1) = '\0';
                }
                else
                {
                    *u = '\0';
                }
                stream->upto = t;
                return (s);
            }
            else
            {
                processed = (int)(t - stream->upto) - 1;
                stream->upto = t - 1;
                u--;
            }
        }
        else
        {
            while ((*u++ = *t++) != '\n') ; /* tight inner loop */
            if (t <= stream->endbuf)
            {
                if (*(t - 2) == '\r') /* t is protected, u isn't */
                {
                    *(u - 2) = '\n';
                    *(u - 1) = '\0';
                }
                else
                {
                    *u = '\0';
                }
                stream->upto = t;
                return (s);
            }
            else
            {
                processed = (int)(t - stream->upto) - 1;
                stream->upto = t - 1;
                u--;
            }
        }
    }
    else
    {
        processed = 0;
    }

    if (n < 1)
    {
        return (NULL);
    }
    if (n < 2)
    {
        *u = '\0';
        return (s);
    }
    if (stream->ungetCh != -1)
    {
        processed++;
        *u++ = (char)stream->ungetCh;
        stream->ungetCh = -1;
    }
    while (1)
    {
        t = stream->upto;
        p = stream->upto + (n - processed) - 1;
        if (p < stream->endbuf)
        {
            c = *p;
            *p = '\n';
        }
        if (stream->noNl)
        {
            while (((*u++ = *t) != '\n') && (*t++ != '\r')) ;
            if (*(u - 1) == '\n')
            {
                t++;
            }
            else
            {
                u--;
                while ((*u++ = *t++) != '\n') ;
            }
        }
        else
        {
            while ((*u++ = *t++) != '\n') ; /* tight inner loop */
        }
        if (p < stream->endbuf)
        {
            *p = (char)c;
        }
        if (((t <= p) && (p < stream->endbuf))
           || ((t <= stream->endbuf) && (p >= stream->endbuf)))
        {
            if (stream->textMode)
            {
                if (stream->noNl)
                {
                    if ((*(t - 1) == '\r') || (*(t - 1) == '\n'))
                    {
                        *(u - 1) = '\0';
                    }
                    else
                    {
                        *u = '\0';
                    }
                }
                else if (*(t - 2) == '\r') /* t is protected, u isn't */
                {
                    *(u - 2) = '\n';
                    *(u - 1) = '\0';
                }
                else
                {
                    *u = '\0';
                }
            }
            stream->upto = t;
            if (stream->textMode)
            {
                stream->quickText = 1;
            }
            return (s);
        }
        else if (((t > p) && (p < stream->endbuf))
                 || ((t > stream->endbuf) && (p >= stream->endbuf)))
        {
            int leave = 1;

            if (stream->textMode)
            {
                if (t > stream->endbuf)
                {
                    if ((t - stream->upto) > 1)
                    {
                        if (*(t - 2) == '\r') /* t is protected, u isn't */
                        {
                            processed -= 1; /* preparation for add */
                        }
                    }
                    leave = 0;
                }
                else
                {
                    if ((*(t - 2) == '\r') && (*(t - 1) == '\n'))
                    {
                        *(u - 2) = '\n';
                        *(u - 1) = '\0';
                    }
                    else
                    {
                        t--;
                        *(u - 1) = '\0';
                    }
                }
            }
            else if (t > stream->endbuf)
            {
                leave = 0;
            }
            else
            {
                *u = '\0';
            }
            if (leave)
            {
                stream->upto = t;
                if (stream->textMode)
                {
                    stream->quickText = 1;
                }
                return (s);
            }
        }
        processed += (int)(t - stream->upto) - 1;
        u--;
        stream->bufStartR += (stream->endbuf - stream->fbuf);
#ifdef __OS2__
        rc = DosRead(stream->hfile, stream->fbuf, stream->szfbuf, &actualRead);
        if (rc != 0)
        {
            actualRead = 0;
            stream->errorInd = 1;
            errno = rc;
        }
#endif
#ifdef __MSDOS__
        actualRead = __read(stream->hfile,
                            stream->fbuf,
                            stream->szfbuf,
                            &errind);
        if (errind)
        {
            errno = actualRead;
            actualRead = 0;
            stream->errorInd = 1;
        }
#endif
        stream->endbuf = stream->fbuf + actualRead;
        *stream->endbuf = '\n';
        if (actualRead == 0)
        {
            *u = '\0';
            if ((u - s) <= 1)
            {
                stream->eofInd = 1;
                return (NULL);
            }
            else
            {
                return (s);
            }
        }
        stream->upto = stream->fbuf;
    }
}
#endif
*/
