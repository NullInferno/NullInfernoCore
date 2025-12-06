#pragma once

// Main includes

#ifdef WINDOWS_SYSTEM
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <locale.h>
#include <emmintrin.h>
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
#include <ctype.h>
#include <locale.h>
#include <emmintrin.h>
#include <stdint.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
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
#define WCHAR wchar_t

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
#define PWCHAR wchar_t*
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
#define CONST_PWCHAR const wchar_t*
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
#define WCHAR wchar_t

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
#define PWCHAR wchar_t*
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
#define CONST_PWCHAR const wchar_t*
#define CONST_PVOID const void*

#endif

// Type definitions

typedef INT32(*TCompareItemsFunction)(CONST_PVOID iData, INT64 iIndex1, INT64 iIndex2, CONST_PVOID iUserData); // Function prototype for item comparison functions
typedef INT32(*TBinarySearchCompareFunction)(CONST_PVOID iData, CONST_PVOID iUserData); // Function prototype for item comparison functions

// Constants

#define MAX_INT32 (INT32)2147483647
#define MIN_INT32 (INT32)-2147483648
#define MAX_UINT32 (UINT32)4294967295U
#define MAX_INT64 (INT64)9223372036854775807LL
#define MIN_INT64 (INT64)-9223372036854775808LL
#define MAX_UINT64 (UINT64)18446744073709551615ULL
#define DATETIME_EMPTY (DATETIME)0xffffffffffffffffull

#define BINARY_SEARCH_ANY_OCCURRENCE 0
#define BINARY_SEARCH_FIRST_OCCURRENCE 1
#define BINARY_SEARCH_LAST_OCCURRENCE 2

// Class forward declarations

class TEnvironment;
class TStopwatch;
class TString;
class TList;
class TStringList;
class TBytes;
class TParamsList;
class TDateTime;
class TStream;
class TMemoryStream;
class TBinaryReader;
class TBinaryWriter;
class TCommandLineParser;
class TFileSystem;
class TFileStream;

// Include other headers

#include "TEnvironment.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TList.h"
#include "TBytes.h"
#include "TStringList.h"
#include "TParamsList.h"
#include "TDateTime.h"
#include "TStream.h"
#include "TMemoryStream.h"
#include "TBinaryReader.h"
#include "TBinaryWriter.h"
#include "TCommandLineParser.h"
#include "TFileSystem.h"
#include "TFileStream.h"

// Macros

#define EXCHANGE_DOUBLE(_v1, _v2) { DOUBLE iTemp = _v1; _v1 = _v2; _v2 = iTemp; }
#define ALIGN16(_Val) (((_Val) & ~15) + 16)
#define ALIGN128(_Val) (((_Val) & ~127) + 128)
#define IS_INDEX_IN(_Index, _Start, _End) (((_Index) >= (_Start)) && ((_Index) < (_End)))
#define IS_INDEX_OUT(_Index, _Start, _End) (((_Index) < (_Start)) || ((_Index) >= (_End)))
#define MIN(_V1, _V2) (((_V1) < (_V2)) ? (_V1) : (_V2))

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

#ifdef WINDOWS_SYSTEM
#define FNC_STRCASECMP _stricmp
#define FNC_STRNCASECMP _strnicmp
#define FNC_FSEEK _fseeki64
#define FNC_FTELL _ftelli64
#else
#define FNC_STRCASECMP strcasecmp
#define FNC_STRNCASECMP strncasecmp
#define FNC_FSEEK fseeko
#define FNC_FTELL ftello
#endif

#define FNC_PRINTF printf
#define FNC_STRLEN strlen
#define FNC_SPRINTF sprintf
#define FNC_SNPRINTF snprintf
#define FNC_VPRINTF vprintf
#define FNC_STRCMP strcmp
#define FNC_STRNCMP strncmp
#define FNC_MEMCPY memcpy
#define FNC_MEMSET memset
#define FNC_SSCANF sscanf
#define FNC_STRCPY strcpy
#define FNC_MEMCPY memcpy
#define FNC_MEMMOVE memmove
#define FNC_STRCHR strchr
#define FNC_STRRCHR strrchr
#define FNC_MEMSET memset
#define FNC_MEMCMP memcmp
#define FNC_WCSLEN wcslen

// Miscellaneous functions

void QuickSort(CONST_PVOID iData, INT64 iItemsCount, INT64 iItemSize, TCompareItemsFunction iCompareFunction, CONST_PVOID iUserData = NULL); // Quick sort algorithm
INT64 BinarySearch(CONST_PVOID iData, INT64 iItemsCount, INT64 iItemSize, TBinarySearchCompareFunction iCompareFunction, CONST_PVOID iUserData = NULL, INT32 iSearchMode = BINARY_SEARCH_ANY_OCCURRENCE); // Find item in sorted data using binary search

DOUBLE RoundDOUBLE(DOUBLE iValue, INT32 iDecimalPlaces); // Round DOUBLE to specified decimal places
BOOL IsEqualDOUBLES(DOUBLE iValue1, DOUBLE iValue2, DOUBLE iEpsilon = 1e-13); // Check if two DOUBLE values are equal 

INT32 INT32ToStr(INT32 iValue, PCHAR oBuffer); // Convert INT32 to string
INT32 UINT32ToStr(UINT32 iValue, PCHAR oBuffer); // Convert UINT32 to string
INT32 INT64ToStr(INT64 iValue, PCHAR oBuffer); // Convert INT64 to string
INT32 UINT64ToStr(UINT64 iValue, PCHAR oBuffer); // Convert UINT64 to string
INT32 DOUBLEToStr(DOUBLE iValue, PCHAR oBuffer, INT32 iDecimalPlaces = 6, CHAR iDecimalPointChar = '.'); // Convert DOUBLE to string

INT32 StrToINT32(CONST_PCHAR iStr, INT32 iDefaultValue = 0, CHAR iTerminatingChar = ' '); // Convert string to INT32
UINT32 StrToUINT32(CONST_PCHAR iStr, UINT32 iDefaultValue = 0, CHAR iTerminatingChar = ' '); // Convert string to UINT32
INT64 StrToINT64(CONST_PCHAR iStr, INT64 iDefaultValue = 0, CHAR iTerminatingChar = ' '); // Convert string to INT64
UINT64 StrToUINT64(CONST_PCHAR iStr, UINT64 iDefaultValue = 0, CHAR iTerminatingChar = ' '); // Convert string to UINT64
DOUBLE StrToDOUBLE(CONST_PCHAR iStr, DOUBLE iDefaultValue = 0.0, CHAR iDecimalPointChar = '.', CHAR iTerminatingChar = ' '); // Convert string to DOUBLE

INT32 ConvertStringBetweenCodepages(CONST_PCHAR iSrcStr, INT32 iSrcCodepage, PCHAR oDstStr, INT32 iDstCodepage); // Convert string between codepages
UINT64 GenerateHash64(CONST_PVOID iData, INT64 iDataSize, CONST_PVOID iTransformTable = NULL, INT32 iTerminator = -1, UINT64 iPreviousValue = 0); // Generate 64-bit hash from data using djb2 algorithm
