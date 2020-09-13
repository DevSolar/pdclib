/* stdarg

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdarg.h>
#include <limits.h>
#include <float.h>

#ifdef TEST

#include "_PDCLIB_test.h"

typedef int ( *intfunc_t )( void );

#define TAG_END     0
#define TAG_INT     1
#define TAG_LONG    2
#define TAG_LLONG   3
#define TAG_DBL     4
#define TAG_LDBL    5
#define TAG_INTPTR  6
#define TAG_LDBLPTR 7
#define TAG_FUNCPTR 8

static int dummy( void )
{
    return INT_MAX;
}

static int test( int s, ... )
{
    va_list ap;
    va_start( ap, s );

    for ( ;; )
    {
        switch ( s )
        {
            case TAG_INT:
            {
                TESTCASE( va_arg( ap, int ) == INT_MAX );
                s = va_arg( ap, int );
                break;
            }

            case TAG_LONG:
            {
                TESTCASE( va_arg( ap, long ) == LONG_MAX );
                s = va_arg( ap, int );
                break;
            }

            case TAG_LLONG:
            {
                TESTCASE( va_arg( ap, long long ) == LLONG_MAX );
                s = va_arg( ap, int );
                break;
            }

            case TAG_DBL:
            {
                TESTCASE( va_arg( ap, double ) == DBL_MAX );
                s = va_arg( ap, int );
                break;
            }

            case TAG_LDBL:
            {
                TESTCASE( va_arg( ap, long double ) == LDBL_MAX );
                s = va_arg( ap, int );
                break;
            }

            case TAG_INTPTR:
            {
                TESTCASE( *( va_arg( ap, int * ) ) == INT_MAX );
                s = va_arg( ap, int );
                break;
            }

            case TAG_LDBLPTR:
            {
                TESTCASE( *( va_arg( ap, long double * ) ) == LDBL_MAX );
                s = va_arg( ap, int );
                break;
            }

            case TAG_FUNCPTR:
            {
                intfunc_t function;
                TESTCASE( ( function = va_arg( ap, intfunc_t ) ) == dummy );
                TESTCASE( function() == INT_MAX );
                s = va_arg( ap, int );
                break;
            }

            case TAG_END:
            {
                va_end( ap );
                return 0;
            }
        }
    }
}

int main( void )
{
    int x = INT_MAX;
    long double d = LDBL_MAX;
    test( TAG_END );
    test( TAG_INT, INT_MAX, TAG_END );
    test( TAG_LONG, LONG_MAX, TAG_LLONG, LLONG_MAX, TAG_END );
    test( TAG_DBL, DBL_MAX, TAG_LDBL, LDBL_MAX, TAG_END );
    test( TAG_INTPTR, &x, TAG_LDBLPTR, &d, TAG_FUNCPTR, dummy, TAG_END );
    return TEST_RESULTS;
}

#endif
