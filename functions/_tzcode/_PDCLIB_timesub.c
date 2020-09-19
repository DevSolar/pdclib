/* _PDCLIB_timesub( const time_t *, int_fast32_t, const struct state *, struct tm * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

/* Return the number of leap years through the end of the given year
   where, to make the math easy, the answer for year zero is defined as zero.
*/
static int leaps_thru_end_of_nonneg( int y )
{
    return y / 4 - y / 100 + y / 400;
}

static int leaps_thru_end_of( const int y )
{
    return ( y < 0
        ? -1 - leaps_thru_end_of_nonneg( -1 - y )
        : leaps_thru_end_of_nonneg( y ) );
}

struct tm * _PDCLIB_timesub( const time_t * timep, int_fast32_t offset, const struct state * sp, struct tm * tmp )
{
    const struct lsinfo * lp;
    time_t                tdays;
    int                   idays;  /* unsigned would be so 2003 */
    int_fast64_t          rem;
    int                   y;
    const int *           ip;
    int_fast64_t          corr;
    bool                  hit;
    int                   i;

    corr = 0;
    hit = false;
    i = ( sp == NULL ) ? 0 : sp->leapcnt;

    while ( --i >= 0 )
    {
        lp = &sp->lsis[ i ];
        if ( *timep >= lp->trans )
        {
            corr = lp->corr;
            hit = ( *timep == lp->trans && ( i == 0 ? 0 : lp[ -1 ].corr ) < corr );
            break;
        }
    }

    y = EPOCH_YEAR;
    tdays = *timep / SECSPERDAY;
    rem = *timep % SECSPERDAY;

    while ( tdays < 0 || tdays >= year_lengths[ _PDCLIB_is_leap( y ) ] )
    {
        int    newy;
        time_t tdelta;
        int    idelta;
        int    leapdays;

        tdelta = tdays / DAYSPERLYEAR;

        if ( ! ( ( ! _PDCLIB_TYPE_SIGNED( time_t ) || _PDCLIB_INT_MIN <= tdelta ) && tdelta <= _PDCLIB_INT_MAX ) )
        {
            goto out_of_range;
        }

        idelta = tdelta;

        if ( idelta == 0 )
        {
            idelta = ( tdays < 0 ) ? -1 : 1;
        }

        newy = y;

        if ( _PDCLIB_increment_overflow( &newy, idelta ) )
        {
            goto out_of_range;
        }

        leapdays = leaps_thru_end_of( newy - 1 ) - leaps_thru_end_of( y - 1 );
        tdays -= ( (time_t)newy - y ) * DAYSPERNYEAR;
        tdays -= leapdays;
        y = newy;
    }

    /* Given the range, we can now fearlessly cast... */
    idays = tdays;
    rem += offset - corr;

    while ( rem < 0 )
    {
        rem += SECSPERDAY;
        --idays;
    }

    while ( rem >= SECSPERDAY )
    {
        rem -= SECSPERDAY;
        ++idays;
    }

    while ( idays < 0 )
    {
        if ( _PDCLIB_increment_overflow( &y, -1 ) )
        {
            goto out_of_range;
        }

        idays += year_lengths[ _PDCLIB_is_leap( y ) ];
    }

    while ( idays >= year_lengths[ _PDCLIB_is_leap( y ) ] )
    {
        idays -= year_lengths[ _PDCLIB_is_leap( y ) ];

        if ( _PDCLIB_increment_overflow( &y, 1 ) )
        {
            goto out_of_range;
        }
    }

    tmp->tm_year = y;

    if ( _PDCLIB_increment_overflow( &tmp->tm_year, -TM_YEAR_BASE ) )
    {
        goto out_of_range;
    }

    tmp->tm_yday = idays;
    /* The "extra" mods below avoid overflow problems. */
    tmp->tm_wday = EPOCH_WDAY +
        ( ( y - EPOCH_YEAR ) % DAYSPERWEEK ) *
        ( DAYSPERNYEAR % DAYSPERWEEK ) +
        leaps_thru_end_of( y - 1 ) -
        leaps_thru_end_of( EPOCH_YEAR - 1 ) +
        idays;
    tmp->tm_wday %= DAYSPERWEEK;

    if ( tmp->tm_wday < 0 )
    {
        tmp->tm_wday += DAYSPERWEEK;
    }

    tmp->tm_hour = (int)( rem / SECSPERHOUR );
    rem %= SECSPERHOUR;
    tmp->tm_min = (int)( rem / SECSPERMIN );

    /* A positive leap second requires a special
       representation. This uses "... ??:59:60" et seq.
    */
    tmp->tm_sec = (int) ( rem % SECSPERMIN ) + hit;
    ip = mon_lengths[ _PDCLIB_is_leap( y ) ];

    for ( tmp->tm_mon = 0; idays >= ip[ tmp->tm_mon ]; ++( tmp->tm_mon ) )
    {
        idays -= ip[ tmp->tm_mon ];
    }

    tmp->tm_mday = (int)( idays + 1 );
    tmp->tm_isdst = 0;
#ifdef TM_GMTOFF
    tmp->TM_GMTOFF = offset;
#endif /* defined TM_GMTOFF */
    return tmp;

 out_of_range:
    *_PDCLIB_errno_func() = _PDCLIB_EOVERFLOW;
    return NULL;
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
