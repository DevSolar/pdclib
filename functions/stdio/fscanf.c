// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int fscanf( FILE * restrict stream, const char * restrict format, ... ) { /* TODO */ };

/* PDPC code - unreviewed
{
    va_list arg;
    int ret;

    va_start(arg, format);
    ret = vvscanf(format, arg, stream, NULL);
    va_end(arg);
    return (ret);
}

static int vvscanf(const char *format, va_list arg, FILE *fp, const char *s)
{
    int ch;
    int fin = 0;
    int cnt = 0;
    char *cptr;
    int *iptr;

    inch();
    while (!fin)
    {
        if (*format == '\0')
        {
            fin = 1;
        }
        else if (*format == '%')
        {
            format++;
            if (*format == '%')
            {
                if (ch != '%') return (cnt);
                inch();
            }
            else if (*format == 's')
            {
                cptr = va_arg(arg, char *);
                *cptr++ = (char)ch;
                inch();
                while ((ch >= 0) && (!isspace(ch)))
                {
                    *cptr++ = (char)ch;
                    inch();
                }
                *cptr = '\0';
                if (ch < 0)
                {
                    fin = 1;
                }
            }
            else if (*format == 'd')
            {
                iptr = va_arg(arg, int *);
                if (!isdigit(ch)) return (cnt);
                *iptr = ch - '0';
                inch();
                while ((ch >= 0) && (isdigit(ch)))
                {
                    *iptr = *iptr * 10 + (ch - '0');
                    inch();
                }
                if (ch < 0)
                {
                    fin = 1;
                }
            }
        }
        else
        {
            if (ch != *format) return (cnt);
            inch();
        }
    }
    return (cnt);
}
*/
