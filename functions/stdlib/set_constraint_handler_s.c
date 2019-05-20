/* set_constraint_handler_s( constraint_handler_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>

#ifndef REGTEST

constraint_handler_t _PDCLIB_constraint_handler = abort_handler_s;

constraint_handler_t set_constraint_handler_s( constraint_handler_t handler )
{
    constraint_handler_t previous = _PDCLIB_constraint_handler;

    if ( handler == NULL )
    {
        _PDCLIB_constraint_handler = abort_handler_s;
    }
    else
    {
        _PDCLIB_constraint_handler = handler;
    }

    return previous;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    TESTCASE( _PDCLIB_constraint_handler == abort_handler_s );
    TESTCASE( set_constraint_handler_s( ignore_handler_s ) == abort_handler_s );
    TESTCASE( _PDCLIB_constraint_handler == ignore_handler_s );
    TESTCASE( set_constraint_handler_s( NULL ) == ignore_handler_s );
    TESTCASE( _PDCLIB_constraint_handler == abort_handler_s );
#endif
    return TEST_RESULTS;
}

#endif
