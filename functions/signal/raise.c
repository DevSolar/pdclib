/* $Id$ */

/* raise( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <signal.h>

#ifndef REGTEST

extern void (*_PDCLIB_sigabrt)( int );
extern void (*_PDCLIB_sigfpe)( int );
extern void (*_PDCLIB_sigill)( int );
extern void (*_PDCLIB_sigint)( int );
extern void (*_PDCLIB_sigsegv)( int );
extern void (*_PDCLIB_sigterm)( int );

int raise( int sig )
{
    switch ( sig )
    {
        case SIGABRT:
            _PDCLIB_sigabrt( sig );
            break;
        case SIGFPE:
            _PDCLIB_sigfpe( sig );
            break;
        case SIGILL:
            _PDCLIB_sigill( sig );
            break;
        case SIGINT:
            _PDCLIB_sigint( sig );
            break;
        case SIGSEGV:
            _PDCLIB_sigsegv( sig );
            break;
        case SIGTERM:
            _PDCLIB_sigterm( sig );
            break;
        default:
            /* TODO: Implement. */
            break;
    }
    /* TODO: Implement. */
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
