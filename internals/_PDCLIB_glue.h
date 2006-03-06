/* $Id$ */

/* Release $Name$ */

/* OS glue functions declaration <_PDCLIB_glue.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>
#endif

/* -------------------------------------------------------------------------- */
/* OS "glue", part 2                                                          */
/* These are the functions you will have to touch, as they are where PDCLib   */
/* interfaces with the operating system.                                      */
/* They operate on data types partially defined by _PDCLIB_config.h.          */
/* -------------------------------------------------------------------------- */

/* A system call that terminates the calling process, returning a given status
   to the environment.
*/
void _PDCLIB_Exit( int status ) _PDCLIB_NORETURN;

/* A system call that adds n pages of memory to the process heap (if n is
   positive), or releases n pages from the process heap (if n is negative).
   Return a (void *) pointing to the *former* end-of-heap if successful, NULL
   otherwise.
*/
void * _PDCLIB_allocpages( int n );

/* A system call that opens a file identified by name in a given mode, and
   returns a file descriptor uniquely identifying that file.
*/
_PDCLIB_fd_t _PDCLIB_open( char const * const filename, int mode );

/* A system call that writes n characters to a file identified by given file
   descriptor. Return the number of characters written.
*/
_PDCLIB_size_t _PDCLIB_write( _PDCLIB_fd_t fd, char const * buffer, _PDCLIB_size_t n );

/* A system call that reads n characters into a buffer, from a file identified
   by given file descriptor. Return the number of characters read.
*/
_PDCLIB_size_t _PDCLIB_read( _PDCLIB_fd_t fd, char * buffer, _PDCLIB_size_t n );

/* A system call that closes a file identified by given file descriptor. */
void _PDCLIB_close( _PDCLIB_fd_t fd );

/* A system call that removes a file identified by name. Return zero on success,
   non-zero otherwise.
*/
int _PDCLIB_remove( const char * filename );

/* A system call that renames a file from given old name to given new name.
   Return zero on success, non-zero otherwise. In case of failure, the file
   must still be accessible by old name.
*/
int _PDCLIB_rename( const char * old, const char * new );
