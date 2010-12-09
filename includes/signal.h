/* $Id$ */

/* Signal handling <string.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_SIGNAL_H
#define _PDCLIB_SIGNAL_H _PDCLIB_SIGNAL_H

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H
#include <_PDCLIB_config.h>
#endif

typedef _PDCLIB_sig_atomic sig_atomic_t;

#define SIG_DFL _PDCLIB_SIG_DFL
#define SIG_ERR _PDCLIB_SIG_ERR
#define SIG_IGN _PDCLIB_SIG_IGN

#define SIGABRT _PDCLIB_SIGABRT
#define SIGFPE  _PDCLIB_SIGFPE
#define SIGILL  _PDCLIB_SIGILL
#define SIGINT  _PDCLIB_SIGINT
#define SIGSEGV _PDCLIB_SIGSEGV
#define SIGTERM _PDCLIB_SIGTERM

/* Returns the value of func for the most recent successful call to signal()
   for the signal sig. Returns SIG_ERR and sets errno to a positive value
   otherwise.
*/
void (*signal( int sig, void (*func)( int ) ) )( int );

/* Returns zero if successful, nonzero otherwise. */
int raise( int sig );

#endif
