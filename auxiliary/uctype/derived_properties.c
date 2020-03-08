/* derived properties

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_utilities.h"

#include "derived_properties.h"

#define LINE_BUFFER_SIZE 500u

struct derived_properties_t * read_derived_properties( const char * filename )
{
    FILE * fh;
    char buffer[ LINE_BUFFER_SIZE ];
    struct derived_properties_t * dp = NULL;
    size_t code_points = 0;
    size_t properties = 0;
    const char * code_point_count = "# Total code points: ";

    if ( ( fh = fopen( filename, "r" ) ) == NULL )
    {
        fprintf( stderr, "Could not open '%s' for reading.\n", filename );
        return NULL;
    }

    if ( ( check_file( fh, LINE_BUFFER_SIZE, ';', sizeof( derived_properties_fields ) / sizeof( int ), derived_properties_fields ) ) != ( size_t )-1 )
    {
        while ( fgets( buffer, LINE_BUFFER_SIZE, fh ) )
        {
            if ( strstr( buffer, code_point_count ) != NULL )
            {
                size_t count = strtoul( buffer + strlen( code_point_count ), NULL, 10 );

                if ( ( SIZE_MAX - count ) < code_points )
                {
                    fprintf( stderr, "Summing up total code points in '%s' would overflow.\n", filename );
                    fclose( fh );
                    return NULL;
                }

                code_points += count;
                ++properties;
            }
        }

        rewind( fh );

        if ( ( dp = malloc( sizeof( struct derived_properties_t ) ) ) )
        {
            dp->count = properties;

            if ( ( dp->name = calloc( properties, sizeof( char * ) ) ) )
            {
                if ( ( dp->begin = calloc( properties, sizeof( size_t ) ) ) )
                {
                    if ( ( dp->end = calloc( properties, sizeof( size_t ) ) ) )
                    {
                        if ( ( dp->code_points = malloc( code_points * sizeof( size_t ) ) ) )
                        {
                            char * p;
                            char * range;

                            properties = 0; /* Re-using the variable */
                            code_points = 0; /* Re-using the variable */

                            while ( fgets( buffer, LINE_BUFFER_SIZE, fh ) )
                            {
                                /* Remove comments */
                                if ( ( p = strchr( buffer, '#' ) ) != NULL )
                                {
                                    *p = '\0';
                                }

                                /* > 0 because of newline */
                                if ( strlen( buffer ) > 1 )
                                {
                                    size_t first;
                                    size_t last;

                                    range = next_token( buffer, ';' );
                                    p = next_token( NULL, ';' );

                                    if ( ! range || ! p )
                                    {
                                        size_t i;

                                        fprintf( stderr, "Parse error, malformed input.\n" );

                                        for ( i = 0; i < properties; ++i )
                                        {
                                            free( dp->name[ i ] );
                                        }

                                        free( dp->name );
                                        free( dp->begin );
                                        free( dp->end );
                                        free( dp->code_points );
                                        free( dp );
                                        return NULL;
                                    }

                                    /* If we got to a new property (except the first) */
                                    if ( dp->name[ properties ] && strcmp( p, dp->name[ properties ] ) )
                                    {
                                        /* Index into ->code_points where the previous property ends */
                                        dp->end[ properties ] = code_points;
                                        ++properties;
                                    }

                                    /* If we got to a new property, even the first */
                                    if ( dp->name[ properties ] == NULL )
                                    {
                                        dp->name[ properties ] = malloc( strlen( p ) + 1 );
                                        strcpy( dp->name[ properties ], p );

                                        /* Index into ->code_points where this property begins */
                                        dp->begin[ properties ] = code_points;
                                    }

                                    /* Re-using p, as we have done everything related to the property
                                       name at this point.
                                    */
                                    first = strtoul( range, &p, 16 );

                                    if ( *p == '\0' )
                                    {
                                        last = first;
                                    }
                                    else
                                    {
                                        while ( *p && ! isxdigit( *p ) )
                                        {
                                            ++p;
                                        }

                                        last = strtoul( p, NULL, 16 );

                                        if ( last <= first )
                                        {
                                            size_t i;

                                            fprintf( stderr, "Parse error, malformed input.\n" );

                                            for ( i = 0; i < properties; ++i )
                                            {
                                                free( dp->name[ i ] );
                                            }

                                            free( dp->name );
                                            free( dp->begin );
                                            free( dp->end );
                                            free( dp->code_points );
                                            free( dp );
                                            return NULL;
                                        }
                                    }

                                    for ( ; first <= last; ++first )
                                    {
                                        dp->code_points[ code_points++ ] = first;
                                    }
                                }
                            }

                            /* Have to end the last property as well */
                            dp->end[ properties ] = code_points;
                        }
                        else
                        {
                            fprintf( stderr, "Memory allocation failure.\n" );
                            free( dp->name );
                            free( dp->begin );
                            free( dp->end );
                            free( dp );
                            dp = NULL;
                        }
                    }
                    else
                    {
                        fprintf( stderr, "Memory allocation failure.\n" );
                        free( dp->name );
                        free( dp->begin );
                        free( dp );
                        dp = NULL;
                    }
                }
                else
                {
                    fprintf( stderr, "Memory allocation failure.\n" );
                    free( dp->name );
                    free( dp );
                    dp = NULL;
                }
            }
            else
            {
                fprintf( stderr, "Memory allocation failure.\n" );
                free( dp );
                dp = NULL;
            }
        }
        else
        {
            fprintf( stderr, "Memory allocation failure.\n" );
        }
    }

    fclose( fh );
    return dp;
}

static int comp( const void * l, const void * r )
{
    const size_t * lhs = l;
    const size_t * rhs = r;

    return ( *lhs < *rhs ) ? -1 : ( *lhs > *rhs ) ? 1 : 0;
}

int lookup_property( struct derived_properties_t * dp, const char * property, size_t codepoint )
{
    size_t i;

    for ( i = 0; i < dp->count; ++i )
    {
        /* Look for the requested property */
        if ( strcmp( dp->name[ i ], property ) == 0 )
        {
            size_t cp = dp->begin[ i ];

            return bsearch( &codepoint, dp->code_points + cp, dp->end[ i ] - cp, sizeof( size_t ), comp ) != NULL;
        }
    }

    return 0;
}

void release_derived_properties( struct derived_properties_t * dp )
{
    size_t i;

    for ( i = 0; i < dp->count; ++i )
    {
        free( dp->name[ i ] );
    }

    free( dp->name );
    free( dp->begin );
    free( dp->end );
    free( dp->code_points );
    free( dp );
}

#ifdef TEST

#include "test.h"

int main( void )
{
    FILE * fh = fopen( "test.txt", "wb+" );
    struct derived_properties_t * dp;

    TESTCASE( fh != NULL );
    TESTCASE( fprintf( fh, "0000..0006 ; Test1 \n" ) == 20 );
    TESTCASE( fprintf( fh, "# Total code points: 7\n" ) == 23 );
    TESTCASE( fprintf( fh, "0001;Test2\n" ) == 11 );
    TESTCASE( fprintf( fh, "# Total code points: 1\n" ) == 23 );

    fclose( fh );
    dp = read_derived_properties( "test.txt" );

    TESTCASE( dp != NULL );
    TESTCASE( dp->count == 2 );
    TESTCASE( ! strcmp( dp->name[0], "Test1" ) );
    TESTCASE( ! strcmp( dp->name[1], "Test2" ) );

    TESTCASE( lookup_property( dp, "Test1", 0 ) );
    TESTCASE( lookup_property( dp, "Test1", 6 ) );
    TESTCASE( ! lookup_property( dp, "Test1", 7 ) );

    TESTCASE( ! lookup_property( dp, "Test2", 0 ) );
    TESTCASE( lookup_property( dp, "Test2", 1 ) );
    TESTCASE( ! lookup_property( dp, "Test2", 2 ) );

    TESTCASE( ! lookup_property( dp, "Test", 0 ) );
    TESTCASE( ! lookup_property( dp, "Test3", 0 ) );

    release_derived_properties( dp );
    remove( "test.txt" );

    return TEST_RESULTS;
}

#endif
