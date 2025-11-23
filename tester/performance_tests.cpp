#include "NullInfernoCore.h"

//	................................................................................................
//  Run performance tests - Environment
//	Input:
//			none
//	Output:
//			none
//	................................................................................................
void RunPerformanceTests_Environment(void) {
	[[maybe_unused]] INT64 Iters;
	[[maybe_unused]] INT64 MaxIters;

	TStopwatch SW;

	PCHAR P1 = PCHAR_ALLOC(10240);
	if (P1 == NULL) return;
	PCHAR P2 = PCHAR_ALLOC(10240);
	if (P2 == NULL) return;

	[[maybe_unused]] PUINT64 Data64;
	[[maybe_unused]] PBYTE DataB;

	// TEnvironment::GenerateRandomUINT32()
#if 0
	MaxIters = 20000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		TEnvironment::GenerateRandomUINT32();
	}
	SW.Pause();
	SW.PrintPerforanceResult("TEnvironment::GenerateRandomUINT32()", Iters);
#endif
	// TEnvironment::GenerateRandomUINT64()
#if 0
	MaxIters = 20000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		TEnvironment::GenerateRandomUINT64();
	}
	SW.Pause();
	SW.PrintPerforanceResult("TEnvironment::GenerateRandomUINT64()", Iters);
#endif
	// TEnvironment::GenerateRandomDOUBLE()
#if 0
	MaxIters = 10000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		TEnvironment::GenerateRandomDOUBLE();
	}
	SW.Pause();
	SW.PrintPerforanceResult("TEnvironment::GenerateRandomDOUBLE()", Iters);
#endif
	// sprintf(UINT32)
#if 0
	MaxIters = 20000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		FNC_SPRINTF(P1, "%u", MAX_UINT32);
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(UINT32)", Iters);
#endif
	// ultoa(UINT32)
#if 0
#ifdef WINDOWS_SYSTEM
	MaxIters = 20000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		_ultoa(MAX_UINT32, P2, 10);
	}
	SW.Pause();
	SW.PrintPerforanceResult("ultoa(UINT32)", Iters);
#endif
#endif
	// UINT32ToStr
#if 0
	MaxIters = 20000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (UINT32ToStr(MAX_UINT32, P1) != 10) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("UINT32ToStr", Iters);
#endif
	// sprintf(INT32)
#if 0
	MaxIters = 20000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		INT32 I32 = MIN_INT32;
		FNC_SPRINTF(P1, "%d", I32);
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(INT32)", Iters);
#endif
	// UINT32ToStr
#if 0
	MaxIters = 20000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		INT32 I32 = MIN_INT32;
		if (INT32ToStr(I32, P1) != 11) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("INT32ToStr", Iters);
#endif
	// sprintf(UINT64)
#if 0
	MaxIters = 10000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		FNC_SPRINTF(P1, "%llu", MAX_UINT64);
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(UINT64)", Iters);
#endif
	// _ui64toa(UINT32)
#if 0
#ifdef WINDOWS_SYSTEM
	MaxIters = 5000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		_ui64toa(MAX_UINT64, P2, 10);
	}
	SW.Pause();
	SW.PrintPerforanceResult("_ui64toa(UINT64)", Iters);
#endif
#endif
	// UINT64ToStr
#if 0
	MaxIters = 20000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT64 U64 = MAX_UINT64;
		if (UINT64ToStr(U64, P1) != 20) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("UINT64ToStr", Iters);
#endif
	// sprintf(DOUBLE)
#if 0
	MaxIters = 1000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		FNC_SPRINTF(P1, "%.12lf", 123456.123456789012);
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(DOUBLE)", Iters);
#endif
	// gcvt
#if 0
	MaxIters = 1000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
#ifdef WINDOWS_SYSTEM
		_gcvt(123456.123456789012, 12, P1);
#else
		gcvt(123456.123456789012, 12, P1);
#endif
	}
	SW.Pause();
	SW.PrintPerforanceResult("gcvt", Iters);
#endif
	// DOUBLEToStr
#if 0
	MaxIters = 10000000;
	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		DOUBLEToStr(123456.123456789012, P1, 12);
	}
	SW.Pause();
	SW.PrintPerforanceResult("DOUBLEToStr", Iters);
#endif
	// sscanf(UINT32)
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%u", MAX_UINT32);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT32 U32;
		if (FNC_SSCANF(P1, "%u", &U32) != 1) break;
		if (U32 != MAX_UINT32) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(UINT32)", Iters);
#endif
	// strtoul
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%u", MAX_UINT32);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT32 U32 = strtoul(P1, NULL, 10);
		if (U32 != MAX_UINT32) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("strtoul", Iters);
#endif
	// StrToUINT32
#if 0
	MaxIters = 20000000;
	SW.Start();
	FNC_SPRINTF(P1, "%u", MAX_UINT32);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT32 U32 = StrToUINT32(P1, 0, ' ');
		if (U32 != MAX_UINT32) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("StrToUINT32", Iters);
#endif
	// sscanf(INT32)
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%d", MAX_INT32);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT32 U32;
		if (FNC_SSCANF(P1, "%d", &U32) != 1) break;
		if (U32 != MAX_INT32) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(INT32)", Iters);
#endif
	// strtol
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%d", MAX_INT32);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT32 U32 = strtol(P1, NULL, 10);
		if (U32 != MAX_INT32) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("strtol", Iters);
#endif
	// StrToINT32
#if 0
	MaxIters = 20000000;
	SW.Start();
	FNC_SPRINTF(P1, "%d", MAX_INT32);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT32 U32 = StrToINT32(P1, 0, ' ');
		if (U32 != MAX_INT32) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("StrToINT32", Iters);
#endif
	// sscanf(UINT64)
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%llu", MAX_UINT64);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT64 U64;
		if (FNC_SSCANF(P1, "%llu", &U64) != 1) break;
		if (U64 != MAX_UINT64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(UINT64)", Iters);
#endif
	// strtoull
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%llu", MAX_UINT64);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT64 U64 = strtoull(P1, NULL, 10);
		if (U64 != MAX_UINT64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("strtoull", Iters);
#endif
	// StrToUINT64
#if 0
	MaxIters = 20000000;
	SW.Start();
	FNC_SPRINTF(P1, "%llu", MAX_UINT64);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT64 U64 = StrToUINT64(P1, 0, ' ');
		if (U64 != MAX_UINT64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("StrToUINT64", Iters);
#endif
	// sscanf(INT64)
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%lld", MAX_INT64);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		INT64 I64;
		if (FNC_SSCANF(P1, "%lld", &I64) != 1) break;
		if (I64 != MAX_INT64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(INT64)", Iters);
#endif
	// strtoll
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%lld", MAX_INT64);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		INT64 I64 = strtoll(P1, NULL, 10);
		if (I64 != MAX_INT64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("strtoll", Iters);
#endif
	// StrToINT64
#if 0
	MaxIters = 20000000;
	SW.Start();
	FNC_SPRINTF(P1, "%lld", MAX_INT64);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		INT64 I64 = StrToINT64(P1, 0, ' ');
		if (I64 != MAX_INT64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("StrToINT64", Iters);
#endif
	// sscanf(DOUBLE)
#if 0
	MaxIters = 5000000;
	SW.Start();
	FNC_SPRINTF(P1, "%.12lf", 123456.123456789012);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		DOUBLE D;
		if (FNC_SSCANF(P1, "%lf", &D) != 1) break;
		if (D != 123456.123456789012) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("sprintf(DOUBLE)", Iters);
#endif
	// strtod
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%.12lf", 123456.123456789012);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		DOUBLE D = strtod(P1, NULL);
		if (D != 123456.123456789012) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("strtod", Iters);
#endif
	// StrToDOUBLE
#if 0
	MaxIters = 10000000;
	SW.Start();
	FNC_SPRINTF(P1, "%.12lf", 123456.123456789012);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		DOUBLE D = StrToDOUBLE(P1, 0, '.', ' ');
		if (D != 123456.123456789012) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("StrToDOUBLE", Iters);
#endif
	// qsort
#if 0
	MaxIters = 1000;

	Data64 = (PUINT64)MEMORY_ALLOC(8192 * sizeof(UINT64));
	for (UINT64 i = 0; i < 8192; i++) Data64[i] = 8193 - i;

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		qsort(Data64, 8192, sizeof(UINT64), [](CONST_PVOID i1, CONST_PVOID i2)->INT32 {
			UINT64 u1 = *(PUINT64)i1;
			UINT64 u2 = *(PUINT64)i2;
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			});
	}
	SW.Pause();
	SW.PrintPerforanceResult("qsort", Iters);
	MEMORY_FREE(Data64);
#endif
	// QuickSort
#if 0
	MaxIters = 1000;

	Data64 = (PUINT64)MEMORY_ALLOC(8192 * sizeof(UINT64));
	for (UINT64 i = 0; i < 8192; i++) Data64[i] = 8193 - i;

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		QuickSort(Data64, 8192, sizeof(UINT64), [](CONST_PVOID iData, INT64 iIndex1, INT64 iIndex2, CONST_PVOID iUserData)->INT32 {
			INT64 u1 = ((PINT64)iData)[iIndex1];
			INT64 u2 = ((PINT64)iData)[iIndex2];
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			});
	}
	SW.Pause();
	SW.PrintPerforanceResult("QuickSort", Iters);
	MEMORY_FREE(Data64);
#endif
	// BinarySearch (any value)
#if 0
	MaxIters = 10000000;

	Data64 = (PUINT64)MEMORY_ALLOC(1024 * sizeof(UINT64));
	for (UINT64 i = 0; i < 1024; i++) Data64[i] = i;

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT64 U64 = Iters % 1024;
		INT64 I = BinarySearch(Data64, 1024, sizeof(UINT64), [](CONST_PVOID iData, CONST_PVOID iUserData)->INT32 {
			INT64 u1 = *((PUINT64)iData);
			INT64 u2 = (UINT64)iUserData;
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			}, (CONST_PVOID)U64, BINARY_SEARCH_ANY_OCCURRENCE);
		if (I != (INT64)U64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("BinarySearch (any value)", Iters);
	MEMORY_FREE(Data64);
#endif
	// BinarySearch (first value)
#if 0
	MaxIters = 10000000;

	Data64 = (PUINT64)MEMORY_ALLOC(1024 * sizeof(UINT64));
	for (UINT64 i = 0; i < 1024; i++) Data64[i] = i;

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT64 U64 = Iters % 1024;
		INT64 I = BinarySearch(Data64, 1024, sizeof(UINT64), [](CONST_PVOID iData, CONST_PVOID iUserData)->INT32 {
			INT64 u1 = *((PUINT64)iData);
			INT64 u2 = (UINT64)iUserData;
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			}, (CONST_PVOID)U64, BINARY_SEARCH_FIRST_OCCURRENCE);
		if (I != (INT64)U64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("BinarySearch (first value)", Iters);
	MEMORY_FREE(Data64);
#endif
	// BinarySearch (last value)
#if 0
	MaxIters = 10000000;

	Data64 = (PUINT64)MEMORY_ALLOC(1024 * sizeof(UINT64));
	for (UINT64 i = 0; i < 1024; i++) Data64[i] = i;

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		UINT64 U64 = Iters % 1024;
		INT64 I = BinarySearch(Data64, 1024, sizeof(UINT64), [](CONST_PVOID iData, CONST_PVOID iUserData)->INT32 {
			INT64 u1 = *((PUINT64)iData);
			INT64 u2 = (UINT64)iUserData;
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			}, (CONST_PVOID)U64, BINARY_SEARCH_LAST_OCCURRENCE);
		if (I != (INT64)U64) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("BinarySearch (last value)", Iters);
	MEMORY_FREE(Data64);
#endif
	// GenerateHash64
#if 0
	MaxIters = 1000000;

	DataB = (PBYTE)MEMORY_ALLOC(1024);
	TBytes::GenerateRandomBytes(DataB, 1024);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (GenerateHash64(DataB, 1024) == 0) break;
	}
	SW.Pause();
	SW.PrintPerforanceResult("GenerateHash64", Iters);
	MEMORY_FREE(DataB);
#endif

	PCHAR_FREE(P1);
	PCHAR_FREE(P2);
}
//	................................................................................................

//	................................................................................................
//  Run performance tests - TString
//	Input:
//			none
//	Output:
//			none
//	................................................................................................
void RunPerformanceTests_TString(void) {
	[[maybe_unused]] INT64 Iters;
	[[maybe_unused]] INT64 MaxIters;

	TStopwatch SW;

	CHAR* volatile P1 = PCHAR_ALLOC(10240);
	if (P1 == NULL) return;
	CHAR* volatile P2 = PCHAR_ALLOC(10240);
	if (P2 == NULL) return;

	TString S1;

	// TString::Compare
#if 0
	MaxIters = 1000000;
	SW.Start();

	TString::GenerateRandomBASE64String(P1, 1024);
	S1.SetValue(P1);
	for (Iters = 0; Iters < MaxIters; Iters++) {
		//TString::GenerateRandomBASE64String(P1, Iters % 1025);
		//S1.SetValue(P1, Iters % 1025);
		if (S1.Compare(P1, 0, -1) != 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::Compare", Iters);
#endif
	// TString::CaseCompare
#if 0
	MaxIters = 1000000;
	SW.Start();

	TString::GenerateRandomBASE64String(P1, 1024);
	S1.SetValue(P1); S1.ToLowercase();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		//TString::GenerateRandomBASE64String(P1, Iters % 1025);
		//S1.SetValue(P1, Iters % 1025);
		if (S1.CaseCompare(P1, 0, -1) != 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::CaseCompare", Iters);
#endif
	// strchr
#if 0
	MaxIters = 10000000;
	memset(P1, 'a', 1024); P1[1024] = 0;

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (FNC_STRCHR(P1, 'b') != NULL) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("strchr", Iters);
#endif
	// strchr 15 chars
#if 0
	MaxIters = 100000000;
	memset(P1, 'a', 15); P1[16] = 0;

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (FNC_STRCHR(P1, 'b') != NULL) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("strchr  (15 chars)", Iters);
#endif
	// TString::FindChar
#if 0
	MaxIters = 10000000;

	memset(P1, 'a', 1024); P1[1023] = 'b'; P1[1024] = 0;
	S1.SetValue(P1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.FindChar('b', 0, 1024, 1) != 1023) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::FindChar", Iters);
#endif
	// TString::FindChar 15 chars
#if 0
	MaxIters = 100000000;

	memset(P1, 'a', 15); P1[16] = 0; P1[14] = 'b';
	S1.SetValue(P1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.FindChar('b', 0, 100, 1) != 14) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::FindChar (15 chars)", Iters);
#endif
	// TString::CaseFindChar
#if 0
	MaxIters = 10000000;

	memset(P1, 'A', 1024); P1[1023] = 'B'; P1[1024] = 0;
	S1.SetValue(P1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.CaseFindChar('b', 0, -1, 1) != 1023) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::CaseFindChar", Iters);
#endif
	// strrchr
#if 0
	MaxIters = 10000000;
	memset(P1, 'a', 1024); P1[1024] = 0; P1[0] = 'b';

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (FNC_STRRCHR(P1, 'b') != P1) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("strrchr", Iters);
#endif
	// strchr (15 chars)
#if 0
	MaxIters = 100000000;
	memset(P1, 'a', 15); P1[16] = 0; P1[0] = 'b';

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (FNC_STRRCHR(P1, 'b') != P1) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("strrchr  (15 chars)", Iters);
#endif
	// TString::ReverseFindChar
#if 0
	MaxIters = 10000000;
	memset(P1, 'a', 1024); P1[0] = 'b'; P1[1024] = 0;
	S1.SetValue(P1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.ReverseFindChar('b', -1, -1, 1) != 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::ReverseFindChar", Iters);
#endif
	// TString::ReverseFindChar (15 chars)
#if 0
	MaxIters = 10000000;
	memset(P1, 'a', 1024); P1[0] = 'b'; P1[16] = 0;
	S1.SetValue(P1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.ReverseFindChar('b', -1, -1, 1) != 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::ReverseFindChar (15 chars)", Iters);
#endif
	// TString::ReverseCaseFindChar
#if 0
	MaxIters = 10000000;
	memset(P1, 'A', 1024); P1[0] = 'B'; P1[1024] = 0;
	S1.SetValue(P1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.ReverseCaseFindChar('b', -1, -1, 1) != 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::ReverseCaseFindChar", Iters);
#endif
	// TString::ReverseFindChar (15 chars)
#if 0
	MaxIters = 10000000;
	memset(P1, 'A', 1024); P1[0] = 'B'; P1[16] = 0;
	S1.SetValue(P1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.ReverseCaseFindChar('b', -1, -1, 1) != 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString::ReverseCaseFindChar (15 chars)", Iters);
#endif
	// TString::GetHashCode
#if 0
	MaxIters = 1000000;
	S1.SetRandomBASE64Value(1024);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.GetHashCode() == 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString:GetHashCode", Iters);
#endif
	// TString::GetCaseHashCode
#if 0
	MaxIters = 1000000;
	S1.SetRandomBASE64Value(1024);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (S1.GetCaseHashCode() == 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TString:GetCaseHashCode", Iters);
#endif

	PCHAR_FREE(P1);
	PCHAR_FREE(P2);
}
//	................................................................................................

//	................................................................................................
//  Run performance tests - TList
//	Input:
//			none
//	Output:
//			none
//	................................................................................................
void RunPerformanceTests_TList(void) {
	[[maybe_unused]] INT64 Iters;
	[[maybe_unused]] INT64 MaxIters;

	TStopwatch SW;

	TList L1, L2;

	// TList::DeleteValue
#if 0
	MaxIters = 500000;

	for (INT64 i = 0; i < 1024; i++) L1.Add(i & 3);
	L2.CreateCopy(&L1); L1.SetCount(0);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		L1.CreateCopy(&L2);
		L1.DeleteValue((PVOID)1, -1, NULL);
		if (L1.Count() != 1024-256) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TList::DeleteValue + TList::CreateCopy", Iters);
#endif
	// TList::Find
#if 0
	MaxIters = 500000;

	L1.SetCount(0);
	for (INT64 i = 0; i < 1024; i++) L1.Add((UINT64)1);
	L1.Add((UINT64)2);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (L1.Find((UINT64)2, 0, -1, 1) != 1024) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TList::Find", Iters);
#endif
	// TList::ReverseFind
#if 0
	MaxIters = 500000;

	L1.SetCount(0);
	L1.Add((UINT64)2);
	for (INT64 i = 0; i < 1024; i++) L1.Add((UINT64)1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (L1.ReverseFind((UINT64)2, -1, -1, 1) != 0) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TList::ReverseFind", Iters);
#endif
	// TList::Sort
#if 0
	MaxIters = 10000;

	L1.SetCount(0);
	for (INT64 i = 0; i < 1024; i++) L1.Add((UINT64)TEnvironment::GenerateRandomUINT64());
	L2.CreateCopy(&L1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		L1.CreateCopy(&L2);
		L1.Sort([](PVOID iItem1, PVOID iItem2)->INT32 {
			UINT64 u1 = (UINT64)iItem1;
			UINT64 u2 = (UINT64)iItem2;
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			});
	}
	SW.Pause();

	SW.PrintPerforanceResult("TList::Sort", Iters);
#endif
	// TList::BinaryFindFirst
#if 0
	MaxIters = 10000000;

	L1.SetCount(0);
	for (INT64 i = 0; i < 1024; i++) L1.Add((UINT64)i);
	L2.CreateCopy(&L1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (L1.BinaryFindFirst((UINT64)1, [](PVOID iSearchValue, PVOID iItem)->INT32 {
			UINT64 u1 = (UINT64)iSearchValue;
			UINT64 u2 = (UINT64)iItem;
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			}) != 1) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TList::BinaryFindFirst", Iters);
#endif
	// TList::BinaryFindLast
#if 0
	MaxIters = 10000000;

	L1.SetCount(0);
	for (INT64 i = 0; i < 1024; i++) L1.Add((UINT64)i);
	L2.CreateCopy(&L1);

	SW.Start();
	for (Iters = 0; Iters < MaxIters; Iters++) {
		if (L1.BinaryFindLast((UINT64)1, [](PVOID iSearchValue, PVOID iItem)->INT32 {
			UINT64 u1 = (UINT64)iSearchValue;
			UINT64 u2 = (UINT64)iItem;
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			}) != 1) break;
	}
	SW.Pause();

	SW.PrintPerforanceResult("TList::BinaryFindLast", Iters);
#endif

}
//	................................................................................................

//	................................................................................................
//  Run all performance tests
//	Input:
//			none
//	Output:
//			none
//	................................................................................................
void RunAllPerformanceTests(void) {
	RunPerformanceTests_Environment();
	RunPerformanceTests_TString();
	RunPerformanceTests_TList();
}
//	................................................................................................
