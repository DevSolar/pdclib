/* Floating-point environment <fenv.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_FENV_H
#define _PDCLIB_FENV_H _PDCLIB_FENV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_lib_ext1.h"
#include "pdclib/_PDCLIB_internal.h"

/*
   IMPORTANT REMINDER

   If you intend to test floating-point exception flags, or set non-default
   rounding modes, remember to invoke
       #pragma STDC FENV_ACCESS ON
   prior to doing so. Otherwise the implementation may assume default
   settings and exception flags not being tested.
*/

/* A type holding the entire floating-point environment (exception status
   flags, rounding mode, plus implementation-defined additional data).
*/
typedef int fenv_t;

/* A type holding the floating-point status flags, plus implementation-
   defined additional data.
*/
typedef int fexcept_t;

/* Floating-point exception macros */

/*
   These are only defined if supported by the platform.
*/

#ifdef _PDCLIB_FE_DIVBYZERO
#define FE_DIVBYZERO _PDCLIB_FE_DIVBYZERO
#endif

#ifdef _PDCLIB_FE_INEXACT
#define FE_INEXACT _PDCLIB_FE_INEXACT
#endif

#ifdef _PDCLIB_FE_INVALID
#define FE_INVALID _PDCLIB_FE_INVALID
#endif

#ifdef _PDCLIB_FE_OVERFLOW
#define FE_OVERFLOW _PDCLIB_FE_OVERFLOW
#endif

#ifdef _PDCLIB_FE_UNDERFLOW
#define FE_UNDERFLOW _PDCLIB_FE_UNDERFLOW
#endif

/*
   All supported exception macros, OR-ed together.
*/

#define FE_ALL_EXCEPT _PDCLIB_FE_ALL_EXCEPT

/* Floating-point rounding macros */

/*
   These are only defined if supported by the platform.
*/

#ifdef _PDCLIB_FE_DOWNWARD
#define FE_DOWNWARD _PDCLIB_FE_DOWNWARD
#endif

#ifdef _PDCLIB_FE_TONEAREST
#define FE_TONEAREST _PDCLIB_FE_TONEAREST
#endif

#ifdef _PDCLIB_FE_TOWARDZERO
#define FE_TOWARDZERO _PDCLIB_FE_TOWARDZERO
#endif

#ifdef _PDCLIB_FE_UPWARD
#define FE_UPWARD _PDCLIB_FE_UPWARD
#endif

/* The default / startup environment. Can be used as argument to the
   fegetenv() / feupdateenv() functions. */
#define FE_DFL_ENV ((fenv_t const *)-1)

/* Floating-point exceptions */

/* Clear the floating-point exceptions passed as argument. Only supported
   exceptions (or zero) may be passed.
   Returns zero if successful, nonzero otherwise.
*/
_PDCLIB_PUBLIC int feclearexcept( int excepts );

/* Save the states of the floating-point exceptions passed as except in
   the object pointed to by flagp. Only supported exceptions (or zero) may
   be passed.
   Returns zero if successful, nonzero otherwise.
*/
_PDCLIB_PUBLIC int fegetexceptflag( fexcept_t * flagp, int excepts );

/* Raise the floating-point exceptions passed as argument.
   the object pointed to by flagp. Only supported exceptions (or zero) may
   be passed.
   The implementation may additionally raise FE_INEXACT after raising
   FE_OVERFLOW or FE_UNDERFLOW.
   Returns zero if successful, nonzero otherwise.
*/
_PDCLIB_PUBLIC int feraiseexcept( int excepts );

/* Set the states of the floating-point exceptions passed as except as
   stored in the object pointed to by flagp.  (by an earlier call to
   fegetexceptflag()). Only supported exceptions (or zero) may be passed.
   Returns zero if successful, nonzero otherwise.
*/
_PDCLIB_PUBLIC int fesetexceptflag( const fexcept_t * flagp, int excepts );

/* Query the states of the floating-point exceptions passed as argument.
   Returns the bitwise OR of the exceptions currently set.
*/
_PDCLIB_PUBLIC int fetestexcept( int excepts );

/* Rounding */

/* Return the current rounding direction macro (see above).
   Returns a negative value if the rounding direction cannot be determined.
*/
_PDCLIB_PUBLIC int fegetround( void );

/* Set the rounding direction to the given argument.
   If the argument is not equal to any of the rounding direction macros
   given above, the rounding direction is not changed.
   Returns zero if successful, non-zero otherwise.
*/
_PDCLIB_PUBLIC int fesetround( int round );

/* Environment */

/* Store the current floating-point environment in the object pointed to
   by envp.
   Returns zero if successful, non-zero otherwise.
*/
_PDCLIB_PUBLIC int fegetenv( fenv_t * envp );

/* Store the current floating-point environment in the object pointed to
   by envp, clear the exception flags, and then install a "continue on
   exception" mode, if available, for all floating-point exceptions.
   Returns zero if successful, non-zero otherwise.
*/
_PDCLIB_PUBLIC int feholdexcept( fenv_t * envp );

/* Load the floating-point environment stored in the object pointed to by
   envp by an earlier call to fegetenv() or feholdexcept().
   Exception flags of the environment are set, but the exceptions are not
   raised.
   Returns zero if successful, non-zero otherwise.
*/
_PDCLIB_PUBLIC int fesetenv( const fenv_t * envp );

/* Temporarily store the currently raised floating-point exception flags,
   load the floating-point environment stored in the object pointed to by
   envp by an earlier call to fegetenv() or feholdexcept(), then raise the
   temporarily stored floating-point exceptions.
   Returns zero if successful, non-zero otherwise.
*/
_PDCLIB_PUBLIC int feupdateenv( const fenv_t * envp );

#ifdef __cplusplus
}
#endif

#endif
