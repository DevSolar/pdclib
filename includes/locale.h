// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Provides information on locale specifics as well as a function to change the
// active locale to something else but the startup default "C".
// ----------------------------------------------------------------------------

#ifndef __LOCALE_H
#define __LOCALE_H __LOCALE_H

// ----------------------------------------------------------------------------
// DEFINES

#define NULL 0

// Locale categories
#define LC_COLLATE   1 // affects strcoll() and strxfrm()
#define LC_CTYPE     2 // affects ctype.h
#define LC_MONETARY  4 // affects monetary aspect of localeconv()
#define LC_NUMERIC   8 // affects numeric aspect of localeconv()
#define LC_TIME     16 // affects strftime()
#define LC_ALL      31 // affects all of the above

// ----------------------------------------------------------------------------
// TYPEDEFS

// TODO: Detailed documentation of grouping formats and field values

struct lconv
{
    // LC_NUMERIC
    char * decimal_point;      // decimal point
    char * grouping;           // grouping
    char * thousands_sep;      // grouping string

    // LC_MONETARY
    char * mon_decimal_point;  // decimal point
    char * mon_grouping;       // grouping
    char * mon_thousands_sep;  // grouping string
    char * negative_sign;      // negative sign
    char * positive_sign;      // positive sign
    char * currency_symbol;    // currency symbol
    char frac_digits;          // after-point digits
    // negative values
    char n_cs_precedes;        // currency symbol preceding value?
    char n_sep_by_space;       // currency symbol seperated by space?
    char n_sign_posn;          // sign position
    // positive values
    char p_cs_precedes;        // currency symbol preceding value?
    char p_sep_by_space;       // currency symbol seperated by space?
    char p_sign_posn;          // sign position?

    // for international monetary values
    char * int_curr_symbol;    // international currency symbol (ISO 4217)
    char int_frac_digits;      // after-point digits
    // negative values
    char int_n_cs_precedes;    // currency symbol preceding value?
    char int_n_sep_by_space;   // currency symbol seperated by space?
    char int_n_sign_posn;      // sign position?
    // positive values
    char int_p_cs_precedes;    // currency symbol preceding value?
    char int_p_sep_by_space;   // currency symbol seperated by space?
    char int_p_sign_posn;      // sign position?
};

// ----------------------------------------------------------------------------
// FUNCTIONS

// Returns a (pointer to a) lconv structure holding the values for the current
// locale. The structure must not be changed; values might become outdated with
// later calls to setlocale() changing LC_NUMERIC, LC_MONETARY or LC_ALL.
struct lconv * localeconv( void );

// Categories are selected by OR'ing the LC_* defines from this header. The
// function sets the current locale to that defined by locale_name, and returns
// the name of the new locale (if it was set successfully) or a null pointer
// (if unsuccessful). At startup, the current locale is "C" by default. A null
// pointer as locale_name leaves the locale unchanged, an empty string sets it
// to the "native" locale.
char * setlocale( int categories, const char * locale_name );

#endif // __LOCALE_H
