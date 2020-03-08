/* derived properties

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef DERIVED_PROPERTIES
#define DERIVED_PROPERTIES DERIVED_PROPERTIES

#include <stddef.h>

/* https://www.unicode.org/reports/tr44/#DerivedCoreProperties.txt */

struct derived_properties_t
{
    size_t count;
    char ** name;
    size_t * begin;
    size_t * end;
    size_t * code_points;
};

static const int derived_properties_fields[] =
{
    -1, /* code point or code point range */
    -1  /* property name */
};

struct derived_properties_t * read_derived_properties( const char * filename );

int lookup_property( struct derived_properties_t * dp, const char * property, size_t codepoint );

void release_derived_properties( struct derived_properties_t * dp );

#endif
