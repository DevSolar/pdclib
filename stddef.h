#ifndef _PDCLIB_STDDEF_H
#define _PDCLIB_STDDEF_H _PDCLIB_STDDEF_H

/* $Id$ */

/* 7.17 Common definitions <stddef.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_DEFS_H
#define _PDCLIB_DEFS_H _PDCLIB_DEFS_H
#include <_PDCLIB_defs.h>
#endif

typedef _PDCLIB_ptrdiff_t ptrdiff_t;
typedef _PDCLIB_size_t    size_t;
typedef _PDCLIB_wchar_t   wchar_t;

#define NULL _PDCLIB_NULL

#define offsetof( type, member ) _PDCLIB_offsetof( type, member )

#endif
