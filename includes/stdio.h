// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Input/output
// ----------------------------------------------------------------------------

#ifndef __STDIO_H
#define __STDIO_H __STDIO_H

// ----------------------------------------------------------------------------
// MACROS

#define _IOFBF       // TODO
#define _IOLBF       // TODO
#define _IONBF       // TODO
#define BUFSIZ       // TODO
#define EOF          // TODO
#define FILENAME_MAX // TODO
#define FOPEN_MAX    // TODO
#define L_tmpnam     // TODO
#define NULL         0
#define SEEK_CUR     // TODO
#define SEEK_END     // TODO
#define SEEK_SET     // TODO
#define TMP_MAX      // TODO

#define stderr // TODO
#define stdin  // TODO
#define stdout // TODO

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef FILE;   // TODO
typedef fpos_t; // TODO
typedef size_t; // TODO

// ----------------------------------------------------------------------------
// FUNCTIONS

// TODO: Documentation.

void clearerr( FILE * stream );
int fclose( FILE * stream );
int feof( FILE * stream );
int ferror( FILE * stream );
int fflush( FILE * stream );
FILE * fopen( const char * restrict filename, const char * restrict mode );
FILE * freopen( const char * restrict filename, const char * restrict mode, FILE * stream );
int remove( const char * filename );
int rename( const char * old, const char * new );
void rewind( FILE * stream );
void setbuf( FILE * restrict stream, char * restrict buf );
int setvbuf( FILE * restrict stream, char * restrict buf, int mode, size_t size );
FILE * tmpfile( void )
char * tmpnam( char * s );

int fseek( FILE * stream, long offset, int mode );
int fsetpos( FILE * stream, const fpos_t * pos );
int fgetpos( FILE * restrict stream, fpos_t * restrict pos );
long ftell( FILE * stream );

int fgetc( FILE * stream );
char *fgets( char * restrict s, int n, FILE * restrict stream );
size_t fread( void * restrict ptr, size_t size, size_t nelem, FILE * restrict stream );
int getc( FILE * stream );
int getchar( void );
char * gets( char * s );
int ungetc( int c, FILE * stream );

int fputc( int c, FILE * stream );
int fputs( const char * restrict s, FILE * restrict stream );
size_t fwrite( const void * restrict ptr, size_t size, size_t nelem, FILE * restrict stream );
void perror( const char * s );
int putc( int c, FILE * stream );
int putchar( int c );
int puts( const char * s );

int fscanf( FILE * restrict stream, const char * restrict format, ... );
int scanf( const char * restrict format, ... );
int sscanf( const char * restrict s, const char * restrict format, ... );
int vfscanf( FILE * restrict stream, const char * restrict format, va_list ap );
int vscanf( const char * restrict format, va_list ap );
int vsscanf( const char * restrict s, const char * restrict format, va_list ap );

int fprintf( FILE * restrict stream, const char * restrict format, ... );
int printf( const char * restrict format, ... );
int snprintf( char * restrict s, size_t n, const char * restrict format, ... );
int sprintf( char * restrict s, const char * restrict format, ... );
int vfprintf( FILE * restrict stream, const char * restrict format, va_list ap );
int vprintf( const char * restrict format, va_list ap );
int vsnprintf( char * restrict s, size_t n, const char * restrict format, va_list ap );
int vsprintf( char * restrict s, const char * restrict format, va_list ap);

#endif // __STDIO_H
