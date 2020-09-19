/* _PDCLIB_tzload( char const *, struct _PDCLIB_timezone *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

static int_fast32_t detzcode( const char * codep )
{
    int_fast32_t result;
    int          i;
    int_fast32_t one = 1;
    int_fast32_t halfmaxval = one << ( 32 - 2 );
    int_fast32_t maxval = halfmaxval - 1 + halfmaxval;
    int_fast32_t minval = -1 - maxval;

    result = codep[ 0 ] & 0x7f;

    for ( i = 1; i < 4; ++i )
    {
        result = ( result << 8 ) | ( codep[ i ] & 0xff );
    }

    if ( codep[ 0 ] & 0x80 )
    {
        /* Do two's-complement negation even on non-two's-complement machines.
           If the result would be minval - 1, return minval.
        */
        result -= ! _PDCLIB_TWOS_COMPLEMENT && result != 0;
        result += minval;
    }

    return result;
}

static int_fast64_t detzcode64( const char * codep )
{
    uint_fast64_t result;
    int           i;
    int_fast64_t  one = 1;
    int_fast64_t  halfmaxval = one << ( 64 - 2 );
    int_fast64_t  maxval = halfmaxval - 1 + halfmaxval;
    int_fast64_t  minval = - _PDCLIB_TWOS_COMPLEMENT - maxval;

    result = codep[ 0 ] & 0x7f;

    for ( i = 1; i < 8; ++i )
    {
        result = ( result << 8 ) | ( codep[ i ] & 0xff );
    }

    if ( codep[ 0 ] & 0x80 )
    {
        /* Do two's-complement negation even on non-two's-complement machines.
           If the result would be minval - 1, return minval.
        */
      result -= ! _PDCLIB_TWOS_COMPLEMENT && result != 0;
      result += minval;
    }

    return result;
}

static bool differ_by_repeat( const time_t t1, const time_t t0 )
{
    if ( ( sizeof( time_t ) * _PDCLIB_CHAR_BIT ) - _PDCLIB_TYPE_SIGNED( time_t ) < SECSPERREPEAT_BITS )
    {
        return 0;
    }

    return ( t1 - t0 ) == SECSPERREPEAT;
}

static bool typesequiv( const struct state * sp, int a, int b )
{
    bool result;

    if ( sp == NULL ||
         a < 0 || a >= sp->typecnt ||
         b < 0 || b >= sp->typecnt )
    {
        result = false;
    }
    else
    {
        const struct ttinfo *  ap = &sp->ttis[ a ];
        const struct ttinfo *  bp = &sp->ttis[ b ];

        result = ( ap->utoff == bp->utoff &&
                   ap->isdst == bp->isdst &&
                   ap->ttisstd == bp->ttisstd &&
                   ap->ttisut == bp->ttisut &&
                   ( strcmp( &sp->chars[ ap->desigidx ], &sp->chars[ bp->desigidx ] ) == 0 )
                 );
    }

    return result;
}

#define TZ_MAGIC "TZif"

struct tzhead
{
    char tzh_magic[ 4 ];       /* TZ_MAGIC */
    char tzh_version[ 1 ];     /* '\0' or '2' or '3' as of 2013 */
    char tzh_reserved[ 15 ];   /* reserved; must be zero */
    char tzh_ttisutcnt[ 4 ];   /* coded number of trans. time flags */
    char tzh_ttisstdcnt[ 4 ];  /* coded number of trans. time flags */
    char tzh_leapcnt[ 4 ];     /* coded number of leap seconds */
    char tzh_timecnt[ 4 ];     /* coded number of transition times */
    char tzh_typecnt[ 4 ];     /* coded number of local time types */
    char tzh_charcnt[ 4 ];     /* coded number of abbr. chars */
};

/* Input buffer for data read from a compiled tz file.  */
union input_buffer
{
    /* The first part of the buffer, interpreted as a header.  */
    struct tzhead tzhead;

    /* The entire buffer.  */
    char buf[ 2 * sizeof ( struct tzhead ) + 2 * sizeof ( struct state ) + 4 * TZ_MAX_TIMES ];
};

/* _PDCLIB_TZDIR with a trailing '/' rather than a trailing '\0'.  */
static char const tzdirslash[ sizeof _PDCLIB_TZDIR + 1 ] = _PDCLIB_TZDIR "/";

/* Local storage needed for 'tzloadbody'.  */
union local_storage
{
    /* The results of analyzing the file's contents after it is opened.  */
    struct file_analysis
    {
        /* The input buffer.  */
        union input_buffer u;

        /* A temporary state used for parsing a TZ string in the file.  */
        struct state st;
    } u;

    /* The file name to be opened.  */
    char fullname[ BIGGEST ( sizeof ( struct file_analysis ), sizeof tzdirslash + 1024 ) ];
};

static int_fast64_t leapcorr( struct state const * sp, time_t t )
{
    struct lsinfo const * lp;
    int i;

    i = sp->leapcnt;

    while ( --i >= 0 )
    {
        lp = &sp->lsis[ i ];

        if ( t >= lp->trans )
        {
            return lp->corr;
        }
    }

    return 0;
}

/* Load tz data from the file named NAME into *SP.  Read extended
   format if DOEXTEND.  Use *LSP for temporary storage.  Return 0 on
   success, an errno value on failure.  */
static int tzloadbody( char const * name, struct state * sp, bool doextend, union local_storage * lsp )
{
    int    i;
    FILE * fid;
    int    stored;
    size_t nread;
    bool   doaccess;
    union  input_buffer * up = &lsp->u.u;
    size_t tzheadsize = sizeof ( struct tzhead );

    sp->goback = sp->goahead = false;

    if ( ! name )
    {
        name = _PDCLIB_TZDEFAULT;

        if ( ! name )
        {
            return _PDCLIB_EINVAL;
        }
    }

    if ( name[ 0 ] == ':' )
    {
        ++name;
    }

    doaccess = name[ 0 ] == '/';

    if ( ! doaccess )
    {
        char const * dot;
        size_t namelen = strlen( name );

        if ( sizeof lsp->fullname - sizeof tzdirslash <= namelen )
        {
            return _PDCLIB_ENAMETOOLONG;
        }

        /* Create a string "TZDIR/NAME".  Using sprintf here
           would pull in stdio (and would fail if the
           resulting string length exceeded INT_MAX!).
        */
        memcpy( lsp->fullname, tzdirslash, sizeof tzdirslash );
        strcpy( lsp->fullname + sizeof tzdirslash, name );

        /* Set doaccess if NAME contains a ".." file name
           component, as such a name could read a file outside
           the TZDIR virtual subtree.
        */
        for ( dot = name; ( dot = strchr( dot, '.' ) ); ++dot )
        {
            if ( ( dot == name || dot[ -1 ] == '/' ) && dot[ 1 ] == '.' && ( dot[ 2 ] == '/' || ! dot[ 2 ] ) )
            {
                doaccess = true;
                break;
            }
        }

        name = lsp->fullname;
    }

    fid = fopen( name, "rb" );

    if ( fid == NULL )
    {
        return errno;
    }

    nread = fread( up->buf, 1, sizeof up->buf, fid );

    if ( nread < tzheadsize )
    {
        int err = errno;

        if ( ! ferror( fid ) )
        {
            err = _PDCLIB_EINVAL;
        }

        fclose( fid );
        return err;
    }

    if ( fclose( fid ) == EOF )
    {
        return errno;
    }

    for ( stored = 4; stored <= 8; stored *= 2 )
    {
        int_fast32_t ttisstdcnt = detzcode( up->tzhead.tzh_ttisstdcnt );
        int_fast32_t ttisutcnt = detzcode( up->tzhead.tzh_ttisutcnt );
        int_fast64_t prevtr = 0;
        int_fast32_t prevcorr = 0;
        int_fast32_t leapcnt = detzcode( up->tzhead.tzh_leapcnt );
        int_fast32_t timecnt = detzcode( up->tzhead.tzh_timecnt );
        int_fast32_t typecnt = detzcode( up->tzhead.tzh_typecnt );
        int_fast32_t charcnt = detzcode( up->tzhead.tzh_charcnt );
        char const *p = up->buf + tzheadsize;
        /* Although tzfile(5) currently requires typecnt to be nonzero,
           support future formats that may allow zero typecnt
           in files that have a TZ string and no transitions.
        */
        if ( ! ( 0 <= leapcnt && leapcnt < TZ_MAX_LEAPS
               && 0 <= typecnt && typecnt < TZ_MAX_TYPES
               && 0 <= timecnt && timecnt < TZ_MAX_TIMES
               && 0 <= charcnt && charcnt < TZ_MAX_CHARS
               && ( ttisstdcnt == typecnt || ttisstdcnt == 0 )
               && ( ttisutcnt == typecnt || ttisutcnt == 0 ) ) )
        {
            return _PDCLIB_EINVAL;
        }

        if ( nread
            < ( tzheadsize       /* struct tzhead */
              + timecnt * stored   /* ats */
              + timecnt        /* types */
              + typecnt * 6        /* ttinfos */
              + charcnt        /* chars */
              + leapcnt * ( stored + 4 ) /* lsinfos */
              + ttisstdcnt     /* ttisstds */
              + ttisutcnt ) )        /* ttisuts */
        {
            return _PDCLIB_EINVAL;
        }

        sp->leapcnt = leapcnt;
        sp->timecnt = timecnt;
        sp->typecnt = typecnt;
        sp->charcnt = charcnt;

        /* Read transitions, discarding those out of time_t range.
           But pretend the last transition before _PDCLIB_TIME_MIN
           occurred at _PDCLIB_TIME_MIN.
        */
        timecnt = 0;

        for ( i = 0; i < sp->timecnt; ++i )
        {
            int_fast64_t at = stored == 4 ? detzcode( p ) : detzcode64( p );
            sp->types[ i ] = at <= _PDCLIB_TIME_MAX;

            if ( sp->types[ i ] )
            {
                time_t attime = ( ( _PDCLIB_TYPE_SIGNED( time_t ) ? at < _PDCLIB_TIME_MIN : at < 0 ) ? _PDCLIB_TIME_MIN : at );

                if ( timecnt && attime <= sp->ats[ timecnt - 1 ] )
                {
                    if ( attime < sp->ats[ timecnt - 1 ] )
                    {
                        return _PDCLIB_EINVAL;
                    }

                    sp->types[ i - 1 ] = 0;
                    timecnt--;
                }

                sp->ats[ timecnt++ ] = attime;
            }

            p += stored;
        }

        timecnt = 0;

        for ( i = 0; i < sp->timecnt; ++i )
        {
            unsigned char typ = *p++;

            if ( sp->typecnt <= typ )
            {
                return _PDCLIB_EINVAL;
            }

            if ( sp->types[ i ] )
            {
                sp->types[ timecnt++ ] = typ;
            }
        }

        sp->timecnt = timecnt;

        for ( i = 0; i < sp->typecnt; ++i )
        {
            struct ttinfo * ttisp;
            unsigned char isdst, desigidx;

            ttisp = &sp->ttis[ i ];
            ttisp->utoff = detzcode( p );
            p += 4;
            isdst = *p++;

            if ( ! ( isdst < 2 ) )
            {
                return _PDCLIB_EINVAL;
            }

            ttisp->isdst = isdst;
            desigidx = *p++;

            if ( ! ( desigidx < sp->charcnt ) )
            {
                return _PDCLIB_EINVAL;
            }

            ttisp->desigidx = desigidx;
        }

        for ( i = 0; i < sp->charcnt; ++i )
        {
            sp->chars[ i ] = *p++;
        }

        sp->chars[ i ] = '\0';    /* ensure '\0' at end */

        /* Read leap seconds, discarding those out of time_t range.  */
        leapcnt = 0;

        for ( i = 0; i < sp->leapcnt; ++i )
        {
            int_fast64_t tr = stored == 4 ? detzcode( p ) : detzcode64( p );
            int_fast32_t corr = detzcode( p + stored );
            p += stored + 4;

            /* Leap seconds cannot occur before the Epoch.  */
            if ( tr < 0 )
            {
                return _PDCLIB_EINVAL;
            }

            if ( tr <= _PDCLIB_TIME_MAX )
            {
                /* Leap seconds cannot occur more than once per UTC month,
                   and UTC months are at least 28 days long (minus 1
                   second for a negative leap second).  Each leap second's
                   correction must differ from the previous one's by 1
                   second.
                */
                if ( tr - prevtr < 28 * SECSPERDAY - 1 || ( corr != prevcorr - 1 && corr != prevcorr + 1 ) )
                {
                    return _PDCLIB_EINVAL;
                }

                sp->lsis[ leapcnt ].trans = prevtr = tr;
                sp->lsis[ leapcnt ].corr = prevcorr = corr;
                ++leapcnt;
            }
        }

        sp->leapcnt = leapcnt;

        for ( i = 0; i < sp->typecnt; ++i )
        {
            struct ttinfo * ttisp;

            ttisp = &sp->ttis[ i ];

            if ( ttisstdcnt == 0 )
            {
                ttisp->ttisstd = false;
            }
            else
            {
                if ( *p != true && *p != false )
                {
                    return _PDCLIB_EINVAL;
                }

                ttisp->ttisstd = *p++;
            }
        }

        for ( i = 0; i < sp->typecnt; ++i )
        {
            struct ttinfo * ttisp;

            ttisp = &sp->ttis[ i ];

            if ( ttisutcnt == 0 )
            {
                ttisp->ttisut = false;
            }
            else
            {
                if ( *p != true && *p != false )
                {
                    return _PDCLIB_EINVAL;
                }

                ttisp->ttisut = *p++;
            }
        }

        /* If this is an old file, we're done. */
        if ( up->tzhead.tzh_version[ 0 ] == '\0' )
        {
            break;
        }

        nread -= p - up->buf;
        memmove( up->buf, p, nread );
    }

    if ( doextend && nread > 2 && up->buf[ 0 ] == '\n' && up->buf[ nread - 1 ] == '\n' && sp->typecnt + 2 <= TZ_MAX_TYPES )
    {
        struct state    *ts = &lsp->u.st;

        up->buf[ nread - 1 ] = '\0';

        if ( _PDCLIB_tzparse( &up->buf[ 1 ], ts, false ) )
        {
            /* Attempt to reuse existing abbreviations.
               Without this, America/Anchorage would be right on
               the edge after 2037 when TZ_MAX_CHARS is 50, as
               sp->charcnt equals 40 (for LMT AST AWT APT AHST
               AHDT YST AKDT AKST) and ts->charcnt equals 10
               (for AKST AKDT).  Reusing means sp->charcnt can
               stay 40 in this example.  */
            int gotabbr = 0;
            int charcnt = sp->charcnt;

            for ( i = 0; i < ts->typecnt; ++i )
            {
                char * tsabbr = ts->chars + ts->ttis[ i ].desigidx;
                int j;

                for ( j = 0; j < charcnt; ++j )
                {
                    if ( strcmp( sp->chars + j, tsabbr ) == 0 )
                    {
                        ts->ttis[ i ].desigidx = j;
                        ++gotabbr;
                        break;
                    }
                }

                if ( ! ( j < charcnt ) )
                {
                    int tsabbrlen = strlen( tsabbr );

                    if ( j + tsabbrlen < TZ_MAX_CHARS )
                    {
                        strcpy( sp->chars + j, tsabbr );
                        charcnt = j + tsabbrlen + 1;
                        ts->ttis[ i ].desigidx = j;
                        ++gotabbr;
                    }
                }
            }

            if ( gotabbr == ts->typecnt )
            {
                sp->charcnt = charcnt;

                /* Ignore any trailing, no-op transitions generated
                   by zic as they don't help here and can run afoul
                   of bugs in zic 2016j or earlier.  */
                while ( 1 < sp->timecnt && ( sp->types[ sp->timecnt - 1 ] == sp->types[ sp->timecnt - 2 ] ) )
                {
                    sp->timecnt--;
                }

                for ( i = 0; i < ts->timecnt; ++i )
                {
                    if ( sp->timecnt == 0 || ( sp->ats[ sp->timecnt - 1 ] < ts->ats[ i ] + leapcorr( sp, ts->ats[ i ] ) ) )
                    {
                        break;
                    }
                }

                while ( i < ts->timecnt && sp->timecnt < TZ_MAX_TIMES )
                {
                    sp->ats[ sp->timecnt ] = ts->ats[ i ] + leapcorr( sp, ts->ats[ i ] );
                    sp->types[ sp->timecnt ] = ( sp->typecnt + ts->types[ i ] );
                    sp->timecnt++;
                    ++i;
                }

                for ( i = 0; i < ts->typecnt; ++i )
                {
                    sp->ttis[ sp->typecnt++ ] = ts->ttis[ i ];
                }
            }
        }
    }

    if ( sp->typecnt == 0 )
    {
        return _PDCLIB_EINVAL;
    }

    if ( sp->timecnt > 1 )
    {
        for ( i = 1; i < sp->timecnt; ++i )
        {
            if ( typesequiv( sp, sp->types[ i ], sp->types[ 0 ] ) && differ_by_repeat( sp->ats[ i ], sp->ats[ 0 ] ) )
            {
                sp->goback = true;
                break;
            }
        }

        for ( i = sp->timecnt - 2; i >= 0; --i )
        {
            if ( typesequiv( sp, sp->types[ sp->timecnt - 1 ], sp->types[ i ] ) && differ_by_repeat( sp->ats[ sp->timecnt - 1 ], sp->ats[ i ] ) )
            {
                sp->goahead = true;
                break;
            }
        }
    }

    /* Infer sp->defaulttype from the data.  Although this default
       type is always zero for data from recent tzdb releases,
       things are trickier for data from tzdb 2018e or earlier.

       The first set of heuristics work around bugs in 32-bit data
       generated by tzdb 2013c or earlier.  The workaround is for
       zones like Australia/Macquarie where timestamps before the
       first transition have a time type that is not the earliest
       standard-time type.  See:
       https://mm.icann.org/pipermail/tz/2013-May/019368.html
    */
    /* If type 0 is unused in transitions, it's the type to use for early times. */
    for ( i = 0; i < sp->timecnt; ++i )
    {
        if ( sp->types[ i ] == 0 )
        {
            break;
        }
    }

    i = i < sp->timecnt ? -1 : 0;

    /* Absent the above,
       if there are transition times
       and the first transition is to a daylight time
       find the standard type less than and closest to
       the type of the first transition.
    */
    if ( i < 0 && sp->timecnt > 0 && sp->ttis[ sp->types[ 0 ] ].isdst )
    {
        i = sp->types[ 0 ];

        while ( --i >= 0 )
        {
            if ( ! sp->ttis[ i ].isdst )
            {
                break;
            }
        }
    }

    /* The next heuristics are for data generated by tzdb 2018e or
       earlier, for zones like EST5EDT where the first transition
       is to DST.
    */
    /* If no result yet, find the first standard type.
       If there is none, punt to type zero.
    */
    if ( i < 0 )
    {
        i = 0;

        while ( sp->ttis[ i ].isdst )
        {
            if ( ++i >= sp->typecnt )
            {
                i = 0;
                break;
            }
        }
    }

    /* A simple 'sp->defaulttype = 0;' would suffice here if we
       didn't have to worry about 2018e-or-earlier data.  Even
       simpler would be to remove the defaulttype member and just
       use 0 in its place.
    */
    sp->defaulttype = i;

    return 0;
}

/* Load tz data from the file named NAME into *SP.  Read extended
   format if DOEXTEND.  Return 0 on success, an errno value on failure.
*/
int _PDCLIB_tzload( char const * name, struct state * sp, bool doextend )
{
    union local_storage ls;
    return tzloadbody( name, sp, doextend, &ls );
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
