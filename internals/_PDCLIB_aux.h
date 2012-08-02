#ifndef _PDCLIB_AUX_H
#define _PDCLIB_AUX_H

/* Auxiliary PDCLib code <_PDCLIB_aux.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* You should not have to edit anything in this file; if you DO have to, it   */
/* would be considered a bug / missing feature: notify the author(s).         */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Version                                                           */
/* -------------------------------------------------------------------------- */

/* Many a compiler gets this wrong, so you might have to hardcode it instead. */

#if __STDC__ != 1
#error Compiler does not define _ _STDC_ _ to 1 (not standard-compliant)!
#endif

#if defined(_PDCLIB_C_VERSION)
	/* Pass - conditional simplification case */
#elif !defined(__STDC_VERSION__)
	#define _PDCLIB_C_VERSION 1990
#elif __STDC_VERSION__ == 199409L
	#define _PDCLIB_C_VERSION 1995
#elif __STDC_VERSION__ == 199901L
	#define _PDCLIB_C_VERSION 1999
#elif __STDC_VERSION__ == 201112L
	#define _PDCLIB_C_VERSION 2011
#else
	#error Unsupported _ _STDC_VERSION_ _ (__STDC_VERSION__) (supported: ISO/IEC 9899:1990, 9899/AMD1:1995, 9899:1999, 9899:2011).
#endif

#if !defined(__cplusplus) || defined(_PDCLIB_CXX_VERSION)
	/* Pass - conditional simplification case */
#elif __cplusplus == 201103L
	#define _PDCLIB_CXX_VERSION 2011
	#if _PDCLIB_C_VERSION < 2011
		#undef _PDCLIB_C_VERSION
   		#define _PDCLIB_C_VERSION 2011
	#endif
#elif __cplusplus == 199711L
   #define _PDCLIB_CXX_VERSION 1997
#else
   #error Unsupported _ _cplusplus (__cplusplus) (supported: ISO/IEC 14882:1997, ISO/IEC 14882:2011).
#endif

#if _PDCLIB_C_VERSION >= 1999 || defined(__cplusplus)
	#ifndef __cplusplus
		#define _PDCLIB_restrict restrict
  	#endif
	#define _PDCLIB_inline   inline
#endif

#if _PDCLIB_CXX_VERSION >= 2011
   	#define _PDCLIB_noreturn [[noreturn]]
#elif _PDCLIB_C_VERSION >= 2011
	#define _PDCLIB_noreturn _Noreturn
#endif

#ifdef __GNUC__
	#ifndef _PDCLIB_restrict
		#define _PDCLIB_restrict __restrict
	#endif

	#ifndef _PDCLIB_inline
		#define _PDCLIB_inline __inline
	#endif

	#ifndef _PDCLIB_noreturn
		#define _PDCLIB_noreturn __attribute__((noreturn))
	#endif
#endif

#ifndef _PDCLIB_restrict
	#define _PDCLIB_restrict
#endif

#ifndef _PDCLIB_inline
	#define _PDCLIB_inline
#endif

#ifndef _PDCLIB_noreturn
	#define _PDCLIB_noreturn
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

#ifdef __cplusplus
	#define _PDCLIB_BEGIN_EXTERN_C extern "C" {
	#define _PDCLIB_END_EXTERN_C }
#else
   #define _PDCLIB_BEGIN_EXTERN_C
   #define _PDCLIB_END_EXTERN_C
#endif

/*#if _PDCLIB_C_VERSION != 1999
#error PDCLib might not be fully conforming to either C89 or C95 prior to v2.x.
#endif*/

/* -------------------------------------------------------------------------- */
/* Helper macros:                                                             */
/* _PDCLIB_cc( x, y ) concatenates two preprocessor tokens without extending  */
/* _PDCLIB_concat( x, y ) concatenates two preprocessor tokens with extending */
/* -------------------------------------------------------------------------- */

#define _PDCLIB_cc( x, y )     x ## y
#define _PDCLIB_concat( x, y ) _PDCLIB_cc( x, y )

#define _PDCLIB_symbol2value( x ) #x
#define _PDCLIB_symbol2string( x ) _PDCLIB_symbol2value( x )

#ifndef __PDCLIB_PURE
    #define __PDCLIB_PURE 0
#endif

#ifndef _PDCLIB_POSIX_EX
    #define _PDCLIB_POSIX_EX (!__PDCLIB_PURE)
#endif
#endif