#pragma once

// Main includes

#ifdef WINDOWS_SYSTEM
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>
#endif

#ifdef LINUX_SYSTEM
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <unistd.h>
#include <float.h>
#include <math.h>
#endif

#ifdef WINDOWS_SYSTEM

#define INT8 char
#define INT16 short
#define INT32 int
#define INT64 __int64
#define UINT8 unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned int
#define UINT64 unsigned __int64
#define FLOAT float
#define DOUBLE double
#define BOOL bool
#define DATETIME unsigned __int64
#define CHAR char
#define BYTE unsigned char

#define PINT8 char*
#define PINT16 short*
#define PINT32 int*
#define PINT64 __int64*
#define PUINT8 unsigned char*
#define PUINT16 unsigned short*
#define PUINT32 unsigned int*
#define PUINT64 unsigned __int64*
#define PFLOAT float*
#define PDOUBLE double*
#define PBOOL bool*
#define PDATETIME unsigned __int64*
#define PCHAR char*
#define PBYTE unsigned char*
#define PVOID void*

#define CONST_PINT8 const char*
#define CONST_PINT16 const short*
#define CONST_PINT32 const int*
#define CONST_PINT64 const __int64*
#define CONST_PUINT8 const unsigned char*
#define CONST_PUINT16 const unsigned short*
#define CONST_PUINT32 const unsigned int*
#define CONST_PUINT64 const unsigned __int64*
#define CONST_PFLOAT const float*
#define CONST_PDOUBLE const double*
#define CONST_PBOOL const bool*
#define CONST_PDATETIME const unsigned __int64*
#define CONST_PCHAR const char*
#define CONST_PBYTE const unsigned char*
#define CONST_PVOID const void*

#endif

#ifdef LINUX_SYSTEM

#define INT8 char
#define INT16 short
#define INT32 int
#define INT64 long long int
#define UINT8 unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned int
#define UINT64 unsigned long long int
#define FLOAT float
#define DOUBLE double
#define BOOL bool
#define DATETIME unsigned long long int
#define CHAR char
#define BYTE unsigned char

#define PINT8 char*
#define PINT16 short*
#define PINT32 int*
#define PINT64 long long int*
#define PUINT8 unsigned char*
#define PUINT16 unsigned short*
#define PUINT32 unsigned int*
#define PUINT64 unsigned long long int*
#define PFLOAT float*
#define PDOUBLE double*
#define PBOOL bool*
#define PDATETIME unsigned long long int*
#define PCHAR char*
#define PBYTE unsigned char*
#define PVOID void*

#define CONST_PINT8 const char*
#define CONST_PINT16 const short*
#define CONST_PINT32 const int*
#define CONST_PINT64 const long long int*
#define CONST_PUINT8 const unsigned char*
#define CONST_PUINT16 const unsigned short*
#define CONST_PUINT32 const unsigned int*
#define CONST_PUINT64 const unsigned long long int*
#define CONST_PFLOAT const float*
#define CONST_PDOUBLE const double*
#define CONST_PBOOL const bool*
#define CONST_PDATETIME const unsigned long long int*
#define CONST_PCHAR const char*
#define CONST_PBYTE const unsigned char*
#define CONST_PVOID const void*

#endif


// Class forward declarations

class TEnvironment;
class TStopwatch;

// Include other headers

#include "TEnvironment.h"
#include "TStopwatch.h"

// Constatnts

#define MAX_INT32 (INT32)2147483647
#define MIN_INT32 (INT32)-2147483648
#define MAX_UINT32 (UINT32)4294967295U
#define MAX_INT64 (INT64)9223372036854775807LL
#define MIN_INT64 (INT64)-9223372036854775808LL
#define MAX_UINT64 (UINT64)18446744073709551615ULL

// Macros

#define EXCHANGE_DOUBLE(_v1, _v2) { DOUBLE iTemp = _v1; _v1 = _v2; _v2 = iTemp; }
#define ALIGN16(_Val) (((_Val) & ~15) + 16)

#ifdef WINDOWS_SYSTEM
#define MEMORY_ALLOC(_size) _aligned_malloc(ALIGN16(_size), 16)
#define MEMORY_FREE(_ptr) _aligned_free(_ptr)
#else
#define MEMORY_ALLOC(_size) malloc(ALIGN16(_size))
#define MEMORY_FREE(_ptr) free(_ptr)
#endif

#define IS_PCHAR_EMPTY(_p) (((_p) == NULL) || (*(_p) == 0 ))
#define PCHAR_ALLOC(_size) (PCHAR)MEMORY_ALLOC((_size) * sizeof(CHAR))
#define PCHAR_FREE(_ptr) MEMORY_FREE(_ptr)

// Standard functions declarations

#define FNC_PRINTF printf
#define FNC_STRLEN strlen
#define FNC_SPRINTF sprintf
#define FNC_SNPRINTF snprintf
#define FNC_VPRINTF vprintf
#define FNC_STRCMP strcmp
#define FNC_MEMCPY memcpy
#define FNC_MEMSET memset
#define FNC_SSCANF sscanf
#define FNC_STRCPY strcpy

// Miscellaneous functions

DOUBLE RoundDOUBLE(DOUBLE iValue, INT32 iDecimalPlaces); // Round DOUBLE to specified decimal places
BOOL IsEqualDOUBLES(DOUBLE iValue1, DOUBLE iValue2, DOUBLE iEpsilon = 1e-13); // Check if two DOUBLE values are equal 

INT32 INT32ToStr(INT32 iValue, PCHAR oBuffer); // Convert INT32 to string
INT32 UINT32ToStr(UINT32 iValue, PCHAR oBuffer); // Convert UINT32 to string
INT32 INT64ToStr(INT64 iValue, PCHAR oBuffer); // Convert INT64 to string
INT32 UINT64ToStr(UINT64 iValue, PCHAR oBuffer); // Convert UINT64 to string
INT32 DOUBLEToStr(DOUBLE iValue, PCHAR oBuffer, INT32 iDecimalPlaces = 6); // Convert DOUBLE to string

INT32 StrToINT32(CONST_PCHAR iStr, INT32 iDefaultValue = 0, CHAR iTerminatingChar = ' '); // Convert string to INT32
UINT32 StrToUINT32(CONST_PCHAR iStr, UINT32 iDefaultValue = 0, CHAR iTerminatingChar = ' '); // Convert string to UINT32
INT64 StrToINT64(CONST_PCHAR iStr, INT64 iDefaultValue = 0, CHAR iTerminatingChar = ' '); // Convert string to INT64
UINT64 StrToUINT64(CONST_PCHAR iStr, UINT64 iDefaultValue = 0, CHAR iTerminatingChar = ' '); // Convert string to UINT64
DOUBLE StrToDOUBLE(CONST_PCHAR iStr, DOUBLE iDefaultValue = 0.0, CHAR iDecimalPointChar = '.', CHAR iTerminatingChar = ' '); // Convert string to DOUBLE
