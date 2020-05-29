/* setlocale( int, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <locale.h>
#include <stdlib.h>
#include <string.h>

#ifndef REGTEST

#if 0
static const char * _PDCLIB_LC_category_name[ _PDCLIB_LC_COUNT ] = { NULL, "LC_COLLATE", "LC_CTYPE", "LC_MONETARY", "LC_NUMERIC", "LC_TIME", "LC_MESSAGES" };

static const char * _PDCLIB_default_locale( int category )
{
    const char * s;

    /* The standard states (7.22.4.6 (3), "the implementation shall behave
       as if no library function calls the getenv function." That is,
       however, in context of the previous paragraph stating that getenv
       "need not avoid data races with other threads of execution that
       modify the environment list".
       PDCLib does not provide means of modifying the environment list.
    */
    if ( ( s = getenv( "LC_ALL" ) ) == NULL )
    {
        if ( category == LC_ALL || ( s = getenv( _PDCLIB_LC_category_name[ category ] ) ) == NULL )
        {
            if ( ( s = getenv( "LANG" ) ) == NULL )
            {
                s = "C";
            }
        }
    }

    return s;
}
#endif

char * setlocale( int category, const char * locale )
{
    /* All below is very much work-in-progress, so we do a dumb-dummy
       return here.
    */
    if ( locale == NULL || ! strcmp( locale, "C" ) )
    {
        return ( char * )"C";
    }
    else
    {
        return NULL;
    }

#if 0
    /* Path to locale data files - _PDCLIB_LOCALE_PATH unless overruled
       by the environment variable whose name is defined by preprocessor
       symbol _PDCLIB_LOCALE_PATH_ENV (defaulting to PDCLIB_I18N).
       Both of these definitions are set in _PDCLIB_config.h.
    */
    const char * path = _PDCLIB_LOCALE_PATH;

    struct _PDCLIB_lc_lconv_numeric_t * numeric = NULL;
    struct _PDCLIB_lc_lconv_monetary_t * monetary = NULL;
    struct _PDCLIB_lc_collate_t * collate = NULL;
    struct _PDCLIB_lc_ctype_t * ctype = NULL;
    struct _PDCLIB_lc_messages_t * messages = NULL;
    struct _PDCLIB_lc_time_t * time = NULL;

    char * rc = ( char * )locale;

    if ( category < 0 || category >= _PDCLIB_LC_COUNT )
    {
        /* Bad category */
        return NULL;
    }

    if ( locale == NULL )
    {
        /* NULL - Return current locale settings */
        /* TODO */
    }

    if ( strlen( locale ) == 0 )
    {
        /* "" - Use default locale */
        locale = _PDCLIB_default_locale( category );
    }

    if ( getenv( _PDCLIB_value2string( _PDCLIB_LOCALE_PATH_ENV ) ) != NULL )
    {
        path = getenv( _PDCLIB_value2string( _PDCLIB_LOCALE_PATH_ENV ) );
    }

    /* We have to do this in two runs. As we might be facing LC_ALL, we
       need to be certain all the loads are successful before we start
       to overwrite the current locale settings, because there is no way
       this function could report a _partial_ success.
    */

    /* Run One -- get all the data for the new locale setting */
    if ( category == LC_COLLATE || category == LC_ALL )
    {
        if ( !( collate = _PDCLIB_load_lc_collate( path, locale ) ) )
        {
            rc = NULL;
        }
    }

    if ( category == LC_CTYPE || category == LC_ALL )
    {
        if ( !( ctype = _PDCLIB_load_lc_ctype( path, locale ) ) )
        {
            rc = NULL;
        }
    }

    if ( category == LC_MONETARY || category == LC_ALL )
    {
        if ( !( monetary = _PDCLIB_load_lc_monetary( path, locale ) ) )
        {
            rc = NULL;
        }
    }

    if ( category == LC_NUMERIC || category == LC_ALL )
    {
        if ( !( numeric = _PDCLIB_load_lc_numeric( path, locale ) ) )
        {
            rc = NULL;
        }
    }

    if ( category == LC_TIME || category == LC_ALL )
    {
        if ( !( time = _PDCLIB_load_lc_time( path, locale ) ) )
        {
            rc = NULL;
        }
    }

    if ( category == LC_MESSAGES || category == LC_ALL )
    {
        if ( !( messages = _PDCLIB_load_lc_messages( path, locale ) ) )
        {
            rc = NULL;
        }
    }

    /* Run Two -- continue or release resources */
    if ( rc != NULL )
    {
        if ( category == LC_COLLATE || category == LC_ALL )
        {
            if ( _PDCLIB_lc_collate->alloced )
            {
                /* free resources */
            }

            *_PDCLIB_lc_collate = *collate;
            free( collate );
        }

        if ( category == LC_CTYPE || category == LC_ALL )
        {
            if ( _PDCLIB_lc_ctype->alloced )
            {
                free( _PDCLIB_lc_ctype->entry - 1 );
            }

            *_PDCLIB_lc_ctype = *ctype;
            free( ctype );
        }

        if ( category == LC_MONETARY || category == LC_ALL )
        {
            if ( _PDCLIB_lc_numeric_monetary.monetary_alloced )
            {
                free( _PDCLIB_lc_numeric_monetary.lconv->mon_decimal_point );
            }

            _PDCLIB_lc_numeric_monetary.lconv->mon_decimal_point = monetary->mon_decimal_point;
            _PDCLIB_lc_numeric_monetary.lconv->mon_thousands_sep = monetary->mon_thousands_sep;
            _PDCLIB_lc_numeric_monetary.lconv->mon_grouping = monetary->mon_grouping;
            _PDCLIB_lc_numeric_monetary.lconv->positive_sign = monetary->positive_sign;
            _PDCLIB_lc_numeric_monetary.lconv->negative_sign = monetary->negative_sign;
            _PDCLIB_lc_numeric_monetary.lconv->currency_symbol = monetary->currency_symbol;
            _PDCLIB_lc_numeric_monetary.lconv->int_curr_symbol = monetary->int_curr_symbol;
            _PDCLIB_lc_numeric_monetary.lconv->frac_digits = monetary->frac_digits;
            _PDCLIB_lc_numeric_monetary.lconv->p_cs_precedes = monetary->p_cs_precedes;
            _PDCLIB_lc_numeric_monetary.lconv->n_cs_precedes = monetary->n_cs_precedes;
            _PDCLIB_lc_numeric_monetary.lconv->p_sep_by_space = monetary->p_sep_by_space;
            _PDCLIB_lc_numeric_monetary.lconv->n_sep_by_space = monetary->n_sep_by_space;
            _PDCLIB_lc_numeric_monetary.lconv->p_sign_posn = monetary->p_sign_posn;
            _PDCLIB_lc_numeric_monetary.lconv->n_sign_posn = monetary->n_sign_posn;
            _PDCLIB_lc_numeric_monetary.lconv->int_frac_digits = monetary->int_frac_digits;
            _PDCLIB_lc_numeric_monetary.lconv->int_p_cs_precedes = monetary->int_p_cs_precedes;
            _PDCLIB_lc_numeric_monetary.lconv->int_n_cs_precedes = monetary->int_n_cs_precedes;
            _PDCLIB_lc_numeric_monetary.lconv->int_p_sep_by_space = monetary->int_p_sep_by_space;
            _PDCLIB_lc_numeric_monetary.lconv->int_n_sep_by_space = monetary->int_n_sep_by_space;
            _PDCLIB_lc_numeric_monetary.lconv->int_p_sign_posn = monetary->int_p_sign_posn;
            _PDCLIB_lc_numeric_monetary.lconv->int_n_sign_posn = monetary->int_n_sign_posn;

            _PDCLIB_lc_numeric_monetary.monetary_alloced = 1;

            free( monetary );
        }

        if ( category == LC_NUMERIC || category == LC_ALL )
        {
            if ( _PDCLIB_lc_numeric_monetary.numeric_alloced )
            {
                free( _PDCLIB_lc_numeric_monetary.lconv->decimal_point );
            }

            _PDCLIB_lc_numeric_monetary.lconv->decimal_point = numeric->decimal_point;
            _PDCLIB_lc_numeric_monetary.lconv->thousands_sep = numeric->thousands_sep;
            _PDCLIB_lc_numeric_monetary.lconv->grouping = numeric->grouping;

            _PDCLIB_lc_numeric_monetary.numeric_alloced = 1;

            free( numeric );
        }

        if ( category == LC_TIME || category == LC_ALL )
        {
            if ( _PDCLIB_lc_time->alloced )
            {
                free( _PDCLIB_lc_time->month_name_abbr[ 0 ] );
            }

            *_PDCLIB_lc_time = *time;
            free( time );
        }

        if ( category == LC_MESSAGES || category == LC_ALL )
        {
            if ( _PDCLIB_lc_messages->alloced )
            {
                free( _PDCLIB_lc_messages->errno_texts[ 0 ] );
            }

            *_PDCLIB_lc_messages = *messages;
            free( messages );
        }
    }

    return NULL;
#endif
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( strcmp( setlocale( LC_ALL, "C" ), "C" ) == 0 );
#ifndef REGTEST
    TESTCASE( setlocale( LC_ALL, "" ) == NULL );
#endif
    TESTCASE( strcmp( setlocale( LC_ALL, NULL ), "C" ) == 0 );
    return TEST_RESULTS;
}

#endif
