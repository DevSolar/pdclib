/* uctype

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include "uctype.h"

size_t get_towupper( size_t codepoint, struct unicode_record_t * ur )
{
    return towupper_differs( ur, codepoint ) ? ur->simple_uppercase_mapping : codepoint;
}

size_t get_towlower( size_t codepoint, struct unicode_record_t * ur )
{
    return towlower_differs( ur, codepoint ) ? ur->simple_lowercase_mapping : codepoint;
}

size_t get_iswupper( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core )
{
    return towlower_differs( ur, codepoint ) || lookup_property( core, "Uppercase", codepoint );
}

size_t get_iswlower( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core )
{
    return towupper_differs( ur, codepoint ) || lookup_property( core, "Lowercase", codepoint );
}

size_t get_iswalpha( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core )
{
    return lookup_property( core, "Alphabetic", codepoint ) || ( is_general_category( ur, "Nd" ) && ! get_iswdigit( codepoint ) );
}

size_t get_iswdigit( size_t codepoint )
{
    return codepoint >= 0x0030 && codepoint <= 0x0039;
}

size_t get_iswxdigit( size_t codepoint )
{
    return get_iswdigit( codepoint ) || ( codepoint >= 0x0041 && codepoint <= 0x0046 ) || ( codepoint >= 0x0061 && codepoint <= 0x0066 );
}

size_t get_iswblank( size_t codepoint, struct unicode_record_t * ur )
{
    return ( codepoint == 0x0009 ) || ( is_general_category( ur, "Zs" ) && ! decomposition_contains( ur, "<noBreak>" ) );
}

size_t get_iswspace( size_t codepoint, struct unicode_record_t * ur )
{
    return is_general_category( ur, "Zl" ) || is_general_category( ur, "Zp" ) || ( is_general_category( ur, "Zs" ) && ! decomposition_contains( ur, "<noBreak>" ) ) || ( codepoint == 0x0020 ) || ( codepoint >= 0x0009 && codepoint <= 0x000D );
}

size_t get_iswcntrl( size_t codepoint, struct unicode_record_t * ur )
{
    return is_general_category( ur, "Zl" ) || is_general_category( ur, "Zp" ) || has_name( ur, "<control>" );
}

size_t get_iswgraph( size_t codepoint, struct unicode_record_t * ur )
{
    return ! is_general_category( ur, "Cs" ) && ! has_name( ur, "<control>" ) && ! get_iswspace( codepoint, ur );
}

size_t get_iswprint( size_t codepoint, struct unicode_record_t * ur )
{
    return ! is_general_category( ur, "Zp" ) && ! is_general_category( ur, "Zl" ) && ! is_general_category( ur, "Cs" ) && ! has_name( ur, "<control>" );
}

size_t get_iswpunct( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core )
{
    return ! get_iswalpha( codepoint, ur, core ) && ! get_iswdigit( codepoint ) && ( ! has_name( ur, "<control>" ) && ! get_iswspace( codepoint, ur ) ) && ! is_general_category( ur, "Cs" );
}

#ifdef TEST

#include "test.h"

int main( void )
{
    TESTCASE( NO_TESTDRIVER );

    return TEST_RESULTS;
}

#endif
