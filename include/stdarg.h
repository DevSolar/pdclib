/* Variable arguments <stdarg.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDARG_H
#define _PDCLIB_STDARG_H _PDCLIB_STDARG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_config.h"

typedef _PDCLIB_va_list va_list;

#define va_arg( ap, type )    _PDCLIB_va_arg( ap, type )
#define va_copy( dest, src )  _PDCLIB_va_copy( dest, src )
#define va_end( ap )          _PDCLIB_va_end( ap )
#define va_start( ap, parmN ) _PDCLIB_va_start( ap, parmN )

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_STDARG_H
#include _PDCLIB_EXTEND_STDARG_H
#endif

#ifdef __cplusplus
}
#endif

#endif
