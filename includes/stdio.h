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

/* PDPC code - unreviewed
/*
    What we have is an internal buffer, which is 8 characters
    longer than the actually used buffer.  E.g. say BUFSIZ is
    512 bytes, then we actually allocate 520 bytes.  The first
    2 characters will be junk, the next 2 characters set to NUL,
    for protection against some backward-compares.  The fourth-last
    character is set to '\n', to protect against overscan.  The
    last 3 characters will be junk, to protect against memory
    violation.  intBuffer is the internal buffer, but everyone refers
    to fbuf, which is actually set to the &intBuffer[4].  Also,
    szfbuf is the size of the "visible" buffer, not the internal
    buffer.  The reason for the 2 junk characters at the beginning
    is to align the buffer on a 4-byte boundary.
*/

typedef struct
{
#if (defined(__OS2__) || defined(__32BIT__))
    unsigned long hfile;  /* OS/2 file handle */
#endif
#if (defined(__MSDOS__) || defined(__DOS__) || defined(__POWERC))
    int hfile; /* dos file handle */
#endif
#if (defined(__MVS__))
    void *hfile;
    int recfm;
    int style;
    int lrecl;
    char ddname[9];
#endif
    int quickBin;  /* 1 = do DosRead NOW!!!! */
    int quickText; /* 1 = quick text mode */
    int textMode; /* 1 = text mode, 0 = binary mode */
    int intFno;   /* internal file number */
    unsigned long bufStartR; /* buffer start represents, e.g. if we
        have read in 3 buffers, each of 512 bytes, and we are
        currently reading from the 3rd buffer, then the first
        character in the buffer would be 1024, so that is what is
        put in bufStartR. */
    char *fbuf;     /* file buffer - this is what all the routines
                       look at. */
    size_t szfbuf;  /* size of file buffer (the one that the routines
                       see, and the user allocates, and what is actually
                       read in from disk) */
    char *upto;     /* what character is next to read from buffer */
    char *endbuf;   /* pointer PAST last character in buffer, ie it
                       points to the '\n' in the internal buffer */
    int errorInd;   /* whether an error has occurred on this file */
    int eofInd;     /* whether EOF has been reached on this file */
    int ungetCh;    /* character pushed back, -1 if none */
    int bufTech;    /* buffering technique, _IOFBF etc */
    char *intBuffer; /* internal buffer */
    int noNl;       /* When doing gets, we don't copy NL */
    int mode;       /* __WRITE_MODE or __READ_MODE */
    int update;     /* Is file update (read + write)? */
    int theirBuffer; /* Is the buffer supplied by them? */
} FILE;

typedef unsigned long fpos_t;

#define NULL ((void *)0)
#define FILENAME_MAX 260
#define FOPEN_MAX 40
#define _IOFBF 1
#define _IOLBF 2
#define _IONBF 3
/*#define BUFSIZ 409600*/
/* #define BUFSIZ 8192 */
/*#define BUFSIZ 5120*/
#define BUFSIZ 6144
/* #define BUFSIZ 10 */
/* #define BUFSIZ 512 */
#define EOF -1
#define L_tmpnam FILENAME_MAX
#define TMP_MAX 25
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define __NFILE (FOPEN_MAX - 3)
#define __WRITE_MODE 1
#define __READ_MODE 2

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

extern FILE *__userFiles[__NFILE];
*/

#endif // __STDIO_H
