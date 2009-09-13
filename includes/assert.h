/* $Id$ */

/* 7.2 Diagnostics <assert.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_AUX_H
#define _PDCLIB_AUX_H _PDCLIB_AUX_H
#include <_PDCLIB_aux.h>
#endif

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H
#include <_PDCLIB_config.h>
#endif

#ifndef _PDCLIB_ASSERT_H
#define _PDCLIB_ASSERT_H _PDCLIB_ASSERT_H
#if _PDCLIB_C_VERSION == 99
void _PDCLIB_assert( char const * const, char const * const, char const * const );
#else
void _PDCLIB_assert( char const * const );
#endif
#endif

/* If NDEBUG is set, assert() is a null operation. */
#undef assert

#ifdef NDEBUG
#define assert( ignore ) ( (void) 0 )
#else
#if _PDCLIB_C_VERSION == 99
#define assert( expression ) ( ( expression ) ? (void) 0 \
        : _PDCLIB_assert( "Assertion failed: " #expression \
                          ", function ", __func__, \
                          ", file " __FILE__ \
                          ", line " _PDCLIB_symbol2string( __LINE__ ) \
                          "." _PDCLIB_endl ) )
#else
#define assert( expression ) ( ( expression ) ? (void) 0 \
        : _PDCLIB_assert( "Assertion failed: " #expression \
                          ", file " __FILE__ \
                          ", line " _PDCLIB_symbol2string( __LINE__ ) \
                          "." _PDCLIB_endl ) )
#endif
#endif

