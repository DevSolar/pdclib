// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Provides the debug macro assert().
// ----------------------------------------------------------------------------

#ifndef __ASSERT_H
#define __ASSERT_H __ASSERT_H

// ----------------------------------------------------------------------------
// AUXILIARY

// Helper function doing the print to stderr and call to abort().
void __assert( char const * const expression, // the tested expression
               char const * const file,       // name of source file
               char const * const function,   // name of function
               int const line );              // number of source file line

// ----------------------------------------------------------------------------
// DEFINES

// TODO: <void expression> is given as (void) 0, which might give a "C style
// cast" warning under C++. Find a void expression that does not give warnings.

// TODO: Check the macro for if-compatibility.

#undef assert
#if defined NDEBUG
#define assert( x ) <void expression>
#else
#define assert( x ) ( x ) ? <void expression> \
                          :  __assert( #x, __FILE__, __func__, __LINE__ )
#endif

#endif // __ASSERT_H
