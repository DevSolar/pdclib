/* $Id$ */

/* Errors <errno.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_ERRNO_H
#define _PDCLIB_ERRNO_H _PDCLIB_ERRNO_H

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>
#endif

#define errno (*_PDCLIB_errno_func())

#define ERANGE _PDCLIB_ERANGE
#define EDOM _PDCLIB_EDOM

#endif

