// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int vsprintf( char * restrict s, const char * restrict format, va_list ap) { /* TODO */ };

/* PDPC code - unreviewed
{
    int ret;

    ret = vvprintf(format, arg, NULL, s);
    if (ret >= 0)
    {
        *(s + ret) = '\0';
    }
    return (ret);
}
*/
