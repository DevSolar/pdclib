// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Common definitions
// ----------------------------------------------------------------------------

#ifndef __STDDEF_H
#define __STDDEF_H __STDDEF_H

// ----------------------------------------------------------------------------
// MACROS

#define NULL  0
#define offsetof( s-type, mbr ) // TODO

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef ptrdiff_t; // TODO
typedef size_t;    // TODO

#ifndef __cplusplus
typedef wchar_t;
#endif // __cplusplus

#endif // __STDDEF_H
