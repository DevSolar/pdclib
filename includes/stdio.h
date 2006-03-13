/* $Id$ */

/* Input/output <stdio.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDIO_H
#define _PDCLIB_STDIO_H _PDCLIB_STDIO_H

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>
#endif

#ifndef _PDCLIB_SIZE_T_DEFINED
#define _PDCLIB_SIZE_T_DEFINED _PDCLIB_SIZE_T_DEFINED
typedef _PDCLIB_size_t size_t;
#endif

#ifndef _PDCLIB_NULL_DEFINED
#define _PDCLIB_NULL_DEFINED _PDCLIB_NULL_DEFINED
#define NULL _PDCLIB_NULL
#endif

/* See setvbuf(), third argument */
/* Fully buffered - transmit block-wise */
#define _IOFBF 2
/* Line buffered - transmit line-wise */
#define _IOLBF 1
/* Not buffered - transmit immediately */
#define _IONBF 0

/* The following are platform-dependant, and defined in _PDCLIB_config.h. */
typedef _PDCLIB_fpos_t        fpos_t;
typedef struct _PDCLIB_file_t FILE;
#define EOF -1
#define BUFSIZ _PDCLIB_BUFSIZ
#define FOPEN_MAX _PDCLIB_FOPEN_MAX
#define FILENAME_MAX _PDCLIB_FILENAME_MAX
#define L_tmpnam _PDCLIB_L_tmpnam
#define TMP_MAX _PDCLIB_TMP_MAX

/* See fseek(), third argument */
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 4

/* Text-mode I/O is at liberty to skip non-printing characters and trailing spaces.
   Binary I/O is at liberty to add trailing zero bytes.
   First operation decides "orientation" of the stream (wide / byte).
   freopen() removes orientation; see also fwide().
   Binary wide-oriented streams have the file-positioning restrictions ascribed to both text and binary streams.
   For wide-oriented streams, after a successful call to a file-positioning function that leaves the file position indicator prior to the end-of-file, a wide character output function can overwrite a partial multibyte character; any file contents beyond the byte(s) written are henceforth indeterminate.
   Whether a file of zero length (unwritten-to) actually exists is implementation-defined.
   Wide text input from file: fgetwc() / mbrtowc()
   Wide text output to file: wcrtomb() / fputwc()
   Multibyte encoding in file may contain embedded null bytes
   Multibyte encoding in file need not begin / end in initial shift state.
   Conversion may trigger EILSEQ.
*/

/* Operations on files */

/* Remove the given file. Returns zero if successful, non-zero otherwise. If
   the file is open, this implementation does flush its buffer and closes the
   file before removing it. (It might be still accessible by another hard link
   etc.
*/
int remove( const char * filename );

/* Rename the given old file to the given new name. Returns zero if successful,
   non-zero otherwise. If successful, the file can no longer be accessed under
   its old name. If the file is open, this implementation does flush its buffer
   and closes the file before renaming it.
*/
int rename( const char * old, const char * new );

/* Opens a temporary file with mode "wb+", i.e. binary, update. The file will
   be removed when it is closed or the process exits normally. Returns a pointer
   to a FILE handle for this file. This implementation does not remove temporary
   files if the process aborts abnormally (e.g. abort()).
*/
FILE * tmpfile( void );

/* Generates a file name that is not equal to any existing filename AT THE TIME
   OF GENERATION. It generates a different name each time it is called. If s is
   a NULL pointer, the name is stored in an internal static array, and a pointer
   to that array is returned. (This is not thread-safe!) If s is not a NULL
   pointer, it is assumed to point to an array of at least L_tmpnam characters.
   The generated name is then stored in s, and s is returned. If tmpnam() is
   unable to generate a suitable name (because all possible variations do exist
   already or the function has been called TMP_MAX times already), NULL is
   returned.
   Note that this implementation cannot guarantee a file of this name is not
   generated between the call to tmpnam() and a subsequent fopen().
*/
char * tmpnam( char * s );

/* File access functions */
int fclose( FILE * stream );
int fflush( FILE * stream );
FILE * fopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode );
FILE * freopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode, FILE * _PDCLIB_restrict stream );
void setbuf( FILE * _PDCLIB_restrict stream, char * _PDCLIB_restrict buf );
int setvbuf( FILE * _PDCLIB_restrict stream, char * _PDCLIB_restrict buf, int mode, size_t size );

/* Formatted input/output functions */
int fprintf( FILE * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, ... );
int fscanf( FILE * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, ... );
int printf( const char * _PDCLIB_restrict format, ... );
int scanf( const char * _PDCLIB_restrict format, ... );
int snprintf( char * _PDCLIB_restrict s, size_t n, const char * _PDCLIB_restrict format, ... );
int sprintf( char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, ... );
int sscanf( const char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, ... );
int vfprintf( FILE * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, _PDCLIB_va_list arg );
int vfscanf( FILE * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, _PDCLIB_va_list arg );
int vprintf( const char * _PDCLIB_restrict format, _PDCLIB_va_list arg );
int vscanf( const char * _PDCLIB_restrict format, _PDCLIB_va_list arg );
int vsnprintf( char * _PDCLIB_restrict s, size_t n, const char * _PDCLIB_restrict format, _PDCLIB_va_list arg );
int vsprintf( char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, _PDCLIB_va_list arg );
int vsscanf( const char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, _PDCLIB_va_list arg );

/* Character input/output functions */

/* Retrieve the next character from given stream. Returns the character, cast
   to int, if successful. If EOF is reached, the EOF indicator of the stream
   is set and EOF returned. If a read error occurs, the error indicator of the
   stream is set and EOF returned.
*/
int fgetc( FILE * stream );

/* Reads at most n-1 characters from given stream into the array s, stopping at
   \n or EOF. The string read is terminated with \n. Returns s if successful.
   If EOF is encountered before any characters are read, the contents of s are
   unchanged, and NULL is returned. If a read error occurs, the contents of s
   are indeterminate, and NULL is returned.
*/
char * fgets( char * _PDCLIB_restrict s, int n, FILE * _PDCLIB_restrict stream );

/* Write the value c (cast to unsigned char) to the given stream. Returns c if
   successful. If a write error occurs, sets the error indicator of the stream
   and returns EOF.
*/
int fputc( int c, FILE * stream );

fputs( s, stream ) - write s to stream (not including terminating \0). Return >0 if
                     successful, EOF on write error. (No mention of err!)

/* Write the string s (not including the terminating \0) to the given stream.
   Returns a value >=0 if successful, EOF if a write error occurs. (The
   standard does not mention the error indicator; this implementation does set
   it in such a case.)
*/
int fputs( const char * _PDCLIB_restrict s, FILE * _PDCLIB_restrict stream );

/* Equivalent to fgetc( stream ), but may be implemented as a macro that
   evaluates its parameter more than once.
*/
#define getc( stream ) fgetc( stream )

/* Equivalent to fgetc( stdin ), but may be implemented as a macro. */
#define getchar() fgetc( stdin )

/* Read characters from given stream into the array s, stopping at \n or EOF.
   The string read is terminated with \0. Returns s if successful. If EOF is
   encountered before any characters are read, the contents of s are unchanged,
   and NULL is returned. If a read error occurs, the contents of s are indeter-
   minate, and NULL is returned.
*/
char * gets( char * s );

/* Equivalent to fputc( c, stream ), but may be implemented as a macro that
   evaluates its parameter more than once.
*/
#define putc( c, stream ) fputc( c, stream )

/* Equivalent to fputc( c, stdout ), but may be implemented as a macro that
   evaluates its parameter more than once.
*/
int putchar( int c );

/* Write the string s (not including the terminating \0) to stdout, and append
   a newline to the output. Returns a value >= 0 when successful, EOF if a
   write error occurred.
*/
int puts( const char * s );

/* Push the value c (cast to unsigned char) back onto the given (input) stream.
   A character pushed back in this way will be delivered by subsequent read
   operations (and skipped by subsequent file positioning operations) as if it
   has not been read. The external representation of the stream is unaffected
   by this pushback (it is a buffer operation). One character of pushback is
   guaranteed, further pushbacks may fail. EOF as value for c does not change
   the input stream and results in failure of the function.
   For text files, the file position indicator is indeterminate until all
   pushed-back characters are read. For binary files, the file position
   indicator is decremented by each successful call of ungetc(). If the file
   position indicator for a binary file was zero before the call of ungetc(),
   behaviour is undefined. (Older versions of the library allowed such a call.)
   Returns the pushed-back character if successful, EOF if it fails.
*/
int ungetc( int c, FILE * stream );

/* Direct input/output functions */

/* Read up to nmemb elements of given size from given stream into the buffer
   pointed to by ptr. Returns the number of elements successfully read, which
   may be less than nmemb if a read error or EOF is encountered. If a read
   error is encountered, the value of the file position indicator is
   indeterminate. If a partial element is read, its value is indeterminate.
   If size or nmemb are zero, the function does nothing and returns zero.
*/
size_t fread( void * _PDCLIB_restrict ptr, size_t size, size_t nmemb, FILE * _PDCLIB_restrict stream );

/* Write up to nmemb elements of given size from buffer pointed to by ptr to
   the given stream. Returns the number of elements successfully written, which
   will be less than nmemb only if a write error is encountered. If a write
   error is encountered, the value of the file position indicator is
   indeterminate. If size or nmemb are zero, the function does nothing and
   returns zero.
*/
size_t fwrite( const void * _PDCLIB_restrict ptr, size_t size, size_t nmemb, FILE * _PDCLIB_restrict stream );

/* File positioning functions */
int fgetpos( FILE * _PDCLIB_restrict stream, fpos_t * _PDCLIB_restrict pos );
int fseek( FILE * stream, long int offset, int whence );
int fsetpos( FILE * stream, const fpos_t * pos );
long int ftell( FILE * stream );
void rewind( FILE * stream );

/* Error-handling functions */
void clearerr( FILE * stream );
int feof( FILE * stream );
int ferror( FILE * stream );
void perror( const char * s );

#endif
