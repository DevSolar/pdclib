// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

FILE * fopen( const char * restrict filename, const char * restrict mode ) { /* TODO */ };

/* PDPC code - unreviewed, verbatim.
NOTE THAT PDPC WAS MEANT TO RUN ON A HOST OS.
I thought the approach to "osfopen()" was close enough to what we have in mind
for pdclib to include the code here.

{
    fnm = filename;
    modus = mode;
    err = 0;
    findSpareSpot();
    if (!err)
    {
        myfile = malloc(sizeof(FILE));
        if (myfile == NULL)
        {
            err = 1;
        }
        else
        {
            fopen2();
            if (err)
            {
                free(myfile);
            }
        }
    }
    if (err)
    {
        myfile = NULL;
    }
    return (myfile);
}

static void fopen2(void)
{
    checkMode();
    if (!err)
    {
        osfopen();
        if (!err)
        {
            __userFiles[spareSpot] = myfile;
            myfile->intFno = spareSpot;
            fopen3();
        }
    }
    return;
}

static void fopen3(void)
{
    myfile->intBuffer = malloc(BUFSIZ + 8);
    if (myfile->intBuffer == NULL)
    {
        err = 1;
    }
    else
    {
        myfile->theirBuffer = 0;
        myfile->fbuf = myfile->intBuffer + 2;
        *myfile->fbuf++ = '\0';
        *myfile->fbuf++ = '\0';
        myfile->szfbuf = BUFSIZ;
#ifndef __MVS__
        myfile->quickText = 0;
#endif
        myfile->noNl = 0;
        myfile->endbuf = myfile->fbuf + myfile->szfbuf;
        *myfile->endbuf = '\n';
#ifdef __MVS__
        myfile->upto = myfile->fbuf;
        myfile->szfbuf = myfile->lrecl;
#else
        myfile->upto = myfile->endbuf;
#endif
        myfile->bufStartR = -(long)myfile->szfbuf;
        myfile->errorInd = 0;
        myfile->eofInd = 0;
        myfile->ungetCh = -1;
        myfile->update = 0;
#ifndef __MVS__
        if (!myfile->textMode)
        {
            myfile->quickBin = 1;
        }
        else
        {
            myfile->quickBin = 0;
        }
#endif
        myfile->mode = __READ_MODE;
        switch (modeType)
        {
            case 2:
            case 3:
            case 5:
            case 6:
            case 8:
            case 9:
            case 11:
            case 12:
                myfile->bufStartR = 0;
                myfile->upto = myfile->fbuf;
                myfile->mode = __WRITE_MODE;
                break;
        }
        switch (modeType)
        {
            case 7:
            case 8:
            case 10:
            case 11:
            case 12:
                myfile->update = 1;
                break;
        }
    }
    return;
}

static void findSpareSpot(void)
{
    int x;

    for (x = 0; x < __NFILE; x++)
    {
        if (__userFiles[x] == NULL)
        {
            break;
        }
    }
    if (x == __NFILE)
    {
        err = 1;
    }
    else
    {
        spareSpot = x;
    }
    return;
}

/* checkMode - interpret mode string */
/* r = 1 */
/* w = 2 */
/* a = 3 */
/* rb = 4 */
/* wb = 5 */
/* ab = 6 */
/* r+ = 7 */
/* w+ = 8 */
/* a+ = 9 */
/* r+b or rb+ = 10 */
/* w+b or wb+ = 11 */
/* a+b or ab+ = 12 */

static void checkMode(void)
{
    if (strncmp(modus, "r+b", 3) == 0)
    {
        modeType = 10;
    }
    else if (strncmp(modus, "rb+", 3) == 0)
    {
        modeType = 10;
    }
    else if (strncmp(modus, "w+b", 3) == 0)
    {
        modeType = 11;
    }
    else if (strncmp(modus, "wb+", 3) == 0)
    {
        modeType = 11;
    }
    else if (strncmp(modus, "a+b", 3) == 0)
    {
        modeType = 12;
    }
    else if (strncmp(modus, "ab+", 3) == 0)
    {
        modeType = 12;
    }
    else if (strncmp(modus, "r+", 2) == 0)
    {
        modeType = 7;
    }
    else if (strncmp(modus, "w+", 2) == 0)
    {
        modeType = 8;
    }
    else if (strncmp(modus, "a+", 2) == 0)
    {
        modeType = 9;
    }
    else if (strncmp(modus, "rb", 2) == 0)
    {
        modeType = 4;
    }
    else if (strncmp(modus, "wb", 2) == 0)
    {
        modeType = 5;
    }
    else if (strncmp(modus, "ab", 2) == 0)
    {
        modeType = 6;
    }
    else if (strncmp(modus, "r", 1) == 0)
    {
        modeType = 1;
    }
    else if (strncmp(modus, "w", 1) == 0)
    {
        modeType = 2;
    }
    else if (strncmp(modus, "a", 1) == 0)
    {
        modeType = 3;
    }
    else
    {
        err = 1;
        return;
    }
    if ((modeType == 4)
        || (modeType == 5)
        || (modeType == 6)
        || (modeType == 10)
        || (modeType == 11)
        || (modeType == 12))
    {
        myfile->textMode = 0;
    }
    else
    {
        myfile->textMode = 1;
    }
    return;
}

static void osfopen(void)
{
#ifdef __OS2__
    APIRET rc;
    ULONG  action;
    ULONG  newsize = 0;
    ULONG  fileAttr = 0;
    ULONG  openAction = 0;
    ULONG  openMode = 0;

    if ((modeType == 1) || (modeType == 4) || (modeType == 7)
        || (modeType == 10))
    {
        openAction |= OPEN_ACTION_FAIL_IF_NEW;
        openAction |= OPEN_ACTION_OPEN_IF_EXISTS;
    }
    else if ((modeType == 2) || (modeType == 5) || (modeType == 8)
             || (modeType == 11))
    {
        openAction |= OPEN_ACTION_CREATE_IF_NEW;
        openAction |= OPEN_ACTION_REPLACE_IF_EXISTS;
    }
    else if ((modeType == 3) || (modeType == 6) || (modeType == 9)
             || (modeType == 12))
    {
        openAction |= OPEN_ACTION_CREATE_IF_NEW;
        openAction |= OPEN_ACTION_OPEN_IF_EXISTS;
    }
    openMode |= OPEN_SHARE_DENYWRITE;
    if ((modeType == 1) || (modeType == 4))
    {
        openMode |= OPEN_ACCESS_READONLY;
    }
    else if ((modeType == 2) || (modeType == 3) || (modeType == 5)
             || (modeType == 6))
    {
        openMode |= OPEN_ACCESS_WRITEONLY;
    }
    else
    {
        openMode |= OPEN_ACCESS_READWRITE;
    }
    if ((strlen(fnm) == 2)
        && (fnm[1] == ':')
        && (openMode == OPEN_ACCESS_READONLY))
    {
        openMode |= OPEN_FLAGS_DASD;
    }
    rc = DosOpen((PSZ)fnm,
                 &myfile->hfile,
                 &action,
                 newsize,
                 fileAttr,
                 openAction,
                 openMode,
                 NULL);
    if (rc != 0)
    {
        err = 1;
        errno = rc;
    }
#endif
#ifdef __MSDOS__
    int mode;
    int errind;

    if ((modeType == 1) || (modeType == 4))
    {
        mode = 0;
    }
    else if ((modeType == 2) || (modeType == 5))
    {
        mode = 1;
    }
    else
    {
        mode = 2;
    }
    myfile->hfile = __open(fnm, mode, &errind);
    if (errind)
    {
        err = 1;
        errno = myfile->hfile;
    }
#endif
#ifdef __MVS__
    int mode;
    char *p;
    int len;

    if ((modeType == 1) || (modeType == 4))
    {
        mode = 0;
    }
    else if ((modeType == 2) || (modeType == 5))
    {
        mode = 1;
    }
    else
    {
        mode = 2;
    }
    p = strchr(fnm, ':');
    if ((p != NULL) && (strncmp(fnm, "dd", 2) == 0))
    {
        p++;
    }
    else
    {
        p = (char *)fnm;
    }
    strcpy(myfile->ddname, "        ");
    len = strlen(p);
    if (len > 8)
    {
        len = 8;
    }
    memcpy(myfile->ddname, p, len);
    p = myfile->ddname;
    while (*p != '\0')
    {
        *p = toupper(*p);
        p++;
    }
    myfile->hfile = 
        __aopen(myfile->ddname, mode, &myfile->recfm, &myfile->lrecl);
    if ((modeType == 4) || (modeType == 5))
    {
        myfile->style = 0; /* binary */
    }
    else
    {
        myfile->style = 2; /* text */
    }
    myfile->style += myfile->recfm;
    if (myfile->style == VARIABLE_TEXT)
    {
        myfile->quickText = 1;
    }
    if (myfile->style == FIXED_BINARY)
    {
        myfile->quickBin = 1;
    }
    else
    {
        myfile->quickBin = 0;
    }
#endif
    return;
}
*/
