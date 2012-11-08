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
   #define _PDCLIB_CXX_VERSION 0
#elif __cplusplus == 201103L
	#define _PDCLIB_CXX_VERSION 2011
    /* TODO: Do we want this? */
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
  #define _PDCLIB_nothrow     noexcept
  #define _PDCLIB_noexcept(x) noexcept(x)
#elif _PDCLIB_CXX_VERSION
  #define _PDCLIB_nothrow     throw()
  #define _PDCLIB_noexcept
#endif

#if _PDCLIB_CXX_VERSION >= 2011
  // Hold off on C++ attribute syntax for now
  // #define _PDCLIB_noreturn [[noreturn]]
#elif _PDCLIB_C_VERSION >= 2011
	#define _PDCLIB_noreturn _Noreturn
#endif

#ifdef _WIN32
   #define _PDCLIB_EXPORT __declspec(dllexport)
   #define _PDCLIB_IMPORT __declspec(dllimport)
#endif

#ifdef __GNUC__
	  #ifndef _PDCLIB_EXPORT
  	    #define _PDCLIB_EXPORT __attribute__((__visibility__("protected")))
    #endif

   	#ifndef _PDCLIB_IMPORT
		#define _PDCLIB_IMPORT
   	#endif

   	#ifndef _PDCLIB_HIDDEN
   		#define _PDCLIB_HIDDEN __attribute__((__visibility__("hidden")))
   	#endif

    #ifndef _PDCLIB_nothrow
      #define _PDCLIB_nothrow __attribute__((__nothrow__))
      #define _PDCLIB_noexcept
    #endif

	#ifndef _PDCLIB_restrict
		#define _PDCLIB_restrict __restrict
	#endif

	#ifndef _PDCLIB_inline
		#define _PDCLIB_inline __inline
	#endif

	#ifndef _PDCLIB_noreturn
    /* If you don't use __noreturn__, then stdnoreturn.h will break things! */
		#define _PDCLIB_noreturn __attribute__((__noreturn__))
	#endif
#endif

#ifndef _PDCLIB_nothrow
  #define _PDCLIB_nothrow
  #define _PDCLIB_noexcept
#endif

#ifndef _PDCLIB_EXPORT
   	#define _PDCLIB_EXPORT
#endif
#ifndef _PDCLIB_IMPORT
   	#define _PDCLIB_IMPORT
#endif
#ifndef _PDCLIB_HIDDEN
   	#define _PDCLIB_HIDDEN
#endif

#if defined(_PDCLIB_SHARED) 
   	#if defined(_PDCLIB_BUILD)
   		#define _PDCLIB_API _PDCLIB_EXPORT
   	#else
   		#define _PDCLIB_API _PDCLIB_IMPORT
   	#endif
#else
   	#define _PDCLIB_API
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
#define _PDCLIB_concat3( x, y, z ) _PDCLIB_concat( _PDCLIB_concat( x, y ), z )

#define _PDCLIB_symbol2value( x ) #x
#define _PDCLIB_symbol2string( x ) _PDCLIB_symbol2value( x )

/* Feature test macros
 *
 * All of the feature test macros come in the following forms
 *   _PDCLIB_*_MIN(min):            Available in versions > min
 *   _PDCLIB_*_MINMAX(min, max):    Available in versions > min < max
 *   _PDCLIB_*_MAX(max):            Availabel in versions < max
 *
 * The defined tests are:
 *   C:     C standard versions 
 *              1990, 1995, 1999, 2011
 *   CXX:   C++ standard versions 
 *              1997, 2011
 *   POSIX: POSIX extension versions.
 *              1 (POSIX.2), 2 (POSIX.2), 199309L (POSIX.1b), 
 *              199506L (POSIX.1c), 200112L (2001), 200809L (2008)
 *   XOPEN: X/Open System Interface (XSI)/Single Unix Specification
 *              0 (XPG4), 500 (SUSv2/UNIX98), 600 (SUSv3/UNIX03), 700 (SUSv4)
 *
 *   Additionally, the macros
 *     _BSD_SOURCE, _SVID_SOURCE and _GNU_SOURCE
 *   are adhered to. If _GNU_SOURCE is defined, _XOPEN_SOURCE and 
 *   _POSIX_C_SOURCE are defined to their most recent values to match glibc 
 *   behaviour
 *
 *   The intention of supporting these feature test macros is to ease 
 *   application portability from these systems to PDCLib systems; in addition,
 *   it eases support for these standards by systems supporting them which are 
 *   using PDCLib as their default C library.
 *
 *   Applications targetting purely PDClib/PDCLib based platforms may define 
 *   just _PDCLIB_EXTENSIONS, which will enable all supported extensions, plus
 *   all features from all supported versions of C and C++.
 *
 */
#define _PDCLIB_C_MIN(min)         _PDCLIB_C_MINMAX(min, 3000)
#define _PDCLIB_CXX_MIN(min)     _PDCLIB_CXX_MINMAX(min, 3000)
#define _PDCLIB_XOPEN_MIN(min) _PDCLIB_XOPEN_MINMAX(min, 30000000)
#define _PDCLIB_POSIX_MIN(min) _PDCLIB_POSIX_MINMAX(min, 30000000)
#define _PDCLIB_C_MAX(max)         _PDCLIB_C_MINMAX(0, max)
#define _PDCLIB_CXX_MAX(max)     _PDCLIB_CXX_MINMAX(0, max)
#define _PDCLIB_XOPEN_MAX(max) _PDCLIB_XOPEN_MINMAX(0, max)
#define _PDCLIB_POSIX_MAX(max) _PDCLIB_POSIX_MINMAX(0, max)
#if defined(_PDCLIB_EXTENSIONS) || defined(_PDCLIB_BUILD)
    #define _PDCLIB_C_MINMAX(min, max) 1
    #define _PDCLIB_CXX_MINMAX(min, max) 1
    #define _PDCLIB_POSIX_MINMAX(min, max) 1
    #define _PDCLIB_XOPEN_MINMAX(min, max) 1

    #undef _PDCLIB_EXTENSIONS
    #undef _PDCLIB_BSD_SOURCE 
    #undef _PDCLIB_SVID_SOURCE
    #undef _PDCLIB_GNU_SOURCE

    #define _PDCLIB_EXTENSIONS 1
    #define _PDCLIB_BSD_SOURCE 1
    #define _PDCLIB_SVID_SOURCE 1
    #define _PDCLIB_GNU_SOURCE 1
#else
    #define _PDCLIB_C_MINMAX(min, max) \
        (_PDCLIB_C_VERSION >= (min) && _PDCLIB_C_VERSION <= (max))
    #define _PDCLIB_CXX_MINMAX(min, max) \
        (_PDCLIB_CXX_VERSION >= (min) && _PDCLIB_CXX_VERSION <= (max))
    #define _PDCLIB_XOPEN_MINMAX(min, max) \
        (defined(_XOPEN_SOURCE) \
            && _XOPEN_SOURCE >= (min) && _XOPEN_SOURCE <= (max))
    #define _PDCLIB_POSIX_MINMAX(min, max) \
        (defined(_POSIX_C_SOURCE) \
            && _POSIX_C_SOURCE >= (min) && _POSIX_C_SOURCE <= (max))

    #if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE-1 == -1)
        /* If _XOPEN_SOURCE is defined as empty, redefine here as zero */
        #undef _XOPEN_SOURCE
        #define _XOPEN_SOURCE 0
    #endif

    #if defined(_GNU_SOURCE)
        #define _PDCLIB_GNU_SOURCE 1
        #define _PDCLIB_SVID_SOURCE 1
        #define _PDCLIB_BSD_SOURCE 1
        #undef _XOPEN_SOURCE
        #define _XOPEN_SOURCE 700
    #else
        #define _PDCLIB_GNU_SOURCE 0
    #endif

    #if defined(_PDCLIB_BSD_SOURCE)
        // pass
    #elif defined(_BSD_SOURCE)
        #define _PDCLIB_BSD_SOURCE 1
    #else
        #define _PDCLIB_BSD_SOURCE 0
    #endif

    #if defined(_PDCLIB_SVID_SOURCE)
        // pass
    #elif defined(_SVID_SOURCE)
        #define _PDCLIB_SVID_SOURCE 1
    #else
        #define _PDCLIB_SVID_SOURCE 0
    #endif

    #if _PDCLIB_XOPEN_MIN(700) && !_PDCLIB_POSIX_MIN(200809L)
        #undef _POSIX_C_SOURCE
        #define _POSIX_C_SOURCE 2008098L    
    #elif _PDCLIB_XOPEN_MIN(600) && !_PDCLIB_POSIX_MIN(200112L)
        #undef _POSIX_C_SOURCE
        #define _POSIX_C_SOURCE 200112L
    #elif _PDCLIB_XOPEN_MIN(0) && !_PDCLIB_POSIX_MIN(2)
        #undef _POSIX_C_SOURCE
        #define _POSIX_C_SOURCE 2
    #endif

    #if defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
        #define _POSIX_C_SOURCE 1
    #endif
#endif

#endif
