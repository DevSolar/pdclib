#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct einfo
{
    char const * string;
    int errno_value;
    char const * text;
} error[] = {

    { "_PDCLIB_E2BIG", E2BIG, "Argument list too long" },
    { "_PDCLIB_EACCES", EACCES, "Permission denied" },
    { "_PDCLIB_EADDRINUSE", EADDRINUSE, "Address in use" },
    { "_PDCLIB_EADDRNOTAVAIL", EADDRNOTAVAIL, "Address not available" },
    { "_PDCLIB_EAFNOSUPPORT", EAFNOSUPPORT, "Address family not supported" },
    { "_PDCLIB_EAGAIN", EAGAIN, "Resource unavailable, try again" },
    { "_PDCLIB_EALREADY", EALREADY, "Connection already in progress" },
    { "_PDCLIB_EBADF", EBADF, "Bad file descriptor" },
    { "_PDCLIB_EBADMSG", EBADMSG, "Bad message" },
    { "_PDCLIB_EBUSY", EBUSY, "Device or resource busy" },
    { "_PDCLIB_ECANCELED", ECANCELED, "Operation canceled" },
    { "_PDCLIB_ECHILD", ECHILD, "No child processes" },
    { "_PDCLIB_ECONNABORTED", ECONNABORTED, "Connection aborted" },
    { "_PDCLIB_ECONNREFUSED", ECONNREFUSED, "Connection refused" },
    { "_PDCLIB_ECONNRESET", ECONNRESET, "Connection reset" },
    { "_PDCLIB_EDEADLK", EDEADLK, "Resource deadlock would occur" },
    { "_PDCLIB_EDESTADDRREQ", EDESTADDRREQ, "Destination address required" },
    { "_PDCLIB_EDOM", EDOM, "Mathematics argument out of domain of function" },
    { "_PDCLIB_EEXIST", EEXIST, "File exists" },
    { "_PDCLIB_EFAULT", EFAULT, "Bad address" },
    { "_PDCLIB_EFBIG", EFBIG, "File too large" },
    { "_PDCLIB_EHOSTUNREACH", EHOSTUNREACH, "Host is unreachable" },
    { "_PDCLIB_EIDRM", EIDRM, "Identifier removed" },
    { "_PDCLIB_EILSEQ", EILSEQ, "Illegal byte sequence" },
    { "_PDCLIB_EINPROGRESS", EINPROGRESS, "Operation in progress" },
    { "_PDCLIB_EINTR", EINTR, "Interrupted function" },
    { "_PDCLIB_EINVAL", EINVAL, "Invalid argument" },
    { "_PDCLIB_EIO", EIO, "I/O error" },
    { "_PDCLIB_EISCONN", EISCONN, "Socket is connected" },
    { "_PDCLIB_EISDIR", EISDIR, "Is a directory" },
    { "_PDCLIB_ELOOP", ELOOP, "Too many levels of symbolic links" },
    { "_PDCLIB_EMFILE", EMFILE, "File descriptor value too large" },
    { "_PDCLIB_EMLINK", EMLINK, "Too many links" },
    { "_PDCLIB_EMSGSIZE", EMSGSIZE, "Message too large" },
    { "_PDCLIB_ENAMETOOLONG", ENAMETOOLONG, "Filename too long" },
    { "_PDCLIB_ENETDOWN", ENETDOWN, "Network is down" },
    { "_PDCLIB_ENETRESET", ENETRESET, "Connection aborted by network" },
    { "_PDCLIB_ENETUNREACH", ENETUNREACH, "Network unreachable" },
    { "_PDCLIB_ENFILE", ENFILE, "Too many files open in system" },
    { "_PDCLIB_ENOBUFS", ENOBUFS, "No buffer space available" },
    { "_PDCLIB_ENODATA", ENODATA, "No message is available on the STREAM head read queue" },
    { "_PDCLIB_ENODEV", ENODEV, "No such device" },
    { "_PDCLIB_ENOENT", ENOENT, "No such file or directory" },
    { "_PDCLIB_ENOEXEC", ENOEXEC, "Executable file format error" },
    { "_PDCLIB_ENOLCK", ENOLCK, "No locks available" },
    { "_PDCLIB_ENOLINK", ENOLINK, "Link has been severed" },
    { "_PDCLIB_ENOMEM", ENOMEM, "Not enough space" },
    { "_PDCLIB_ENOMSG", ENOMSG, "No message of the desired type" },
    { "_PDCLIB_ENOPROTOOPT", ENOPROTOOPT, "Protocol not available" },
    { "_PDCLIB_ENOSPC", ENOSPC, "No space left on device" },
    { "_PDCLIB_ENOSR", ENOSR, "No STREAM resources" },
    { "_PDCLIB_ENOSTR", ENOSTR, "Not a STREAM" },
    { "_PDCLIB_ENOSYS", ENOSYS, "Function not supported" },
    { "_PDCLIB_ENOTCONN", ENOTCONN, "The socket is not connected" },
    { "_PDCLIB_ENOTDIR", ENOTDIR, "Not a directory" },
    { "_PDCLIB_ENOTEMPTY", ENOTEMPTY, "Directory not empty" },
    { "_PDCLIB_ENOTRECOVERABLE", ENOTRECOVERABLE, "State not recoverable" },
    { "_PDCLIB_ENOTSOCK", ENOTSOCK, "Not a socket" },
    { "_PDCLIB_ENOTSUP", ENOTSUP, "Not supported" },
    { "_PDCLIB_ENOTTY", ENOTTY, "Inappropriate I/O control operation" },
    { "_PDCLIB_ENXIO", ENXIO, "No such device or address" },
    { "_PDCLIB_EOPNOTSUPP", EOPNOTSUPP, "Operation not supported on socket" },
    { "_PDCLIB_EOVERFLOW", EOVERFLOW, "Value too large to be stored in data type" },
    { "_PDCLIB_EOWNERDEAD", EOWNERDEAD, "Previous owner died" },
    { "_PDCLIB_EPERM", EPERM, "Operation not permitted" },
    { "_PDCLIB_EPIPE", EPIPE, "Broken pipe" },
    { "_PDCLIB_EPROTO", EPROTO, "Protocol error" },
    { "_PDCLIB_EPROTONOSUPPORT", EPROTONOSUPPORT, "Protocol not supported" },
    { "_PDCLIB_EPROTOTYPE", EPROTOTYPE, "Protocol wrong type for socket" },
    { "_PDCLIB_ERANGE", ERANGE, "Result too large" },
    { "_PDCLIB_EROFS", EROFS, "Read-only file system" },
    { "_PDCLIB_ESPIPE", ESPIPE, "Invalid seek" },
    { "_PDCLIB_ESRCH", ESRCH, "No such process" },
    { "_PDCLIB_ETIME", ETIME, "Stream ioctl() timeout" },
    { "_PDCLIB_ETIMEDOUT", ETIMEDOUT, "Connection timed out" },
    { "_PDCLIB_ETXTBSY", ETXTBSY, "Text file busy" },
    { "_PDCLIB_EWOULDBLOCK", EWOULDBLOCK, "Operation would block" },
    { "_PDCLIB_EXDEV", EXDEV, "Cross-device link" },

};

int main( int argc, char * argv[] )
{
    size_t errno_max = 0;
    size_t text_len_max = 0;
    size_t string_len_max = 0;

    for ( size_t i = 0; i < sizeof( error ) / sizeof( error[0] ); ++i )
    {
        if ( error[i].errno_value > errno_max )
        {
            errno_max = error[i].errno_value;
        }

        if ( strlen( error[i].string ) > string_len_max )
        {
            string_len_max = strlen( error[i].string );
        }

        if ( strlen( error[i].text ) > text_len_max )
        {
            text_len_max = strlen( error[i].text );
        }
    }

    for ( size_t i = 0; i < sizeof( error ) / sizeof( error[0] ); ++i )
    {
        printf( "/* %s */\n#define %-*s %3d\n", error[i].text, string_len_max, error[i].string, error[i].errno_value );
    }

    string_len_max -= 8;
    struct einfo * sortlst = malloc( sizeof( struct einfo ) * ( errno_max + 1 ) );

    for ( size_t i = 0; i <= errno_max; ++i )
    {
        int index = -1;

        for ( size_t j = 0; j < sizeof( error ) / sizeof( error[0] ); ++j )
        {
            if ( error[j].errno_value == i )
            {
                index = j;
                break;
            }
        }

        if ( index >= 0 )
        {
            printf( "        /* %-*s */ (char *)\"%s (%s)\",\n", string_len_max, error[index].string + 8, error[index].string + 8, error[index].text );
        }
        else
        {
            printf( "        /* %-*s */ (char *)\"unknown error\",\n", string_len_max, "unknown error" );
        }
    }
}
