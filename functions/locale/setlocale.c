/* setlocale( int, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <locale.h>
#include <stdlib.h>

#ifndef REGTEST

char * setlocale( int category, const char * locale )
{
    /* Path to locale data files - _PDCLIB_LOCALE_PATH unless overruled
       by the environment variable whose name is defined vy preprocessor
       symbol _PDCLIB_LOCALE_PATH_ENV (defaulting to PDCLIB_I18N).
       Both of these definitions are set in _PDCLIB_config.h.
    */
    const char * path = _PDCLIB_LOCALE_PATH;

    if ( getenv( _PDCLIB_symbol2string( _PDCLIB_LOCALE_PATH_ENV ) ) != NULL )
    {
        path = getenv( _PDCLIB_symbol2string( _PDCLIB_LOCALE_PATH_ENV ) );
    }

    if ( category == LC_COLLATE || category == LC_ALL )
    {
        _PDCLIB_load_lc_collate( path, locale );
    }

    if ( category == LC_CTYPE || category == LC_ALL )
    {
        _PDCLIB_load_lc_ctype( path, locale );
    }

    if ( category == LC_MONETARY || category == LC_ALL )
    {
        _PDCLIB_load_lc_monetary( path, locale );
    }

    if ( category == LC_NUMERIC || category == LC_ALL )
    {
        _PDCLIB_load_lc_numeric( path, locale );
    }

    if ( category == LC_TIME || category == LC_ALL )
    {
        _PDCLIB_load_lc_time( path, locale );
    }

    return NULL;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    setlocale(0,"");
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
