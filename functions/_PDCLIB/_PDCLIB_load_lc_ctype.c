/* _PDCLIB_load_lc_ctype( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <inttypes.h>
#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdclib/_PDCLIB_internal.h"

struct _PDCLIB_lc_ctype_t * _PDCLIB_load_lc_ctype( const char * path, const char * locale )
{
    struct _PDCLIB_lc_ctype_t * rc = NULL;
    const char * extension = "_ctype.dat";
    char * file = (char *)malloc( strlen( path ) + strlen( locale ) + strlen( extension ) + 1 );

    if ( file )
    {
        FILE * fh;

        strcpy( file, path );
        strcat( file, locale );
        strcat( file, extension );

        if ( ( fh = fopen( file, "rb" ) ) != NULL )
        {
            if ( ( rc = (struct _PDCLIB_lc_ctype_t *)malloc( sizeof( struct _PDCLIB_lc_ctype_t ) ) ) != NULL )
            {
                struct _PDCLIB_lc_ctype_entry_t * entry;

                if ( ( entry = (struct _PDCLIB_lc_ctype_entry_t *)malloc( sizeof( struct _PDCLIB_lc_ctype_entry_t ) * _PDCLIB_CHARSET_SIZE + 1 ) ) != NULL )
                {
                    rc->entry = entry + 1;
                    rc->entry[ -1 ].flags = rc->entry[ -1 ].upper = rc->entry[ -1 ].lower =  0;

                    if ( fscanf( fh, "%x %x %x %x %x %x", &rc->digits_low, &_PDCLIB_lc_ctype->digits_high, &_PDCLIB_lc_ctype->Xdigits_low, &_PDCLIB_lc_ctype->Xdigits_high, &_PDCLIB_lc_ctype->xdigits_low, &_PDCLIB_lc_ctype->xdigits_high ) == 6 )
                    {
                        size_t i;

                        for ( i = 0; i < _PDCLIB_CHARSET_SIZE; ++i )
                        {
                            if ( fscanf( fh, "%" SCNx16 " %hhx %hhx", &rc->entry[ i ].flags, &rc->entry[ i ].upper, &rc->entry[ i ].lower ) != 3 )
                            {
                                fclose( fh );
                                free( file );
                                free( rc->entry - 1 );
                                free( rc );
                                return NULL;
                            }
                        }
                    }

                    rc->alloced = 1;
                }
                else
                {
                    free( rc );
                }
            }

            fclose( fh );
        }

        free( file );
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <ctype.h>

int main( void )
{
#ifndef REGTEST
    FILE * fh = fopen( "test_ctype.dat", "wb" );
    TESTCASE( fh != NULL );
    /* For test purposes, let's set up a charset that only has the hex digits */
    /* 0x00..0x09 - digits */
    /* 0x11..0x16 - Xdigits */
    /* 0x21..0x26 - xdigits */
    TESTCASE( fprintf( fh, "%x %x\n", 0x00, 0x09 ) );
    TESTCASE( fprintf( fh, "%x %x %x %x\n", 0x11, 0x16, 0x21, 0x26 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x00, 0x00 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x01, 0x01 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x02, 0x02 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x03, 0x03 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x04, 0x04 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x05, 0x05 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x06, 0x06 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x07, 0x07 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x08, 0x08 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH, 0x09, 0x09 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x0A, 0x0A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x0B, 0x0B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x0C, 0x0C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x0D, 0x0D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x0E, 0x0E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x0F, 0x0F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x10, 0x10 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x11, 0x11 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x12, 0x12 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x13, 0x13 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x14, 0x14 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x15, 0x15 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x16, 0x16 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x17, 0x17 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x18, 0x18 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x19, 0x19 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x1A, 0x1A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x1B, 0x1B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x1C, 0x1C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x1D, 0x1D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x1E, 0x1E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x1F, 0x1F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x20, 0x20 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x21, 0x21 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x22, 0x22 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x23, 0x23 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x24, 0x24 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x25, 0x25 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x26, 0x26 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x27, 0x27 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x28, 0x28 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x29, 0x29 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x2A, 0x2A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x2B, 0x2B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x2C, 0x2C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x2D, 0x2D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x2E, 0x2E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x2F, 0x2F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x30, 0x30 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x31, 0x31 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x32, 0x32 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x33, 0x33 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x34, 0x34 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x35, 0x35 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x36, 0x36 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x37, 0x37 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x38, 0x38 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x39, 0x39 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x3A, 0x3A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x3B, 0x3B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x3C, 0x3C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x3D, 0x3D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x3E, 0x3E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x3F, 0x3F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x40, 0x40 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x41, 0x41 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x42, 0x42 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x43, 0x43 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x44, 0x44 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x45, 0x45 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x46, 0x46 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x47, 0x47 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x48, 0x48 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x49, 0x49 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x4A, 0x4A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x4B, 0x4B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x4C, 0x4C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x4D, 0x4D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x4E, 0x4E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x4F, 0x4F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x50, 0x50 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x51, 0x51 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x52, 0x52 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x53, 0x53 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x54, 0x54 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x55, 0x55 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x56, 0x56 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x57, 0x57 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x58, 0x58 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x59, 0x59 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x5A, 0x5A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x5B, 0x5B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x5C, 0x5C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x5D, 0x5D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x5E, 0x5E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x5F, 0x5F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x60, 0x60 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x61, 0x61 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x62, 0x62 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x63, 0x63 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x64, 0x64 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x65, 0x65 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x66, 0x66 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x67, 0x67 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x68, 0x68 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x69, 0x69 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x6A, 0x6A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x6B, 0x6B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x6C, 0x6C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x6D, 0x6D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x6E, 0x6E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x6F, 0x6F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x70, 0x70 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x71, 0x71 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x72, 0x72 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x73, 0x73 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x74, 0x74 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x75, 0x75 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x76, 0x76 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x77, 0x77 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x78, 0x78 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x79, 0x79 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x7A, 0x7A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x7B, 0x7B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x7C, 0x7C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x7D, 0x7D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x7E, 0x7E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x7F, 0x7F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x80, 0x80 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x81, 0x81 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x82, 0x82 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x83, 0x83 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x84, 0x84 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x85, 0x85 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x86, 0x86 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x87, 0x87 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x88, 0x88 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x89, 0x89 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x8A, 0x8A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x8B, 0x8B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x8C, 0x8C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x8D, 0x8D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x8E, 0x8E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x8F, 0x8F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x90, 0x90 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x91, 0x91 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x92, 0x92 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x93, 0x93 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x94, 0x94 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x95, 0x95 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x96, 0x96 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x97, 0x97 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x98, 0x98 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x99, 0x99 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x9A, 0x9A ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x9B, 0x9B ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x9C, 0x9C ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x9D, 0x9D ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x9E, 0x9E ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0x9F, 0x9F ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA0, 0xA0 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA1, 0xA1 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA2, 0xA2 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA3, 0xA3 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA4, 0xA4 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA5, 0xA5 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA6, 0xA6 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA7, 0xA7 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA8, 0xA8 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xA9, 0xA9 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xAA, 0xAA ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xAB, 0xAB ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xAC, 0xAC ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xAD, 0xAD ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xAE, 0xAE ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xAF, 0xAF ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB0, 0xB0 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB1, 0xB1 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB2, 0xB2 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB3, 0xB3 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB4, 0xB4 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB5, 0xB5 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB6, 0xB6 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB7, 0xB7 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB8, 0xB8 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xB9, 0xB9 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xBA, 0xBA ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xBB, 0xBB ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xBC, 0xBC ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xBD, 0xBD ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xBE, 0xBE ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xBF, 0xBF ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC0, 0xC0 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC1, 0xC1 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC2, 0xC2 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC3, 0xC3 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC4, 0xC4 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC5, 0xC5 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC6, 0xC6 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC7, 0xC7 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC8, 0xC8 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xC9, 0xC9 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xCA, 0xCA ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xCB, 0xCB ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xCC, 0xCC ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xCD, 0xCD ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xCE, 0xCE ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xCF, 0xCF ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD0, 0xD0 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD1, 0xD1 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD2, 0xD2 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD3, 0xD3 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD4, 0xD4 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD5, 0xD5 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD6, 0xD6 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD7, 0xD7 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD8, 0xD8 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xD9, 0xD9 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xDA, 0xDA ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xDB, 0xDB ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xDC, 0xDC ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xDD, 0xDD ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xDE, 0xDE ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xDF, 0xDF ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE0, 0xE0 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE1, 0xE1 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE2, 0xE2 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE3, 0xE3 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE4, 0xE4 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE5, 0xE5 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE6, 0xE6 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE7, 0xE7 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE8, 0xE8 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xE9, 0xE9 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xEA, 0xEA ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xEB, 0xEB ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xEC, 0xEC ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xED, 0xED ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xEE, 0xEE ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xEF, 0xEF ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF0, 0xF0 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF1, 0xF1 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF2, 0xF2 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF3, 0xF3 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF4, 0xF4 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF5, 0xF5 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF6, 0xF6 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF7, 0xF7 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF8, 0xF8 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xF9, 0xF9 ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xFA, 0xFA ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xFB, 0xFB ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xFC, 0xFC ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xFD, 0xFD ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xFE, 0xFE ) );
    TESTCASE( fprintf( fh, "%x %x %x\n", 0x00, 0xFF, 0xFF ) );
    fclose( fh );
    TESTCASE( _PDCLIB_load_lc_ctype( "./", "test" ) != NULL );
    remove( "test_ctype.dat" );
    /*
    TESTCASE( isdigit( 0x00 ) && ! isxdigit( 0x00 ) && ! isalpha( 0x00 ) );
    TESTCASE( ! isdigit( 0x11 ) && isxdigit( 0x11 ) && isalpha( 0x11 ) && isupper( 0x11 ) && ! islower( 0x11 ) );
    TESTCASE( ! isdigit( 0x21 ) && isxdigit( 0x21 ) && isalpha( 0x21 ) && ! isupper( 0x11 ) && islower( 0x11 ) );
    */
#endif
    return TEST_RESULTS;
}

#endif
