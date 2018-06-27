/* _PDCLIB_stdstream

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <locale.h>
#include <limits.h>

#ifndef REGTEST
#include "_PDCLIB_io.h"
#include <threads.h>

static char _PDCLIB_sin_buffer[BUFSIZ];
static char _PDCLIB_sout_buffer[BUFSIZ];
static char _PDCLIB_serr_buffer[BUFSIZ];

static unsigned char _PDCLIB_sin_ungetbuf[_PDCLIB_UNGETCBUFSIZE];
static unsigned char _PDCLIB_sout_ungetbuf[_PDCLIB_UNGETCBUFSIZE];
static unsigned char _PDCLIB_serr_ungetbuf[_PDCLIB_UNGETCBUFSIZE];

extern _PDCLIB_fileops_t _PDCLIB_fileops;

static FILE _PDCLIB_serr = {
    .ops        = &_PDCLIB_fileops,
    .handle     = { .pointer = NULL },
    .buffer     = _PDCLIB_serr_buffer,
    .bufsize    = BUFSIZ,
    .bufidx     = 0,
    .bufend     = 0,
    .ungetidx   = 0,
    .ungetbuf   = _PDCLIB_serr_ungetbuf,
    .status     = _IONBF | _PDCLIB_FWRITE | _PDCLIB_STATIC,
    .filename   = NULL,
    .next       = NULL,
};
static FILE _PDCLIB_sout = {
    .ops        = &_PDCLIB_fileops,
    .handle     = { .pointer = NULL },
    .buffer     = _PDCLIB_sout_buffer,
    .bufsize    = BUFSIZ,
    .bufidx     = 0,
    .bufend     = 0,
    .ungetidx   = 0,
    .ungetbuf   = _PDCLIB_sout_ungetbuf,
    .status     = _IOLBF | _PDCLIB_FWRITE | _PDCLIB_STATIC,
    .filename   = NULL,
    .next       = &_PDCLIB_serr
};
static FILE _PDCLIB_sin  = {
    .ops        = &_PDCLIB_fileops,
    .handle     = { .pointer = NULL },
    .buffer     = _PDCLIB_sin_buffer,
    .bufsize    = BUFSIZ,
    .bufidx     = 0,
    .bufend     = 0,
    .ungetidx   = 0,
    .ungetbuf   = _PDCLIB_sin_ungetbuf,
    .status     = _IOLBF | _PDCLIB_FREAD | _PDCLIB_STATIC,
    .filename   = NULL,
    .next       = &_PDCLIB_sout
};

FILE * stdin  = &_PDCLIB_sin;
FILE * stdout = &_PDCLIB_sout;
FILE * stderr = &_PDCLIB_serr;

FILE * _PDCLIB_filelist = &_PDCLIB_sin;

/* Todo: Better solution than this! */
__attribute__((constructor)) static void init_stdio(void)
{
    _PDCLIB_initclocale( &_PDCLIB_global_locale );
    mtx_init(&stdin->lock,  mtx_recursive);
    mtx_init(&stdout->lock, mtx_recursive);
    mtx_init(&stderr->lock, mtx_recursive);
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    /* Testing covered by several other testdrivers using stdin / stdout /
       stderr.
    */
    return TEST_RESULTS;
}

#endif
