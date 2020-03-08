/* main

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef TEST
#include <wctype.h>
#endif

#include "uctype.h"

/* RLE Compressed Output

   <wctype.h> requires *11* flags:
   iswupper, iswlower, iswalpha, iswdigit, iswblank, iswspace,
   iswcntrl, iswxdigit, iswgraph, iswprint.
   iswalnum (the 12th classification function) is *defined* as
   iswalpha || iswdigit. And iswdigit and iswxdigit are defined
   in a rather restrictive way that can be expressed by simple
   ranges instead of lookup tables. And isgraph is defined as
   isprint && ! isspace (which is trivial to check that it holds
   true for all the records provided by get-unicode-ctype, at
   least up to Unicode 11.0).
   So we have only 8 flags we actually need in a lookup... nicely
   reducing the storage requirement to an unsigned char.

   Another trick is to express toupper / tolower as offsets
   instead of absolute values, which will allow run-time-length
   compression of the data.
*/

struct output_record_t
{
    size_t codepoint;
    int toupper_diff;
    int tolower_diff;
    unsigned char flags;
};

#ifdef TEST
static void print_codepoint_age( size_t codepoint, struct derived_properties_t * age )
{
    size_t index = age->count;

    while ( index )
    {
        --index;

        if ( lookup_property( age, age->name[ index ], codepoint ) )
        {
            printf( "%s", age->name[ index ] );
            return;
        }
    }
}

static void print_additional_codepoint_info( size_t codepoint, struct unicode_record_t * ur )
{
    printf( " - %s",      ur->name );
    printf( " - %s",      ur->general_category );
    printf( " - %d",      ur->canonical_combining_class );
    printf( " - %s",      ur->bidi_class );
    printf( " - %s",      ( ur->decomposition ? ur->decomposition : "NULL" ) );
    printf( " - %d",      ur->numeric_type );
    printf( " - %d",      ur->numeric_digit );
    printf( " - %s",      ( ur->numeric_value ? ur->numeric_value : "NULL" ) );
    printf( " - %c",      ur->bidi_mirrored );
    printf( " - U+%06zx", ur->simple_uppercase_mapping );
    printf( " - U+%06zx", ur->simple_lowercase_mapping );
    printf( " - U+%06zx", ur->simple_titlecase_mapping );
    printf( " - " );

    /* Implementations are at liberty to return non-zero values other
       than 1 for "true".
    */
    printf( "%d", ( iswupper( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswlower( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswalpha( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswdigit( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswblank( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswspace( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswcntrl( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswxdigit( codepoint ) ) ? 1 : 0 );
    printf( "%d", ( iswgraph( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswprint( codepoint ) )  ? 1 : 0 );
    printf( "%d", ( iswpunct( codepoint ) )  ? 1 : 0 );
}

static void print_codepoint_info( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core, struct derived_properties_t * age )
{
    int rc;
    int equal = 1;

    if ( codepoint % 20 == 0 )
    {
        printf( "   cp      up       low    UlA0_WCXGP.\n" );
    }

    printf( "U+%06zX ", codepoint );

    rc = get_towupper( codepoint, ur );
    equal &= ( ( unsigned )rc == towupper( codepoint ) );
    printf( "U+%06X ", rc );

    rc = get_towlower( codepoint, ur );
    equal &= ( ( unsigned )rc == towlower( codepoint ) );
    printf( "U+%06X ", rc );

    rc = get_iswupper( codepoint, ur, core );
    equal &= ( iswupper( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswlower( codepoint, ur, core );
    equal &= ( iswlower( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswalpha( codepoint, ur, core );
    equal &= ( iswalpha( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswdigit( codepoint );
    equal &= ( iswdigit( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswblank( codepoint, ur );
    equal &= ( iswblank( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswspace( codepoint, ur );
    equal &= ( iswspace( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswcntrl( codepoint, ur );
    equal &= ( iswcntrl( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswxdigit( codepoint );
    equal &= ( iswxdigit( codepoint ) ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswgraph( codepoint, ur );
    equal &= ( iswgraph( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswprint( codepoint, ur );
    equal &= ( iswprint( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    rc = get_iswpunct( codepoint, ur, core );
    equal &= ( iswpunct( codepoint )  ? 1 : 0 == rc );
    printf( "%d", rc ? 1 : 0 );

    if ( codepoint != ur->code_point )
    {
        /* These two may only differ for codepoint "ranges", which are
           signified by "..., First>" / "..., Last>" pairs in UnicodeData.
           If they differ and it's NOT a range, that is an error of some
           kind.
        */
        if ( ! strstr( ur->name, ", Last>" ) || codepoint < ( ur - 1 )->code_point )
        {
            printf( " ERROR: U+%06zX != U+%06zX outside of First, Last codepoint range.  ", codepoint, ur->code_point );
        }
    }

    if ( ! equal )
    {
        printf( " ERROR: Deviation from SysLib: " );
        print_codepoint_age( codepoint, age );
        print_additional_codepoint_info( codepoint, ur );
    }

    printf( "\n" );
}
#else
static struct output_record_t get_output_record( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core )
{
    struct output_record_t rc;
    char buffer[ 9 ];

    rc.codepoint = codepoint;
    rc.toupper_diff = get_towupper( codepoint, ur ) - codepoint;
    rc.tolower_diff = get_towlower( codepoint, ur ) - codepoint;

    sprintf( buffer, "%zu%zu%zu%zu%zu%zu%zu%zu",
             get_iswupper( codepoint, ur, core ),
             get_iswlower( codepoint, ur, core ),
             get_iswalpha( codepoint, ur, core ),
             get_iswblank( codepoint, ur ),
             get_iswspace( codepoint, ur ),
             get_iswcntrl( codepoint, ur ),
             get_iswprint( codepoint, ur ),
             get_iswpunct( codepoint, ur, core ) );

    rc.flags = strtoul( buffer, NULL, 2 );

    return rc;
}
#endif

int main( int argc, char * argv[] )
{
    struct unicode_data_t * ud;
    struct derived_properties_t * core;
#ifdef TEST
    struct derived_properties_t * age;
#endif

    char * locale = setlocale( LC_CTYPE, "" );

    if ( ! strstr( locale, "UTF-8" ) || strstr( locale, "TR" ) || strstr( locale, "tr" ) )
    {
        fprintf( stderr, "Need non-turkish locale to work correctly.\n'%s' will not do.\n", locale );
        return EXIT_FAILURE;
    }

#ifdef TEST
    if ( argc != 4 )
#else
    if ( argc != 3 )
#endif
    {
        printf( "\n"
                "Usage: get-uctypes <UnicodeData.txt> <DerivedCoreProperties.txt>"
#ifdef TEST
                " <DerivedAge.txt>"
#endif
                "\n\n"
                "Generates lookup tables for <wctype.h> from files available from\n"
                "the Unicode Consortium.\n"
                "\n"
                "The required files can be retrieved from the following URL:\n"
                "\n"
                "http://www.unicode.org/Public/UCD/latest/ucd/\n"
                "\n" );
        return EXIT_FAILURE;
    }

    if ( ( ud = read_unicode_data( argv[ 1 ] ) ) != NULL )
    {
        if ( ( core = read_derived_properties( argv[ 2 ] ) ) != NULL )
        {
#ifndef TEST
            /* Print (to file) RLE compressed data */
            FILE * fh = fopen( "ctype.dat", "wb" );

            if ( fh )
            {
                size_t codepoint = 0;
                size_t i = 0;
                struct unicode_record_t * ur = &( ud->records[i] );
                /* Name substring indicating a code point _range_ */
                const char * last = ", Last>";

                struct output_record_t previous = get_output_record( codepoint, ur, core );

                fprintf( fh, "%zx ", previous.codepoint );

                for ( codepoint = 1; codepoint < 0x10fffe; ++codepoint )
                {
                    struct output_record_t current;

                    while ( codepoint > ur->code_point )
                    {
                        ur = &( ud->records[++i] );
                    }

                    if ( codepoint != ur->code_point && ( ur->name && ( strstr( ur->name, last ) != ( ur->name + strlen( ur->name ) - strlen( last ) ) ) ) )
                    {
                        /* Unregistered Code Point */
                        continue;
                    }

                    current = get_output_record( codepoint, ur, core );

                    /* RLE */
                    if ( current.codepoint != previous.codepoint + 1 ||
                         current.toupper_diff != previous.toupper_diff ||
                         current.tolower_diff != previous.tolower_diff ||
                         current.flags != previous.flags )
                    {
                        fprintf( fh, "%zx %d %d %hhx\n", previous.codepoint, previous.toupper_diff, previous.tolower_diff, previous.flags );
                        fprintf( fh, "%zx ", current.codepoint );
                    }

                    previous = current;
                }

                fprintf( fh, "%zx %d %d %hhx\n", previous.codepoint, previous.toupper_diff, previous.tolower_diff, previous.flags );
                fclose( fh );
            }
            else
            {
                fprintf( stderr, "Could not open 'ctype.dat' for writing.\n" );
            }

#else

            if ( ( age = read_derived_properties( argv[ 3 ] ) ) != NULL )
            {
                /* Print (to screen) raw data comparing our results
                   to the system library.
                   Differences are often because the system library
                   uses older data, which is why we add the age to
                   the output.
                */
                size_t codepoint = 0;
                size_t i = 0;
                struct unicode_record_t * ur = &( ud->records[i] );
                /* Name substring indicating a code point _range_ */
                const char * last = ", Last>";

                for ( codepoint = 0; codepoint < 0x10fffe; ++codepoint )
                {
                    while ( codepoint > ur->code_point )
                    {
                        ur = &( ud->records[++i] );
                    }

                    if ( codepoint != ur->code_point && ! name_ends_with( ur, last ) )
                    {
                        /* Unregistered Code Point */
                        continue;
                    }

                    print_codepoint_info( codepoint, ur, core, age );
                }

                release_derived_properties( age );
            }

#endif

            release_derived_properties( core );
        }

        release_unicode_data( ud );
    }

    return EXIT_SUCCESS;
}
