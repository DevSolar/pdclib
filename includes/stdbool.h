// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Boolean type and values
// ----------------------------------------------------------------------------

#ifndef __STDBOOL_H
#define __STDBOOL_H __STDBOOL_H

// ----------------------------------------------------------------------------
// MACROS

#define __bool_true_false_are_defined 1

#ifndef __cplusplus

#define bool  _Bool
#define false 0
#define true  1

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef int bool;

#endif // __cplusplus

#endif // __STDBOOL_H
