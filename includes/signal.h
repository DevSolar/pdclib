// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Signal handling
// ----------------------------------------------------------------------------

#ifndef __SIGNAL_H
#define __SIGNAL_H __SIGNAL_H

// TODO: Documentation

// ----------------------------------------------------------------------------
// MACROS

#define SIGABRT // TODO - personality?
#define SIGFPE  // TODO - personality?
#define SIGILL  // TODO - personality?
#define SIGINT  // TODO - personality?
#define SIGSEGV // TODO - personality?
#define SIGTERM // TODO - personality?
#define SIG_DFL // TODO - personality?
#define SIG_ERR // TODO - personality?
#define SIG_IGN // TODO - personality?

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef sig_atomic_t; // TODO - personality?

// ----------------------------------------------------------------------------
// FUNCTIONS

int raise( int sig );                                        // TODO
void ( * signal( int sig, void ( *func )( int ) ) ) ( int ); // TODO

#endif // __SIGNAL_H
