// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// TODO
// ----------------------------------------------------------------------------

#ifndef __SIGNAL_H
#define __SIGNAL_H __SIGNAL_H

// ----------------------------------------------------------------------------
// MACROS

#define SIGABRT // TODO
#define SIGFPE  // TODO
#define SIGILL  // TODO
#define SIGINT  // TODO
#define SIGSEGV // TODO
#define SIGTERM // TODO
#define SIG_DFL // TODO
#define SIG_ERR // TODO
#define SIG_IGN // TODO

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef sig_atomic_t; // TODO

// ----------------------------------------------------------------------------
// FUNCTIONS

int raise( int sig );                                        // TODO
void ( * signal( int sig, void ( *func )( int ) ) ) ( int ); // TODO

#endif // __SIGNAL_H
