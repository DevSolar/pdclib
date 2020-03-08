/* _PDCLIB_strtok( char *, rsize_t *, const char *, char ** )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

char * _PDCLIB_strtok( char * _PDCLIB_restrict s1, rsize_t * _PDCLIB_restrict s1max, const char * _PDCLIB_restrict s2, char ** _PDCLIB_restrict ptr )
{
    const char * p = s2;

    if ( s1max == NULL || s2 == NULL || ptr == NULL || ( s1 == NULL && *ptr == NULL ) || *s1max > RSIZE_MAX )
    {
        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return NULL;
    }

    if ( s1 != NULL )
    {
        /* new string */
        *ptr = s1;
    }
    else
    {
        /* old string continued */
        if ( *ptr == NULL )
        {
            /* No old string, no new string, nothing to do */
            return NULL;
        }

        s1 = *ptr;
    }

    /* skip leading s2 characters */
    while ( *p && *s1 )
    {
        if ( *s1 == *p )
        {
            /* found separator; skip and start over */
            if ( *s1max == 0 )
            {
                _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
                return NULL;
            }

            ++s1;
            --( *s1max );
            p = s2;
            continue;
        }

        ++p;
    }

    if ( ! *s1 )
    {
        /* no more to parse */
        *ptr = s1;
        return NULL;
    }

    /* skipping non-s2 characters */
    *ptr = s1;

    while ( **ptr )
    {
        p = s2;

        while ( *p )
        {
            if ( **ptr == *p++ )
            {
                /* found separator; overwrite with '\0', position *ptr, return */
                if ( *s1max == 0 )
                {
                    _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
                    return NULL;
                }

                --( *s1max );
                *( ( *ptr )++ ) = '\0';
                return s1;
            }
        }

        if ( *s1max == 0 )
        {
            _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
            return NULL;
        }

        --( *s1max );
        ++( *ptr );
    }

    /* parsed to end of string */
    return s1;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#ifndef REGTEST

static int HANDLER_CALLS = 0;

static void test_handler( const char * _PDCLIB_restrict msg, void * _PDCLIB_restrict ptr, errno_t error )
{
    ++HANDLER_CALLS;
}

#endif

int main( void )
{
#ifndef REGTEST
    /* The original PDCLib strtok() test */
    char s[] = "_a_bc__d_";
    rsize_t max = strlen( s );
    char * p;

    TESTCASE( _PDCLIB_strtok( s, &max, "_", &p ) == &s[1] );
    TESTCASE( max == 6 );
    TESTCASE( s[1] == 'a' );
    TESTCASE( s[2] == '\0' );
    TESTCASE( _PDCLIB_strtok( NULL, &max, "_", &p ) == &s[3] );
    TESTCASE( max == 3 );
    TESTCASE( s[3] == 'b' );
    TESTCASE( s[4] == 'c' );
    TESTCASE( s[5] == '\0' );
    TESTCASE( _PDCLIB_strtok( NULL, &max, "_", &p ) == &s[7] );
    TESTCASE( max == 0 );
    TESTCASE( s[6] == '_' );
    TESTCASE( s[7] == 'd' );
    TESTCASE( s[8] == '\0' );
    TESTCASE( _PDCLIB_strtok( NULL, &max, "_", &p ) == NULL );
    TESTCASE( max == 0 );
    strcpy( s, "ab_cd" );
    max = strlen( s );
    TESTCASE( _PDCLIB_strtok( s, &max, "_", &p ) == &s[0] );
    TESTCASE( s[0] == 'a' );
    TESTCASE( s[1] == 'b' );
    TESTCASE( s[2] == '\0' );
    TESTCASE( _PDCLIB_strtok( NULL, &max, "_", &p ) == &s[3] );
    TESTCASE( s[3] == 'c' );
    TESTCASE( s[4] == 'd' );
    TESTCASE( s[5] == '\0' );
    TESTCASE( _PDCLIB_strtok( NULL, &max, "_", &p ) == NULL );

    /* Testing the constraint handling */
    strcpy( s, "ab.cd" );
    max = 2;
    TESTCASE( set_constraint_handler_s( test_handler ) == abort_handler_s );
    TESTCASE( _PDCLIB_strtok( s, &max, ".", &p ) == NULL );
    TESTCASE( HANDLER_CALLS == 1 );

    {
        /* The strtok_s() example code from the standard */
        char str1[] = "?a???b,,,#c";
        char str2[] = "\t \t";
        rsize_t max1 = strlen( str1 );
        rsize_t max2 = strlen( str2 );
        char * ptr1;
        char * ptr2;

        TESTCASE( _PDCLIB_strtok( str1, &max1, "?", &ptr1 ) == &str1[1] );
        TESTCASE( _PDCLIB_strtok( NULL, &max1, ",", &ptr1 ) == &str1[3] );
        TESTCASE( _PDCLIB_strtok( str2, &max2, " \t", &ptr2 ) == NULL );
        TESTCASE( _PDCLIB_strtok( NULL, &max1, "#,", &ptr1 ) == &str1[10] );
        TESTCASE( _PDCLIB_strtok( NULL, &max1, "?", &ptr1 ) == NULL );
    }
#endif
    return TEST_RESULTS;
}

#endif
