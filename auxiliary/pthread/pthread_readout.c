#define _GNU_SOURCE

#include <assert.h>
#include <stdalign.h>
#include <stddef.h>
#include <stdio.h>

#include <limits.h>

#include "pthread.h"

/* For _PDCLIB_time -> reconstructing struct _PDCLIB_timespec */
#include "_PDCLIB_config.h"

#define symbol2value( x ) #x
#define symbol2string( x ) symbol2value( x )

struct _PDCLIB_timespec
{
    _PDCLIB_time tv_sec;
    long tv_nsec;
};

static void print_mutex( const char * define, pthread_mutex_t mutex )
{
    printf( "%s { {", define );
    for ( size_t i = 0; i < sizeof( pthread_mutex_t ); ++i )
    {
        if ( i > 0 )
        {
            printf( "," );
        }
        if ( ! ( i % 8 ) )
        {
            printf( "\\\n    " );
        }
        printf( " 0x%02hhx", ((unsigned char *)&mutex)[i] );
    }
    printf( " } }\n" );
}

static int print_recursive_mutex_data( void )
{
    pthread_mutexattr_t mutex_attr;

    if ( pthread_mutexattr_init( &mutex_attr ) == 0 )
    {
        if ( pthread_mutexattr_settype( &mutex_attr, PTHREAD_MUTEX_RECURSIVE ) == 0 )
        {
            pthread_mutex_t mutex;

            if ( pthread_mutex_init( &mutex, &mutex_attr ) == 0 )
            {
                print_mutex( "#define _PDCLIB_MTX_RECURSIVE_INIT", mutex );
                pthread_mutexattr_destroy( &mutex_attr );
                return 1;
            }
        }
    }

    return 0;
}

static int print_plain_mutex_data( void )
{
    pthread_mutex_t mutex;

    if ( pthread_mutex_init( &mutex, NULL ) == 0 )
    {
        print_mutex( "#define _PDCLIB_MTX_PLAIN_INIT", mutex );
        return 1;
    }

    return 0;
}

int main( int argc, char * argv[] )
{
    pthread_cond_t      cond;
    pthread_mutex_t     mutex;
    pthread_condattr_t  cnd_attr;
    pthread_mutexattr_t mtx_attr;
    pthread_attr_t      thrd_attr;

    /* In interfacing 'our' threads.h functions with pthread, we assume
       that 'our' struct timespec and the host system's struct timespec
       can be safely cast to each other. So we check that the layout is
       identical.
       If these asserts fail, you need to find out what the platform uses
       for struct timespec, and adjust the timespec definition here and
       in PDCLib's _PDCLIB_config.h / time.h.
    */
    struct timespec ts;
    struct _PDCLIB_timespec pts;
    assert( sizeof( ts.tv_sec ) == sizeof( pts.tv_sec ) );
    assert( alignof( ts.tv_sec ) == alignof( pts.tv_sec ) );
    assert( sizeof( ts.tv_nsec ) == sizeof( pts.tv_nsec ) );
    assert( sizeof( struct timespec ) == sizeof( struct _PDCLIB_timespec ) );
    assert( offsetof( struct timespec, tv_sec ) == offsetof( struct _PDCLIB_timespec, tv_sec ) );
    assert( offsetof( struct timespec, tv_nsec ) == offsetof( struct _PDCLIB_timespec, tv_nsec ) );

    /* Similarly, we assume (in the threads/ files) that 'our' thrd_t can be
       safely cast to pthread_t and back, mtx_t to pthread_mutex_t, cnd_t to
       pthread_cond_t, tss_t to pthread_key_t, and once_flag to pthread_once_t.
       What we assert here is that the types used by the platform's pthread
       implementation are, indeed, the fundamental types assumed here.
       (Which are then printed out for inclusion in _PDCLIB_config.h, so
       that PDCLib's structures are compatible.)
       If these assertions fail, you need to find out the fundamental types
       used by the platform's pthread implementation (on my x86_64 machine
       in /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h), and adjust
       both the assert() statements and the printf() statements accordingly.
    */

    puts( "/* Use this in _PDCLIB_config.h, 'threads' section, for interfacing pthread.  */" );

    /* Thread */
    assert( sizeof( pthread_t ) == sizeof( unsigned long int ) );
    printf( "typedef unsigned long int _PDCLIB_thrd_t;\n" );

    /* Condition */
    assert( sizeof( cond.__align ) == sizeof( long long int ) );
    printf( "typedef union { unsigned char _PDCLIB_cnd_t_data[ %zd ]; long long int _PDCLIB_cnd_t_align; } _PDCLIB_cnd_t;\n", sizeof( pthread_cond_t ) );

    /* Mutex */
    assert( sizeof( mutex.__align ) == sizeof( long int ) );
    printf( "typedef union { unsigned char _PDCLIB_mtx_t_data[ %zd ]; long int _PDCLIB_mtx_t_align; } _PDCLIB_mtx_t;\n", sizeof( pthread_mutex_t ) );

    /* Thread Specific Storage */
    assert( sizeof( pthread_key_t ) == sizeof( unsigned int ) );
    printf( "typedef unsigned int _PDCLIB_tss_t;\n" );

    /* once_flag */
    assert( sizeof( pthread_once_t ) == sizeof( int ) );
    assert( alignof( pthread_once_t ) == alignof( int ) );
    printf( "typedef int _PDCLIB_once_flag;\n" );

    /* once_flag init */
    printf( "#define _PDCLIB_ONCE_FLAG_INIT %s\n", symbol2string( PTHREAD_ONCE_INIT ) );

    printf( "#define _PDCLIB_RECURSIVE_MUTEX_INIT %s\n", symbol2value(PTHREAD_MUTEX_INITIALIZER) );

    /* _PDCLIB_TSS_DTOR_ITERATIONS */
    printf( "/* This one is actually hidden in <limits.h>, and only if __USE_POSIX is      */\n"
            "/* defined prior to #include <limits.h> (PTHREAD_DESTRUCTOR_ITERATIONS).      */\n"
	    "#define _PDCLIB_TSS_DTOR_ITERATIONS %d\n", PTHREAD_DESTRUCTOR_ITERATIONS );

    /* Pthread attibutes */

    printf( "/* The following are not made public in any header, but used internally for   */\n"
            "/* interfacing with the pthread API.                                          */\n" );

    assert( sizeof( cnd_attr.__align ) == sizeof( int ) );
    printf( "typedef union { unsigned char _PDCLIB_cnd_attr_t_data[ %zd ]; int _PDCLIB_cnd_attr_t_align; } _PDCLIB_cnd_attr_t;\n", sizeof( pthread_condattr_t ) );

    assert( sizeof( mtx_attr.__align ) == sizeof( int ) );
    printf( "typedef union { unsigned char _PDCLIB_mtx_attr_t_data[ %zd ]; int _PDCLIB_mtx_attr_t_align; } _PDCLIB_mtx_attr_t;\n", sizeof( pthread_mutexattr_t ) );

    assert( sizeof( thrd_attr.__align ) == sizeof( long int ) );
    printf( "typedef union { unsigned char _PDCLIB_thrd_attr_t_data[ %zd ]; long int _PDCLIB_thrd_attr_t_align; } _PDCLIB_thrd_attr_t;\n", sizeof( pthread_attr_t ) );

    printf( "/* Static initialization of recursive mutex.                                  */\n" );
    print_recursive_mutex_data();

    printf( "/* Static initialization of plain / timeout mutex (identical with pthread).   */\n" );
    print_plain_mutex_data();
}
