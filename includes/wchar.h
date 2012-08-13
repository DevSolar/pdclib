/* 7. <wchar.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/


#ifndef _PDCLIB_WCHAR_H
#define _PDCLIB_WCHAR_H
#include <_PDCLIB_int.h>
_PDCLIB_BEGIN_EXTERN_C
/* This is VASTLY incomplete. Functions being implemented as required by other
   portions of the library
 */

#ifndef _PDCLIB_SIZE_T_DEFINED
#define _PDCLIB_SIZE_T_DEFINED _PDCLIB_SIZE_T_DEFINED
typedef _PDCLIB_size_t size_t;
#endif

#ifndef __cplusplus
#ifndef _PDCLIB_WCHAR_T_DEFINED
#define _PDCLIB_WCHAR_T_DEFINED _PDCLIB_WCHAR_T_DEFINED
typedef _PDCLIB_wchar_t   wchar_t;
#endif
#endif

wchar_t *wcschr( const wchar_t * haystack, wchar_t needle );
wchar_t *wcsrchr( const wchar_t * haystack, wchar_t needle );
size_t   wcslen( const wchar_t * string);
wchar_t *wcscpy( wchar_t * _PDCLIB_restrict dest, 
                 const wchar_t * _PDCLIB_restrict src);

_PDCLIB_END_EXTERN_C
#endif
