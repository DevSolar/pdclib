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

// TODO: Documentation

// ----------------------------------------------------------------------------
// MACROS

#include "__NULL.h"

#define offsetof( s-type, mbr ) // TODO - personality?

// ----------------------------------------------------------------------------
// TYPEDEFS

#include "__size_t.h"
#include "__wchar_t.h"

typedef ptrdiff_t; // TODO - personality?

#endif // __STDDEF_H
