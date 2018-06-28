/* unicode data

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_utilities.h"

#include "unicode_data.h"

#define LINE_BUFFER_SIZE 500

struct unicode_data_t * read_unicode_data( const char * filename )
{
    FILE * fh;
    char buffer[ LINE_BUFFER_SIZE ];
    struct unicode_data_t * ud = NULL;
    int_least32_t lines;

    if ( ( fh = fopen( filename, "r" ) ) == NULL )
    {
        fprintf( stderr, "Could not open '%s' for reading.\n", filename );
        return NULL;
    }

    if ( ( lines = check_file( fh, LINE_BUFFER_SIZE, ';', sizeof( unicode_record_fields ) / sizeof( int ), unicode_record_fields ) ) > 0 )
    {
        if ( ( ud = malloc( sizeof( struct unicode_data_t ) ) ) )
        {
            ud->size = lines;

            if ( ( ud->records = malloc( lines * sizeof( struct unicode_record_t ) ) ) )
            {
                int_least32_t i;

                for ( i = 0; i < lines; ++i )
                {
                    char *  p;

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
                free( ud );
                ud = NULL;
            }
        }
    }

    fclose( fh );
    return ud;
}

#ifdef TEST

#include "test.h"

#include <inttypes.h>

int main( void )
{
    struct unicode_data_t * ud = read_unicode_data( "UnicodeData.txt" );
    TESTCASE( ud != NULL );
    TESTCASE( ud->size > 32000 );

    return TEST_RESULTS;
}

#endif
