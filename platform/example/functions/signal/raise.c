/* $Id$ */

/* raise( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <signal.h>

#ifndef REGTEST

#include <stdlib.h>

extern void (*_PDCLIB_sigabrt)( int );
extern void (*_PDCLIB_sigfpe)( int );
extern void (*_PDCLIB_sigill)( int );
extern void (*_PDCLIB_sigint)( int );
extern void (*_PDCLIB_sigsegv)( int );
extern void (*_PDCLIB_sigterm)( int );

int raise( int sig )
{
    void (*sighandler)( int );
    switch ( sig )
    {
        case SIGABRT:
            sighandler = _PDCLIB_sigabrt;
            break;
        case SIGFPE:
            sighandler = _PDCLIB_sigfpe;
            break;
        case SIGILL:
            sighandler = _PDCLIB_sigill;
            break;
        case SIGINT:
            sighandler = _PDCLIB_sigint;
            break;
        case SIGSEGV:
            sighandler = _PDCLIB_sigsegv;
            break;
        case SIGTERM:
            sighandler = _PDCLIB_sigterm;
            break;
        default:
            /* TODO: Implement. */
            break;
    }
    if ( sighandler == SIG_DFL )
    {
        _Exit( EXIT_FAILURE );
    }
    else if ( sighandler != SIG_IGN )
    {
        sighandler = signal( sig, SIG_DFL );
        sighandler( sig );
    }
    return 0;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}
#endif
