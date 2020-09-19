/* _PDCLIB_tzparse( char const *, struct _PDCLIB_timezone *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

#include <ctype.h>
#include <string.h>

/* The DST rules to use if TZ has no rules and we can't load TZDEFRULES.
   Default to US rules as of 2017-05-07.
   POSIX does not specify the default DST rules;
   for historical reasons, US rules are a common default.
*/
#ifndef TZDEFRULESTRING
#define TZDEFRULESTRING ",M3.2.0,M11.1.0"
#endif

#ifndef TZDEFRULES
#define TZDEFRULES "posixrules"
#endif

enum rule_t
{
    JULIAN_DAY,           /* Jn = Julian day                   */
    DAY_OF_YEAR,          /* n = day of year                   */
    MONTH_NTH_DAY_OF_WEEK /* Mm.n.d = month, week, day of week */
};

struct rule
{
    enum rule_t  type; /* type of rule            */
    int          day;  /* day number of rule      */
    int          week; /* week number of rule     */
    int          mon;  /* month number of rule    */
    int_fast32_t time; /* transition time of rule */
};

/* Given a pointer into a timezone string, extract a number from that string.
   Check that the number is within a specified range; if it is not, return
   NULL.
   Otherwise, return a pointer to the first character not part of the number.
*/
static const char * getnum( const char * strp, int * nump, int min, int max )
{
    char c;
    int  num;

    if ( strp == NULL || ! isdigit( (unsigned char)( c = *strp ) ) )
    {
        return NULL;
    }

    num = 0;

    do
    {
        num = num * 10 + ( c - '0' );

        if ( num > max )
        {
            return NULL;    /* illegal value */
        }

        c = *++strp;
    } while ( isdigit( (unsigned char)c ) );

    if ( num < min )
    {
        return NULL;        /* illegal value */
    }

    *nump = num;
    return strp;
}

/* Given a pointer into a timezone string, extract a number of seconds,
   in hh[:mm[:ss]] form, from the string.
   If any error occurs, return NULL.
   Otherwise, return a pointer to the first character not part of the number
   of seconds.
*/
static const char * getsecs( const char * strp, int_fast32_t * secsp )
{
    int num;

    /* 'HOURSPERDAY * DAYSPERWEEK - 1' allows quasi-Posix rules like
       "M10.4.6/26", which does not conform to Posix,
       but which specifies the equivalent of
       "02:00 on the first Sunday on or after 23 Oct".
    */
    strp = getnum( strp, &num, 0, HOURSPERDAY * DAYSPERWEEK - 1 );

    if ( strp == NULL )
    {
        return NULL;
    }

    *secsp = num * (int_fast32_t) SECSPERHOUR;

    if ( *strp == ':' )
    {
        ++strp;
        strp = getnum( strp, &num, 0, MINSPERHOUR - 1 );

        if ( strp == NULL )
        {
            return NULL;
        }

        *secsp += num * SECSPERMIN;

        if ( *strp == ':' )
        {
            ++strp;
            /* 'SECSPERMIN' allows for leap seconds.  */
            strp = getnum( strp, &num, 0, SECSPERMIN );

            if ( strp == NULL )
            {
                return NULL;
            }

            *secsp += num;
        }
    }

    return strp;
}

/* Given a pointer into a timezone string, extract an offset, in
   [+-]hh[:mm[:ss]] form, from the string.
   If any error occurs, return NULL.
   Otherwise, return a pointer to the first character not part of the time.
*/
static const char * getoffset( const char * strp, int_fast32_t * offsetp )
{
    bool neg = false;

    if ( *strp == '-' )
    {
        neg = true;
        ++strp;
    }
    else if ( *strp == '+' )
    {
        ++strp;
    }

    strp = getsecs( strp, offsetp );

    if ( strp == NULL )
    {
        return NULL;        /* illegal time */
    }

    if ( neg )
    {
        *offsetp = - *offsetp;
    }

    return strp;
}

/* Given a pointer into a timezone string, extract a rule in the form
   date[/time]. See POSIX section 8 for the format of "date" and "time".
   If a valid rule is not found, return NULL.
   Otherwise, return a pointer to the first character not part of the rule.
*/
static const char * getrule( const char * strp, struct rule * rulep )
{
    if ( *strp == 'J' )
    {
        /* Julian day. */
        rulep->type = JULIAN_DAY;
        ++strp;
        strp = getnum( strp, &rulep->day, 1, DAYSPERNYEAR );
    }
    else if ( *strp == 'M' )
    {
        /* Month, week, day. */
        rulep->type = MONTH_NTH_DAY_OF_WEEK;
        ++strp;
        strp = getnum( strp, &rulep->mon, 1, MONSPERYEAR );

        if ( strp == NULL )
        {
            return NULL;
        }

        if ( *strp++ != '.' )
        {
            return NULL;
        }

        strp = getnum( strp, &rulep->week, 1, 5 );

        if ( strp == NULL )
        {
            return NULL;
        }

        if ( *strp++ != '.' )
        {
            return NULL;
        }

        strp = getnum( strp, &rulep->day, 0, DAYSPERWEEK - 1 );
    }
    else if ( isdigit( (unsigned char)*strp ) )
    {
        /* Day of year. */
        rulep->type = DAY_OF_YEAR;
        strp = getnum( strp, &rulep->day, 0, DAYSPERLYEAR - 1 );
    }
    else
    {
        return NULL;        /* invalid format */
    }

    if ( strp == NULL )
    {
        return NULL;
    }

    if ( *strp == '/' )
    {
        /* Time specified. */
        ++strp;
        strp = getoffset( strp, &rulep->time );
    }
    else
    {
        rulep->time = 2 * SECSPERHOUR;    /* default = 2:00:00 */
    }

    return strp;
}

/* Given a year, a rule, and the offset from UT at the time that rule takes
   effect, calculate the year-relative time that rule takes effect.
*/
static int_fast32_t transtime( const int year, struct rule const * rulep, const int_fast32_t offset )
{
    bool         leapyear;
    int_fast32_t value = 0;
    int          i;
    int          d;
    int          m1;
    int          yy0;
    int          yy1;
    int          yy2;
    int          dow;

    leapyear = _PDCLIB_is_leap( year );

    switch ( rulep->type )
    {
        case JULIAN_DAY:
            /* Jn - Julian day, 1 == January 1, 60 == March 1 even in leap
               years.
               In non-leap years, or if the day number is 59 or less, just
               add SECSPERDAY times the day number-1 to the time of
               January 1, midnight, to get the day.
            */
            value = ( rulep->day - 1 ) * SECSPERDAY;

            if ( leapyear && rulep->day >= 60 )
            {
                value += SECSPERDAY;
            }

            break;

        case DAY_OF_YEAR:
            /* n - day of year.
               Just add SECSPERDAY times the day number to the time of
               January 1, midnight, to get the day.
            */
            value = rulep->day * SECSPERDAY;
            break;

        case MONTH_NTH_DAY_OF_WEEK:
            /* Mm.n.d - nth "dth day" of month m.  */

            /* Use Zeller's Congruence to get day-of-week of first day of
               month.
            */
            m1 = ( rulep->mon + 9 ) % 12 + 1;
            yy0 = ( rulep->mon <= 2 ) ? ( year - 1 ) : year;
            yy1 = yy0 / 100;
            yy2 = yy0 % 100;
            dow = ( ( 26 * m1 - 2 ) / 10 + 1 + yy2 + yy2 / 4 + yy1 / 4 - 2 * yy1 ) % 7;

            if ( dow < 0 )
            {
                dow += DAYSPERWEEK;
            }

            /* "dow" is the day-of-week of the first day of the month. Get
               the day-of-month (zero-origin) of the first "dow" day of the
               month.
            */
            d = rulep->day - dow;

            if ( d < 0 )
            {
                d += DAYSPERWEEK;
            }

            for ( i = 1; i < rulep->week; ++i )
            {
                if ( d + DAYSPERWEEK >= mon_lengths[ leapyear ][ rulep->mon - 1 ] )
                {
                    break;
                }

                d += DAYSPERWEEK;
            }

            /* "d" is the day-of-month (zero-origin) of the day we want. */
            value = d * SECSPERDAY;

            for ( i = 0; i < rulep->mon - 1; ++i )
            {
                value += mon_lengths[ leapyear ][ i ] * SECSPERDAY;
            }

            break;
    }

    /* "value" is the year-relative time of 00:00:00 UT on the day in
       question. To get the year-relative time of the specified local
       time on that day, add the transition time and the current offset
       from UT.
    */
    return value + rulep->time + offset;
}

/* Given a pointer into a timezone string, scan until a character that is not
   a valid character in a time zone abbreviation is found.
   Return a pointer to that character.
*/
static const char * getzname( const char * strp )
{
    char c;

    while ( ( c = *strp ) != '\0' && ! isdigit( (unsigned char)c ) && c != ',' && c != '-' && c != '+' )
    {
        ++strp;
    }

    return strp;
}

/* Given a pointer into an extended timezone string, scan until the ending
   delimiter of the time zone abbreviation is located.
   Return a pointer to the delimiter.

   As with getzname above, the legal character set is actually quite
   restricted, with other characters producing undefined results.
   We don't do any checking here; checking is done later in common-case code.
*/
static const char * getqzname( const char *strp, const int delim )
{
    int c;

    while ( ( c = *strp ) != '\0' && c != delim )
    {
        ++strp;
    }

    return strp;
}

static bool increment_overflow_time( time_t * tp, int_fast32_t j )
{
    /* This is like
       'if (! (_PDCLIB_TIME_MIN <= *tp + j && *tp + j <= _PDCLIB_TIME_MAX)) ...',
       except that it does the right thing even if *tp + j would overflow.
    */
    if ( ! ( j < 0
           ? ( _PDCLIB_TYPE_SIGNED( time_t ) ? _PDCLIB_TIME_MIN - j <= *tp : -1 - j < *tp )
           : *tp <= _PDCLIB_TIME_MAX - j ) )
    {
        return true;
    }

    *tp += j;
    return false;
}

/* Given a POSIX section 8-style TZ string, fill in the rule tables as
   appropriate.
*/
bool _PDCLIB_tzparse( const char * name, struct state * sp, bool lastditch )
{
    const char * stdname;
    const char * dstname;
    size_t       stdlen;
    size_t       dstlen;
    size_t       charcnt;
    int_fast32_t stdoffset;
    int_fast32_t dstoffset;
    char *       cp;
    bool         load_ok;

    stdname = name;

    if ( lastditch )
    {
        stdlen = sizeof gmt - 1;
        name += stdlen;
        stdoffset = 0;
    }
    else
    {
        if ( *name == '<' )
        {
            name++;
            stdname = name;
            name = getqzname( name, '>' );

            if ( *name != '>' )
            {
                return false;
            }

            stdlen = name - stdname;
            name++;
        }
        else
        {
            name = getzname( name );
            stdlen = name - stdname;
        }

        if ( ! stdlen )
        {
            return false;
        }

        name = getoffset( name, &stdoffset );

        if ( name == NULL )
        {
            return false;
        }
    }

    charcnt = stdlen + 1;

    if ( sizeof sp->chars < charcnt )
    {
        return false;
    }

    load_ok = _PDCLIB_tzload( TZDEFRULES, sp, false ) == 0;

    if ( ! load_ok )
    {
        sp->leapcnt = 0;        /* so, we're off a little */
    }

    if ( *name != '\0' )
    {
        if ( *name == '<' )
        {
            dstname = ++name;
            name = getqzname( name, '>' );

            if ( *name != '>' )
            {
                return false;
            }

            dstlen = name - dstname;
            name++;
        }
        else
        {
            dstname = name;
            name = getzname( name );
            dstlen = name - dstname; /* length of DST abbr. */
        }

        if ( ! dstlen )
        {
            return false;
        }

        charcnt += dstlen + 1;

        if ( sizeof sp->chars < charcnt )
        {
            return false;
        }

        if ( *name != '\0' && *name != ',' && *name != ';' )
        {
            name = getoffset( name, &dstoffset );

            if ( name == NULL )
            {
                return false;
            }
        }
        else
        {
            dstoffset = stdoffset - SECSPERHOUR;
        }

        if ( *name == '\0' && ! load_ok )
        {
            name = TZDEFRULESTRING;
        }

        if ( *name == ',' || *name == ';' )
        {
            struct rule  start;
            struct rule  end;
            int          year;
            int          yearlim;
            int          timecnt;
            time_t       janfirst;
            int_fast32_t janoffset = 0;
            int          yearbeg;

            ++name;

            if ( ( name = getrule( name, &start ) ) == NULL )
            {
                return false;
            }

            if ( *name++ != ',' )
            {
                return false;
            }

            if ( ( name = getrule( name, &end ) ) == NULL )
            {
                return false;
            }

            if ( *name != '\0' )
            {
                return false;
            }

            sp->typecnt = 2;    /* standard time and DST */
            /* Two transitions per year, from EPOCH_YEAR forward. */
            _PDCLIB_init_ttinfo( &sp->ttis[ 0 ], -stdoffset, false, 0 );
            _PDCLIB_init_ttinfo( &sp->ttis[ 1 ], -dstoffset, true, stdlen + 1 );
            sp->defaulttype = 0;
            timecnt = 0;
            janfirst = 0;
            yearbeg = EPOCH_YEAR;

            do
            {
              int_fast32_t yearsecs = year_lengths[ _PDCLIB_is_leap( yearbeg - 1 ) ] * SECSPERDAY;
              yearbeg--;

              if ( increment_overflow_time( &janfirst, -yearsecs ) )
              {
                  janoffset = -yearsecs;
                  break;
              }
            } while ( EPOCH_YEAR - YEARSPERREPEAT / 2 < yearbeg );

            yearlim = yearbeg + YEARSPERREPEAT + 1;

            for ( year = yearbeg; year < yearlim; year++ )
            {
                int_fast32_t starttime = transtime( year, &start, stdoffset ), endtime = transtime( year, &end, dstoffset );
                int_fast32_t yearsecs = ( year_lengths[ _PDCLIB_is_leap( year ) ] * SECSPERDAY );
                bool reversed = endtime < starttime;

                if ( reversed )
                {
                    int_fast32_t swap = starttime;
                    starttime = endtime;
                    endtime = swap;
                }

                if ( reversed
                    || ( starttime < endtime
                    && ( endtime - starttime
                        < ( yearsecs
                           + ( stdoffset - dstoffset ) ) ) ) )
                {
                    if ( TZ_MAX_TIMES - 2 < timecnt )
                    {
                        break;
                    }

                    sp->ats[ timecnt ] = janfirst;

                    if ( ! increment_overflow_time( &sp->ats[ timecnt ], janoffset + starttime ) )
                    {
                        sp->types[ timecnt++ ] = ! reversed;
                    }

                    sp->ats[ timecnt ] = janfirst;

                    if ( ! increment_overflow_time( &sp->ats[ timecnt ], janoffset + endtime ) )
                    {
                        sp->types[ timecnt++ ] = reversed;
                        yearlim = year + YEARSPERREPEAT + 1;
                    }
                }

                if ( increment_overflow_time ( &janfirst, janoffset + yearsecs ) )
                {
                    break;
                }

                janoffset = 0;
            }

            sp->timecnt = timecnt;

            if ( ! timecnt )
            {
                sp->ttis[ 0 ] = sp->ttis[ 1 ];
                sp->typecnt = 1;    /* Perpetual DST.  */
            }
            else if ( YEARSPERREPEAT < year - yearbeg )
            {
                sp->goback = sp->goahead = true;
            }
        }
        else
        {
            int_fast32_t theirstdoffset;
            int_fast32_t theirdstoffset;
            int_fast32_t theiroffset;
            bool         isdst;
            int          i;
            int          j;

            if ( *name != '\0' )
            {
                return false;
            }

            /* Initial values of theirstdoffset and theirdstoffset. */
            theirstdoffset = 0;

            for ( i = 0; i < sp->timecnt; ++i )
            {
                j = sp->types[ i ];

                if ( ! sp->ttis[ j ].isdst )
                {
                    theirstdoffset = - sp->ttis[ j ].utoff;
                    break;
                }
            }

            theirdstoffset = 0;

            for ( i = 0; i < sp->timecnt; ++i )
            {
                j = sp->types[ i ];
                if ( sp->ttis[ j ].isdst )
                {
                    theirdstoffset = - sp->ttis[ j ].utoff;
                    break;
                }
            }

            /* Initially we're assumed to be in standard time. */
            isdst = false;
            theiroffset = theirstdoffset;

            /* Now juggle transition times and types
               tracking offsets as you do.
            */
            for ( i = 0; i < sp->timecnt; ++i )
            {
                j = sp->types[ i ];
                sp->types[ i ] = sp->ttis[ j ].isdst;

                if ( sp->ttis[ j ].ttisut )
                {
                    /* No adjustment to transition time */
                }
                else
                {
                    /* If daylight saving time is in
                       effect, and the transition time was
                       not specified as standard time, add
                       the daylight saving time offset to
                       the transition time; otherwise, add
                       the standard time offset to the
                       transition time.
                    */
                    /* Transitions from DST to DDST
                       will effectively disappear since
                       POSIX provides for only one DST
                       offset.
                    */
                    if ( isdst && ! sp->ttis[ j ].ttisstd )
                    {
                        sp->ats[ i ] += dstoffset - theirdstoffset;
                    }
                    else
                    {
                        sp->ats[ i ] += stdoffset - theirstdoffset;
                    }
                }

                theiroffset = -sp->ttis[ j ].utoff;
                if ( sp->ttis[ j ].isdst )
                {
                    theirdstoffset = theiroffset;
                }
                else
                {
                    theirstdoffset = theiroffset;
                }
            }

            /* Finally, fill in ttis. */
            _PDCLIB_init_ttinfo( &sp->ttis[ 0 ], -stdoffset, false, 0 );
            _PDCLIB_init_ttinfo( &sp->ttis[ 1 ], -dstoffset, true, stdlen + 1 );
            sp->typecnt = 2;
            sp->defaulttype = 0;
        }
    }
    else
    {
        dstlen = 0;
        sp->typecnt = 1;        /* only standard time */
        sp->timecnt = 0;
        _PDCLIB_init_ttinfo( &sp->ttis[ 0 ], -stdoffset, false, 0 );
        sp->defaulttype = 0;
    }

    sp->charcnt = charcnt;
    cp = sp->chars;
    memcpy( cp, stdname, stdlen );
    cp += stdlen;
    *cp++ = '\0';

    if ( dstlen != 0 )
    {
        memcpy( cp, dstname, dstlen );
        *( cp + dstlen ) = '\0';
    }

    return true;
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
