/* $Id$ */

/* _PDCLIB_errno

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>

#ifndef REGTEST

int _PDCLIB_errno = 0;

int * _PDCLIB_errno_func()
{
    return &_PDCLIB_errno;
}

/* TODO: Doing this via a static array is not the way to do it. */
char const * _PDCLIB_errno_texts[] = {
    "",
    "ERANGE (Range error)",
    "EDOM (Domain error)",
    "EIO (I/O error)",
    "EUNKNOWN (Unknown error)",
    "EINVAL (Invalid parameter value)",
    "ERETRY (I/O retries exceeded)"
};

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <errno.h>

int main()
{
    errno = 0;
    TESTCASE( errno == 0 );
    errno = EDOM;
    TESTCASE( errno == EDOM );
    errno = ERANGE;
    TESTCASE( errno == ERANGE );
    return TEST_RESULTS;
}

#endif

