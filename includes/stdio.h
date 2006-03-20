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
#define _IOFBF 2
#define _IOLBF 1
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

/* Operations on files */

/* Remove the given file.
   Returns zero if successful, non-zero otherwise.
   This implementation does detect if the filename corresponds to an open file,
   and closes it before attempting the rename.
*/
int remove( const char * filename );

/* Rename the given old file to the given new name.
   Returns zero if successful, non-zero otherwise. 
   This implementation does detect if the old filename corresponds to an open
   file, and closes it before attempting the rename.
   If the already is a file with the new filename, behaviour is defined by the
   OS.
*/
int rename( const char * old, const char * new );

/* Open a temporary file with mode "wb+", i.e. binary-update. Remove the file
   automatically if it is closed or the program exits normally (by returning
   from main() or calling exit()).
   Returns a pointer to a FILE handle for this file.
   This implementation does not remove temporary files if the process aborts
   abnormally (e.g. abort()).
*/
FILE * tmpfile( void );

/* Generate a file name that is not equal to any existing filename AT THE TIME
   OF GENERATION. Generate a different name each time it is called.
   Returns a pointer to an internal static buffer containing the filename if s
   is a NULL pointer. (This is not thread-safe!)
   Returns s if it is not a NULL pointer (s is then assumed to point to an array
   of at least L_tmpnam characters).
   Returns NULL if unable to generate a suitable name (because all possible
   names already exist, or the function has been called TMP_MAX times already).
   Note that this implementation cannot guarantee a file of the name generated
   is not generated between the call to this function and a subsequent fopen().
*/
char * tmpnam( char * s );

/* File access functions */

/* Close the file associated with the given stream (after flushing its buffers).
   Returns zero if successful, EOF if any errors occur.
*/
int fclose( FILE * stream );

/* Flush the buffers of the given output stream. If the stream is an input
   stream, or an update stream with the last operation being an input operation,
   behaviour is undefined.
   If stream is a NULL pointer, perform the buffer flushing for all applicable
   streams.
   Returns zero if successful, EOF if a write error occurs.
   Sets the error indicator of the stream if a write error occurs.
*/
int fflush( FILE * stream );

/* Open the file with the given filename in the given mode, and return a stream
   handle for it in which error and end-of-file indicator are cleared. Defined
   values for mode are:

   READ MODES
                      text files        binary files
   without update     "r"               "rb"
   with update        "r+"              "rb+" or "r+b"

   Opening in read mode fails if no file with the given filename exists, or if
   cannot be read.

   WRITE MODES
                      text files        binary files
   without update     "w"               "wb"
   with update        "w+"              "wb+" or "w+b"

   With write modes, if a file with the given filename already exists, it is
   truncated to zero length.

   APPEND MODES
                      text files        binary files
   without update     "a"               "ab"
   with update        "a+"              "ab+" or "a+b"

   With update modes, if a file with the given filename already exists, it is
   not truncated to zero length, but all writes are forced to end-of-file (this
   regardless to fseek() calls). Note that binary files opened in append mode
   might have their end-of-file padded with '\0' characters.

   Update modes mean that both input and output functions can be performed on
   the stream, but output must be terminated with a call to either fflush(),
   fseek(), fsetpos(), or rewind() before input is performed, and input must
   be terminated with a call to either fseek(), fsetpos(), or rewind() before
   output is performed, unless input encountered end-of-file.

   If a text file is opened with update mode, the implementation is at liberty
   to open a binary stream instead. This implementation honors the exact mode
   given.

   The stream is fully buffered if and only if it can be determined not to
   refer to an interactive device. As the generic code of this implementation
   cannot determine this, _IOLBF (line buffering) is used for all streams.

   If the mode string begins with but is longer than one of the above sequences
   the implementation is at liberty to ignore the additional characters, or do
   implementation-defined things. This implementation only accepts the exact
   modes above.

   Returns a pointer to the stream handle if successfull, NULL otherwise.
*/
FILE * fopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode );

/* Close any file currently associated with the given stream. Open the file
   identified by the given filename with the given mode (equivalent to fopen()),
   and associate it with the given stream. If filename is a NULL pointer,
   attempt to change the mode of the given stream.
   This implementation allows the following mode changes: TODO
   (Primary use of this function is to redirect stdin, stdout, and stderr.)
*/
FILE * freopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode, FILE * _PDCLIB_restrict stream );

/* If buf is a NULL pointer, call setvbuf( stream, NULL, _IONBF, BUFSIZ ).
   If buf is not a NULL pointer, call setvbuf( stream, buf, _IOFBF, BUFSIZ ).
*/
void setbuf( FILE * _PDCLIB_restrict stream, char * _PDCLIB_restrict buf );

/* Set the given stream to the given buffering mode. If buf is not a NULL
   pointer, use buf as file buffer (of given size). If buf is a NULL pointer,
   use a buffer of given size allocated internally. _IONBF causes unbuffered
   behaviour, _IOLBF causes line-buffered behaviour, _IOFBF causes fully
   buffered behaviour. Calling this function is only valid right after a file is
   opened, and before any other operation (except for any unsuccessful calls to
   setvbuf()) has been performed.
   Returns zero if successful, nonzero otherwise.
*/
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

/* Retrieve the next character from given stream.
   Returns the character, EOF otherwise.
   If end-of-file is reached, the EOF indicator of the stream is set.
   If a read error occurs, the error indicator of the stream is set.
*/
int fgetc( FILE * stream );

/* Read at most n-1 characters from given stream into the array s, stopping at
   \n or EOF. Terminate the read string with \n. If EOF is encountered before
   any characters are read, leave the contents of s unchanged.
   Returns s if successful, NULL otherwise.
   If a read error occurs, the error indicator of the stream is set. In this
   case, the contents of s are indeterminate.
*/
char * fgets( char * _PDCLIB_restrict s, int n, FILE * _PDCLIB_restrict stream );

/* Write the value c (cast to unsigned char) to the given stream.
   Returns c if successful, EOF otherwise.
   If a write error occurs, sets the error indicator of the stream is set.
*/
int fputc( int c, FILE * stream );

/* Write the string s (not including the terminating \0) to the given stream.
   Returns a value >=0 if successful, EOF otherwise.
   This implementation does set the error indicator of the stream if a write
   error occurs.
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

/* Store the current position indicator (and, where appropriate, the current
   mbstate_t status object) for the given stream into the given pos object. The
   actual contents of the object are unspecified, but it can be used as second
   parameter to fsetpos() to reposition the stream to the exact position and
   parse state at the time fgetpos() was called.
   Returns zero if successful, nonzero otherwise.
   TODO: Implementation-defined errno setting for fgetpos().
*/
int fgetpos( FILE * _PDCLIB_restrict stream, fpos_t * _PDCLIB_restrict pos );

/* Set the position indicator for the given stream to the given offset from:
   - the beginning of the file if whence is SEEK_SET,
   - the current value of the position indicator if whence is SEEK_CUR,
   - end-of-file if whence is SEEK_END.
   On text streams, non-zero offsets are only allowed with SEEK_SET, and must
   have been returned by ftell() for the same file.
   Any characters buffered by ungetc() are dropped, the end-of-file indicator
   for the stream is cleared. If the given stream is an update stream, the next
   operation after a successful fseek() may be either input or output.
   Returns zero if successful, nonzero otherwise. If a read/write error occurs,
   the error indicator for the given stream is set.
*/
int fseek( FILE * stream, long int offset, int whence );

/* Set the position indicator (and, where appropriate the mbstate_t status
   object) for the given stream to the given pos object (created by an earlier
   call to fgetpos() on the same file).
   Any characters buffered by ungetc() are dropped, the end-of-file indicator
   for the stream is cleared. If the given stream is an update stream, the next
   operation after a successful fsetpos() may be either input or output.
   Returns zero if successful, nonzero otherwise. If a read/write error occurs,
   the error indicator for the given stream is set.
   TODO: Implementation-defined errno setting for fsetpos().
*/
int fsetpos( FILE * stream, const fpos_t * pos );

/* Return the current offset of the given stream from the beginning of the
   associated file. For text streams, the exact value returned is unspecified
   (and may not be equal to the number of characters), but may be used in
   subsequent calls to fseek().
   Returns -1L if unsuccessful.
   TODO: Implementation-defined errno setting for ftell().
*/
long int ftell( FILE * stream );

/* Equivalent to (void)fseek( stream, 0L, SEEK_SET ), except that the error
   indicator for the stream is also cleared.
*/
void rewind( FILE * stream );

/* Error-handling functions */

/* Clear the end-of-file and error indicators for the given stream. */
void clearerr( FILE * stream );

/* Return zero if the end-of-file indicator for the given stream is not set,
   nonzero otherwise.
*/
int feof( FILE * stream );

/* Return zero if the error indicator for the given stream is not set, nonzero
   otherwise.
*/
int ferror( FILE * stream );

/* If s is neither a NULL pointer nor an empty string, print the string to
   stderr (with appended colon (':') and a space) first. In any case, print an
   error message depending on the current value of errno (being the same as if
   strerror( errno ) had been called).
*/
void perror( const char * s );

#endif
