/* $Id$ */

/* Release $Name$ */

/* strcoll( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* TODO: Dummy function, PDCLib does not support locales yet. */

int strcmp( const char * s1, const char * s2 );

int strcoll( const char * s1, const char * s2 )
{
    return strcmp( s1, s2 );
}
