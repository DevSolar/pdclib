/* _PDCLIB_open(_PDCLIB_fd_t*, const _PDCLIB_fileops_t**,
                char const*, unsigned int)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/
#ifndef REGTEST
#include "_PDCLIB_glue.h"
#include "_PDCLIB_io.h"
#include <fcntl.h>


extern const _PDCLIB_fileops_t _PDCLIB_fileops;

bool _PDCLIB_open(
   _PDCLIB_fd_t* fd, const _PDCLIB_fileops_t** ops,
   char const * filename, unsigned int mode )
{
    int osmode;
    switch ( mode & ( _PDCLIB_FREAD | _PDCLIB_FWRITE | _PDCLIB_FAPPEND | _PDCLIB_FRW ) )
    {
        case _PDCLIB_FREAD: /* "r" */
            osmode = O_RDONLY;
            break;
        case _PDCLIB_FWRITE: /* "w" */
            osmode = O_WRONLY | O_CREAT | O_TRUNC;
            break;
        case _PDCLIB_FAPPEND: /* "a" */
            osmode = O_WRONLY | O_APPEND | O_CREAT;
            break;
        case _PDCLIB_FREAD | _PDCLIB_FRW: /* "r+" */
            osmode = O_RDWR;
            break;
        case _PDCLIB_FWRITE | _PDCLIB_FRW: /* "w+" */
            osmode = O_RDWR | O_CREAT | O_TRUNC;
            break;
        case _PDCLIB_FAPPEND | _PDCLIB_FRW: /* "a+" */
            osmode = O_RDWR | O_APPEND | O_CREAT;
            break;
        default: /* Invalid mode */
            return -1;
    }

    fd->sval = open(filename, osmode, 0664);
    if(fd->sval == -1) {
        return false;
    }

    *ops = &_PDCLIB_fileops;
    return true;
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
