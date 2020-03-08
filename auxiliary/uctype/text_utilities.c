/* text utilities

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include "text_utilities.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char * trim( char * s )
{
    char * p;

    /* Skip over leading whitespace */
    while ( *s && isspace( *s ) )
    {
        ++s;
    }

    /* Trim trailing whitespace */
    p = s;

    while ( *p )
    {
        ++p;
    }

    while ( isspace( *( --p ) ) )
    {
        *p = '\0';
    }

    return s;
}

char * next_token( char * s, char delim )
{
    static char * p = NULL;
    char * rc;

    if ( s != NULL )
    {
        /* Re-init the to-be-tokenized string */
        p = s;
    }

    /* Remembering the start of the next token */
    rc = p;

    /* In case the function has not been initialized, or the previous
       string been exhaused, do nothing.
    */
    if ( p )
    {
        /* Re-using s here */
        if ( ( s = strchr( p, delim ) ) )
        {
            /* Null the delimiter */
            *s = '\0';
            /* Make the internal, static pointer point to the next token */
            p = s + 1;
        }
        else
        {
            /* Delimiter not found, end-of-string reached. */
            p = NULL;
        }

        /* Trim the result */
        rc = trim( rc );
    }

    return rc;
}

size_t check_file( FILE * fh, size_t buffer_size, char delim, size_t fields, int const * widths )
{
    /* Dynamically allocated buffer */
    char * buffer = malloc( buffer_size );
    size_t lines = 0;

    rewind( fh );

    while ( fgets( buffer, buffer_size, fh ) )
    {
        size_t i;
        char * p;

        ++lines;

        /* Check line for complete read */
        if ( buffer[ strlen( buffer ) - 1 ] != '\n' )
        {
            fprintf( stderr, "Line %zu will not fit into a %zu-character buffer.\n", lines, buffer_size );
            rewind( fh );
            free( buffer );
            return -1;
        }

        /* Remove comments */
        if ( ( p = strchr( buffer, '#' ) ) != NULL )
        {
            *p = '\0';
        }

        /* > 1 because of newline */
        if ( strlen( buffer ) > 1 )
        {
            /* Check field count and field widths */
            p = next_token( buffer, delim );

            for ( i = 0; i < fields; ++i )
            {
                if ( ! p )
                {
                    fprintf( stderr, "Line %zu contains less than %zu fields.\n", lines, fields );
                    rewind( fh );
                    free( buffer );
                    return -1;
                }

                if ( widths[ i ] >= 0 && strlen( p ) >= ( unsigned )widths[ i ] )
                {
                    fprintf( stderr, "Line %zu: Field %zu '%s' will not fit in a %d character string.\n", lines, i + 1, p, widths[ i ] );
                    rewind( fh );
                    free( buffer );
                    return -1;
                }

                p = next_token( NULL, delim );
            }

            if ( p )
            {
                fprintf( stderr, "Line %zu contains more than %zu fields.\n", lines, fields );
                rewind( fh );
                free( buffer );
                return -1;
            }
        }
    }

    /* Rewind, free the buffer, and report the number of lines */
    rewind( fh );
    free( buffer );
    return lines;
}

#ifdef TEST

#include "test.h"

int main( void )
{
    FILE * fh = fopen( "test.txt", "wb+" );
    int widths[] = { 4, 4, 4 };
    char buffer[ 500 ];

    /* check_file() (and as dependency, next_token() */

    /* All ok */
    TESTCASE( fprintf( fh, "%s;%s;%s\n", "1", "123", "12" ) == 9 );
    TESTCASE( fprintf( fh, ";;\n" ) == 3 );
    TESTCASE( check_file( fh, 10, ';', 3, widths ) == 2 );
    /* Field 1 too long */
    TESTCASE( fprintf( fh, "%s;%s;%s\n", "", "1234", "1" ) == 8 );
    TESTCASE( check_file( fh, 10, ';', 3, widths ) == ( size_t )-1 );
    /* Too few fields */
    TESTCASE( fprintf( fh, "%s;%s\n", "123", "123" ) == 8 );
    TESTCASE( check_file( fh, 10, ';', 3, widths ) == ( size_t )-1 );
    /* Too many fields */
    TESTCASE( fprintf( fh, "%s;%s;%s;%s\n", "1", "1", "1", "1" ) == 8 );
    TESTCASE( check_file( fh, 10, ';', 3, widths ) == ( size_t )-1 );
    /* Line too long */
    TESTCASE( fprintf( fh, "%s;%s;%s\n", "12", "123", "12" ) == 10 );
    TESTCASE( check_file( fh, 10, ';', 3, widths ) == ( size_t )-1 );

    fclose( fh );
    remove( "test.txt" );

    /* trim() */

    strcpy( buffer, "  xyz" );
    TESTCASE( ! strcmp( trim( buffer ), "xyz" ) );
    strcpy( buffer, "xyz  " );
    TESTCASE( ! strcmp( trim( buffer ), "xyz" ) );
    strcpy( buffer, "  xyz  " );
    TESTCASE( ! strcmp( trim( buffer ), "xyz" ) );
    strcpy( buffer, "  x" );
    TESTCASE( ! strcmp( trim( buffer ), "x" ) );
    strcpy( buffer, "x  " );
    TESTCASE( ! strcmp( trim( buffer ), "x" ) );
    strcpy( buffer, " " );
    TESTCASE( ! strcmp( trim( buffer ), "" ) );
    strcpy( buffer, "  " );
    TESTCASE( ! strcmp( trim( buffer ), "" ) );
    strcpy( buffer, "" );
    TESTCASE( ! strcmp( trim( buffer ), "" ) );

    return TEST_RESULTS;
}

#endif
