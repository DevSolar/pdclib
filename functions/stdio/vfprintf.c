// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int vfprintf( FILE * restrict stream, const char * restrict format, va_list ap ) { /* TODO */ };

/* PDPC code - unreviewed
{
    int ret;

    ret = vvprintf(format, arg, stream, NULL);
    return (ret);
}

{
    int fin = 0;
    int vint;
    char *vcptr;
    int chcount = 0;
    size_t len;
    char numbuf[50];
    char *nptr;

    while (!fin)
    {
        if (*format == '\0')
        {
            fin = 1;
        }
        else if (*format == '%')
        {
            format++;
            if (*format == 'd')
            {
                int neg = 0;

                vint = va_arg(arg, int);
                if (vint < 0)
                {
                    neg = 1;
                    vint = -vint;
                }
                nptr = numbuf;
                do
                {
                    *nptr++ = (char)('0' + vint % 10);
                    vint /= 10;
                } while (vint > 0);
                if (neg)
                {
                    *nptr++ = '-';
                }
                do
                {
                    nptr--;
                    outch(*nptr);
                    chcount++;
                } while (nptr != numbuf);
            }
            else if (*format == 's')
            {
                vcptr = va_arg(arg, char *);
                if (fq == NULL)
                {
                    len = strlen(vcptr);
                    memcpy(s, vcptr, len);
                    s += len;
                    chcount += len;
                }
                else
                {
                    fputs(vcptr, fq);
                    chcount += strlen(vcptr);
                }
            }
            else if (*format == 'c')
            {
                vint = va_arg(arg, int);
                outch(vint);
                chcount++;
            }
            else if (*format == '%')
            {
                outch('%');
                chcount++;
            }
            else
            {
                int extraCh;

                extraCh = examine(&format, fq, s, &arg, chcount);
                chcount += extraCh;
                if (s != NULL)
                {
                    s += extraCh;
                }
            }
        }
        else
        {
            outch(*format);
            chcount++;
        }
        format++;
    }
    return (chcount);
}

static int examine(const char **formt, FILE *fq, char *s, va_list *arg,
                   int chcount)
{
    int extraCh = 0;
    int flagMinus = 0;
    int flagPlus = 0;
    int flagSpace = 0;
    int flagHash = 0;
    int flagZero = 0;
    int width = 0;
    int precision = -1;
    int half = 0;
    int lng = 0;
    int specifier = 0;
    int fin;
    long lvalue;
    unsigned long ulvalue;
    char *svalue;
    char work[50];
    int x;
    int y;
    int rem;
    const char *format;
    int base;
    int fillCh;
    int neg;
    int length;

    unused(chcount);
    format = *formt;
    /* processing flags */
    fin = 0;
    while (!fin)
    {
        switch (*format)
        {
            case '-': flagMinus = 1;
                      break;
            case '+': flagPlus = 1;
                      break;
            case ' ': flagSpace = 1;
                      break;
            case '#': flagHash = 1;
                      break;
            case '0': flagZero = 1;
                      break;
            default:  fin = 1;
                      break;
        }
        if (!fin)
        {
            format++;
        }
        else
        {
            if (flagSpace && flagPlus)
            {
                flagSpace = 0;
            }
            if (flagMinus)
            {
                flagZero = 0;
            }
        }
    }

    /* processing width */
    if (isdigit((unsigned char)*format))
    {
        while (isdigit((unsigned char)*format))
        {
            width = width * 10 + (*format - '0');
            format++;
        }
    }

    /* processing precision */
    if (*format == '.')
    {
        format++;
        precision = 0;
        while (isdigit((unsigned char)*format))
        {
            precision = precision * 10 + (*format - '0');
            format++;
        }
    }

    /* processing h/l/L */
    if (*format == 'h')
    {
        half = 1;
    }
    else if (*format == 'l')
    {
        lng = 1;
    }
    else if (*format == 'L')
    {
        lng = 1;
    }
    else
    {
        format--;
    }
    format++;

    if (precision < 0)
    {
        precision = 1;
    }
    /* processing specifier */
    specifier = *format;

    if (strchr("dxXuiop", specifier) != NULL)
    {
#if defined(__MSDOS__) && !defined(__PDOS__)
        if (specifier == 'p')
        {
            lng = 1;
        }
#endif
        if (lng)
        {
            lvalue = va_arg(*arg, long);
        }
        else if (half)
        {
            lvalue = va_arg(*arg, short);
        }
        else
        {
            lvalue = va_arg(*arg, int);
        }
        ulvalue = (unsigned long)lvalue;
        if ((lvalue < 0) && ((specifier == 'd') || (specifier == 'i')))
        {
            neg = 1;
            ulvalue = -lvalue;
        }
        else
        {
            neg = 0;
        }
        if ((specifier == 'X') || (specifier == 'x') || (specifier == 'p'))
        {
            base = 16;
        }
        else if (specifier == 'o')
        {
            base = 8;
        }
        else
        {
            base = 10;
        }
        if (specifier == 'p')
        {
#if defined(__OS2__) || defined(__PDOS__)
            precision = 8;
#endif
#if defined(__MSDOS__) && !defined(__PDOS__)
            precision = 9;
#endif
        }
        x = 0;
        while (ulvalue > 0)
        {
            rem = (int)(ulvalue % base);
            if (rem < 10)
            {
                work[x] = (char)('0' + rem);
            }
            else
            {
                if ((specifier == 'X') || (specifier == 'p'))
                {
                    work[x] = (char)('A' + (rem - 10));
                }
                else
                {
                    work[x] = (char)('a' + (rem - 10));
                }
            }
            x++;
#if defined(__MSDOS__) && !defined(__PDOS__)
            if ((x == 4) && (specifier == 'p'))
            {
                work[x] = ':';
                x++;
            }
#endif
            ulvalue = ulvalue / base;
        }
        while (x < precision)
        {
            work[x] = '0';
            x++;
        }
        if (neg)
        {
            work[x++] = '-';
        }
        if (flagZero)
        {
            fillCh = '0';
        }
        else
        {
            fillCh = ' ';
        }
        y = x;
        if (!flagMinus)
        {
            while (y < width)
            {
                outch(fillCh);
                extraCh++;
                y++;
            }
        }
        if (flagHash && (toupper(specifier) == 'X'))
        {
            outch('0');
            outch('x');
            extraCh += 2;
        }
        x--;
        while (x >= 0)
        {
            outch(work[x]);
            extraCh++;
            x--;
        }
        if (flagMinus)
        {
            while (y < width)
            {
                outch(fillCh);
                extraCh++;
                y++;
            }
        }
    }
    else if (specifier == 's')
    {
        svalue = va_arg(*arg, char *);
        fillCh = ' ';
        if (precision > 1)
        {
            char *p;

            p = memchr(svalue, '\0', precision);
            if (p != NULL)
            {
                length = (int)(p - svalue);
            }
            else
            {
                length = precision;
            }
        }
        else
        {
            length = strlen(svalue);
        }
        if (!flagMinus)
        {
            if (length < width)
            {
                extraCh += (width - length);
                for (x = 0; x < (width - length); x++)
                {
                    outch(fillCh);
                }
            }
        }
        for (x = 0; x < length; x++)
        {
            outch(svalue[x]);
        }
        extraCh += length;
        if (flagMinus)
        {
            if (length < width)
            {
                extraCh += (width - length);
                for (x = 0; x < (width - length); x++)
                {
                    outch(fillCh);
                }
            }
        }
    }
    *formt = format;
    return (extraCh);
}
*/
