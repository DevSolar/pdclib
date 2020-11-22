/* vfscanf( FILE *, const char *, va_list )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

int vfscanf( FILE * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, va_list arg )
{
    /* TODO: This function should interpret format as multibyte characters.  */
    struct _PDCLIB_status_t status;
    status.base = 0;
    status.flags = 0;
    status.n = 0;
    status.i = 0;
    status.current = 0;
    status.s = NULL;
    status.width = 0;
    status.prec = EOF;
    status.stream = stream;

    _PDCLIB_LOCK( stream->mtx );

    if ( _PDCLIB_prepread( stream ) == EOF || _PDCLIB_CHECKBUFFER( stream ) == EOF )
    {
        _PDCLIB_UNLOCK( stream->mtx );
        return EOF;
    }

    va_copy( status.arg, arg );

    while ( *format != '\0' )
    {
        const char * rc;

        if ( ( *format != '%' ) || ( ( rc = _PDCLIB_scan( format, &status ) ) == format ) )
        {
            int c;

            /* No conversion specifier, match verbatim */
            if ( isspace( *format ) )
            {
                /* Whitespace char in format string: Skip all whitespaces */
                /* No whitespaces in input does not result in matching error */
                while ( isspace( c = getc( stream ) ) )
                {
                    ++status.i;
                }

                if ( ! feof( stream ) )
                {
                    ungetc( c, stream );
                }
            }
            else
            {
                /* Non-whitespace char in format string: Match verbatim */
                if ( ( ( c = getc( stream ) ) != *format ) || feof( stream ) )
                {
                    /* Matching error */
                    if ( ! feof( stream ) && ! ferror( stream ) )
                    {
                        ungetc( c, stream );
                    }
                    else if ( status.n == 0 )
                    {
                        _PDCLIB_UNLOCK( stream->mtx );
                        return EOF;
                    }

                    _PDCLIB_UNLOCK( stream->mtx );
                    return status.n;
                }
                else
                {
                    ++status.i;
                }
            }

            ++format;
        }
        else
        {
            /* NULL return code indicates matching error */
            if ( rc == NULL )
            {
                break;
            }

            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }

    va_end( status.arg );
    _PDCLIB_UNLOCK( stream->mtx );
    return status.n;
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "stdio/vfscanf.c"
#define _PDCLIB_FILEIO

#include "_PDCLIB_test.h"

static int testscanf( FILE * stream, const char * format, ... )
{
    va_list ap;
    int result;
    va_start( ap, format );
    result = vfscanf( stream, format, ap );
    va_end( ap );
    return result;
}

int main( void )
{
    FILE * source;
    TESTCASE( ( source = fopen( testfile, "wb+" ) ) != NULL );
#include "scanf_testcases.h"
    TESTCASE( fclose( source ) == 0 );
    return TEST_RESULTS;
}

#endif
