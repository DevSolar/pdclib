#ifndef _PDCLIB_GLUE_H
#define _PDCLIB_GLUE_H
/* $Id$ */

/* OS glue functions declaration <_PDCLIB_glue.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_int.h>
#include <stdbool.h>
#include <stddef.h>
_PDCLIB_BEGIN_EXTERN_C

/* -------------------------------------------------------------------------- */
/* OS "glue", part 2                                                          */
/* These are the functions you will have to touch, as they are where PDCLib   */
/* interfaces with the operating system.                                      */
/* They operate on data types partially defined by _PDCLIB_config.h.          */
/* -------------------------------------------------------------------------- */

/* stdlib.h */

/* A system call that terminates the calling process, returning a given status
   to the environment.
*/
_PDCLIB_noreturn void _PDCLIB_Exit( int status );

/* A system call which allocates n pages of memory and returns a pointer to 
   them. On failure, returns NULL
*/
void * _PDCLIB_allocpages( size_t n );

/* A system call which frees the n pages of memory pointed to by p */
void _PDCLIB_freepages( void * p, size_t n );

#ifdef _PDCLIB_HAVE_REALLOCPAGES
/* A system call which attempts to reallocate the group of \p on pages starting
   at \p p, resizing the chunk to be \p nn pages long. If \p mayMove is true, 
   then then the group of pages may move; otherwise, if the group cannot be 
   resized in its current position, failure must be reported.

   On failure, returns NULL; on success, returns the address of the group of 
   pages (if mayMove == false, then this must be equal to \p p)
*/
void * _PDCLIB_reallocpages( void* p, size_t on, size_t nn, bool mayMove);
#endif

/* stdio.h */

/* A system call that opens a file identified by name in a given mode. Return 
   a file descriptor uniquely identifying that file.
   (The mode is the return value of the _PDCLIB_filemode() function.)
*/
_PDCLIB_fd_t _PDCLIB_open( char const * const filename, unsigned int mode );

/* A system call that writes a stream's buffer.
   Returns 0 on success, EOF on write error.
   Sets stream error flags and errno appropriately on error.
*/
int _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream );

/* A system call that fills a stream's buffer.
   Returns 0 on success, EOF on read error / EOF.
   Sets stream EOF / error flags and errno appropriately on error.
*/
int _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream );

/* A system call that repositions within a file. Returns new offset on success,
   -1 / errno on error.
*/
_PDCLIB_int64_t _PDCLIB_seek( struct _PDCLIB_file_t * stream, _PDCLIB_int64_t offset, int whence );

/* A system call that closes a file identified by given file descriptor. Return
   zero on success, non-zero otherwise.
*/
int _PDCLIB_close( _PDCLIB_fd_t fd );

/* A system call that removes a file identified by name. Return zero on success,
   non-zero otherwise.
*/
int _PDCLIB_remove( const char * filename );

/* A system call that renames a file from given old name to given new name.
   Return zero on success, non-zero otherwise. In case of failure, the file
   must still be accessible by old name. Any handling of open files etc. is
   done by standard rename() already.
*/
int _PDCLIB_rename( const char * old, const char * newn);

_PDCLIB_END_EXTERN_C
#endif
