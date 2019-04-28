/* Auxiliary PDCLib code <_PDCLIB_aux.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_AUX_H
#define _PDCLIB_AUX_H _PDCLIB_AUX_H

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

#if __STDC_VERSION__ < 199901L
#define _PDCLIB_restrict
#define _PDCLIB_inline
#else
#define _PDCLIB_restrict restrict
#define _PDCLIB_inline inline
#endif

#if __STDC_VERSION__ < 201112L
#define _PDCLIB_Noreturn
#else
#define _PDCLIB_Noreturn _Noreturn
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

/* -------------------------------------------------------------------------- */
/* Helper macros:                                                             */
/* _PDCLIB_cc( x, y ) concatenates two preprocessor tokens without extending  */
/* _PDCLIB_concat( x, y ) concatenates two preprocessor tokens with extending */
/* _PDCLIB_static_assert( e, m ) does a compile-time assertion of expression  */
/*                               e, with m as the failure message.            */
/* _PDCLIB_TYPE_SIGNED( type ) resolves to true if type is signed.            */
/* _PDCLIB_TWOS_COMPLEMENT( type ) resolves to true if two's complement is    */
/*                                 used for type.                             */
/* _PDCLIB_LOCK( mtx ) lock a mutex if library has threads support.           */
/* _PDCLIB_UNLOCK( mtx ) unlock a mutex if library has threads support.       */
/* -------------------------------------------------------------------------- */

#define _PDCLIB_cc( x, y )     x ## y
#define _PDCLIB_concat( x, y ) _PDCLIB_cc( x, y )

#define _PDCLIB_static_assert( e, m ) enum { _PDCLIB_concat( _PDCLIB_assert_, __LINE__ ) = 1 / ( !!(e) ) }

#define _PDCLIB_TYPE_SIGNED( type ) (((type) -1) < 0)
#define _PDCLIB_TWOS_COMPLEMENT( type ) ((type) ~ (type) 0 < 0 )

#define _PDCLIB_symbol2value( x ) #x
#define _PDCLIB_symbol2string( x ) _PDCLIB_symbol2value( x )

#ifndef __STDC_NO_THREADS__
#define _PDCLIB_LOCK( mtx ) mtx_lock( &mtx )
#define _PDCLIB_UNLOCK( mtx ) mtx_unlock( &mtx )
#else
#define _PDCLIB_LOCK( mtx )
#define _PDCLIB_UNLOCK( mtx )
#endif

#endif
