// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int sprintf( char * restrict s, const char * restrict format, ... ) { /* TODO */ };

/* PDPC code - unreviewed
{
    va_list arg;
    int ret;

    va_start(arg, format);
    ret = vsprintf(s, format, arg);
    va_end(arg);
    return (ret);
}
*/
