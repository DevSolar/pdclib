/* uctype data

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef UCTYPE
#define UCTYPE

#include "derived_properties.h"
#include "unicode_data.h"

size_t get_towupper( size_t codepoint, struct unicode_record_t * ur );
size_t get_towlower( size_t codepoint, struct unicode_record_t * ur );
size_t get_iswupper( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core );
size_t get_iswlower( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core );
size_t get_iswalpha( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core );
size_t get_iswdigit( size_t codepoint );
size_t get_iswxdigit( size_t codepoint );
size_t get_iswblank( size_t codepoint, struct unicode_record_t * ur );
size_t get_iswspace( size_t codepoint, struct unicode_record_t * ur );
size_t get_iswcntrl( size_t codepoint, struct unicode_record_t * ur );
size_t get_iswgraph( size_t codepoint, struct unicode_record_t * ur );
size_t get_iswprint( size_t codepoint, struct unicode_record_t * ur );
size_t get_iswpunct( size_t codepoint, struct unicode_record_t * ur, struct derived_properties_t * core );

#endif
