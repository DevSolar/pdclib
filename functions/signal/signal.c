/* $Id$ */

/* signal( int sig, void (*func)( int ) )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <signal.h>

#ifndef REGTEST

#include <stdlib.h>

static void default_handler( int sig )
{
    /* TODO: Implement error message */
    exit( EXIT_FAILURE );
}

void (*_PDCLIB_sigabrt)( int ) = default_handler;
void (*_PDCLIB_sigfpe)( int )  = default_handler;
void (*_PDCLIB_sigill)( int )  = default_handler;
void (*_PDCLIB_sigint)( int )  = default_handler;
void (*_PDCLIB_sigsegv)( int ) = default_handler;
void (*_PDCLIB_sigterm)( int ) = default_handler;

void (*signal( int sig, void (*func)( int ) ) )( int )
{
    void (*oldhandler)( int );
    switch ( sig )
    {
        case SIGABRT:
            oldhandler = _PDCLIB_sigabrt;
            _PDCLIB_sigabrt = func;
            break;
        case SIGFPE:
            oldhandler = _PDCLIB_sigfpe;
            _PDCLIB_sigfpe = func;
            break;
        case SIGILL:
            oldhandler = _PDCLIB_sigill;
            _PDCLIB_sigill = func;
            break;
        case SIGINT:
            oldhandler = _PDCLIB_sigint;
            _PDCLIB_sigint = func;
            break;
        case SIGSEGV:
            oldhandler = _PDCLIB_sigsegv;
            _PDCLIB_sigsegv = func;
            break;
        case SIGTERM:
            oldhandler = _PDCLIB_sigterm;
            _PDCLIB_sigterm = func;
            break;
        default:
            /* TODO: Implement. */
            break;
    }
    return oldhandler;
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
