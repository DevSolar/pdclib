// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Format conversion of integer types
// ----------------------------------------------------------------------------

#ifndef __INTTYPES_H
#define __INTTYPES_H __INTTYPES_H

// TODO: Documentation

// ----------------------------------------------------------------------------
// TYPEDEFS

typedef struct
{
 intmax_t quotient,
 intmax_t remainder;
}
imaxdiv_t;

// ----------------------------------------------------------------------------
// FUNCTIONS - C++

#ifdef __cplusplus
intmax_t abs( intmax_t i );
imaxdiv_t div( intmax_t numer, intmax_t denom );
#endif __cplusplus

// ----------------------------------------------------------------------------
// FUNCTIONS - Standard C

intmax_t imaxabs( intmax_t i );
imaxdiv_t imaxdiv( intmax_t numer, intmax_t denom );

intmax_t strtoimax( const char * restrict s, char * * restrict endptr, int base );
uintmax_t strtoumax( const char * restrict s, char * * restrict endptr, int base );
intmax_t wcstoimax( const wchar_t * restrict s, wchar_t * * restrict endptr, int base );
uintmax_t wcstoumax( const wchar_t * restrict s, wchar_t * * restrict endptr, int base );

// ----------------------------------------------------------------------------
// MACROS (PRINT)

#define PRId8
#define PRId16
#define PRId32
#define PRId64

#define PRIdFAST8
#define PRIdFAST16
#define PRIdFAST32
#define PRIdFAST64

#define PRIdLEAST8
#define PRIdLEAST16
#define PRIdLEAST32
#define PRIdLEAST64

#define PRIdMAX
#define PRIdPTR

#define PRIi8
#define PRIi16
#define PRIi32
#define PRIi64

#define PRIiFAST8
#define PRIiFAST16
#define PRIiFAST32
#define PRIiFAST64

#define PRIiLEAST8
#define PRIiLEAST16
#define PRIiLEAST32
#define PRIiLEAST64

#define PRIiMAX
#define PRIiPTR

#define PRIo8
#define PRIo16
#define PRIo32
#define PRIo64

#define PRIoFAST8
#define PRIoFAST16
#define PRIoFAST32
#define PRIoFAST64

#define PRIoLEAST8
#define PRIoLEAST16
#define PRIoLEAST32
#define PRIoLEAST64

#define PRIoMAX
#define PRIoPTR

#define PRIu8
#define PRIu16
#define PRIu32
#define PRIu64

#define PRIuFAST8
#define PRIuFAST16
#define PRIuFAST32
#define PRIuFAST64

#define PRIuLEAST8
#define PRIuLEAST16
#define PRIuLEAST32
#define PRIuLEAST64

#define PRIuMAX
#define PRIuPTR

#define PRIx8
#define PRIx16
#define PRIx32
#define PRIx64

#define PRIxFAST8
#define PRIxFAST16
#define PRIxFAST32
#define PRIxFAST64

#define PRIxLEAST8
#define PRIxLEAST16
#define PRIxLEAST32
#define PRIxLEAST64

#define PRIxMAX
#define PRIxPTR

#define PRIX8
#define PRIX16
#define PRIX32
#define PRIX64

#define PRIXFAST8
#define PRIXFAST16
#define PRIXFAST32
#define PRIXFAST64

#define PRIXLEAST8
#define PRIXLEAST16
#define PRIXLEAST32
#define PRIXLEAST64

#define PRIXMAX
#define PRIXPTR

// ----------------------------------------------------------------------------
// MACROS (SCAN)

#define SCNd8
#define SCNd16
#define SCNd32
#define SCNd64

#define SCNdFAST8
#define SCNdFAST16
#define SCNdFAST32
#define SCNdFAST64

#define SCNdLEAST8
#define SCNdLEAST16
#define SCNdLEAST32
#define SCNdLEAST64

#define SCNdMAX
#define SCNdPTR

#define SCNi8
#define SCNi16
#define SCNi32
#define SCNi64

#define SCNiFAST8
#define SCNiFAST16
#define SCNiFAST32
#define SCNiFAST64

#define SCNiLEAST8
#define SCNiLEAST16
#define SCNiLEAST32
#define SCNiLEAST64

#define SCNiMAX
#define SCNiPTR

#define SCNo8
#define SCNo16
#define SCNo32
#define SCNo64

#define SCNoFAST8
#define SCNoFAST16
#define SCNoFAST32
#define SCNoFAST64

#define SCNoLEAST8
#define SCNoLEAST16
#define SCNoLEAST32
#define SCNoLEAST64

#define SCNoMAX
#define SCNoPTR

#define SCNu8
#define SCNu16
#define SCNu32
#define SCNu64

#define SCNuFAST8
#define SCNuFAST16
#define SCNuFAST32
#define SCNuFAST64

#define SCNuLEAST8
#define SCNuLEAST16
#define SCNuLEAST32
#define SCNuLEAST64

#define SCNuMAX
#define SCNuPTR

#define SCNx8
#define SCNx16
#define SCNx32
#define SCNx64

#define SCNxFAST8
#define SCNxFAST16
#define SCNxFAST32
#define SCNxFAST64

#define SCNxLEAST8
#define SCNxLEAST16
#define SCNxLEAST32
#define SCNxLEAST64

#define SCNxMAX
#define SCNxPTR

#define SCNX8
#define SCNX16
#define SCNX32
#define SCNX64

#define SCNXFAST8
#define SCNXFAST16
#define SCNXFAST32
#define SCNXFAST64

#define SCNXLEAST8
#define SCNXLEAST16
#define SCNXLEAST32
#define SCNXLEAST64

#define SCNXMAX
#define SCNXPTR

#endif // __INTTYPES_H
