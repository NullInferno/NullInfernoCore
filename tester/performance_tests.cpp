#include "NullInfernoCore.h"

//	................................................................................................
//  Run performance tests - Environment
//	Input:
//			none
//	Output:
//			none
//	................................................................................................
void RunPerformanceTests_Environment(void) {
	INT64 Iters;
	INT64 MaxIters;

	TStopwatch SW;

	PCHAR P1 = PCHAR_ALLOC(10240);
	if (P1 == NULL) return;
	PCHAR P2 = PCHAR_ALLOC(10240);
	if (P2 == NULL) return;

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
	INT64 Iters;
	INT64 MaxIters;

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
#if 1
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
#if 1
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
#if 1
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
#if 1
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
#if 1
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
#if 1
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

	PCHAR_FREE(P1);
	PCHAR_FREE(P2);
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
}
//	................................................................................................
