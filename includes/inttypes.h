/* $Id$ */

/* 7.8 Format conversion of integer types <inttypes.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_INTTYPES_H
#define _PDCLIB_INTTYPES_H _PDCLIB_INTTYPES_H

#include <stdint.h>

typedef struct _PDCLIB_imaxdiv_t imaxdiv_t;

#define SCNu32 "u"
#define PRNu32 "u"
/* TODO: Print / Scan Macros */
/*
PRId8   PRIdLEAST8   PRIdFAST8   PRIdMAX
PRId16  PRIdLEAST16  PRIdFAST16  PRIdPTR
PRId32  PRIdLEAST32  PRIdFAST32
PRId64  PRIdLEAST64  PRIdFAST64

PRIi8   PRIiLEAST8   PRIiFAST8   PRIiMAX
PRIi16  PRIiLEAST16  PRIiFAST16  PRIdPTR
PRIi32  PRIiLEAST32  PRIiFAST32
PRIi64  PRIiLEAST64  PRIiFAST64

PRIo8   PRIoLEAST8   PRIoFAST8   PRIoMAX
PRIo16  PRIoLEAST16  PRIoFAST16  PRIoPTR
PRIo32  PRIoLEAST32  PRIoFAST32
PRIo64  PRIoLEAST64  PRIoFAST64

PRIu8   PRIuLEAST8   PRIuFAST8   PRIuMAX
PRIu16  PRIuLEAST16  PRIuFAST16  PRIuPTR
PRIu32  PRIuLEAST32  PRIuFAST32
PRIu64  PRIuLEAST64  PRIuFAST64

PRIx8   PRIxLEAST8   PRIxFAST8   PRIxMAX
PRIx16  PRIxLEAST16  PRIxFAST16  PRIxPTR
PRIx32  PRIxLEAST32  PRIxFAST32
PRIx64  PRIxLEAST64  PRIxFAST64

PRIX8   PRIXLEAST8   PRIXFAST8   PRIXMAX
PRIX16  PRIXLEAST16  PRIXFAST16  PRIXPTR
PRIX32  PRIXLEAST32  PRIXFAST32
PRIX64  PRIXLEAST64  PRIXFAST64

SCNd8   SCNdLEAST8   SCNdFAST8   SCNdMAX
SCNd16  SCNdLEAST16  SCNdFAST16  SCNdPTR
SCNd32  SCNdLEAST32  SCNdFAST32
SCNd64  SCNdLEAST64  SCNdFAST64

SCNi8   SCNiLEAST8   SCNiFAST8   SCNiMAX
SCNi16  SCNiLEAST16  SCNiFAST16  SCNdPTR
SCNi32  SCNiLEAST32  SCNiFAST32
SCNi64  SCNiLEAST64  SCNiFAST64

SCNo8   SCNoLEAST8   SCNoFAST8   SCNoMAX
SCNo16  SCNoLEAST16  SCNoFAST16  SCNoPTR
SCNo32  SCNoLEAST32  SCNoFAST32
SCNo64  SCNoLEAST64  SCNoFAST64

SCNu8   SCNuLEAST8   SCNuFAST8   SCNuMAX
SCNu16  SCNuLEAST16  SCNuFAST16  SCNuPTR
SCNu32  SCNuLEAST32  SCNuFAST32
SCNu64  SCNuLEAST64  SCNuFAST64

SCNx8   SCNxLEAST8   SCNxFAST8   SCNxMAX
SCNx16  SCNxLEAST16  SCNxFAST16  SCNxPTR
SCNx32  SCNxLEAST32  SCNxFAST32
SCNx64  SCNxLEAST64  SCNxFAST64

SCNX8   SCNXLEAST8   SCNXFAST8   SCNXMAX
SCNX16  SCNXLEAST16  SCNXFAST16  SCNXPTR
SCNX32  SCNXLEAST32  SCNXFAST32
SCNX64  SCNXLEAST64  SCNXFAST64
*/

/* 7.8.2 Functions for greatest-width integer types */

/* Calculate the absolute value of j */
intmax_t imaxabs( intmax_t j );

/* Return quotient (quot) and remainder (rem) of an integer division in the
   imaxdiv_t struct.
*/
imaxdiv_t imaxdiv( intmax_t numer, intmax_t denom );

/* Seperate the character array nptr into three parts: A (possibly empty)
   sequence of whitespace characters, a character representation of an integer
   to the given base, and trailing invalid characters (including the terminating
   null character). If base is 0, assume it to be 10, unless the integer
   representation starts with 0x / 0X (setting base to 16) or 0 (setting base to
   8). If given, base can be anything from 0 to 36, using the 26 letters of the
   base alphabet (both lowercase and uppercase) as digits 10 through 35.
   The integer representation is then converted into the return type of the
   function. It can start with a '+' or '-' sign. If the sign is '-', the result
   of the conversion is negated.
   If the conversion is successful, the converted value is returned. If endptr
   is not a NULL pointer, a pointer to the first trailing invalid character is
   returned in *endptr.
   If no conversion could be performed, zero is returned (and nptr in *endptr,
   if endptr is not a NULL pointer). If the converted value does not fit into
   the return type, the functions return INTMAX_MIN, INTMAX_MAX, or UINTMAX_MAX,
   respectively, depending on the sign of the integer representation and the
   return type, and errno is set to ERANGE.
*/
/* This function is equivalent to strtol() / strtoul() in <stdlib.h>, but on
   the potentially larger type.
*/
intmax_t strtoimax( const char * _PDCLIB_restrict nptr, char * * _PDCLIB_restrict endptr, int base );
uintmax_t strtoumax( const char * _PDCLIB_restrict nptr, char * * _PDCLIB_restrict endptr, int base );

/* TODO: wcstoimax(), wcstoumax() */

#endif

