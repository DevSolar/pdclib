// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Wide character classification and mapping utilities
// ----------------------------------------------------------------------------

#ifndef __WCTYPE_H
#define __WCTYPE_H __WCTYPE_H

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef wctrans_t;
typedef wctype_t;
typedef wint_t;

// ----------------------------------------------------------------------------
// FUNCTIONS

int iswalnum( wint_t c );
int iswalpha( wint_t c );
int iswblank( wint_t c );
int iswcntrl( wint_t c );
int iswctype( wint_t c, wctype_t category );
int iswdigit( wint_t c );
int iswgraph( wint_t c );
int iswlower( wint_t c );
int iswprint( wint_t c );
int iswpunct( wint_t c );
int iswspace( wint_t c );
int iswupper( wint_t c );
int iswxdigit( wint_t c );

wint_t towctrans( wint_t c, wctrans_t category );
wint_t towlower( wint_t c );
wint_t towupper( wint_t c );

wctrans_t wctrans( const char * property );
wctype_t wctype( const char * property );

#endif // __WCTYPE_H
