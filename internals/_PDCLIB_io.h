#ifndef _PDCLIB_IO_H
#define _PDCLIB_IO_H
#include "_PDCLIB_int.h"
#include "_PDCLIB_threadconfig.h"

/* PDCLib internal I/O logic <_PDCLIB_int.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* Flags for representing mode (see fopen()). Note these must fit the same
   status field as the _IO?BF flags in <stdio.h> and the internal flags below.
*/
#define _PDCLIB_FREAD     8u
#define _PDCLIB_FWRITE   16u
#define _PDCLIB_FAPPEND  32u 
#define _PDCLIB_FRW      64u
#define _PDCLIB_FBIN    128u

/* Internal flags, made to fit the same status field as the flags above. */
/* -------------------------------------------------------------------------- */
/* free() the buffer memory on closing (false for user-supplied buffer) */
#define _PDCLIB_FREEBUFFER   512u
/* stream has encountered error / EOF */
#define _PDCLIB_ERRORFLAG   1024u
#define _PDCLIB_EOFFLAG     2048u
/* stream is wide-oriented */
#define _PDCLIB_WIDESTREAM  4096u
/* stream is byte-oriented */
#define _PDCLIB_BYTESTREAM  8192u
/* file associated with stream should be remove()d on closing (tmpfile()) */
#define _PDCLIB_DELONCLOSE 16384u
/* stream handle should not be free()d on close (stdin, stdout, stderr) */
#define _PDCLIB_STATIC     32768u

typedef union _PDCLIB_fd
{
#if defined(_PDCLIB_OSFD_T)
    _PDCLIB_OSFD_T      osfd;
#endif
    void *              pointer;
    _PDCLIB_uintptr_t   uval;
    _PDCLIB_intptr_t    sval;     
} _PDCLIB_fd_t;

/* Internal functions */
/* Writes a stream's buffer.
   Returns 0 on success, EOF on write error.
   Sets stream error flags and errno appropriately on error.
*/
int _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream );

/* Fills a stream's buffer.
   Returns 0 on success, EOF on read error / EOF.
   Sets stream EOF / error flags and errno appropriately on error.
*/
int _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream );

/* Repositions within a file. Returns new offset on success,
   -1 / errno on error.
*/
_PDCLIB_int_fast64_t _PDCLIB_seek( struct _PDCLIB_file_t * stream, 
                                  _PDCLIB_int_fast64_t offset, int whence );

/* File backend I/O operations
 *
 * PDCLib will call through to these methods as needed to implement the stdio
 * functions.
 */
typedef struct _PDCLIB_fileops
{
    /*! Read length bytes from the file into buf; returning the number of bytes
     *  actually read in *numBytesRead.
     *
     *  Returns true if bytes were read successfully; on end of file, returns
     *  true with *numBytesRead == 0.
     *
     *  On error, returns false and sets errno appropriately. *numBytesRead is
     *  ignored in this situation.
     */
    _PDCLIB_bool (*read)( _PDCLIB_fd_t self, 
                          void * buf, 
                          _PDCLIB_size_t length, 
                          _PDCLIB_size_t * numBytesRead );

    /*! Write length bytes to the file from buf; returning the number of bytes
     *  actually written in *numBytesWritten
     *
     *  Returns true if bytes were written successfully. On error, returns false
     *  and setss errno appropriately (as with read, *numBytesWritten is 
     *  ignored)
     */
    _PDCLIB_bool (*write)( _PDCLIB_fd_t self, const void * buf, 
                   _PDCLIB_size_t length, _PDCLIB_size_t * numBytesWritten );

    /* Seek to the file offset specified by offset, from location whence, which
     * may be one of the standard constants SEEK_SET/SEEK_CUR/SEEK_END
     */
    _PDCLIB_bool (*seek)( _PDCLIB_fd_t self, _PDCLIB_int_fast64_t offset, 
                          int whence, _PDCLIB_int_fast64_t *newPos );

    void (*close)( _PDCLIB_fd_t self );

    /*! Behaves as read does, except for wide characters. Both length and 
     *  *numCharsRead represent counts of characters, not bytes.
     *
     *  This function is optional; if missing, PDCLib will buffer the character
     *  data as bytes and perform translation directly into the user's buffers.
     *  It is useful if your backend can directly take wide characters (for 
     *  example, the Windows console)
     */
    _PDCLIB_bool (*wread)( _PDCLIB_fd_t self, _PDCLIB_wchar_t * buf, 
                     _PDCLIB_size_t length, _PDCLIB_size_t * numCharsRead );

    /* Behaves as write does, except for wide characters. As with wread, both
     * length and *numCharsWritten are character counts.
     *
     * This function is also optional; if missing, PDCLib will buffer the 
     * character data as bytes and do translation directly from the user's 
     * buffers. You only need to implement this if your backend can directly 
     * take wide characters (for example, the Windows console)
     */
    _PDCLIB_bool (*wwrite)( _PDCLIB_fd_t self, const _PDCLIB_wchar_t * buf, 
                     _PDCLIB_size_t length, _PDCLIB_size_t * numCharsWritten );
} _PDCLIB_fileops_t;

/* Position / status structure for getpos() / fsetpos(). */
struct _PDCLIB_fpos_t
{
    _PDCLIB_int_fast64_t offset; /* File position offset */
    int                  status; /* Multibyte parsing state (unused, reserved) */
};

/* FILE structure */
struct _PDCLIB_file_t
{
    const _PDCLIB_fileops_t * ops;
    _PDCLIB_fd_t              handle;   /* OS file handle */
    _PDCLIB_MTX_T             lock;     /* file lock */
    char *                    buffer;   /* Pointer to buffer memory */
    _PDCLIB_size_t            bufsize;  /* Size of buffer */
    _PDCLIB_size_t            bufidx;   /* Index of current position in buffer */
    _PDCLIB_size_t            bufend;   /* Index of last pre-read character in buffer */
    struct _PDCLIB_fpos_t     pos;      /* Offset and multibyte parsing state */
    _PDCLIB_size_t            ungetidx; /* Number of ungetc()'ed characters */
    unsigned char *           ungetbuf; /* ungetc() buffer */
    unsigned int              status;   /* Status flags; see above */
    /* multibyte parsing status to be added later */
    char *                    filename; /* Name the current stream has been opened with */
    struct _PDCLIB_file_t *   next;     /* Pointer to next struct (internal) */
};


#endif
