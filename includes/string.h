// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// String handling
// ----------------------------------------------------------------------------

#ifndef __STRING_H
#define __STRING_H __STRING_H

// ----------------------------------------------------------------------------
// MACROS

#define NULL 0

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef size_t;

// ----------------------------------------------------------------------------
// FUNCTIONS

int memcmp( const void * s1, const void * s2, size_t n );
void * memcpy( void * restrict s1, const void * restrict s2, size_t n );
void * memmove( void * s1, const void * s2, size_t n );
void * memset( void * s, int c, size_t n );
char * strcat( char * restrict s1, const char * restrict s2 );
int strcmp( const char * s1, const char * s2 );
int strcoll( const char * s1, const char * s2 );
char * strcpy( char * restrict s1, const char * restrict s2 );
size_t strcspn( const char * s1, const char * s2 );
char * strerror( int errcode );
size_t strlen( const char * s );
char * strncat( char * restrict s1, const char * restrict s2, size_t n );
int strncmp( const char * s1, const char * s2, size_t n );
char * strncpy( char * restrict s1, const char * restrict s2, size_t n );
size_t strspn( const char * s1, const char * s2 );
char * strtok( char * restrict s1, const char * restrict s2 );
size_t strxfrm( char * restrict s1, const char * restrict s2, size_t n );

#ifdef __cplusplus

const void * memchr( const void * s, int c, size_t n );
void * memchr( void * s, int c, size_t n );
const char * strchr( const char * s, int c );
char * strchr( char * s, int c );
const char * strpbrk( const char * s1, const char * s2 );
char * strpbrk( char * s1, const char * s2 );
const char * strrchr( const char * s, int c );
char * strrchr( char * s, int c );
const char * strstr( const char * s1, const char * s2 );
char * strstr( char * s1, const char * s2 );

#else

void * memchr( const void * s, int c, size_t n );
char * strchr( const char * s, int c );
char * strpbrk( const char *s1, const char * s2 );
char * strrchr( const char * s, int c );
char * strstr( const char * s1, const char * s2 );

#endif // __cplusplus

#endif // __STRING_H
