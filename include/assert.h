/* Diagnostics <assert.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_internal.h"

#ifndef _PDCLIB_ASSERT_H
#define _PDCLIB_ASSERT_H _PDCLIB_ASSERT_H
_PDCLIB_PUBLIC void _PDCLIB_assert99( const char * const, const char * const, const char * const );
_PDCLIB_PUBLIC void _PDCLIB_assert89( const char * const );
#endif

/* If NDEBUG is set, assert() is a null operation. */
#undef assert

#ifdef NDEBUG
#define assert( ignore ) ( (void) 0 )
#else
#if __STDC_VERSION__ >= 199901L
#define assert( expression ) ( ( expression ) ? (void) 0 \
        : _PDCLIB_assert99( "Assertion failed: " #expression \
                            ", function ", __func__, \
                            ", file " __FILE__ \
                            ", line " _PDCLIB_value2string( __LINE__ ) \
                            ".\n" ) )
#else
#define assert( expression ) ( ( expression ) ? (void) 0 \
        : _PDCLIB_assert89( "Assertion failed: " #expression \
                            ", file " __FILE__ \
                            ", line " _PDCLIB_value2string( __LINE__ ) \
                            ".\n" ) )
#endif
#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_ASSERT_H
#include _PDCLIB_EXTEND_ASSERT_H
#endif

#ifdef __cplusplus
}
#endif
