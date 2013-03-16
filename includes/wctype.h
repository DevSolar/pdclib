/* 7.30 Wide Character Classification and Mapping Utilities <wctype.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_WCTYPE_H
#define _PDCLIB_WCTYPE_H _PDCLIB_WCTYPE_H
#include <_PDCLIB_int.h>
_PDCLIB_BEGIN_EXTERN_C

#ifndef _PDCLIB_WINT_T_DEFINED
#define _PDCLIB_WINT_T_DEFINED _PDCLIB_WINT_T_DEFINED
typedef _PDCLIB_wint_t wint_t;
#endif

typedef int wctrans_t;
typedef int wctype_t;

/* 7.30.2.1 Character classification functions */
int iswalnum( wint_t _Wc );
int iswalpha( wint_t _Wc );
int iswblank( wint_t _Wc );
int iswcntrl( wint_t _Wc );
int iswdigit( wint_t _Wc );
int iswgraph( wint_t _Wc );
int iswlower( wint_t _Wc );
int iswprint( wint_t _Wc );
int iswpunct( wint_t _Wc );
int iswspace( wint_t _Wc );
int iswupper( wint_t _Wc );
int iswxdigit( wint_t _Wc );

/* 7.30.2.2 Extensible character classification functions */
int iswctype( wint_t _Wc, wctype_t _Desc );
wctype_t wctype( const char * _Property );

/* 7.30.3 Wide character case mapping utilities */
wint_t towlower( wint_t _Wc );
wint_t towupper( wint_t _Wc );

/* 7.30.3.2 Extensible wide character case mapping functions */
wint_t towctrans( wint_t _Wc, wctrans_t _Desc );
wctrans_t wctrans( const char * _Property );

_PDCLIB_END_EXTERN_C
#endif // _PDCLIB_WCTYPE_H
