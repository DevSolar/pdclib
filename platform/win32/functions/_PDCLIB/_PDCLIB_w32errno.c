/* _PDCLIB_w32errno( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <errno.h>
#include <wchar.h> // Watcom bug: winnt.h assumes string.h defines wchar_t
#include <windows.h>

void _PDCLIB_w32errno(void);

void _PDCLIB_w32errno(void)
{
    // Not exhaustive
    switch(GetLastError()) {
        case ERROR_SUCCESS:
            return;
        case ERROR_FILE_NOT_FOUND:
        case ERROR_PATH_NOT_FOUND:
        case ERROR_INVALID_DRIVE:
            errno = ENOENT; break;
        case ERROR_TOO_MANY_OPEN_FILES:
            errno = EMFILE; break;
        case ERROR_ACCESS_DENIED:
        case ERROR_WRITE_PROTECT:
            errno = EPERM; break;
        case ERROR_INVALID_HANDLE:
            errno = EBADF; break;
        case ERROR_NOT_ENOUGH_MEMORY:
        case ERROR_OUTOFMEMORY:
            errno = ENOMEM; break;
        case ERROR_NOT_READY:
            errno = EAGAIN; break;
        case ERROR_BAD_LENGTH:
            errno = EINVAL; break;
        default:
            // TODO: reconsider what to use here?
            errno = ENOSYS; break;
    }
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
