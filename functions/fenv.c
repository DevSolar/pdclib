// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int feclearexcept( int exceptions ) { /* TODO */ };
int fegetexceptflag( fexcept_t * flags, int exceptions ) { /* TODO */ };
int feraiseexcept( int exceptions ) { /* TODO */ };
int fesetexceptflag( const fexcept_t * flags, int exceptions ) { /* TODO */ };
int fetestexcept( int exceptions ) { /* TODO */ };

int fegetround( void ) { /* TODO */ };
int fesetround( int mode ) { /* TODO */ };

int fegetenv( fenv_t * environment ) { /* TODO */ };
int feholdexcept( fenv_t * environment ) { /* TODO */ };
int fesetenv( const fenv_t * environment ) { /* TODO */ };
int feupdateenv( const fenv_t * environment ) { /* TODO */ };
