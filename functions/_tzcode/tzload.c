/* tzload( char const *, struct state *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define _DEFAULT_SOURCE

#include "_PDCLIB_config.h"

#include "_PDCLIB_tzcode.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
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

struct tzdata_t
{
    unsigned char ver;
    int_fast32_t leapcnt;
    int_fast32_t timecnt;
    int_fast32_t typecnt;
    int_fast32_t charcnt;
    /*
    bool goback;
    bool goahead;
    */
    struct transition_t
    {
        time_t        time;
        unsigned char typeidx;
    } * transition;
    struct type_t
    {
        int_fast32_t utoff;
        bool         isdst;
        int          desigidx;
        bool         isstd;
        bool         isut;
    } * type;
    char * designations;
    struct leapsecond_t
    {
        time_t       occur;
        int_fast32_t corr;
    } * leapsecond;
    //int defaulttype;
};

static void free_tzdata( struct tzdata_t * data )
{
    free( data->transition );
    free( data->type );
    free( data->designations );
    free( data->leapsecond );
    free( data );
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
        return NULL;
    }

    /* version -- \0, '2', or '3' */
    if ( tzread_val( E_UCHAR, fh ) < '2' )
    {
        /* Minimum required version is version 2 (64-bit time values). */
        return NULL;
    }

    /* reserved */
    if ( fread( reserved, 1, 15, fh ) != 15 )
    {
        return NULL;
    }

    if ( ( data = (struct tzdata_t *)calloc( 1, sizeof( struct tzdata_t ) ) ) == NULL )
    {
        /* Memory allocation failed */
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
        return NULL;
    }

    /* magic, v2 */
    if ( fread( magic, 1, 4, fh ) != 4 || memcmp( magic, "TZif", 4 ) != 0 )
    {
        free_tzdata( data );
        return NULL;
    }

    /* version -- '2' or '3' (we ruled out version 1 above) */
    data->ver = tzread_val( E_UCHAR, fh );

    /* reserved */
    if ( fread( reserved, 1, 15, fh ) != 15 )
    {
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
            return NULL;
        }

        /* Sanity check -- should be a pointer into designations array */
        if ( ( data->type[i].desigidx = tzread_val( E_UCHAR, fh ) ) >= data->charcnt )
        {
            free_tzdata( data );
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
            return NULL;
        }
    }

    return data;
}


/* Load tz data from the named file into the given structure. Read extended
   format if doextend is set. Return 0 on success, an errno value on failure.
*/
int tzload( char const * name, struct state * sp, bool doextend )
{
    struct tzdata_t * data;
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

    if ( doextend )
    {
        /* TODO */
    }

    fclose( tzfile );
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
