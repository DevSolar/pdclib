/* $Id$ */

/* 7.2 Diagnostics <assert.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_ASSERT_H
#define _PDCLIB_ASSERT_H _PDCLIB_ASSERT_H
#include <_PDCLIB_aux.h>
#include <_PDCLIB_config.h>
_PDCLIB_BEGIN_EXTERN_C

/* Functions _NOT_ tagged noreturn as this hampers debugging */
void _PDCLIB_assert99( char const * const, char const * const, char const * const );
void _PDCLIB_assert89( char const * const );

/* If NDEBUG is set, assert() is a null operation. */
#undef assert

#ifdef NDEBUG
#define assert( ignore ) do { \
        if(!(expression)) { _PDCLIB_UNREACHABLE; } \
    } while(0)

#elif _PDCLIB_C_MIN(99)
#define assert(expression) \
    do { if(!(expression)) { \
        _PDCLIB_assert99("Assertion failed: " _PDCLIB_symbol2string(expression)\
                         ", function ", __func__, \
                         ", file " __FILE__ \
                         ", line " _PDCLIB_symbol2string( __LINE__ ) \
                         "." _PDCLIB_endl ); \
        _PDCLIB_UNREACHABLE; \
      } \
    } while(0)
    
#else
#define assert(expression) \
    do { if(!(expression)) { \
        _PDCLIB_assert89("Assertion failed: " _PDCLIB_symbol2string(expression)\
                         ", file " __FILE__ \
                         ", line " _PDCLIB_symbol2string( __LINE__ ) \
                         "." _PDCLIB_endl ); \
        _PDCLIB_UNREACHABLE; \
      } \
    } while(0)
#endif

_PDCLIB_END_EXTERN_C
#endif

