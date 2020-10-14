/* Errors <errno.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_ERRNO_H
#define _PDCLIB_ERRNO_H _PDCLIB_ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_lib_ext1.h"
#include "pdclib/_PDCLIB_internal.h"

/* FIXME: With <threads.h>, this needs to be in thread-specific storage. */
#define errno (*_PDCLIB_errno_func())

/* C only requires the following three */

/* Result too large */
#define ERANGE          _PDCLIB_ERANGE
/* Mathematics argument out of domain of function */
#define EDOM            _PDCLIB_EDOM
/* Illegal byte sequence */
#define EILSEQ          _PDCLIB_EILSEQ

/* C++ additionally requires the folloing */

/* Argument list too long */
#define E2BIG           _PDCLIB_E2BIG
/* Permission denied */
#define EACCES          _PDCLIB_EACCES
/* Address in use */
#define EADDRINUSE      _PDCLIB_EADDRINUSE
/* Address not available */
#define EADDRNOTAVAIL   _PDCLIB_EADDRNOTAVAIL
/* Address family not supported */
#define EAFNOSUPPORT    _PDCLIB_EAFNOSUPPORT
/* Resource unavailable, try again */
#define EAGAIN          _PDCLIB_EAGAIN
/* Connection already in progress */
#define EALREADY        _PDCLIB_EALREADY
/* Bad file descriptor */
#define EBADF           _PDCLIB_EBADF
/* Bad message */
#define EBADMSG         _PDCLIB_EBADMSG
/* Device or resource busy */
#define EBUSY           _PDCLIB_EBUSY
/* Operation canceled */
#define ECANCELED       _PDCLIB_ECANCELED
/* No child processes */
#define ECHILD          _PDCLIB_ECHILD
/* Connection aborted */
#define ECONNABORTED    _PDCLIB_ECONNABORTED
/* Connection refused */
#define ECONNREFUSED    _PDCLIB_ECONNREFUSED
/* Connection reset */
#define ECONNRESET      _PDCLIB_ECONNRESET
/* Resource deadlock would occur */
#define EDEADLK         _PDCLIB_EDEADLK
/* Destination address required */
#define EDESTADDRREQ    _PDCLIB_EDESTADDRREQ
/* File exists */
#define EEXIST          _PDCLIB_EEXIST
/* Bad address */
#define EFAULT          _PDCLIB_EFAULT
/* File too large */
#define EFBIG           _PDCLIB_EFBIG
/* Host is unreachable */
#define EHOSTUNREACH    _PDCLIB_EHOSTUNREACH
/* Identifier removed */
#define EIDRM           _PDCLIB_EIDRM
/* Operation in progress */
#define EINPROGRESS     _PDCLIB_EINPROGRESS
/* Interrupted function */
#define EINTR           _PDCLIB_EINTR
/* Invalid argument */
#define EINVAL          _PDCLIB_EINVAL
/* I/O error */
#define EIO             _PDCLIB_EIO
/* Socket is connected */
#define EISCONN         _PDCLIB_EISCONN
/* Is a directory */
#define EISDIR          _PDCLIB_EISDIR
/* Too many levels of symbolic links */
#define ELOOP           _PDCLIB_ELOOP
/* File descriptor value too large */
#define EMFILE          _PDCLIB_EMFILE
/* Too many links */
#define EMLINK          _PDCLIB_EMLINK
/* Message too large */
#define EMSGSIZE        _PDCLIB_EMSGSIZE
/* Filename too long */
#define ENAMETOOLONG    _PDCLIB_ENAMETOOLONG
/* Network is down */
#define ENETDOWN        _PDCLIB_ENETDOWN
/* Connection aborted by network */
#define ENETRESET       _PDCLIB_ENETRESET
/* Network unreachable */
#define ENETUNREACH     _PDCLIB_ENETUNREACH
/* Too many files open in system */
#define ENFILE          _PDCLIB_ENFILE
/* No buffer space available */
#define ENOBUFS         _PDCLIB_ENOBUFS
/* No message is available on the STREAM head read queue */
#define ENODATA         _PDCLIB_ENODATA
/* No such device */
#define ENODEV          _PDCLIB_ENODEV
/* No such file or directory */
#define ENOENT          _PDCLIB_ENOENT
/* Executable file format error */
#define ENOEXEC         _PDCLIB_ENOEXEC
/* No locks available */
#define ENOLCK          _PDCLIB_ENOLCK
/* Link has been severed */
#define ENOLINK         _PDCLIB_ENOLINK
/* Not enough space */
#define ENOMEM          _PDCLIB_ENOMEM
/* No message of the desired type */
#define ENOMSG          _PDCLIB_ENOMSG
/* Protocol not available */
#define ENOPROTOOPT     _PDCLIB_ENOPROTOOPT
/* No space left on device */
#define ENOSPC          _PDCLIB_ENOSPC
/* No STREAM resources */
#define ENOSR           _PDCLIB_ENOSR
/* Not a STREAM */
#define ENOSTR          _PDCLIB_ENOSTR
/* Function not supported */
#define ENOSYS          _PDCLIB_ENOSYS
/* The socket is not connected */
#define ENOTCONN        _PDCLIB_ENOTCONN
/* Not a directory */
#define ENOTDIR         _PDCLIB_ENOTDIR
/* Directory not empty */
#define ENOTEMPTY       _PDCLIB_ENOTEMPTY
/* State not recoverable */
#define ENOTRECOVERABLE _PDCLIB_ENOTRECOVERABLE
/* Not a socket */
#define ENOTSOCK        _PDCLIB_ENOTSOCK
/* Not supported */
#define ENOTSUP         _PDCLIB_ENOTSUP
/* Inappropriate I/O control operation */
#define ENOTTY          _PDCLIB_ENOTTY
/* No such device or address */
#define ENXIO           _PDCLIB_ENXIO
/* Operation not supported on socket */
#define EOPNOTSUPP      _PDCLIB_EOPNOTSUPP
/* Value too large to be stored in data type */
#define EOVERFLOW       _PDCLIB_EOVERFLOW
/* Previous owner died */
#define EOWNERDEAD      _PDCLIB_EOWNERDEAD
/* Operation not permitted */
#define EPERM           _PDCLIB_EPERM
/* Broken pipe */
#define EPIPE           _PDCLIB_EPIPE
/* Protocol error */
#define EPROTO          _PDCLIB_EPROTO
/* Protocol not supported */
#define EPROTONOSUPPORT _PDCLIB_EPROTONOSUPPORT
/* Protocol wrong type for socket */
#define EPROTOTYPE      _PDCLIB_EPROTOTYPE
/* Read-only file system */
#define EROFS           _PDCLIB_EROFS
/* Invalid seek */
#define ESPIPE          _PDCLIB_ESPIPE
/* No such process */
#define ESRCH           _PDCLIB_ESRCH
/* Stream ioctl() timeout */
#define ETIME           _PDCLIB_ETIME
/* Connection timed out */
#define ETIMEDOUT       _PDCLIB_ETIMEDOUT
/* Text file busy */
#define ETXTBSY         _PDCLIB_ETXTBSY
/* Operation would block */
#define EWOULDBLOCK     _PDCLIB_EWOULDBLOCK
/* Cross-device link */
#define EXDEV           _PDCLIB_EXDEV

/* Annex K -- Bounds-checking interfaces */

#if ( __STDC_WANT_LIB_EXT1__ + 0 ) != 0
#ifndef _PDCLIB_ERRNO_T_DEFINED
#define _PDCLIB_ERRNO_T_DEFINED _PDCLIB_ERRNO_T_DEFINED
typedef int errno_t;
#endif
#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_ERRNO_H
#include _PDCLIB_EXTEND_ERRNO_H
#endif

#ifdef __cplusplus
}
#endif

#endif
