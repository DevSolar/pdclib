// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Floating-point environment
// ----------------------------------------------------------------------------

#ifndef __FENV_H
#define __FENV_H __FENV_H

// TODO: Documentation, checking for personality

// ----------------------------------------------------------------------------
// MACROS

// Used
#define FE_DIVBYZERO  // TODO
#define FE_INEXACT    // TODO
#define FE_INVALID    // TODO
#define FE_OVERFLOW   // TODO
#define FE_UNDERFLOW  // TODO
#define FE_ALL_EXCEPT // TODO

#define FE_DOWNWARD   // TODO
#define FE_TONEAREST  // TODO
#define FE_TOWARDZERO // TODO
#define FE_UPWARD     // TODO

#define FE_DFL_ENV    // TODO

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef fenv_t;    // TODO
typedef fexcept_t; // TODO

// ----------------------------------------------------------------------------
// FUNCTIONS

int feclearexcept( int exceptions );
int fegetexceptflag( fexcept_t * flags, int exceptions );
int feraiseexcept( int exceptions );
int fesetexceptflag( const fexcept_t * flags, int exceptions );
int fetestexcept( int exceptions );

int fegetround( void );
int fesetround( int mode );

int fegetenv( fenv_t * environment );
int feholdexcept( fenv_t * environment );
int fesetenv( const fenv_t * environment );
int feupdateenv( const fenv_t * environment );

#endif // __FENV_H
