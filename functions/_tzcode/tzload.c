/* tzload( char const *, struct state *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define _DEFAULT_SOURCE

#include "_PDCLIB_tzcode.h"

#include "_PDCLIB_config.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef TEST
/* For test purposes, make epoch bias a modifiable value, and reduce the
   _PDCLIB_TIME_MIN / _PDCLIB_TIME_MAX range to small values known to fit
   into any time_t definition.
*/
#undef _PDCLIB_EPOCH_BIAS
#undef _PDCLIB_TIME_MIN
#undef _PDCLIB_TIME_MAX
int_fast64_t _PDCLIB_EPOCH_BIAS;
#define _PDCLIB_TIME_MIN -128
#define _PDCLIB_TIME_MAX 127
#endif

#define SECSPERDAY ((int_fast32_t)24 * 60 * 60)

/* A "repeat" means the 400-year cycle of the Gregorian calendar. Over the
   duration of a repeat, a year averages 365.2425 days, which is 31556952
   seconds.
*/
#define AVGSECSPERYEAR     INT64_C( 31556952 )
#define SECSPERREPEAT      (400 * AVGSECSPERYEAR)
/* The number of bits required to store SECSPERREPEAT */
#define SECSPERREPEAT_BITS 34

#define TIME_T_LESS_THAN_INT64 ( _PDCLIB_TIME_MIN <= - INT64_C( 0x7fffffffffffffff ) && _PDCLIB_TIME_MAX >= INT64_C( 0x7fffffffffffffff ) )

static FILE * tzopen( char const * name )
{
    char * fullname;
    FILE * rc;

    if ( name == NULL )
    {
        name = _PDCLIB_TZDEFAULT;

        if ( name == NULL )
        {
            errno = EINVAL;
            return NULL;
        }
    }

    if ( name[0] == ':' )
    {
        ++name;
    }

    if ( name[0] == '/' )
    {
        fullname = (char *)name;
    }
    else
    {
        if ( ( fullname = (char *)malloc( strlen( name ) + sizeof( _PDCLIB_TZDIR ) + 1 ) ) == NULL )
        {
            errno = ENOMEM;
            return NULL;
        }

        strcpy( fullname, _PDCLIB_TZDIR );
        strcat( fullname, name );
    }

    rc = fopen( fullname, "rb" );

    if ( fullname != name )
    {
        free( fullname );
    }

    return rc;
}

enum width_t
{
    E_UCHAR = 1,
    E_INT32 = 4,
    E_INT64 = 8
};

static int_fast64_t tzread_val( enum width_t width, FILE * tzfile )
{
    int_fast64_t rc = 0;
    unsigned char in[ width ];

    if ( fread( in, 1, width, tzfile ) == width )
    {
        int i;

        if ( width == E_UCHAR )
        {
            return in[0];
        }

        /* Read network order (big-endian), masking out negative bit. */
        rc = in[0] & 0x7f;

        for ( i = 1; i < width; ++i )
        {
            rc = ( rc << 8 ) | ( in[i] & 0xff );
        }

        /* File data is encoded in two's complement. We ensure that we get
           correct negative values even on non-two's-complement machines.
        */
        if ( in[0] & 0x80 )
        {
            /* This is INTn_MIN on one's complement and signed magnitude,
               and (INTn_MIN + 1) on two's complement; "minval" in the sense
               that it's the minimum value that can be represented on any
               architecture.
            */
            int_fast64_t const minval = ( ( width == 4 ) ? INT32_C( 0x7fffffff ) : INT64_C( 0x7fffffffffffffff ) ) * -1;

            /* Two's complement negation would be to substract INTn_MIN from rc.
               We substract the minval calculated above, and then substract one
               more *if it can be represented in n bits on this architecture*.
               This is always true on two's complement, and true on the other
               architectures if rc is not zero.
               Strictly speaking, two's complement INTn_MIN *would* be
               representable on non-two's-complement as well if CHAR_BITS > 8,
               but there's a limit to the complexity I'm willing to add here
               for that case. The basis for this implementation, tzcode, does
               not handle the case either.
            */
            rc += minval - ( _PDCLIB_TWOS_COMPLEMENT || rc > 0 );
        }
    }

    return rc;
}

/* Returns -1 if value < _PDCLIB_TIME_MIN, 1 if value > _PDCLIB_TIME_MAX,
   and 0 if value representable by time_t has been read.
*/
static int tzread_time( time_t * time, FILE * tzfile )
{
    int_fast64_t val = tzread_val( E_INT64, tzfile );

    /* Avoid overflow when adding bias to (Unix time) value read from file. */
    if ( _PDCLIB_EPOCH_BIAS >= 0 )
    {
        if ( val > ( _PDCLIB_TIME_MAX - _PDCLIB_EPOCH_BIAS ) )
        {
            *time = _PDCLIB_TIME_MAX;
            return 1;
        }

        if ( ( val + _PDCLIB_EPOCH_BIAS ) < _PDCLIB_TIME_MIN )
        {
            *time = _PDCLIB_TIME_MIN;
            return -1;
        }
    }
    else /* _PDCLIB_EPOCH_BIAS < 0 */
    {
        if ( val < ( _PDCLIB_TIME_MIN - _PDCLIB_EPOCH_BIAS ) )
        {
            *time = _PDCLIB_TIME_MIN;
            return -1;
        }

        if ( ( val + _PDCLIB_EPOCH_BIAS ) > _PDCLIB_TIME_MAX )
        {
            *time = _PDCLIB_TIME_MAX;
            return 1;
        }
    }

    *time = val + _PDCLIB_EPOCH_BIAS;
    return 0;
}

static void free_tzdata( struct tzdata_t * data )
{
    free( data->transition );
    free( data->type );
    free( data->designations );
    free( data->leapsecond );
    free( data );
}

static void tzread_extension( struct tzdata_t * data, FILE * fh )
{
    long start;
    long end;
    char * buffer;

    if ( fgetc( fh ) != '\n' )
    {
        return;
    }

    start = ftell( fh );

    while ( ! feof( fh ) && ( fgetc( fh ) != '\n' ) )
    {
        /* EMPTY */
    }

    if ( feof( fh ) )
    {
        /* No complete extension found. */
        return;
    }

    end = ftell( fh );

    if ( ( buffer = (char *)malloc( end - start ) ) == NULL )
    {
        /* No memory. */
        return;
    }

    if ( fseek( fh, start, SEEK_SET ) != 0 )
    {
        /* I/O error. */
        return;
    }

    fgets( buffer, end - start, fh );

#if 0
    /* FIXME: tzparse() not yet implemented. */
    if ( tzparse( buffer, data, false ) )
    {
        /* TODO */
    }
#endif
}

static struct tzdata_t * tzread_data( FILE * fh )
{
    struct tzdata_t * data;
    char magic[4];
    char reserved[15];
    int_fast32_t i;
    int_fast32_t idx;

    /* These two counts are only needed during the actual read. The other
       counts are stored in the tzdata_t structure.
    */
    int_fast32_t isutcnt;
    int_fast32_t isstdcnt;

    /* magic */
    if ( fread( magic, 1, 4, fh ) != 4 || memcmp( magic, "TZif", 4 ) != 0 )
    {
        errno = EINVAL;
        return NULL;
    }

    /* version -- \0, '2', or '3' */
    if ( tzread_val( E_UCHAR, fh ) < '2' )
    {
        /* Minimum required version is version 2 (64-bit time values). */
        errno = EINVAL;
        return NULL;
    }

    /* reserved */
    if ( fread( reserved, 1, 15, fh ) != 15 )
    {
        errno = EINVAL;
        return NULL;
    }

    if ( ( data = (struct tzdata_t *)calloc( 1, sizeof( struct tzdata_t ) ) ) == NULL )
    {
        /* Memory allocation failed */
        errno = ENOMEM;
        return NULL;
    }

    /* counts */
    isutcnt  = tzread_val( E_INT32, fh );
    isstdcnt = tzread_val( E_INT32, fh );

    data->leapcnt = tzread_val( E_INT32, fh );
    data->timecnt = tzread_val( E_INT32, fh );
    data->typecnt = tzread_val( E_INT32, fh );
    data->charcnt = tzread_val( E_INT32, fh );

    /* Skip v1 data block
       (timecnt * 4)       transition times
       (timecnt)           transition types
       (typecnt * 6)       local time type records
       (charcnt)           time zone designations
       (leapcnt * (4 + 4)) leap-second records
       (isstdcnt)          standard/wall indicators
       (isutcnt)           UT/local indicators
    */
    if ( fseek( fh, (data->timecnt * 5) + (data->typecnt * 6) + data->charcnt + (data->leapcnt * 8) + isstdcnt + isutcnt, SEEK_CUR ) != 0 )
    {
        free_tzdata( data );
        errno = EINVAL;
        return NULL;
    }

    /* magic, v2 */
    if ( fread( magic, 1, 4, fh ) != 4 || memcmp( magic, "TZif", 4 ) != 0 )
    {
        free_tzdata( data );
        errno = EINVAL;
        return NULL;
    }

    /* version -- '2' or '3' (we ruled out version 1 above) */
    data->ver = tzread_val( E_UCHAR, fh );

    /* reserved */
    if ( fread( reserved, 1, 15, fh ) != 15 )
    {
        errno = EINVAL;
        return NULL;
    }

    /* counts */
    isutcnt  = tzread_val( E_INT32, fh );
    isstdcnt = tzread_val( E_INT32, fh );

    data->leapcnt = tzread_val( E_INT32, fh );
    data->timecnt = tzread_val( E_INT32, fh );
    data->typecnt = tzread_val( E_INT32, fh );
    data->charcnt = tzread_val( E_INT32, fh );

    /* Allocating memory */
    data->transition = (struct transition_t *)calloc( data->timecnt, sizeof( struct transition_t ) );
    data->type = (struct type_t *)calloc( data->typecnt, sizeof( struct type_t ) );
    data->leapsecond = (struct leapsecond_t *)calloc( data->leapcnt, sizeof( struct leapsecond_t ) );
    data->designations = (char *)malloc( data->charcnt );

    if ( data->transition == NULL || data->type == NULL || data->leapsecond == NULL || data->designations == NULL )
    {
        free_tzdata( data );
        errno = ENOMEM;
        return NULL;
    }

    /* We check each time stamp in the file against the value range of
       time_t. (Values in the file are 64 bit, time_t might be less, or
       have a different epoch.)
       Values too large are dropped wholesale. The last of the too-small
       values gets floor()ed to the minimum representable value, so we
       "enter" valid value ranges with a defined state. To store the
       information which entries were in range or not (for when we read
       in type information in the next loop and have to drop the same
       indices as in this one), we temporarily use transition_t.typeidx
       as bool.
       i is the file entry index, idx the stored timestamp index.
    */
    for ( i = 0, idx = 0; i < data->timecnt; ++i )
    {
        time_t time;

        if ( ( data->transition[ i ].typeidx = tzread_time( &time, fh ) ) < 1 )
        {
            if ( idx > 0 )
            {
                /* Sanity check. */
                if ( time < data->transition[ idx - 1 ].time )
                {
                    free_tzdata( data );
                    errno = EINVAL;
                    return NULL;
                }

                /* Using the last entry floor()ed to _PDCLIB_TIME_MIN
                   by tzread_time() as idx zero.
                */
                if ( time == data->transition[ idx - 1 ].time )
                {
                    data->transition[ i - 1 ].typeidx = -1;
                    --idx;
                }
            }

            data->transition[ idx++ ].time = time;
        }
    }

    /* Now read the type indices corresponding to the timestamps that
       checked out OK in the loop above.
    */
    for ( i = 0, idx = 0; i < data->timecnt; ++i )
    {
        unsigned char type = tzread_val( E_UCHAR, fh );

        /* Sanity check. */
        if ( type > data->typecnt )
        {
            free_tzdata( data );
            errno = EINVAL;
            return NULL;
        }

        if ( data->transition[ i ].typeidx == 0 )
        {
            data->transition[ idx++ ].typeidx = type;
        }
    }

    /* TODO: data->timecnt versus idx -- realloc */
    data->timecnt = idx;

    /* Read transition type info -- UT offset, DST, designation index */
    for ( i = 0; i < data->typecnt; ++i )
    {
        data->type[i].utoff = tzread_val( E_INT32, fh );

        /* Sanity check -- expecting bool */
        if ( ( data->type[i].isdst = tzread_val( E_UCHAR, fh ) ) > 1 )
        {
            free_tzdata( data );
            errno = EINVAL;
            return NULL;
        }

        /* Sanity check -- should be a pointer into designations array */
        if ( ( data->type[i].desigidx = tzread_val( E_UCHAR, fh ) ) >= data->charcnt )
        {
            free_tzdata( data );
            errno = EINVAL;
            return NULL;
        }
    }

    /* Read designations array */
    fread( data->designations, 1, data->charcnt, fh );

    /* Read leap second entries, again checking timestamps against time_t
       value range.
    */
    for ( i = 0, idx = 0; i < data->leapcnt; ++i )
    {
        time_t time;

        if ( tzread_time( &time, fh ) == 0 )
        {
            /* Sanity check -- no leap seconds before Unix epoch (1970) */
            if ( time < _PDCLIB_EPOCH_BIAS )
            {
                free_tzdata( data );
                errno = EINVAL;
                return NULL;
            }

            data->leapsecond[ idx ].occur = time;
            data->leapsecond[ idx ].corr = tzread_val( E_INT32, fh );
            ++idx;
        }
    }

    /* TODO: data->leapcnt versus idx -- realloc */
    data->leapcnt = idx;

    /* Read isstd flags */
    for ( i = 0; i < isstdcnt; ++i )
    {
        /* Sanity check -- expecting bool */
        if ( ( data->type[i].isstd = tzread_val( E_UCHAR, fh ) ) > 1 )
        {
            free_tzdata( data );
            errno = EINVAL;
            return NULL;
        }
    }

    /* Read isut flags */
    for ( i = 0; i < isutcnt; ++i )
    {
        /* Sanity check -- expecting bool */
        if ( ( data->type[i].isut = tzread_val( E_UCHAR, fh ) ) > 1 )
        {
            free_tzdata( data );
            errno = EINVAL;
            return NULL;
        }
    }

    return data;
}

static bool typesequiv( struct tzdata_t const * data, int_fast32_t a, int_fast32_t b )
{
    if ( data == NULL || a < 0 || a >= data->typecnt || b < 0 || b >= data->typecnt )
    {
        return false;
    }

    struct type_t const * type_a = &data->type[ a ];
    struct type_t const * type_b = &data->type[ b ];

    return type_a->utoff == type_b->utoff &&
           type_a->isdst == type_b->isdst &&
           type_a->isstd == type_b->isstd &&
           type_a->isut  == type_b->isut  &&
           ( strcmp( &data->designations[ type_a->desigidx ], &data->designations[ type_b->desigidx ] ) == 0 );
}

static bool differ_by_repeat( time_t const t1, time_t const t0 )
{
    if ( ( sizeof( time_t ) * CHAR_BIT ) < SECSPERREPEAT_BITS )
    {
        return 0;
    }

    return t1 - t0 == SECSPERREPEAT;
}

/* Setting goback, goahead, and defaulttype fields based on file data. */
static void tzdata_complete( struct tzdata_t * data )
{
    int_fast32_t i;

    if ( data->timecnt > 1 )
    {
        for ( i = 1; i < data->timecnt; ++i )
        {
            /* Whether the current transition time and the first transition
               time form a complete "repeat" of 400 years.
            */
            if ( typesequiv( data, i, 0 ) &&
                 differ_by_repeat( data->transition[ i ].time, data->transition[ 0 ].time ) )
            {
                data->goback = true;
                break;
            }
        }

        for ( i = data->timecnt - 2; i >= 0; --i )
        {
            /* Whether the current transition time and the last transition
               time form a complete "repeat" of 400 years.
            */
            if ( typesequiv( data, data->timecnt - 1, i ) &&
                 differ_by_repeat( data->transition[ data->timecnt - 1 ].time, data->transition[ i ].time ) )
            {
                data->goahead = true;
                break;
            }
        }
    }

    /* Infer defaulttype from the data.  Although this default
       type is always zero for data from recent tzdb releases,
       things are trickier for data from tzdb 2018e or earlier.

       The first set of heuristics work around bugs in 32-bit data
       generated by tzdb 2013c or earlier.  The workaround is for
       zones like Australia/Macquarie where timestamps before the
       first transition have a time type that is not the earliest
       standard-time type.  See:

       https://mm.icann.org/pipermail/tz/2013-May/019368.html
    */

    /* If type 0 is unused in transitions, it's the type to use for
       early times.
    */
    for ( i = 0; i < data->timecnt; ++i )
    {
        if ( data->transition[ i ].typeidx == 0 )
        {
            break;
        }
    }

    i = ( i < data->timecnt ) ? -1 : 0;

    /* Absent the above, if there are transition times and the first
       transition is to a daylight savings time, find the standard
       type less than and closest to the type of the first transition.
    */

    if ( i < 0 && data->timecnt > 0 && data->type[ data->transition[0].typeidx ].isdst )
    {
        i = data->transition[0].typeidx;

        while ( --i >= 0 )
        {
            if ( ! data->type[ i ].isdst )
            {
                break;
            }
        }
    }

    /* The next heuristics are for data generated by tzdb 2018e or earlie,
       for zones like EST5EDT where the first transition is to DST.
    */
    /* If no result yet, find the first standard type. If there is
       none, punt to type zero.
    */

    if ( i < 0 )
    {
        i = 0;

        while ( data->type[ i ].isdst )
        {
            if ( ++i >= data->typecnt )
            {
                i = 0;
                break;
            }
        }
    }

    /* A simple 'data->defaulttype = 0;' would suffice here if we did not
       have to worry about 2018e-or-earlier data. Even simpler would be to
       remove the defaulttype member and just use 0 in its place.
    */
    data->defaulttype = i;
}


/* Load tz data from the named file into the given structure. Read extended
   format if doextend is set. Return 0 on success, an errno value on failure.
*/
int tzload( char const * name, struct tzdata_t * data, bool doextend )
{
    FILE * tzfile;

    if ( ( tzfile = tzopen( name ) ) == NULL )
    {
        return errno;
    }

    if ( feof( tzfile ) || ( data = tzread_data( tzfile ) ) == NULL )
    {
        fclose( tzfile );
        return errno;
    }

    /* Read version 3 POSIX extensions, if present. */
    if ( doextend )
    {
        tzread_extension( data, tzfile );
    }

    if ( data->typecnt == 0 )
    {
        free_tzdata( data );
        errno = EINVAL;
        return errno;
    }

    fclose( tzfile );

    tzdata_complete( data );

    return 0;
}

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    char * path = "testfile";
    FILE * fh = fopen( path, "wb+" );
    time_t time;
    TESTCASE( fh != NULL );

    /* Test values for tzread_val() */
    /* UCHAR as bool */
    TESTCASE( fwrite( "\x00\x01\xff\x80", 1, 4, fh ) == 4 ); /* false, true, true, true */
    /* UCHAR as value */
    TESTCASE( fwrite( "\x00\x01\xff\x80", 1, 4, fh ) == 4 ); /* 0, 1, 255, 128 (because unsigned) */
    /* int32 */
    TESTCASE( fwrite( "\x00\x00\x00\x00", 1, 4, fh ) == 4 ); /* 0 */
    TESTCASE( fwrite( "\x7f\xff\xff\xff", 1, 4, fh ) == 4 ); /* MAX */
    TESTCASE( fwrite( "\x80\x00\x00\x00", 1, 4, fh ) == 4 ); /* MIN */
    TESTCASE( fwrite( "\xff\xff\xff\xff", 1, 4, fh ) == 4 ); /* -1 */
    /* int64 */
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x00", 1, 8, fh ) == 8 ); /* 0 */
    TESTCASE( fwrite( "\x7f\xff\xff\xff\xff\xff\xff\xff", 1, 8, fh ) == 8 ); /* MAX */
    TESTCASE( fwrite( "\x80\x00\x00\x00\x00\x00\x00\x00", 1, 8, fh ) == 8 ); /* MIN */
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\xff", 1, 8, fh ) == 8 ); /* -1 */

    /* Test values for tzread_time() -- note we artificially reduced the
       _PDCLIB_TIME_MIN / _PDCLIB_TIME_MAX range to 8 bit to be independent
       from the actual width of time_t for testing.
    */
    /* ...reading with BIAS 0... */
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x7f", 1, 8, fh ) == 8 ); /* MAX */
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x80", 1, 8, fh ) == 8 ); /* MAX + 1 */
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\x80", 1, 8, fh ) == 8 ); /* MIN */
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\x7f", 1, 8, fh ) == 8 ); /* MIN - 1 */
    /* ...reading with BIAS 1... */
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x7e", 1, 8, fh ) == 8 ); /* MAX - 1 */
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x7f", 1, 8, fh ) == 8 ); /* MAX */
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\x7e", 1, 8, fh ) == 8 ); /* MIN - 2 */
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\x7f", 1, 8, fh ) == 8 ); /* MIN - 1 */
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\x80", 1, 8, fh ) == 8 ); /* MIN */
    /* ...reading with BIAS -1... */
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x81", 1, 8, fh ) == 8 ); /* MAX + 2 */
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x80", 1, 8, fh ) == 8 ); /* MAX + 1 */
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x7f", 1, 8, fh ) == 8 ); /* MAX */
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\x80", 1, 8, fh ) == 8 ); /* MIN */
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\x81", 1, 8, fh ) == 8 ); /* MIN + 1 */

    fclose( fh );
    TESTCASE( ( path = realpath( path, NULL ) ) != NULL );
    fh = tzopen( path );

    /* Testing tzread_val() */
    /* UCHAR as bool */
    TESTCASE( ! tzread_val( E_UCHAR, fh ) );
    TESTCASE(   tzread_val( E_UCHAR, fh ) );
    TESTCASE(   tzread_val( E_UCHAR, fh ) );
    TESTCASE(   tzread_val( E_UCHAR, fh ) );
    /* UCCHAR as value */
    TESTCASE( tzread_val( E_UCHAR, fh ) == 0 );
    TESTCASE( tzread_val( E_UCHAR, fh ) == 1 );
    TESTCASE( tzread_val( E_UCHAR, fh ) == 255 );
    TESTCASE( tzread_val( E_UCHAR, fh ) == 128 );
    /* int32 */
    TESTCASE( tzread_val( E_INT32, fh ) == INT32_C(           0 ) );
    TESTCASE( tzread_val( E_INT32, fh ) == INT32_C(  2147483647 ) );
    TESTCASE( tzread_val( E_INT32, fh ) == INT32_C( -2147483648 ) );
    TESTCASE( tzread_val( E_INT32, fh ) == INT32_C(          -1 ) );
    /* int64 */
    TESTCASE( tzread_val( E_INT64, fh ) == INT64_C(                    0 ) );
    TESTCASE( tzread_val( E_INT64, fh ) == INT64_C(  9223372036854775807 ) );
    TESTCASE( tzread_val( E_INT64, fh ) == INT64_C( -9223372036854775807 ) - 1 );
    TESTCASE( tzread_val( E_INT64, fh ) == INT64_C(                   -1 ) );

    /* Testing tzread_time() */
    /* FIXME: Reduce _PDCLIB_TIME_MIN / _PDCLIB_TIME_MAX so testing is not
       depending on time_t 64bit-ness.
    */
    _PDCLIB_EPOCH_BIAS = 0;
    TESTCASE( tzread_time( &time, fh ) == 0 );
    TESTCASE( time == 127 );
    TESTCASE( tzread_time( &time, fh ) == 1 );
    TESTCASE( time == 127 );
    TESTCASE( tzread_time( &time, fh ) == 0 );
    TESTCASE( time == -128 );
    TESTCASE( tzread_time( &time, fh ) == -1 );
    TESTCASE( time == -128 );

    _PDCLIB_EPOCH_BIAS = 1;
    TESTCASE( tzread_time( &time, fh ) == 0 );
    TESTCASE( time == 127 );
    TESTCASE( tzread_time( &time, fh ) == 1 );
    TESTCASE( time == 127 );
    TESTCASE( tzread_time( &time, fh ) == -1 );
    TESTCASE( time == -128 );
    TESTCASE( tzread_time( &time, fh ) == 0 );
    TESTCASE( time == -128 );
    TESTCASE( tzread_time( &time, fh ) == 0 );
    TESTCASE( time == -127 );

    _PDCLIB_EPOCH_BIAS = -1;
    TESTCASE( tzread_time( &time, fh ) == 1 );
    TESTCASE( time == 127 );
    TESTCASE( tzread_time( &time, fh ) == 0 );
    TESTCASE( time == 127 );
    TESTCASE( tzread_time( &time, fh ) == 0 );
    TESTCASE( time == 126 );
    TESTCASE( tzread_time( &time, fh ) == -1 );
    TESTCASE( time == -128 );
    TESTCASE( tzread_time( &time, fh ) == 0 );
    TESTCASE( time == -128 );

    fclose( fh );
    remove( path );
    free( path );
    return TEST_RESULTS;
}

#endif
