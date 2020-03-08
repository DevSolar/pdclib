/* unicode data

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_utilities.h"

#include "unicode_data.h"

#define LINE_BUFFER_SIZE 500u

struct unicode_data_t * read_unicode_data( const char * filename )
{
    FILE * fh;
    char buffer[ LINE_BUFFER_SIZE ];
    struct unicode_data_t * ud = NULL;
    size_t lines;

    if ( ( fh = fopen( filename, "r" ) ) == NULL )
    {
        fprintf( stderr, "Could not open '%s' for reading.\n", filename );
        return NULL;
    }

    if ( ( lines = check_file( fh, LINE_BUFFER_SIZE, ';', sizeof( unicode_record_fields ) / sizeof( int ), unicode_record_fields ) ) != ( size_t )-1 )
    {
        if ( ( ud = malloc( sizeof( struct unicode_data_t ) ) ) )
        {
            ud->size = lines;

            if ( ( ud->records = calloc( lines, sizeof( struct unicode_record_t ) ) ) )
            {
                size_t i;

                for ( i = 0; i < lines; ++i )
                {
                    char * p;

                    fgets( buffer, LINE_BUFFER_SIZE, fh );
                    ud->records[ i ].code_point = strtoul( next_token( buffer, ';' ), NULL, 16 );
                    p = next_token( NULL, ';' );

                    if ( *p )
                    {
                        ud->records[ i ].name = malloc( strlen( p ) + 1 );
                        strcpy( ud->records[ i ].name, p );
                    }

                    strcpy( ud->records[ i ].general_category, next_token( NULL, ';' ) );

                    p = next_token( NULL, ';' );
                    ud->records[ i ].canonical_combining_class = ( *p ) ? strtol( p, NULL, 10 ) : -1l;

                    strcpy( ud->records[ i ].bidi_class, next_token( NULL, ';' ) );

                    p = next_token( NULL, ';' );

                    if ( *p )
                    {
                        ud->records[ i ].decomposition = malloc( strlen( p ) + 1 );
                        strcpy( ud->records[ i ].decomposition, p );
                    }

                    p = next_token( NULL, ';' );
                    ud->records[ i ].numeric_type = ( *p ) ? strtol( p, NULL, 10 ) : -1l;

                    p = next_token( NULL, ';' );
                    ud->records[ i ].numeric_digit = ( *p ) ? strtol( p, NULL, 10 ) : -1l;

                    p = next_token( NULL, ';' );

                    if ( *p )
                    {
                        ud->records[ i ].numeric_value = malloc( strlen( p ) + 1 );
                        strcpy( ud->records[ i ].numeric_value, p );
                    }

                    p = next_token( NULL, ';' );
                    ud->records[ i ].bidi_mirrored = ( *p ) ? *p : '\0';

                    next_token( NULL, ';' ); /* Unicode_1_Name */
                    next_token( NULL, ';' ); /* ISO_Comment */

                    ud->records[ i ].simple_uppercase_mapping = strtoul( next_token( NULL, ';' ), NULL, 16 );
                    ud->records[ i ].simple_lowercase_mapping = strtoul( next_token( NULL, ';' ), NULL, 16 );
                    ud->records[ i ].simple_titlecase_mapping = strtoul( next_token( NULL, ';' ), NULL, 16 );
                }
            }
            else
            {
                fprintf( stderr, "Memory allocation failure.\n" );
                free( ud );
                ud = NULL;
            }
        }
        else
        {
            fprintf( stderr, "Memory allocation failure.\n" );
        }
    }

    fclose( fh );
    return ud;
}

int has_name( struct unicode_record_t * ur, const char * name )
{
    return strcmp( ur->name, name ) == 0;
}

int name_ends_with( struct unicode_record_t * ur, const char * name )
{
    return strstr( ur->name, name ) == ( ur->name + ( strlen( ur->name ) - strlen( name ) ) );
}

int is_general_category( struct unicode_record_t * ur, const char * category )
{
    return strcmp( ur->general_category, category ) == 0;
}

int decomposition_contains( struct unicode_record_t * ur, const char * substring )
{
    return ur->decomposition && strstr( ur->decomposition, substring ) != NULL;
}

int towupper_differs( struct unicode_record_t * ur, size_t codepoint )
{
    return ur->simple_uppercase_mapping && ( ur->simple_uppercase_mapping != codepoint );
}

int towlower_differs( struct unicode_record_t * ur, size_t codepoint )
{
    return ur->simple_lowercase_mapping && ( ur->simple_lowercase_mapping != codepoint );
}

void release_unicode_data( struct unicode_data_t * ud )
{
    size_t i;

    for ( i = 0; i < ud->size; ++i )
    {
        free( ud->records[i].name );
        free( ud->records[i].decomposition );
        free( ud->records[i].numeric_value );
    }

    free( ud->records );
    free( ud );
}

#ifdef TEST

#include "test.h"

#include <inttypes.h>

int main( void )
{
    FILE * fh = fopen( "test.txt", "w" );
    struct unicode_data_t * ud;
    int rc;

    TESTCASE( fh != NULL );
    TESTCASE( fprintf( fh, "%04x;%s;%s;%d;%s;;;;;%c;%s;;;;\n", 0, "<control>", "Cc", 0, "BN", 'N', "NULL" ) == 38 );
    TESTCASE( ( rc = fprintf( fh, "%04x;%s;%s;%d;%s;%s;;;%s;%c;;;%04x;;%04x\n", 0x2170, "SMALL ROMAN NUMERAL ONE", "Nl", 0, "L", "<compat> 0069", "1", 'N', 0x2160, 0x2160 ) ) == 69 );

    fclose( fh );
    ud = read_unicode_data( "test.txt" );
    remove( "test.txt" );

    TESTCASE( ud != NULL );
    TESTCASE( ud->size == 2 );

    TESTCASE( ud->records[0].code_point == 0 );
    TESTCASE( strcmp( ud->records[0].name, "<control>" ) == 0 );
    TESTCASE( strcmp( ud->records[0].general_category, "Cc" ) == 0 );
    TESTCASE( ud->records[0].canonical_combining_class == 0 );
    TESTCASE( strcmp( ud->records[0].bidi_class, "BN" ) == 0 );
    TESTCASE( ud->records[0].decomposition == NULL );
    TESTCASE( ud->records[0].numeric_type == -1 );
    TESTCASE( ud->records[0].numeric_digit == -1 );
    TESTCASE( ud->records[0].numeric_value == NULL );
    TESTCASE( ud->records[0].bidi_mirrored == 'N' );
    TESTCASE( ud->records[0].simple_uppercase_mapping == 0 );
    TESTCASE( ud->records[0].simple_lowercase_mapping == 0 );
    TESTCASE( ud->records[0].simple_titlecase_mapping == 0 );

    TESTCASE( ud->records[1].code_point == 0x2170 );
    TESTCASE( strcmp( ud->records[1].name, "SMALL ROMAN NUMERAL ONE" ) == 0 );
    TESTCASE( strcmp( ud->records[1].general_category, "Nl" ) == 0 );
    TESTCASE( ud->records[1].canonical_combining_class == 0 );
    TESTCASE( strcmp( ud->records[1].bidi_class, "L" ) == 0 );
    TESTCASE( strcmp( ud->records[1].decomposition, "<compat> 0069" ) == 0 );
    TESTCASE( ud->records[1].numeric_type == -1 );
    TESTCASE( ud->records[1].numeric_digit == -1 );
    TESTCASE( strcmp( ud->records[1].numeric_value, "1" ) == 0 );
    TESTCASE( ud->records[1].bidi_mirrored == 'N' );
    TESTCASE( ud->records[1].simple_uppercase_mapping == 0x2160 );
    TESTCASE( ud->records[1].simple_lowercase_mapping == 0 );
    TESTCASE( ud->records[1].simple_titlecase_mapping == 0x2160 );

    TESTCASE( is_general_category( &( ud->records[0] ), "Cc" ) );
    TESTCASE( ! is_general_category( &( ud->records[0] ), "" ) );
    TESTCASE( is_general_category( &( ud->records[1] ), "Nl" ) );
    TESTCASE( ! is_general_category( &( ud->records[1] ), "Foo" ) );

    TESTCASE( decomposition_contains( &( ud->records[1] ), "<compat>" ) );
    TESTCASE( ! decomposition_contains( &( ud->records[1] ), "Foo" ) );

    TESTCASE( ! towupper_differs( &( ud->records[0] ), 0 ) );
    TESTCASE( ! towlower_differs( &( ud->records[0] ), 0 ) );
    TESTCASE( towupper_differs( &( ud->records[1] ), 0x2170 ) );
    TESTCASE( ! towlower_differs( &( ud->records[1] ), 0x2170 ) );

    release_unicode_data( ud );

    return TEST_RESULTS;
}

#endif
