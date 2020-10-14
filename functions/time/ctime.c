/* ctime( const time_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

char * ctime( const time_t * timer )
{
    /* Section 4.12.3.2 of X3.159-1989 requires that
        The ctime function converts the calendar time pointed to by timer
        to local time in the form of a string. It is equivalent to
            asctime(localtime(timer))
    */
    struct tm * tmp = localtime( timer );
    return tmp ? asctime( tmp ) : NULL;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdio.h>

int main( void )
{
    /* TODO: System Clock DST */
    time_t t;

    t = -2147483648l;
    TESTCASE( strcmp( ctime( &t ), "Fri Dec 13 21:45:52 1901\n" ) == 0 );
    puts( ctime( &t ) );

    t = 2147483647l;
    TESTCASE( strcmp( ctime( &t ), "Tue Jan 19 04:14:07 2038\n" ) == 0 );

    return TEST_RESULTS;
}

#endif
