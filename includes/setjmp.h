// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Nonlocal jumps
// ----------------------------------------------------------------------------

#ifndef __SETJMP_H
#define __SETJMP_H __SETJMP_H

// ----------------------------------------------------------------------------
// TYPEDEFS

struct jmp_buf[1];

// ----------------------------------------------------------------------------
// FUNCTIONS

// TODO
int setjmp(jmp_buf env);

// TODO
void longjmp(jmp_buf env, int val);

#endif // __SETJMP_H
