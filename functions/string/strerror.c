// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <errno.h>

char * strerror( int errcode )
{
    switch ( errcode )
    {
        case 0:
            return "no error";
            break;
        case EDOM:
            return "domain error";
            break;
        case EILSEQ:
            return "illegal sequence";
            break;
        case ERANGE:
            return "range error";
            break;
        default:
            return "unknown error";
            break;
    }
}
