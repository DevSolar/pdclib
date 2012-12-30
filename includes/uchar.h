/* 7.28 <uchar.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/


#ifndef _PDCLIB_UCHAR_H
#define _PDCLIB_UCHAR_H
#include <_PDCLIB_encoding.h>
_PDCLIB_BEGIN_EXTERN_C

/* This is mostly a placeholder. for now. This header will be completed by the
 * release of 0.6, but at present merely exposes types needed by the rest of the
 * library
 */

#ifndef _PDCLIB_SIZE_T_DEFINED
#define _PDCLIB_SIZE_T_DEFINED _PDCLIB_SIZE_T_DEFINED
typedef _PDCLIB_size_t size_t;
#endif

#ifndef _PDCLIB_MBSTATE_T_DEFINED
#define _PDCLIB_MBSTATE_T_DEFINED _PDCLIB_MBSTATE_T_DEFINED
typedef struct _PDCLIB_mbstate_t mbstate_t;
#endif

#ifndef __cplusplus
#ifndef _PDCLIB_CHAR16_T_DEFINED
#define _PDCLIB_CHAR16_T_DEFINED _PDCLIB_CHAR16_T_DEFINED
typedef _PDCLIB_char16_t char16_t;
#endif

#ifndef _PDCLIB_CHAR32_T_DEFINED
#define _PDCLIB_CHAR32_T_DEFINED _PDCLIB_CHAR32_T_DEFINED
typedef _PDCLIB_char32_t char32_t;
#endif

#endif