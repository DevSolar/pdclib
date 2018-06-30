/* Wide character classification and mapping utilities <wctype.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_WCTYPE_H
#define _PDCLIB_WCTYPE_H _PDCLIB_WCTYPE_H

#include "pdclib/_PDCLIB_int.h"

// wint_t
// wctrans_t
// wctype_t
// WEOF

/* Wide character classification functions */

int iswalnum( wint_t wc );
int iswalpha( wint_t wc );
int iswblank( wint_t wc );
int iswcntrl( wint_t wc );
int iswdigit( wint_t wc );
int iswgraph( wint_t wc );
int iswlower( wint_t wc );
int iswprint( wint_t wc );
int iswpunct( wint_t wc );
int iswspace( wint_t wc );
int iswupper( wint_t wc );
int iswxdigit( wint_t wc );

/* Extensible wide character classification functions */

int iswctype( wint_t wc, wctype_t desc );
wctype_t wctype( const char * property );

/* Wide character case mapping utilities */

wint_t towlower( wint_t wc );
wint_t towupper( wint_t wc );

/* Extensible wide character case mapping utilities */

wint_t towctrans( wint_t wc, wctrans_t desc );
wctrans_t wctrans( const char * property );

#endif
