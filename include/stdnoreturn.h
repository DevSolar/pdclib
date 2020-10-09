/* _Noreturn <stdnoreturn.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDNORETURN_H
#define _PDCLIB_STDNORETURN_H _PDCLIB_STDNORETURN_H

#include "pdclib/_PDCLIB_internal.h"

/* This basically breaks the letter of the standard (which states that
   noreturn be defined to _Noreturn). This defines noreturn -> _Noreturn
   on C11 compliant compilers only (as older compilers do not know about
   _Noreturn).
*/
#define noreturn _PDCLIB_Noreturn

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_STDNORETURN_H
#include _PDCLIB_EXTEND_STDNORETURN_H
#endif

#endif
