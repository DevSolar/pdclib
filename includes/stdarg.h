// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Variable arguments
// ----------------------------------------------------------------------------

#ifndef __STDARG_H
#define __STDARG_H __STDARG_H

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef do-type va_list;

// ----------------------------------------------------------------------------
// MACROS

#define va_arg( va_list ap, Ty )             // TODO
#define va_copy( va_list dest, va_list src ) // TODO
#define va_end( va_list ap )                 // TODO
#define va_start( va_list ap, last-par )     // TODO

/* PDPC code - unreviewed
#define va_start(ap, parmN) ap = (char *)&parmN + 4
#define va_arg(ap, type) *(type *)(ap += sizeof(type), ap - sizeof(type))
#define va_end(ap) ap = 0
*/

#endif // __STDARG_H
