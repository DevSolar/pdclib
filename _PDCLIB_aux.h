/* $Id$ */

/* Release $Name$ */

/* Auxiliary PDCLib code <_PDCLIB_aux.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Standard Version                                                           */
/* -------------------------------------------------------------------------- */

/* Many a compiler gets this wrong, so you might have to hardcode it instead. */

#if __STDC__ != 1
#error Compiler does not define _ _STDC_ _ to 1 (not standard-compliant)!
#endif

#ifndef __STDC_VERSION__
#define _PDCLIB_C_VERSION 90
#elif __STDC_VERSION__ == 199409L
#define _PDCLIB_C_VERSION 95
#elif __STDC_VERSION__ == 199901L
#define _PDCLIB_C_VERSION 99
#else
#error Unsupported _ _STDC_VERSION_ _ (__STDC_VERSION__) (supported: ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999).
#endif

#ifndef __STDC_HOSTED__
#error Compiler does not define _ _STDC_HOSTED_ _ (not standard-compliant)!
#elif __STDC_HOSTED__ == 0
#define _PDCLIB_HOSTED 0
#elif __STDC_HOSTED__ == 1
#define _PDCLIB_HOSTED 1
#else
#error Compiler does not define _ _STDC_HOSTED_ _ to 0 or 1 (not standard-compliant)!
#endif

#if _PDCLIB_C_VERSION != 99
#warning Up to and including v1.x, PDCLib is only aiming at ISO/IEC 9899:1999 (C99).
#warning PDCLib might not be fully conforming to either C89 or C95 prior to v2.x.
#endif

#if _PDCLIB_HOSTED != 0
#warning Up to the 1.x release, PDCLib is only complete as a freestanding environment.
#warning PDCLib might not be fully conforming as a hosted environment.
#endif

/* -------------------------------------------------------------------------- */
/* Helper macros:                                                             */
/* _PDCLIB_cc( x, y ) concatenates two preprocessor tokens without extending  */
/* _PDCLIB_concat( x, y ) concatenates two preprocessor tokens with extending */
/* -------------------------------------------------------------------------- */

#define _PDCLIB_cc( x, y )     x ## y
#define _PDCLIB_concat( x, y ) _PDCLIB_cc( x, y )

#define _PDCLIB_symbol2value( x ) #x
#define _PDCLIB_symbol2string( x ) _PDCLIB_symbol2value( x )
#define _PDCLIB_symbol2identity( x ) x

