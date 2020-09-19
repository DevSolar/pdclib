/* _PDCLIB_mktime_tzname( struct state *, struct tm *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

/* Adapted from code provided by Robert Elz, who writes:
    The "best" way to do mktime I think is based on an idea of Bob
    Kridle's (so its said...) from a long time ago.
    It does a binary search of the time_t space. Since time_t's are
    just 32 bits, its a max of 32 iterations (even at 64 bits it
    would still be very reasonable).
*/

#ifndef WRONG
#define WRONG   (-1)
#endif

/* Normalize logic courtesy Paul Eggert. */

static bool increment_overflow32( int_fast32_t * lp, int m )
{
    int_fast32_t const l = *lp;

    if ( ( l >= 0 ) ? ( m > _PDCLIB_INT_FAST32_MAX - l ) : ( m < _PDCLIB_INT_FAST32_MIN - l ) )
    {
        return true;
    }

    *lp += m;
    return false;
}

static bool normalize_overflow( int * tensptr, int * unitsptr, int base )
{
    int tensdelta;

    tensdelta = ( *unitsptr >= 0 ) ?
        ( *unitsptr / base ) :
        ( -1 - ( -1 - *unitsptr ) / base );
    *unitsptr -= tensdelta * base;
    return _PDCLIB_increment_overflow( tensptr, tensdelta );
}

static bool normalize_overflow32( int_fast32_t * tensptr, int * unitsptr, int base )
{
    int tensdelta;

    tensdelta = ( *unitsptr >= 0 ) ?
        ( *unitsptr / base ) :
        ( -1 - ( -1 - *unitsptr ) / base );
    *unitsptr -= tensdelta * base;
    return increment_overflow32( tensptr, tensdelta );
}

static int tmcomp( const struct tm * atmp, const struct tm * btmp )
{
    int result;

    if ( atmp->tm_year != btmp->tm_year )
    {
        return atmp->tm_year < btmp->tm_year ? -1 : 1;
    }

    if ( ( result = ( atmp->tm_mon - btmp->tm_mon ) ) == 0 &&
         ( result = ( atmp->tm_mday - btmp->tm_mday ) ) == 0 &&
         ( result = ( atmp->tm_hour - btmp->tm_hour ) ) == 0 &&
         ( result = ( atmp->tm_min - btmp->tm_min ) ) == 0 )
    {
        result = atmp->tm_sec - btmp->tm_sec;
    }

    return result;
}

static time_t time2sub( struct tm * tmp, struct tm *(*funcp)( struct state const *, time_t const *, int_fast32_t, struct tm * ), struct state const * sp, const int_fast32_t offset, bool * okayp, bool do_norm_secs )
{
    int          dir;
    int          i, j;
    int          saved_seconds;
    int_fast32_t li;
    time_t       lo;
    time_t       hi;
    int_fast32_t y;
    time_t       newt;
    time_t       t;
    struct tm    yourtm, mytm;

    *okayp = false;
    yourtm = *tmp;

    if ( do_norm_secs )
    {
        if ( normalize_overflow( &yourtm.tm_min, &yourtm.tm_sec, SECSPERMIN ) )
        {
            return WRONG;
        }
    }

    if ( normalize_overflow( &yourtm.tm_hour, &yourtm.tm_min, MINSPERHOUR ) )
    {
        return WRONG;
    }

    if ( normalize_overflow( &yourtm.tm_mday, &yourtm.tm_hour, HOURSPERDAY ) )
    {
        return WRONG;
    }

    y = yourtm.tm_year;

    if ( normalize_overflow32( &y, &yourtm.tm_mon, MONSPERYEAR ) )
    {
        return WRONG;
    }

    /* Turn y into an actual year number for now.
       It is converted back to an offset from TM_YEAR_BASE later.
    */
    if ( increment_overflow32( &y, TM_YEAR_BASE ) )
    {
        return WRONG;
    }

    while ( yourtm.tm_mday <= 0 )
    {
        if ( increment_overflow32( &y, -1 ) )
        {
            return WRONG;
        }

        li = y + ( 1 < yourtm.tm_mon );
        yourtm.tm_mday += year_lengths[ _PDCLIB_is_leap( li ) ];
    }
    while ( yourtm.tm_mday > DAYSPERLYEAR )
    {
        li = y + ( 1 < yourtm.tm_mon );
        yourtm.tm_mday -= year_lengths[ _PDCLIB_is_leap( li ) ];

        if ( increment_overflow32( &y, 1 ) )
        {
            return WRONG;
        }
    }

    for ( ; ; )
    {
        i = mon_lengths[ _PDCLIB_is_leap( y ) ][ yourtm.tm_mon ];

        if ( yourtm.tm_mday <= i )
        {
            break;
        }

        yourtm.tm_mday -= i;

        if ( ++yourtm.tm_mon >= MONSPERYEAR )
        {
            yourtm.tm_mon = 0;

            if ( increment_overflow32( &y, 1 ) )
            {
                return WRONG;
            }
        }
    }

    if ( increment_overflow32( &y, -TM_YEAR_BASE ) )
    {
        return WRONG;
    }

    if ( ! ( _PDCLIB_INT_MIN <= y && y <= _PDCLIB_INT_MAX ) )
    {
        return WRONG;
    }

    yourtm.tm_year = y;

    if ( yourtm.tm_sec >= 0 && yourtm.tm_sec < SECSPERMIN )
    {
        saved_seconds = 0;
    }
    else if ( y + TM_YEAR_BASE < EPOCH_YEAR )
    {
        /* We can't set tm_sec to 0, because that might push the
           time below the minimum representable time.
           Set tm_sec to 59 instead.
           This assumes that the minimum representable time is
           not in the same minute that a leap second was deleted from,
           which is a safer assumption than using 58 would be.
        */
        if ( _PDCLIB_increment_overflow( &yourtm.tm_sec, 1 - SECSPERMIN ) )
        {
            return WRONG;
        }

        saved_seconds = yourtm.tm_sec;
        yourtm.tm_sec = SECSPERMIN - 1;
    }
    else
    {
        saved_seconds = yourtm.tm_sec;
        yourtm.tm_sec = 0;
    }

    /* Do a binary search (this works whatever time_t's type is). */
    lo = _PDCLIB_TIME_MIN;
    hi = _PDCLIB_TIME_MAX;

    for ( ; ; )
    {
        t = lo / 2 + hi / 2;

        if ( t < lo )
        {
            t = lo;
        }
        else if ( t > hi )
        {
            t = hi;
        }

        if ( ! funcp( sp, &t, offset, &mytm ) )
        {
            /* Assume that t is too extreme to be represented in
               a struct tm; arrange things so that it is less
               extreme on the next pass.
            */
            dir = ( t > 0 ) ? 1 : -1;
        }
        else
        {
            dir = tmcomp( &mytm, &yourtm );
        }

        if ( dir != 0 )
        {
            if ( t == lo )
            {
                if ( t == _PDCLIB_TIME_MAX )
                {
                    return WRONG;
                }

                ++t;
                ++lo;
            }
            else if ( t == hi )
            {
                if ( t == _PDCLIB_TIME_MIN )
                {
                    return WRONG;
                }

                --t;
                --hi;
            }

            if ( lo > hi )
            {
                return WRONG;
            }

            if ( dir > 0 )
            {
                hi = t;
            }
            else
            {
                lo = t;
            }

            continue;
        }

#if defined TM_GMTOFF && ! UNINIT_TRAP
        if ( mytm.TM_GMTOFF != yourtm.TM_GMTOFF
            && ( yourtm.TM_GMTOFF < 0
            ? ( -SECSPERDAY <= yourtm.TM_GMTOFF
               && ( mytm.TM_GMTOFF <=
                   ( SMALLEST ( _PDCLIB_INT_FAST32_MAX, _PDCLIB_LONG_MAX )
                + yourtm.TM_GMTOFF ) ) )
            : ( yourtm.TM_GMTOFF <= SECSPERDAY
               && ( ( BIGGEST ( _PDCLIB_INT_FAST32_MIN, _PDCLIB_LONG_MIN )
                + yourtm.TM_GMTOFF )
                   <= mytm.TM_GMTOFF ) ) ) )
        {
            /* MYTM matches YOURTM except with the wrong UT offset.
               YOURTM.TM_GMTOFF is plausible, so try it instead.
               It's OK if YOURTM.TM_GMTOFF contains uninitialized data,
               since the guess gets checked.
            */
            time_t altt = t;
            int_fast32_t diff = mytm.TM_GMTOFF - yourtm.TM_GMTOFF;

            if ( ! increment_overflow_time( &altt, diff ) )
            {
                struct tm alttm;
                if ( funcp( sp, &altt, offset, &alttm )
                    && alttm.tm_isdst == mytm.tm_isdst
                    && alttm.TM_GMTOFF == yourtm.TM_GMTOFF
                    && tmcomp( &alttm, &yourtm ) == 0 )
                {
                    t = altt;
                    mytm = alttm;
                }
            }
        }
#endif

        if ( yourtm.tm_isdst < 0 || mytm.tm_isdst == yourtm.tm_isdst )
        {
            break;
        }

        /* Right time, wrong type.
           Hunt for right time, right type.
           It's okay to guess wrong since the guess
           gets checked.
        */
        if ( sp == NULL )
        {
            return WRONG;
        }

        for ( i = sp->typecnt - 1; i >= 0; --i )
        {
            if ( sp->ttis[ i ].isdst != yourtm.tm_isdst )
            {
                continue;
            }

            for ( j = sp->typecnt - 1; j >= 0; --j )
            {
                if ( sp->ttis[ j ].isdst == yourtm.tm_isdst )
                {
                    continue;
                }

                newt = ( t + sp->ttis[ j ].utoff - sp->ttis[ i ].utoff );

                if ( ! funcp( sp, &newt, offset, &mytm ) )
                {
                    continue;
                }

                if ( tmcomp( &mytm, &yourtm ) != 0 )
                {
                    continue;
                }

                if ( mytm.tm_isdst != yourtm.tm_isdst )
                {
                    continue;
                }

                /* We have a match. */
                t = newt;
                goto label;
            }
        }

        return WRONG;
    }

label:
    newt = t + saved_seconds;

    if ( ( newt < t ) != ( saved_seconds < 0 ) )
    {
        return WRONG;
    }

    t = newt;

    if ( funcp( sp, &t, offset, tmp ) )
    {
        *okayp = true;
    }

    return t;
}

static time_t time2( struct tm * tmp, struct tm *(*funcp)( struct state const *, time_t const *, int_fast32_t, struct tm * ), struct state const * sp, const int_fast32_t offset, bool * okayp )
{
    time_t t;

    /* First try without normalization of seconds
       (in case tm_sec contains a value associated with a leap second).
       If that fails, try with normalization of seconds.
    */
    t = time2sub( tmp, funcp, sp, offset, okayp, false );
    return *okayp ? t : time2sub( tmp, funcp, sp, offset, okayp, true );
}

static time_t time1( struct tm * tmp, struct tm *(*funcp)( struct state const *, time_t const *, int_fast32_t, struct tm * ), struct state const * sp, const int_fast32_t offset )
{
    time_t        t;
    int           samei, otheri;
    int           sameind, otherind;
    int           i;
    int           nseen;
    char          seen[TZ_MAX_TYPES];
    unsigned char types[TZ_MAX_TYPES];
    bool          okay;

    if ( tmp == NULL )
    {
        *_PDCLIB_errno_func() = _PDCLIB_EINVAL;
        return WRONG;
    }

    if ( tmp->tm_isdst > 1 )
    {
        tmp->tm_isdst = 1;
    }

    t = time2( tmp, funcp, sp, offset, &okay );

    if ( okay )
    {
        return t;
    }

    if ( tmp->tm_isdst < 0 )
    {
#ifdef PCTS
        /* POSIX Conformance Test Suite code courtesy Grant Sullivan. */
        tmp->tm_isdst = 0;  /* reset to std and try again */
#else
        return t;
#endif
    }

    /* We're supposed to assume that somebody took a time of one type
       and did some math on it that yielded a "struct tm" that's bad.
       We try to divine the type they started from and adjust to the
       type they need.
    */
    if ( sp == NULL )
    {
        return WRONG;
    }

    for ( i = 0; i < sp->typecnt; ++i )
    {
        seen[ i ] = false;
    }

    nseen = 0;

    for ( i = sp->timecnt - 1; i >= 0; --i )
    {
        if ( ! seen[ sp->types[ i ] ] )
        {
            seen[ sp->types[ i ] ] = true;
            types[ nseen++ ] = sp->types[ i ];
        }
    }

    for ( sameind = 0; sameind < nseen; ++sameind )
    {
        samei = types[ sameind ];

        if ( sp->ttis[ samei ].isdst != tmp->tm_isdst )
        {
            continue;
        }

        for ( otherind = 0; otherind < nseen; ++otherind )
        {
            otheri = types[ otherind ];

            if ( sp->ttis[ otheri ].isdst == tmp->tm_isdst )
            {
                continue;
            }

            tmp->tm_sec += ( sp->ttis[ otheri ].utoff - sp->ttis[ samei ].utoff );
            tmp->tm_isdst = ! tmp->tm_isdst;
            t = time2( tmp, funcp, sp, offset, &okay );

            if ( okay )
            {
                return t;
            }

            tmp->tm_sec -= ( sp->ttis[ otheri ].utoff - sp->ttis[ samei ].utoff );
            tmp->tm_isdst = ! tmp->tm_isdst;
        }
    }

    return WRONG;
}

time_t _PDCLIB_mktime_tzname( struct state * sp, struct tm * tmp, bool setname )
{
    if ( sp )
    {
        return time1( tmp, _PDCLIB_localsub, sp, setname );
    }
    else
    {
        _PDCLIB_gmtcheck();
        return time1( tmp, _PDCLIB_gmtsub, &_PDCLIB_gmtmem, 0 );
    }
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
