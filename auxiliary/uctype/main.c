/* main

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char * argv[] )
{
#ifndef TEST
    char * locale = setlocale( LC_CTYPE, "" );

    if ( ! strstr( locale, "UTF-8" ) || strstr( locale, "TR" ) || strstr( locale, "tr" ) )
    {
        fprintf( stderr, "Need non-turkish locale to work correctly.\n'%s' will not do.\n", locale );
        return EXIT_FAILURE;
    }

    if ( argc != 4 )
    {
        printf( "\n"
                "Usage: get-uctypes <UnicodeData.txt> <DerivedCoreProperties.txt> <DerivedAge.txt>\n"
                "\n"
                "Generates lookup tables for <wctype.h> from files available from\n"
                "the Unicode Consortium.\n"
                "\n"
                "The required files can be retrieved from the following URL:\n"
                "\n"
                "http://www.unicode.org/Public/UCD/latest/ucd/\n"
                "\n" );
        return EXIT_FAILURE;
    }
#endif

    return EXIT_SUCCESS;
}
