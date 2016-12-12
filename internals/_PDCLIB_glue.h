/* OS glue functions declaration <_PDCLIB_glue.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef __PDCLIB_GLUE_H
#define __PDCLIB_GLUE_H __PDCLIB_GLUE_H

#include "_PDCLIB_int.h"
#include "_PDCLIB_io.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

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

/* Open the file with the given name and mode. Return the file descriptor in 
 * *fd and a pointer to the operations structure in **ops on success.
 *
 * Return true on success and false on failure.
 */
bool _PDCLIB_open( 
   _PDCLIB_fd_t* fd, const _PDCLIB_fileops_t** ops,
   char const * filename, unsigned int mode );

/* A system call that renames a file from given old name to given new name.
   Return zero on success, non-zero otherwise. In case of failure, the file
   must still be accessible by old name. Any handling of open files etc. is
   done by standard rename() already.
*/
int _PDCLIB_rename( const char * old, const char * newn);

#ifdef __cplusplus
}
#endif

#endif
