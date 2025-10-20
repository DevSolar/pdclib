/* Boolean type and values <stdbool.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDBOOL_H
#define _PDCLIB_STDBOOL_H _PDCLIB_STDBOOL_H

#ifndef __cplusplus
#define bool                          _Bool
#define true                          1
#define false                         0
#endif
#define __bool_true_false_are_defined 1

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_STDBOOL_H
#include _PDCLIB_EXTEND_STDBOOL_H
#endif

#endif
