/* _PDCLIB_tzset_unlocked( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

#include <stdlib.h>
#include <string.h>

#ifndef TZ_ABBR_MAX_LEN
#define TZ_ABBR_MAX_LEN 16
#endif

#ifndef TZ_ABBR_CHAR_SET
#define TZ_ABBR_CHAR_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 :+-._"
#endif

#ifndef TZ_ABBR_ERR_CHAR
#define TZ_ABBR_ERR_CHAR '_'
#endif

/* This string was in the Factory zone through version 2016f.  */
#define GRANDPARENTED   "Local time zone must be set--see zic manual page"

#ifndef TZ_STRLEN_MAX
#define TZ_STRLEN_MAX 255
#endif

static char lcl_TZname[ TZ_STRLEN_MAX + 1 ];
int  lcl_is_set = 0;

static void scrub_abbrs( struct state * sp )
{
    int i;

    /* First, replace bogus characters. */
    for ( i = 0; i < sp->charcnt; ++i )
    {
        if ( strchr( TZ_ABBR_CHAR_SET, sp->chars[ i ] ) == NULL )
        {
            sp->chars[ i ] = TZ_ABBR_ERR_CHAR;
        }
    }

    /* Second, truncate long abbreviations. */
    for ( i = 0; i < sp->typecnt; ++i )
    {
        const struct ttinfo * const ttisp = &sp->ttis[ i ];
        char * cp = &sp->chars[ ttisp->desigidx ];

        if ( strlen( cp ) > TZ_ABBR_MAX_LEN && strcmp( cp, GRANDPARENTED ) != 0 )
        {
            *( cp + TZ_ABBR_MAX_LEN ) = '\0';
        }
    }
}

/* Initialize *SP to a value appropriate for the TZ setting NAME.
   Return 0 on success, an errno value on failure.
*/
static int zoneinit( struct state * sp, char const * name )
{
    if (name && ! name[0])
    {
        /* User wants it fast rather than right. */
        sp->leapcnt = 0;        /* so, we're off a little */
        sp->timecnt = 0;
        sp->typecnt = 0;
        sp->charcnt = 0;
        sp->goback = sp->goahead = false;
        _PDCLIB_init_ttinfo( &sp->ttis[ 0 ], 0, false, 0 );
        strcpy( sp->chars, gmt );
        sp->defaulttype = 0;
        return 0;
    }
    else
    {
        int err = _PDCLIB_tzload( name, sp, true );

        if ( err != 0 && name && name[ 0 ] != ':' && _PDCLIB_tzparse( name, sp, false ) )
        {
            err = 0;
        }

        if ( err == 0 )
        {
            scrub_abbrs( sp );
        }

        return err;
    }
}

static void settzname( void )
{
    struct state * const sp = &_PDCLIB_lclmem;
    int                  i;

#if HAVE_TZNAME
    tzname[ 0 ] = tzname[ 1 ] = (char *) ( sp ? wildabbr : gmt );
#endif
#if USG_COMPAT
    daylight = 0;
    timezone = 0;
#endif
#if ALTZONE
    altzone = 0;
#endif
    if ( sp == NULL )
    {
        return;
    }
    /* And to get the latest time zone abbreviations into tzname... */
    for ( i = 0; i < sp->typecnt; ++i )
    {
        const struct ttinfo * const ttisp = &sp->ttis[ i ];
        _PDCLIB_update_tzname_etc( sp, ttisp );
    }

    for ( i = 0; i < sp->timecnt; ++i )
    {
        const struct ttinfo * const ttisp = &sp->ttis[ sp->types[ i ] ];
        _PDCLIB_update_tzname_etc( sp, ttisp );
#if USG_COMPAT
        if ( ttisp->isdst )
        {
            daylight = 1;
        }
#endif
    }
}

static void tzsetlcl( char const * name )
{
    struct state * sp = &_PDCLIB_lclmem;
    int lcl = name ? strlen( name ) < sizeof lcl_TZname : -1;

    if ( lcl < 0
            ? lcl_is_set < 0
            : 0 < lcl_is_set && strcmp( lcl_TZname, name ) == 0 )
    {
        return;
    }

    if ( sp )
    {
        if ( zoneinit( sp, name ) != 0 )
        {
            zoneinit( sp, "" );
        }

        if ( 0 < lcl )
        {
            strcpy( lcl_TZname, name );
        }
    }

    settzname();
    lcl_is_set = lcl;
}

void _PDCLIB_tzset_unlocked( void )
{
    tzsetlcl( getenv( "TZ" ) );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
#endif

    return TEST_RESULTS;
}

#endif
