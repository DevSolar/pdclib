/* _PDCLIB_stdinit

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example initialization of stdin, stdout and stderr to the integer
   file descriptors 0, 1, and 2, respectively. This applies for a great variety
   of operating systems, including POSIX compliant ones.
*/

#include <stdio.h>
#include <locale.h>
#include <limits.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

/* In a POSIX system, stdin / stdout / stderr are equivalent to the (int) file
   descriptors 0, 1, and 2 respectively.
*/
/* TODO: This is proof-of-concept, requires finetuning. */
static char _PDCLIB_sin_buffer[BUFSIZ];
static char _PDCLIB_sout_buffer[BUFSIZ];
static char _PDCLIB_serr_buffer[BUFSIZ];

static struct _PDCLIB_file_t _PDCLIB_serr = { 2, _PDCLIB_serr_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, { 0 }, _IONBF | _PDCLIB_FWRITE,
#ifndef __STDC_NO_THREADS__
    _PDCLIB_MTX_RECURSIVE_INIT,
#endif
    NULL, NULL
};
static struct _PDCLIB_file_t _PDCLIB_sout = { 1, _PDCLIB_sout_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, { 0 }, _IOLBF | _PDCLIB_FWRITE,
#ifndef __STDC_NO_THREADS__
    _PDCLIB_MTX_RECURSIVE_INIT,
#endif
    NULL, &_PDCLIB_serr
};
static struct _PDCLIB_file_t _PDCLIB_sin  = { 0, _PDCLIB_sin_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, { 0 }, _IOLBF | _PDCLIB_FREAD,
#ifndef __STDC_NO_THREADS__
    _PDCLIB_MTX_RECURSIVE_INIT,
#endif
    NULL, &_PDCLIB_sout
};

struct _PDCLIB_file_t * stdin  = &_PDCLIB_sin;
struct _PDCLIB_file_t * stdout = &_PDCLIB_sout;
struct _PDCLIB_file_t * stderr = &_PDCLIB_serr;

/* FIXME: This approach is a possible attack vector. */
struct _PDCLIB_file_t * _PDCLIB_filelist = &_PDCLIB_sin;

#ifndef __STDC_NO_THREADS__
_PDCLIB_mtx_t _PDCLIB_filelist_mtx = _PDCLIB_MTX_PLAIN_INIT;
_PDCLIB_mtx_t _PDCLIB_time_mtx = _PDCLIB_MTX_PLAIN_INIT;
#endif

/* "C" locale - defaulting to ASCII-7.
   1 kByte (+ 4 byte) of <ctype.h> data.
   Each line: flags, lowercase, uppercase.
*/
static struct _PDCLIB_lc_ctype_entry_t _ctype_entries_C[ _PDCLIB_CHARSET_SIZE + 1 ] =
{
    { /* EOF */    0,    0,    0 },
    { /* NUL */ _PDCLIB_CTYPE_CNTRL,                                             0x00, 0x00 },
    { /* SOH */ _PDCLIB_CTYPE_CNTRL,                                             0x01, 0x01 },
    { /* STX */ _PDCLIB_CTYPE_CNTRL,                                             0x02, 0x02 },
    { /* ETX */ _PDCLIB_CTYPE_CNTRL,                                             0x03, 0x03 },
    { /* EOT */ _PDCLIB_CTYPE_CNTRL,                                             0x04, 0x04 },
    { /* ENQ */ _PDCLIB_CTYPE_CNTRL,                                             0x05, 0x05 },
    { /* ACK */ _PDCLIB_CTYPE_CNTRL,                                             0x06, 0x06 },
    { /* BEL */ _PDCLIB_CTYPE_CNTRL,                                             0x07, 0x07 },
    { /*  BS */ _PDCLIB_CTYPE_CNTRL,                                             0x08, 0x08 },
    { /*  HT */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_BLANK | _PDCLIB_CTYPE_SPACE, 0x09, 0x09 },
    { /*  LF */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_SPACE,                       0x0A, 0x0A },
    { /*  VT */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_SPACE,                       0x0B, 0x0B },
    { /*  FF */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_SPACE,                       0x0C, 0x0C },
    { /*  CR */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_SPACE,                       0x0D, 0x0D },
    { /*  SO */ _PDCLIB_CTYPE_CNTRL,                                             0x0E, 0x0E },
    { /*  SI */ _PDCLIB_CTYPE_CNTRL,                                             0x0F, 0x0F },
    { /* DLE */ _PDCLIB_CTYPE_CNTRL,                                             0x10, 0x10 },
    { /* DC1 */ _PDCLIB_CTYPE_CNTRL,                                             0x11, 0x11 },
    { /* DC2 */ _PDCLIB_CTYPE_CNTRL,                                             0x12, 0x12 },
    { /* DC3 */ _PDCLIB_CTYPE_CNTRL,                                             0x13, 0x13 },
    { /* DC4 */ _PDCLIB_CTYPE_CNTRL,                                             0x14, 0x14 },
    { /* NAK */ _PDCLIB_CTYPE_CNTRL,                                             0x15, 0x15 },
    { /* SYN */ _PDCLIB_CTYPE_CNTRL,                                             0x16, 0x16 },
    { /* ETB */ _PDCLIB_CTYPE_CNTRL,                                             0x17, 0x17 },
    { /* CAN */ _PDCLIB_CTYPE_CNTRL,                                             0x18, 0x18 },
    { /*  EM */ _PDCLIB_CTYPE_CNTRL,                                             0x19, 0x19 },
    { /* SUB */ _PDCLIB_CTYPE_CNTRL,                                             0x1A, 0x1A },
    { /* ESC */ _PDCLIB_CTYPE_CNTRL,                                             0x1B, 0x1B },
    { /*  FS */ _PDCLIB_CTYPE_CNTRL,                                             0x1C, 0x1C },
    { /*  GS */ _PDCLIB_CTYPE_CNTRL,                                             0x1D, 0x1D },
    { /*  RS */ _PDCLIB_CTYPE_CNTRL,                                             0x1E, 0x1E },
    { /*  US */ _PDCLIB_CTYPE_CNTRL,                                             0x1F, 0x1F },
    { /*  SP */ _PDCLIB_CTYPE_BLANK | _PDCLIB_CTYPE_SPACE,                       0x20, 0x20 },
    { /* '!' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x21, 0x21 },
    { /* '"' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x22, 0x22 },
    { /* '#' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x23, 0x23 },
    { /* '$' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x24, 0x24 },
    { /* '%' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x25, 0x25 },
    { /* '&' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x26, 0x26 },
    { /* ''' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x27, 0x27 },
    { /* '(' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x28, 0x28 },
    { /* ')' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x29, 0x29 },
    { /* '*' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2A, 0x2A },
    { /* '+' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2B, 0x2B },
    { /* ',' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2C, 0x2C },
    { /* '-' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2D, 0x2D },
    { /* '.' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2E, 0x2E },
    { /* '/' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2F, 0x2F },
    { /* '0' */ _PDCLIB_CTYPE_GRAPH,                                             0x30, 0x30 },
    { /* '1' */ _PDCLIB_CTYPE_GRAPH,                                             0x31, 0x31 },
    { /* '2' */ _PDCLIB_CTYPE_GRAPH,                                             0x32, 0x32 },
    { /* '3' */ _PDCLIB_CTYPE_GRAPH,                                             0x33, 0x33 },
    { /* '4' */ _PDCLIB_CTYPE_GRAPH,                                             0x34, 0x34 },
    { /* '5' */ _PDCLIB_CTYPE_GRAPH,                                             0x35, 0x35 },
    { /* '6' */ _PDCLIB_CTYPE_GRAPH,                                             0x36, 0x36 },
    { /* '7' */ _PDCLIB_CTYPE_GRAPH,                                             0x37, 0x37 },
    { /* '8' */ _PDCLIB_CTYPE_GRAPH,                                             0x38, 0x38 },
    { /* '9' */ _PDCLIB_CTYPE_GRAPH,                                             0x39, 0x39 },
    { /* ':' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3A, 0x3A },
    { /* ';' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3B, 0x3B },
    { /* '<' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3C, 0x3C },
    { /* '=' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3D, 0x3D },
    { /* '>' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3E, 0x3E },
    { /* '?' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3F, 0x3F },
    { /* '@' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x40, 0x40 },
    { /* 'A' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x41, 0x61 },
    { /* 'B' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x42, 0x62 },
    { /* 'C' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x43, 0x63 },
    { /* 'D' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x44, 0x64 },
    { /* 'E' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x45, 0x65 },
    { /* 'F' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x46, 0x66 },
    { /* 'G' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x47, 0x67 },
    { /* 'H' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x48, 0x68 },
    { /* 'I' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x49, 0x69 },
    { /* 'J' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4A, 0x6A },
    { /* 'K' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4B, 0x6B },
    { /* 'L' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4C, 0x6C },
    { /* 'M' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4D, 0x6D },
    { /* 'N' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4E, 0x6E },
    { /* 'O' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4F, 0x6F },
    { /* 'P' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x50, 0x70 },
    { /* 'Q' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x51, 0x71 },
    { /* 'R' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x52, 0x72 },
    { /* 'S' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x53, 0x73 },
    { /* 'T' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x54, 0x74 },
    { /* 'U' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x55, 0x75 },
    { /* 'V' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x56, 0x76 },
    { /* 'W' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x57, 0x77 },
    { /* 'X' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x58, 0x78 },
    { /* 'Y' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x59, 0x79 },
    { /* 'Z' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x5A, 0x7A },
    { /* '[' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5B, 0x5B },
    { /* '\' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5C, 0x5C },
    { /* ']' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5D, 0x5D },
    { /* '^' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5E, 0x5E },
    { /* '_' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5F, 0x5F },
    { /* '`' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x60, 0x60 },
    { /* 'a' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x41, 0x61 },
    { /* 'b' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x42, 0x62 },
    { /* 'c' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x43, 0x63 },
    { /* 'd' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x44, 0x64 },
    { /* 'e' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x45, 0x65 },
    { /* 'f' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x46, 0x66 },
    { /* 'g' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x47, 0x67 },
    { /* 'h' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x48, 0x68 },
    { /* 'i' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x49, 0x69 },
    { /* 'j' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4A, 0x6A },
    { /* 'k' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4B, 0x6B },
    { /* 'l' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4C, 0x6C },
    { /* 'm' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4D, 0x6D },
    { /* 'n' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4E, 0x6E },
    { /* 'o' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4F, 0x6F },
    { /* 'p' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x50, 0x70 },
    { /* 'q' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x51, 0x71 },
    { /* 'r' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x52, 0x72 },
    { /* 's' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x53, 0x73 },
    { /* 't' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x54, 0x74 },
    { /* 'u' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x55, 0x75 },
    { /* 'v' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x56, 0x76 },
    { /* 'w' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x57, 0x77 },
    { /* 'x' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x58, 0x78 },
    { /* 'y' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x59, 0x79 },
    { /* 'z' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x5A, 0x7A },
    { /* '{' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x7B, 0x7B },
    { /* '|' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x7C, 0x7C },
    { /* '}' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x7D, 0x7D },
    { /* '~' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x7E, 0x7E },
    { /* DEL */ _PDCLIB_CTYPE_CNTRL,                                             0x7F, 0x7F },
    { 0x00, 0x80, 0x80 },
    { 0x00, 0x81, 0x81 },
    { 0x00, 0x82, 0x82 },
    { 0x00, 0x83, 0x83 },
    { 0x00, 0x84, 0x84 },
    { 0x00, 0x85, 0x85 },
    { 0x00, 0x86, 0x86 },
    { 0x00, 0x87, 0x87 },
    { 0x00, 0x88, 0x88 },
    { 0x00, 0x89, 0x89 },
    { 0x00, 0x8A, 0x8A },
    { 0x00, 0x8B, 0x8B },
    { 0x00, 0x8C, 0x8C },
    { 0x00, 0x8D, 0x8D },
    { 0x00, 0x8E, 0x8E },
    { 0x00, 0x8F, 0x8F },
    { 0x00, 0x90, 0x90 },
    { 0x00, 0x91, 0x91 },
    { 0x00, 0x92, 0x92 },
    { 0x00, 0x93, 0x93 },
    { 0x00, 0x94, 0x94 },
    { 0x00, 0x95, 0x95 },
    { 0x00, 0x96, 0x96 },
    { 0x00, 0x97, 0x97 },
    { 0x00, 0x98, 0x98 },
    { 0x00, 0x99, 0x99 },
    { 0x00, 0x9A, 0x9A },
    { 0x00, 0x9B, 0x9B },
    { 0x00, 0x9C, 0x9C },
    { 0x00, 0x9D, 0x9D },
    { 0x00, 0x9E, 0x9E },
    { 0x00, 0x9F, 0x9F },
    { 0x00, 0xA0, 0xA0 },
    { 0x00, 0xA1, 0xA1 },
    { 0x00, 0xA2, 0xA2 },
    { 0x00, 0xA3, 0xA3 },
    { 0x00, 0xA4, 0xA4 },
    { 0x00, 0xA5, 0xA5 },
    { 0x00, 0xA6, 0xA6 },
    { 0x00, 0xA7, 0xA7 },
    { 0x00, 0xA8, 0xA8 },
    { 0x00, 0xA9, 0xA9 },
    { 0x00, 0xAA, 0xAA },
    { 0x00, 0xAB, 0xAB },
    { 0x00, 0xAC, 0xAC },
    { 0x00, 0xAD, 0xAD },
    { 0x00, 0xAE, 0xAE },
    { 0x00, 0xAF, 0xAF },
    { 0x00, 0xB0, 0xB0 },
    { 0x00, 0xB1, 0xB1 },
    { 0x00, 0xB2, 0xB2 },
    { 0x00, 0xB3, 0xB3 },
    { 0x00, 0xB4, 0xB4 },
    { 0x00, 0xB5, 0xB5 },
    { 0x00, 0xB6, 0xB6 },
    { 0x00, 0xB7, 0xB7 },
    { 0x00, 0xB8, 0xB8 },
    { 0x00, 0xB9, 0xB9 },
    { 0x00, 0xBA, 0xBA },
    { 0x00, 0xBB, 0xBB },
    { 0x00, 0xBC, 0xBC },
    { 0x00, 0xBD, 0xBD },
    { 0x00, 0xBE, 0xBE },
    { 0x00, 0xBF, 0xBF },
    { 0x00, 0xC0, 0xC0 },
    { 0x00, 0xC1, 0xC1 },
    { 0x00, 0xC2, 0xC2 },
    { 0x00, 0xC3, 0xC3 },
    { 0x00, 0xC4, 0xC4 },
    { 0x00, 0xC5, 0xC5 },
    { 0x00, 0xC6, 0xC6 },
    { 0x00, 0xC7, 0xC7 },
    { 0x00, 0xC8, 0xC8 },
    { 0x00, 0xC9, 0xC9 },
    { 0x00, 0xCA, 0xCA },
    { 0x00, 0xCB, 0xCB },
    { 0x00, 0xCC, 0xCC },
    { 0x00, 0xCD, 0xCD },
    { 0x00, 0xCE, 0xCE },
    { 0x00, 0xCF, 0xCF },
    { 0x00, 0xD0, 0xD0 },
    { 0x00, 0xD1, 0xD1 },
    { 0x00, 0xD2, 0xD2 },
    { 0x00, 0xD3, 0xD3 },
    { 0x00, 0xD4, 0xD4 },
    { 0x00, 0xD5, 0xD5 },
    { 0x00, 0xD6, 0xD6 },
    { 0x00, 0xD7, 0xD7 },
    { 0x00, 0xD8, 0xD8 },
    { 0x00, 0xD9, 0xD9 },
    { 0x00, 0xDA, 0xDA },
    { 0x00, 0xDB, 0xDB },
    { 0x00, 0xDC, 0xDC },
    { 0x00, 0xDD, 0xDD },
    { 0x00, 0xDE, 0xDE },
    { 0x00, 0xDF, 0xDF },
    { 0x00, 0xE0, 0xE0 },
    { 0x00, 0xE1, 0xE1 },
    { 0x00, 0xE2, 0xE2 },
    { 0x00, 0xE3, 0xE3 },
    { 0x00, 0xE4, 0xE4 },
    { 0x00, 0xE5, 0xE5 },
    { 0x00, 0xE6, 0xE6 },
    { 0x00, 0xE7, 0xE7 },
    { 0x00, 0xE8, 0xE8 },
    { 0x00, 0xE9, 0xE9 },
    { 0x00, 0xEA, 0xEA },
    { 0x00, 0xEB, 0xEB },
    { 0x00, 0xEC, 0xEC },
    { 0x00, 0xED, 0xED },
    { 0x00, 0xEE, 0xEE },
    { 0x00, 0xEF, 0xEF },
    { 0x00, 0xF0, 0xF0 },
    { 0x00, 0xF1, 0xF1 },
    { 0x00, 0xF2, 0xF2 },
    { 0x00, 0xF3, 0xF3 },
    { 0x00, 0xF4, 0xF4 },
    { 0x00, 0xF5, 0xF5 },
    { 0x00, 0xF6, 0xF6 },
    { 0x00, 0xF7, 0xF7 },
    { 0x00, 0xF8, 0xF8 },
    { 0x00, 0xF9, 0xF9 },
    { 0x00, 0xFA, 0xFA },
    { 0x00, 0xFB, 0xFB },
    { 0x00, 0xFC, 0xFC },
    { 0x00, 0xFD, 0xFD },
    { 0x00, 0xFE, 0xFE },
    { 0x00, 0xFF, 0xFF }
};

struct _PDCLIB_lc_ctype_t _PDCLIB_lc_ctype_C = { 0, 0x30, 0x39, 0x41, 0x46, 0x61, 0x66, &_ctype_entries_C[1] };
struct _PDCLIB_lc_ctype_t * _PDCLIB_lc_ctype = &_PDCLIB_lc_ctype_C;

struct _PDCLIB_lc_collate_t _PDCLIB_lc_collate_C = { 0 };
struct _PDCLIB_lc_collate_t * _PDCLIB_lc_collate = &_PDCLIB_lc_collate_C;

struct lconv _PDCLIB_lconv =
{
    /* decimal_point      */ ( char * )".",
    /* thousands_sep      */ ( char * )"",
    /* grouping           */ ( char * )"",
    /* mon_decimal_point  */ ( char * )"",
    /* mon_thousands_sep  */ ( char * )"",
    /* mon_grouping       */ ( char * )"",
    /* positive_sign      */ ( char * )"",
    /* negative_sign      */ ( char * )"",
    /* currency_symbol    */ ( char * )"",
    /* int_curr_symbol    */ ( char * )"",
    /* frac_digits        */ CHAR_MAX,
    /* p_cs_precedes      */ CHAR_MAX,
    /* n_cs_precedes      */ CHAR_MAX,
    /* p_sep_by_space     */ CHAR_MAX,
    /* n_sep_by_space     */ CHAR_MAX,
    /* p_sign_posn        */ CHAR_MAX,
    /* n_sign_posn        */ CHAR_MAX,
    /* int_frac_digits    */ CHAR_MAX,
    /* int_p_cs_precedes  */ CHAR_MAX,
    /* int_n_cs_precedes  */ CHAR_MAX,
    /* int_p_sep_by_space */ CHAR_MAX,
    /* int_n_sep_by_space */ CHAR_MAX,
    /* int_p_sign_posn    */ CHAR_MAX,
    /* int_n_sign_posn    */ CHAR_MAX
};

struct _PDCLIB_lc_numeric_monetary_t _PDCLIB_lc_numeric_monetary =
{
    &_PDCLIB_lconv,
    0, /* numeric_allocated  */
    0  /* monetary_allocated */
};

struct _PDCLIB_lc_messages_t _PDCLIB_lc_messages_C =
{
    0,
    /* _PDCLIB_errno_texts */
    {
        /* unknown error   */ ( char * )"unknown error",
        /* EPERM           */ ( char * )"EPERM (Operation not permitted)",
        /* ENOENT          */ ( char * )"ENOENT (No such file or directory)",
        /* ESRCH           */ ( char * )"ESRCH (No such process)",
        /* EINTR           */ ( char * )"EINTR (Interrupted function)",
        /* EIO             */ ( char * )"EIO (I/O error)",
        /* ENXIO           */ ( char * )"ENXIO (No such device or address)",
        /* E2BIG           */ ( char * )"E2BIG (Argument list too long)",
        /* ENOEXEC         */ ( char * )"ENOEXEC (Executable file format error)",
        /* EBADF           */ ( char * )"EBADF (Bad file descriptor)",
        /* ECHILD          */ ( char * )"ECHILD (No child processes)",
        /* EAGAIN          */ ( char * )"EAGAIN (Resource unavailable, try again)",
        /* ENOMEM          */ ( char * )"ENOMEM (Not enough space)",
        /* EACCES          */ ( char * )"EACCES (Permission denied)",
        /* EFAULT          */ ( char * )"EFAULT (Bad address)",
        /* unknown error   */ ( char * )"unknown error",
        /* EBUSY           */ ( char * )"EBUSY (Device or resource busy)",
        /* EEXIST          */ ( char * )"EEXIST (File exists)",
        /* EXDEV           */ ( char * )"EXDEV (Cross-device link)",
        /* ENODEV          */ ( char * )"ENODEV (No such device)",
        /* ENOTDIR         */ ( char * )"ENOTDIR (Not a directory)",
        /* EISDIR          */ ( char * )"EISDIR (Is a directory)",
        /* EINVAL          */ ( char * )"EINVAL (Invalid argument)",
        /* ENFILE          */ ( char * )"ENFILE (Too many files open in system)",
        /* EMFILE          */ ( char * )"EMFILE (File descriptor value too large)",
        /* ENOTTY          */ ( char * )"ENOTTY (Inappropriate I/O control operation)",
        /* ETXTBSY         */ ( char * )"ETXTBSY (Text file busy)",
        /* EFBIG           */ ( char * )"EFBIG (File too large)",
        /* ENOSPC          */ ( char * )"ENOSPC (No space left on device)",
        /* ESPIPE          */ ( char * )"ESPIPE (Invalid seek)",
        /* EROFS           */ ( char * )"EROFS (Read-only file system)",
        /* EMLINK          */ ( char * )"EMLINK (Too many links)",
        /* EPIPE           */ ( char * )"EPIPE (Broken pipe)",
        /* EDOM            */ ( char * )"EDOM (Mathematics argument out of domain of function)",
        /* ERANGE          */ ( char * )"ERANGE (Result too large)",
        /* EDEADLK         */ ( char * )"EDEADLK (Resource deadlock would occur)",
        /* ENAMETOOLONG    */ ( char * )"ENAMETOOLONG (Filename too long)",
        /* ENOLCK          */ ( char * )"ENOLCK (No locks available)",
        /* ENOSYS          */ ( char * )"ENOSYS (Function not supported)",
        /* ENOTEMPTY       */ ( char * )"ENOTEMPTY (Directory not empty)",
        /* ELOOP           */ ( char * )"ELOOP (Too many levels of symbolic links)",
        /* unknown error   */ ( char * )"unknown error",
        /* ENOMSG          */ ( char * )"ENOMSG (No message of the desired type)",
        /* EIDRM           */ ( char * )"EIDRM (Identifier removed)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* ENOSTR          */ ( char * )"ENOSTR (Not a STREAM)",
        /* ENODATA         */ ( char * )"ENODATA (No message is available on the STREAM head read queue)",
        /* ETIME           */ ( char * )"ETIME (Stream ioctl() timeout)",
        /* ENOSR           */ ( char * )"ENOSR (No STREAM resources)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* ENOLINK         */ ( char * )"ENOLINK (Link has been severed)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* EPROTO          */ ( char * )"EPROTO (Protocol error)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* EBADMSG         */ ( char * )"EBADMSG (Bad message)",
        /* EOVERFLOW       */ ( char * )"EOVERFLOW (Value too large to be stored in data type)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* EILSEQ          */ ( char * )"EILSEQ (Illegal byte sequence)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* ENOTSOCK        */ ( char * )"ENOTSOCK (Not a socket)",
        /* EDESTADDRREQ    */ ( char * )"EDESTADDRREQ (Destination address required)",
        /* EMSGSIZE        */ ( char * )"EMSGSIZE (Message too large)",
        /* EPROTOTYPE      */ ( char * )"EPROTOTYPE (Protocol wrong type for socket)",
        /* ENOPROTOOPT     */ ( char * )"ENOPROTOOPT (Protocol not available)",
        /* EPROTONOSUPPORT */ ( char * )"EPROTONOSUPPORT (Protocol not supported)",
        /* unknown error   */ ( char * )"unknown error",
        /* ENOTSUP         */ ( char * )"ENOTSUP (Not supported)",
        /* unknown error   */ ( char * )"unknown error",
        /* EAFNOSUPPORT    */ ( char * )"EAFNOSUPPORT (Address family not supported)",
        /* EADDRINUSE      */ ( char * )"EADDRINUSE (Address in use)",
        /* EADDRNOTAVAIL   */ ( char * )"EADDRNOTAVAIL (Address not available)",
        /* ENETDOWN        */ ( char * )"ENETDOWN (Network is down)",
        /* ENETUNREACH     */ ( char * )"ENETUNREACH (Network unreachable)",
        /* ENETRESET       */ ( char * )"ENETRESET (Connection aborted by network)",
        /* ECONNABORTED    */ ( char * )"ECONNABORTED (Connection aborted)",
        /* ECONNRESET      */ ( char * )"ECONNRESET (Connection reset)",
        /* ENOBUFS         */ ( char * )"ENOBUFS (No buffer space available)",
        /* EISCONN         */ ( char * )"EISCONN (Socket is connected)",
        /* ENOTCONN        */ ( char * )"ENOTCONN (The socket is not connected)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* ETIMEDOUT       */ ( char * )"ETIMEDOUT (Connection timed out)",
        /* ECONNREFUSED    */ ( char * )"ECONNREFUSED (Connection refused)",
        /* unknown error   */ ( char * )"unknown error",
        /* EHOSTUNREACH    */ ( char * )"EHOSTUNREACH (Host is unreachable)",
        /* EALREADY        */ ( char * )"EALREADY (Connection already in progress)",
        /* EINPROGRESS     */ ( char * )"EINPROGRESS (Operation in progress)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* ECANCELED       */ ( char * )"ECANCELED (Operation canceled)",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* unknown error   */ ( char * )"unknown error",
        /* EOWNERDEAD      */ ( char * )"EOWNERDEAD (Previous owner died)",
        /* ENOTRECOVERABLE */ ( char * )"ENOTRECOVERABLE (State not recoverable)",
    }
};

struct _PDCLIB_lc_messages_t * _PDCLIB_lc_messages = &_PDCLIB_lc_messages_C;

struct _PDCLIB_lc_time_t _PDCLIB_lc_time_C =
{
    0,
    /* _PDCLIB_month_name_abbr */
    {
        ( char * )"Jan",
        ( char * )"Feb",
        ( char * )"Mar",
        ( char * )"Apr",
        ( char * )"May",
        ( char * )"Jun",
        ( char * )"Jul",
        ( char * )"Aug",
        ( char * )"Sep",
        ( char * )"Oct",
        ( char * )"Nov",
        ( char * )"Dec"
    },
    /* _PDCLIB_month_name_full */
    {
        ( char * )"January",
        ( char * )"February",
        ( char * )"March",
        ( char * )"April",
        ( char * )"May",
        ( char * )"June",
        ( char * )"July",
        ( char * )"August",
        ( char * )"September",
        ( char * )"October",
        ( char * )"November",
        ( char * )"December"
    },
    /* _PDCLIB_day_name_abbr */
    {
        ( char * )"Sun",
        ( char * )"Mon",
        ( char * )"Tue",
        ( char * )"Wed",
        ( char * )"Thu",
        ( char * )"Fri",
        ( char * )"Sat"
    },
    /* _PDCLIB_day_name_full */
    {
        ( char * )"Sunday",
        ( char * )"Monday",
        ( char * )"Tuesday",
        ( char * )"Wednesday",
        ( char * )"Thursday",
        ( char * )"Friday",
        ( char * )"Saturday"
    },
    /* date / time format */ ( char * )"%a %b %e %T %Y",
    /* 12h time format    */ ( char * )"%I:%M:%S %p",
    /* date format        */ ( char * )"%m/%d/%y",
    /* time format        */ ( char * )"%T",
    /* AM / PM designation */
    {
        ( char * )"AM",
        ( char * )"PM"
    }
};

struct _PDCLIB_lc_time_t * _PDCLIB_lc_time = &_PDCLIB_lc_time_C;

struct state _PDCLIB_lclmem;
struct state _PDCLIB_gmtmem;

/* Section 4.12.3 of X3.159-1989 requires that
    Except for the strftime function, these functions [asctime,
    ctime, gmtime, localtime] return values in one of two static
    objects: a broken-down time structure and an array of char.
   Thanks to Paul Eggert for noting this.
*/
struct tm _PDCLIB_tm;

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
