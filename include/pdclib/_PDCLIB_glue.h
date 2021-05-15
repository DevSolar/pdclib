/* OS glue functions declaration <_PDCLIB_glue.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_GLUE_H
#define _PDCLIB_GLUE_H _PDCLIB_GLUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_internal.h"

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
_PDCLIB_LOCAL _PDCLIB_Noreturn void _PDCLIB_Exit( int status ) _PDCLIB_NORETURN;


/* stdio.h */

/* A system call that opens a file identified by name in a given mode. Return
   a file descriptor uniquely identifying that file.
   (The mode is the return value of the _PDCLIB_filemode() function.)
*/
_PDCLIB_LOCAL _PDCLIB_fd_t _PDCLIB_open( const char * const filename, unsigned int mode );

/* A system call that writes a stream's buffer.
   Returns 0 on success, EOF on write error.
   Sets stream error flags and errno appropriately on error.
*/
_PDCLIB_LOCAL int _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream );

/* A system call that fills a stream's buffer.
   Returns 0 on success, EOF on read error / EOF.
   Sets stream EOF / error flags and errno appropriately on error.
*/
_PDCLIB_LOCAL int _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream );

/* A system call that repositions within a file. Returns new offset on success,
   -1 / errno on error.
*/
_PDCLIB_LOCAL _PDCLIB_int_least64_t _PDCLIB_seek( struct _PDCLIB_file_t * stream, _PDCLIB_int_least64_t offset, int whence );

/* A system call that closes a file identified by given file descriptor. Return
   zero on success, non-zero otherwise.
*/
_PDCLIB_LOCAL int _PDCLIB_close( _PDCLIB_fd_t fd );

/* A system call that changes the mode of a given stream to that passed as
   argument (the argument being the value returned by _PDCLIB_filemode()),
   *without* closing the stream. See comments in example implementation
   for details. Return zero if the requested mode change is not supported
   for this stream and freopen() should try to close and reopen the stream;
   return INT_MIN if the change is not supported and freopen() should close
   and NOT try to close / reopen (i.e., fail). Return any other value on
   success.
*/
_PDCLIB_LOCAL int _PDCLIB_changemode( struct _PDCLIB_file_t * stream, unsigned int mode );

/* A system call that returns a canonicalized absolute filename in
   dynamically allocated memory, or NULL if the file does not exist.
*/
_PDCLIB_LOCAL char * _PDCLIB_realpath( const char * path );

/* A system call that removes a file. Return zero on success, non-zero
   otherwise.
*/
_PDCLIB_LOCAL int _PDCLIB_remove( const char * pathname );

/* A system call that renames a file from given old name to given new name.
   Return zero on success, non-zero otherwise. In case of failure, the file
   must still be accessible by old name. Any handling of open files etc. is
   done by standard rename() already.
*/
_PDCLIB_LOCAL int _PDCLIB_rename( const char * oldpath, const char * newpath );

#ifdef __cplusplus
}
#endif

#endif
