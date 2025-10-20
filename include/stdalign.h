/* Alignment <stdalign.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDALIGN_H
#define _PDCLIB_STDALIGN_H _PDCLIB_STDALIGN_H

#define __alignas_is_defined 1
#define __alignof_is_defined 1

#ifndef __cplusplus
#if ! defined( __STDC_VERSION__ ) || ( __STDC_VERSION__ < 202311L )
#define alignas _Alignas
#define alignof _Alignof
#elif __STDC_VERSION__ >= 202311L
#warning C23 added alignas and alignof as keywords, using <stdalign.h> is deprecated.
#endif
#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_STDALIGN_H
#include _PDCLIB_EXTEND_STDALIGN_H
#endif

#endif

