/* Alternative spellings <iso646.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_ISO646_H
#define _PDCLIB_ISO646_H _PDCLIB_ISO646_H

#ifndef __cplusplus
#define and &&
#define and_eq &=
#define bitand &
#define bitor |
#define compl ~
#define not !
#define not_eq !=
#define or ||
#define or_eq |=
#define xor ^
#define xor_eq ^=
#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_ISO646_H
#include _PDCLIB_EXTEND_ISO646_H
#endif

#endif
