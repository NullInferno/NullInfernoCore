#include "NullInfernoCore.h"

#ifdef WINDOWS_SYSTEM
CONST_PCHAR TEST_FOLDER = "Z:\\Development\\Temp";

TFileSystemAttributes WindowsAttaributes2FileSystemAttributes(UINT32 iValue);
UINT32 FileSystemAttributes2WindowsAttaributes(TFileSystemAttributes iValue);

#else
CONST_PCHAR TEST_FOLDER = "/home/nullinferno/projects/Temp";

TFileSystemAttributes LinuxAttaributes2FileSystemAttributes(UINT32 iAttr, UINT32 iChmod, UINT32 iExt2Attr);
void FileSystemAttributes2LinuxAttaributes(TFileSystemAttributes iValue, UINT32* oAttr, UINT32* oChmod, UINT32* oExt2Attr);
#endif

//	................................................................................................
//  Run validity tests for environment
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_Environment(void) {

	PCHAR P1 = PCHAR_ALLOC(10240);
	if (P1 == NULL) return TEnvironment::ShowTestErrorMessage(-999, "Memory allocation error");
	PCHAR P2 = PCHAR_ALLOC(10240);
	if (P2 == NULL) return TEnvironment::ShowTestErrorMessage(-999, "Memory allocation error");

	UINT32 U32; INT32 I32;
	UINT64 U64; INT64 I64;
	DOUBLE Dbl;

	if ((UINT32ToStr(0, P1) != 1) || (FNC_STRCMP(P1, "0") != 0)) return TEnvironment::ShowTestErrorMessage(-1, "UINT32ToStr");
	U32 = 1;
	for (INT32 i = 1; i < 11; i++) {
		FNC_SPRINTF(P2, "%u", U32);
		if ((UINT32ToStr(U32, P1) != i) || (FNC_STRCMP(P1, P2) != 0)) return TEnvironment::ShowTestErrorMessage(-2, "UINT32ToStr");
		U32 *= 10;
	}
	I32 = -1;
	for (INT32 i = 2; i < 12; i++) {
		FNC_SPRINTF(P2, "%d", I32);
		if ((INT32ToStr(I32, P1) != i) || (FNC_STRCMP(P1, P2) != 0)) return TEnvironment::ShowTestErrorMessage(-3, "INT32ToStr");
		I32 *= 10;
	}

	for (INT32 i = 0; i < 10240; i++) {
		U32 = TEnvironment::GenerateRandomUINT32();
		UINT32ToStr(U32, P1); FNC_SPRINTF(P2, "%u", U32); if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessage(-4, "UINT32ToStr");
		I32 = (INT32)TEnvironment::GenerateRandomUINT32();
		INT32ToStr(I32, P1); FNC_SPRINTF(P2, "%d", I32); if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessage(-5, "INT32ToStr");
	}

	if ((UINT64ToStr(0, P1) != 1) || (FNC_STRCMP(P1, "0") != 0)) return TEnvironment::ShowTestErrorMessage(-6, "UINT64ToStr");
	U64 = 1;
	for (INT32 i = 1; i < 21; i++) {
		FNC_SPRINTF(P2, "%llu", U64);
		if ((UINT64ToStr(U64, P1) != i) || (FNC_STRCMP(P1, P2) != 0)) return TEnvironment::ShowTestErrorMessage(-7, "UINT64ToStr");
		U64 *= 10;
	}

	I64 = -1;
	for (INT32 i = 2; i < 20; i++) {
		FNC_SPRINTF(P2, "%lld", I64);
		if ((INT64ToStr(I64, P1) != i) || (FNC_STRCMP(P1, P2) != 0)) return TEnvironment::ShowTestErrorMessage(-8, "INT64ToStrm (%d)", i);
		I64 *= 10;
	}

	for (INT32 i = 0; i < 10240; i++) {
		U64 = TEnvironment::GenerateRandomUINT64();
		UINT64ToStr(U64, P1); FNC_SPRINTF(P2, "%llu", U64); if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessage(-9, "UINT64ToStr (%llu)", U64);
		I64 = (INT64)TEnvironment::GenerateRandomUINT64();
		INT64ToStr(I64, P1); FNC_SPRINTF(P2, "%lld", I64); if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessage(-10, "INT64ToStr");
	}

	Dbl = RoundDOUBLE(1.255, 0); if (!IsEqualDOUBLES(Dbl, 1)) return TEnvironment::ShowTestErrorMessage(-11, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.255, 1); if (!IsEqualDOUBLES(Dbl, 1.3)) return TEnvironment::ShowTestErrorMessage(-12, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.255, 2); if (!IsEqualDOUBLES(Dbl, 1.26)) return TEnvironment::ShowTestErrorMessage(-13, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.255, 3); if (!IsEqualDOUBLES(Dbl, 1.255)) return TEnvironment::ShowTestErrorMessage(-14, "RoundDOUBLE (%lf)", Dbl);
	Dbl = RoundDOUBLE(1.255, 4); if (!IsEqualDOUBLES(Dbl, 1.255)) return TEnvironment::ShowTestErrorMessage(-15, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 0); if (!IsEqualDOUBLES(Dbl, 2)) return TEnvironment::ShowTestErrorMessage(-16, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 1); if (!IsEqualDOUBLES(Dbl, 2)) return TEnvironment::ShowTestErrorMessage(-17, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 2); if (!IsEqualDOUBLES(Dbl, 2)) return TEnvironment::ShowTestErrorMessage(-18, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 3); if (!IsEqualDOUBLES(Dbl, 1.999)) return TEnvironment::ShowTestErrorMessage(-19, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 4); if (!IsEqualDOUBLES(Dbl, 1.9985)) return TEnvironment::ShowTestErrorMessage(-20, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 5); if (!IsEqualDOUBLES(Dbl, 1.9985)) return TEnvironment::ShowTestErrorMessage(-21, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985123422349, 12); if (!IsEqualDOUBLES(Dbl, 1.998512342235)) return TEnvironment::ShowTestErrorMessage(-22, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985123422345, 12); if (!IsEqualDOUBLES(Dbl, 1.998512342235)) return TEnvironment::ShowTestErrorMessage(-23, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985123422344, 12); if (!IsEqualDOUBLES(Dbl, 1.998512342234)) return TEnvironment::ShowTestErrorMessage(-24, "RoundDOUBLE");

	for (INT32 i = 0; i < 13; i++) {
		Dbl = 0;
		DOUBLEToStr(Dbl, P1, i); FNC_SPRINTF(P2, "%.*lf", i, Dbl);
		if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessage(-25, "DOUBLEToStr");
		Dbl = 0.001234567;
		DOUBLEToStr(Dbl, P1, i); FNC_SPRINTF(P2, "%.*lf", i, Dbl);
		if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessage(-26, "DOUBLEToStr");
		for (INT32 j = 0; j < 10240; j++) {
			Dbl = RoundDOUBLE(TEnvironment::GenerateRandomDOUBLE(-1, 1), i);
			//Dbl = -551827.99113683111500;
			DOUBLEToStr(Dbl, P1, i); FNC_SPRINTF(P2, "%.*lf", i, Dbl);
			if (FNC_STRCMP(P1, P2) != 0) {
				DOUBLEToStr(Dbl, P1, i);
				FNC_SPRINTF(P2, "%.*lf", i, Dbl);
				return TEnvironment::ShowTestErrorMessage(-27, "DOUBLEToStr (%d, %.14lf, %s, %s)", i, Dbl, P1, P2);
			}
		}
	}

	FNC_SPRINTF(P1, "%u", MAX_UINT32);
	if (StrToUINT32(P1, 0, ' ') != MAX_UINT32) return TEnvironment::ShowTestErrorMessage(-28, "StrToUINT32");
	if (StrToUINT32("9999", 0, ' ') != 9999) return TEnvironment::ShowTestErrorMessage(-29, "StrToUINT32");
	if (StrToUINT32("99999999", 0, ' ') != 99999999) return TEnvironment::ShowTestErrorMessage(-30, "StrToUINT32");
	if (StrToUINT32("999999999", 0, ' ') != 999999999) return TEnvironment::ShowTestErrorMessage(-31, "StrToUINT32");

	FNC_SPRINTF(P1, "%d", MAX_INT32);
	if (StrToINT32(P1, 0, ' ') != MAX_INT32) return TEnvironment::ShowTestErrorMessage(-32, "StrToINT32");
	if (StrToINT32("-9999", 0, ' ') != -9999) return TEnvironment::ShowTestErrorMessage(-33, "StrToINT32");
	if (StrToINT32("-99999999", 0, ' ') != -99999999) return TEnvironment::ShowTestErrorMessage(-34, "StrToINT32");
	if (StrToINT32("-999999999", 0, ' ') != -999999999) return TEnvironment::ShowTestErrorMessage(-35, "StrToINT32");

	if (StrToUINT32("99 99", 0, ' ') != 99) return TEnvironment::ShowTestErrorMessage(-36, "StrToUINT32");

	for (INT32 i = 0; i < 10240; i++) {
		U32 = TEnvironment::GenerateRandomUINT32();
		UINT32ToStr(U32, P1); if (StrToUINT32(P1, 0, ' ') != U32) return TEnvironment::ShowTestErrorMessage(-37, "UINT32ToStr + StrToUINT32");
		I32 = (INT32)TEnvironment::GenerateRandomUINT32();
		INT32ToStr(I32, P1); if (StrToINT32(P1, 0, ' ') != I32) return TEnvironment::ShowTestErrorMessage(-38, "INT32ToStr + StrToINT32");
	}

	FNC_SPRINTF(P1, "%llu", MAX_UINT64);
	if (StrToUINT64(P1, 0, ' ') != MAX_UINT64) return TEnvironment::ShowTestErrorMessage(-39, "StrToUINT64");
	if (StrToUINT64("9999", 0, ' ') != 9999) return TEnvironment::ShowTestErrorMessage(-40, "StrToUINT64");
	if (StrToUINT64("99999999", 0, ' ') != 99999999) return TEnvironment::ShowTestErrorMessage(-41, "StrToUINT64");
	if (StrToUINT64("999999999", 0, ' ') != 999999999) return TEnvironment::ShowTestErrorMessage(-42, "StrToUINT64");

	FNC_SPRINTF(P1, "%lld", MAX_INT64);
	if (StrToINT64(P1, 0, ' ') != MAX_INT64) return TEnvironment::ShowTestErrorMessage(-43, "StrToINT64");
	if (StrToINT64("-9999", 0, ' ') != -9999) return TEnvironment::ShowTestErrorMessage(-44, "StrToINT64");
	if (StrToINT64("-99999999", 0, ' ') != -99999999) return TEnvironment::ShowTestErrorMessage(-45, "StrToINT64");
	if (StrToINT64("-999999999", 0, ' ') != -999999999) return TEnvironment::ShowTestErrorMessage(-46, "StrToINT64");

	if (StrToUINT64("99 99", 0, ' ') != 99) return TEnvironment::ShowTestErrorMessage(-47, "StrToUINT64");

	for (INT64 i = 0; i < 10240; i++) {
		U64 = TEnvironment::GenerateRandomUINT64();
		UINT64ToStr(U64, P1); if (StrToUINT64(P1, 0, ' ') != U64) return TEnvironment::ShowTestErrorMessage(-37, "UINT64ToStr + StrToUINT64");
		I64 = (INT64)TEnvironment::GenerateRandomUINT64();
		INT64ToStr(I64, P1); if (StrToINT64(P1, 0, ' ') != I64) return TEnvironment::ShowTestErrorMessage(-38, "INT64ToStr + StrToINT64");
	}

	Dbl = StrToDOUBLE("1.255", 0, '.', ' '); if (!IsEqualDOUBLES(Dbl, 1.255)) return TEnvironment::ShowTestErrorMessage(-39, "StrToDOUBLE");
	Dbl = StrToDOUBLE("1.999999999999", 0, '.', ' '); if (!IsEqualDOUBLES(Dbl, 1.999999999999)) return TEnvironment::ShowTestErrorMessage(-40, "StrToDOUBLE");

	for (INT64 i = 0; i < 10240; i++) {
		Dbl = TEnvironment::GenerateRandomDOUBLE();
		DOUBLEToStr(Dbl, P1, 12);
		DOUBLE Dbl2 = StrToDOUBLE(P1, 0, '.', ' ');
		if (!IsEqualDOUBLES(Dbl, Dbl2, 1e-12)) return TEnvironment::ShowTestErrorMessage(-37, "DOUBLEToStr + StrToDOUBLE (%.12lf, %.12lf)", Dbl, Dbl2);
	}

	INT64 Data[8];
	for (INT64 i = 0; i < 8; i++) Data[i] = 9 - i;
	QuickSort(Data, 8, sizeof(INT64), [](CONST_PVOID iData, INT64 iIndex1, INT64 iIndex2, CONST_PVOID iUserData) -> INT32 {
		INT64 V1 = ((PINT64)iData)[iIndex1];
		INT64 V2 = ((PINT64)iData)[iIndex2];
		if (V1 < V2) return -1;
		if (V1 > V2) return 1;
		return 0;
		}, NULL);

	if ((Data[0] != 2) || (Data[1] != 3) || (Data[2] != 4) || (Data[3] != 5) || (Data[4] != 6) || (Data[5] != 7) || (Data[6] != 8) || (Data[7] != 9)) return TEnvironment::ShowTestErrorMessage(-38, "QuickSort");

	QuickSort(Data, 8, sizeof(INT64), [](CONST_PVOID iData, INT64 iIndex1, INT64 iIndex2, CONST_PVOID iUserData) -> INT32 {
		INT64 V1 = ((PINT64)iData)[iIndex1];
		INT64 V2 = ((PINT64)iData)[iIndex2];
		if (V1 < V2) return 1;
		if (V1 > V2) return -1;
		return 0;
		}, NULL);

	if ((Data[0] != 9) || (Data[1] != 8) || (Data[2] != 7) || (Data[3] != 6) || (Data[4] != 5) || (Data[5] != 4) || (Data[6] != 3) || (Data[7] != 2)) return TEnvironment::ShowTestErrorMessage(-39, "QuickSort");

	for (INT64 i = 0; i < 8; i++) Data[i] = i;

	for (INT64 i = -1; i < 8; i++) {
		U64 = (UINT64)i;
		I64 = BinarySearch(Data, 8, sizeof(INT64), [](CONST_PVOID iData, CONST_PVOID iUserData) -> INT32 {
			UINT64 V1 = *((PUINT64)iData);
			UINT64 V2 = (UINT64)iUserData;
			return V1 == V2 ? 0 : (V1 < V2 ? -1 : 1);
			}, (CONST_PVOID)U64);
		if (I64 != i) return TEnvironment::ShowTestErrorMessage(-40, "BinarySearch");
	}

	Data[3] = 1; U64 = 1;
	I64 = BinarySearch(Data, 8, sizeof(INT64), [](CONST_PVOID iData, CONST_PVOID iUserData) -> INT32 {
		UINT64 V1 = *((PUINT64)iData);
		UINT64 V2 = (UINT64)iUserData;
		return V1 == V2 ? 0 : (V1 < V2 ? -1 : 1);
		}, (CONST_PVOID)U64, BINARY_SEARCH_FIRST_OCCURRENCE);
	if (I64 != 1) return TEnvironment::ShowTestErrorMessage(-41, "BinarySearch");
	I64 = BinarySearch(Data, 8, sizeof(INT64), [](CONST_PVOID iData, CONST_PVOID iUserData) -> INT32 {
		UINT64 V1 = *((PUINT64)iData);
		UINT64 V2 = (UINT64)iUserData;
		return V1 == V2 ? 0 : (V1 < V2 ? -1 : 1);
		}, (CONST_PVOID)U64, BINARY_SEARCH_LAST_OCCURRENCE);
	if (I64 != 3) return TEnvironment::ShowTestErrorMessage(-42, "BinarySearch");

	strcpy(P1, "abcdefgh");
	U64 = GenerateHash64(P1, FNC_STRLEN(P1), NULL, -1);
	if (U64 != GenerateHash64(P1, -1, NULL, 0)) return TEnvironment::ShowTestErrorMessage(-43, "GenerateHash64");

	PUINT64 D1 = (PUINT64)MEMORY_ALLOC(1024 * sizeof(UINT64));
	PUINT64 D2 = (PUINT64)MEMORY_ALLOC(1024 * sizeof(UINT64));
	PUINT64 D3 = (PUINT64)MEMORY_ALLOC(1024 * sizeof(UINT64));

	for (INT64 i = 0; i < 1024; i++) D1[i] = TEnvironment::GenerateRandomUINT64();

	for (INT64 j = 2; j < 1024; j++) {
		FNC_MEMCPY(D2, D1, j * sizeof(UINT64));
		FNC_MEMCPY(D3, D1, j * sizeof(UINT64));

		qsort(D2, j, sizeof(UINT64), [](CONST_PVOID i1, CONST_PVOID i2) -> INT32 {
			UINT64 u1 = *((PUINT64)i1);
			UINT64 u2 = *((PUINT64)i2);
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			});
		QuickSort(D3, j, sizeof(UINT64), [](CONST_PVOID iData, INT64 iIndex1, INT64 iIndex2, CONST_PVOID iUserData) -> INT32 {
			UINT64 u1 = ((PUINT64)iData)[iIndex1];
			UINT64 u2 = ((PUINT64)iData)[iIndex2];
			return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
			}, D3);

		for (INT64 i = 0; i < j; i++) {
			if (D2[i] != D3[i]) return TEnvironment::ShowTestErrorMessage(-44, "QuickSort");
		}
	}

	MEMORY_FREE(D1);
	MEMORY_FREE(D2);
	MEMORY_FREE(D3);

	PCHAR_FREE(P1);
	PCHAR_FREE(P2);
	return true;
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TString
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TString(void) {
	PCHAR P1 = PCHAR_ALLOC(1024);
	PCHAR P2 = PCHAR_ALLOC(1024);
	if ((P1 == NULL) || (P2 == NULL)) {
		TEnvironment::ShowTestErrorMessage(-1999, "Memory allocation failed in validity tests for TString");
		return false;
	}

	TString S1, S2, S3;

	for (INT64 i = 0; i < 1024; i++) {
		TString::GenerateRandomBASE64String(P1, i);
		S1.SetValue(P1, -1); if ((S1.Length != i) || (FNC_STRCMP(S1.PChar(), P1) != 0)) return TEnvironment::ShowTestErrorMessage(-1001, "TString::SetValue (%lld)", i);
		S1.Release();
		S1.SetValue(P1, i); if ((S1.Length != i) || (FNC_STRCMP(S1.PChar(), P1) != 0)) return TEnvironment::ShowTestErrorMessage(-1002, "TString::SetValue (%lld)", i);
	}

	S1.SetValue("012");
	S1.SetLength(2); if ((S1.Length != 2) || (FNC_STRCMP(S1.PChar(), "01") != 0)) return TEnvironment::ShowTestErrorMessage(-1003, "TString::SetLength");
	S1.SetLength(1); if ((S1.Length != 1) || (FNC_STRCMP(S1.PChar(), "0") != 0)) return TEnvironment::ShowTestErrorMessage(-1004, "TString::SetLength");
	S1.SetLength(0); if ((S1.Length != 0) || (FNC_STRCMP(S1.PChar(), "") != 0)) return TEnvironment::ShowTestErrorMessage(-1005, "TString::SetLength");

	for (INT32 i = 0; i < 1024; i++) {
		INT32 I32 = (INT32)TEnvironment::GenerateRandomUINT32();
		S1.SetValue(I32); if (S1.AsINT32() != I32) return TEnvironment::ShowTestErrorMessage(-1006, "TString::SetValue(INT32) + TString::AsINT32");
		UINT32 U32 = TEnvironment::GenerateRandomUINT32();
		S1.SetValue(U32); if (S1.AsUINT32() != U32) return TEnvironment::ShowTestErrorMessage(-1007, "TString::SetValue(UINT32) + TString::AsUINT32");
		INT64 I64 = (INT64)TEnvironment::GenerateRandomUINT64();
		S1.SetValue(I64); if (S1.AsINT64() != I64) return TEnvironment::ShowTestErrorMessage(-1008, "TString::SetValue(INT64) + TString::AsINT64");
		UINT64 U64 = TEnvironment::GenerateRandomUINT64();
		S1.SetValue(U64); if (S1.AsUINT64() != U64) return TEnvironment::ShowTestErrorMessage(-1009, "TString::SetValue(UINT64) + TString::AsUINT64");
		DOUBLE D = TEnvironment::GenerateRandomDOUBLE(-10000, 10000);
		for (INT32 j = 0; j < 13; j++) {
			S1.SetValue(D, j); DOUBLE D2 = S1.AsDOUBLE();
			if (IsEqualDOUBLES(D, D2) != 0) return TEnvironment::ShowTestErrorMessage(-1010, "TString::SetValue(DOUBLE) + TString::AsDOUBLE");
		}
	}

	S1.SetValue(""); if (S1.Compare("", 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1011, "TString::Compare");
	S1.SetValue(""); if (S1.Compare("a", 0, -1) >= 0) return TEnvironment::ShowTestErrorMessage(-1012, "TString::Compare");
	S1.SetValue("a"); if (S1.Compare("", 0, -1) <= 0) return TEnvironment::ShowTestErrorMessage(-1013, "TString::Compare");
	S1.SetValue("a"); if (S1.Compare("", 1, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1014, "TString::Compare");
	S1.SetValue("a"); if (S1.Compare("a", 1, -1) >= 0) return TEnvironment::ShowTestErrorMessage(-1015, "TString::Compare");
	S1.SetValue("a"); if (S1.Compare("a", 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1016, "TString::Compare");
	S1.SetValue("ab"); if (S1.Compare("a", 0, -1) <= 0) return TEnvironment::ShowTestErrorMessage(-1017, "TString::Compare");
	S1.SetValue("ab"); if (S1.Compare("a", 0, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1018, "TString::Compare");
	S1.SetValue("ab"); if (S1.Compare("a", 1, 1) <= 0) return TEnvironment::ShowTestErrorMessage(-1019, "TString::Compare");
	S1.SetValue("abcde"); if (S1.Compare("bcd", 1, -1) <= 0) return TEnvironment::ShowTestErrorMessage(-1020, "TString::Compare");
	S1.SetValue("abcde"); if (S1.Compare("bcd", 1, 3) != 0) return TEnvironment::ShowTestErrorMessage(-1021, "TString::Compare");
	S1.SetValue("abcde"); if (S1.Compare("bcd", 1, 0) <= 0) return TEnvironment::ShowTestErrorMessage(-1022, "TString::Compare");

	for (INT64 i = 0; i < 1024; i++) {
		TString::GenerateRandomBASE64String(P1, i);
		S1.SetValue(P1, -1);
		if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1023, "TString::Compare (%lld)", i);
		TString::GenerateRandomBASE64String(P2, i);
		INT32 R1 = FNC_STRCMP(P1, P2); if (R1 != 0) R1 = (R1 < 0) ? -1 : 1;
		INT32 R2 = S1.Compare(P2, 0, -1); if (R2 != 0) R2 = (R2 < 0) ? -1 : 1;
		if (R1 != R2) return TEnvironment::ShowTestErrorMessage(-1024, "TString::Compare (%lld)", i);
	}

	S1.SetValue(""); if (S1.CaseCompare("", 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1025, "TString::CaseCompare");
	S1.SetValue(""); if (S1.CaseCompare("a", 0, -1) >= 0) return TEnvironment::ShowTestErrorMessage(-1026, "TString::CaseCompare");
	S1.SetValue("A"); if (S1.CaseCompare("", 0, -1) <= 0) return TEnvironment::ShowTestErrorMessage(-1027, "TString::CaseCompare");
	S1.SetValue("A"); if (S1.CaseCompare("", 1, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1028, "TString::CaseCompare");
	S1.SetValue("A"); if (S1.CaseCompare("a", 1, -1) >= 0) return TEnvironment::ShowTestErrorMessage(-1029, "TString::CaseCompare");
	S1.SetValue("A"); if (S1.CaseCompare("a", 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1030, "TString::CaseCompare");
	S1.SetValue("AB"); if (S1.CaseCompare("a", 0, -1) <= 0) return TEnvironment::ShowTestErrorMessage(-1031, "TString::CaseCompare");
	S1.SetValue("AB"); if (S1.CaseCompare("a", 0, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1032, "TString::CaseCompare");
	S1.SetValue("AB"); if (S1.CaseCompare("a", 1, 1) <= 0) return TEnvironment::ShowTestErrorMessage(-1033, "TString::CaseCompare");
	S1.SetValue("ABCDE"); if (S1.CaseCompare("bcd", 1, -1) <= 0) return TEnvironment::ShowTestErrorMessage(-1034, "TString::CaseCompare");
	S1.SetValue("ABCDE"); if (S1.CaseCompare("bcd", 1, 3) != 0) return TEnvironment::ShowTestErrorMessage(-1035, "TString::CaseCompare");
	S1.SetValue("ABCDE"); if (S1.CaseCompare("bcd", 1, 0) <= 0) return TEnvironment::ShowTestErrorMessage(-1036, "TString::CaseCompare");

	for (INT64 i = 0; i < 1024; i++) {
		TString::GenerateRandomBASE64String(P1, i);
		S1.SetValue(P1, -1);
		if (S1.CaseCompare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1037, "TString::CaseCompare (%lld)", i);
		TString::GenerateRandomBASE64String(P2, i);
		INT32 R1 = FNC_STRCASECMP(P1, P2); if (R1 != 0) R1 = (R1 < 0) ? -1 : 1;
		INT32 R2 = S1.CaseCompare(P2, 0, -1); if (R2 != 0) R2 = (R2 < 0) ? -1 : 1;
		if (R1 != R2) {
			R1 = FNC_STRCASECMP(P1, P2);
			R2 = S1.CaseCompare(P2, 0, -1);
			return TEnvironment::ShowTestErrorMessage(-1038, "TString::CaseCompare (%lld)", i);
		}
	}

	for (UINT32 i = 1; i < 256; i++) P1[i - 1] = i;
	P1[255] = 0;

	S1.SetValue(P1); S1.ToLowercase(28591); if (S1.CaseCompare(P1, 0, -1, 28591) != 0) return TEnvironment::ShowTestErrorMessage(-1040, "ToLowercase");
	S1.SetValue(P1); S1.ToLowercase(1250); if (S1.CaseCompare(P1, 0, -1, 1250) != 0) return TEnvironment::ShowTestErrorMessage(-1041, "ToLowercase");
	S1.SetValue(P1); S1.ToLowercase(1252); if (S1.CaseCompare(P1, 0, -1, 1252) != 0) return TEnvironment::ShowTestErrorMessage(-1042, "ToLowercase");
	S1.SetValue(P1); S1.ToUppercase(28591); if (S1.CaseCompare(P1, 0, -1, 28591) != 0) return TEnvironment::ShowTestErrorMessage(-1043, "ToLowercase");
	S1.SetValue(P1); S1.ToUppercase(1250); if (S1.CaseCompare(P1, 0, -1, 1250) != 0) return TEnvironment::ShowTestErrorMessage(-1044, "ToLowercase");
	S1.SetValue(P1); S1.ToUppercase(1252); if (S1.CaseCompare(P1, 0, 256, 1252) != 0) return TEnvironment::ShowTestErrorMessage(-1045, "ToLowercase");


#ifdef WINDOWS_SYSTEM
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); CharLowerA(P1); S1.ToLowercase(); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1046, "TString::ToLowercase");
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); CharLowerA(P1); S1.ToLowercase(1250); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1047, "TString::ToLowercase");
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); CharLowerA(P1); S1.ToLowercase(1252); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1048, "TString::ToLowercase");

	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); CharUpperA(P1); S1.ToUppercase(); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1049, "TString::ToUppercase");
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); CharUpperA(P1); S1.ToUppercase(1250); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1050, "TString::ToUppercase");
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); CharUpperA(P1); S1.ToUppercase(1252); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1051, "TString::ToUppercase");
#else

	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); 
	//CharLowerA(P1); 
	for (INT32 i = 0; P1[i] != 0; i++) P1[i] = tolower((BYTE)P1[i]);
	S1.ToLowercase(); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1046, "TString::ToLowercase (%s)", P1);
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); 
	//CharLowerA(P1); 
	setlocale(LC_CTYPE, "Slovak_Slovakia.1250");
	for (INT32 i = 0; P1[i] != 0; i++) P1[i] = tolower((BYTE)P1[i]);
	S1.ToLowercase(1250); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1047, "TString::ToLowercase");
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); 
	//CharLowerA(P1); 
	setlocale(LC_CTYPE, "en_US.cp1252");
	for (INT32 i = 0; P1[i] != 0; i++) P1[i] = tolower((BYTE)P1[i]);
	S1.ToLowercase(1252); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1048, "TString::ToLowercase");

	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); 
	//CharUpperA(P1); 
	for (INT32 i = 0; P1[i] != 0; i++) P1[i] = toupper((BYTE)P1[i]);
	S1.ToUppercase(); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1049, "TString::ToUppercase (%s)", P1);
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); 
	//CharUpperA(P1); 
	setlocale(LC_CTYPE, "Slovak_Slovakia.1250");
	for (INT32 i = 0; P1[i] != 0; i++) P1[i] = toupper((BYTE)P1[i]);
	S1.ToUppercase(1250); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1050, "TString::ToUppercase");
	TString::GenerateRandomBASE64String(P1, 512); S1.SetValue(P1); 
	//CharUpperA(P1); 
	setlocale(LC_CTYPE, "en_US.cp1252");
	for (INT32 i = 0; P1[i] != 0; i++) P1[i] = toupper((BYTE)P1[i]);
	S1.ToUppercase(1252); if (S1.Compare(P1, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-1051, "TString::ToUppercase");
#endif

	S1.SetValue("aabb"); S1.RightTrim(); if ((S1.Length != 4) || (FNC_STRCMP(S1.PChar(), "aabb") != 0)) return TEnvironment::ShowTestErrorMessage(-1052, "TString::RightTrim");
	S1.SetValue("aabb  "); S1.RightTrim(); if ((S1.Length != 4) || (FNC_STRCMP(S1.PChar(), "aabb") != 0)) return TEnvironment::ShowTestErrorMessage(-1053, "TString::RightTrim");
	S1.SetValue("bbaa  "); S1.RightTrim('a'); if ((S1.Length != 2) || (FNC_STRCMP(S1.PChar(), "bb") != 0)) return TEnvironment::ShowTestErrorMessage(-1054, "TString::RightTrim");
	S1.SetValue("   "); S1.RightTrim(); if ((S1.Length != 0) || (FNC_STRCMP(S1.PChar(), "") != 0)) return TEnvironment::ShowTestErrorMessage(-1055, "TString::RightTrim");
	S1.SetValue("aabb"); S1.LeftTrim(); if ((S1.Length != 4) || (FNC_STRCMP(S1.PChar(), "aabb") != 0)) return TEnvironment::ShowTestErrorMessage(-1056, "TString::LeftTrim");
	S1.SetValue(" aabb"); S1.LeftTrim(); if ((S1.Length != 4) || (FNC_STRCMP(S1.PChar(), "aabb") != 0)) return TEnvironment::ShowTestErrorMessage(-1057, "TString::LeftTrim");
	S1.SetValue(" aabb"); S1.LeftTrim('a'); if ((S1.Length != 2) || (FNC_STRCMP(S1.PChar(), "bb") != 0)) return TEnvironment::ShowTestErrorMessage(-1058, "TString::LeftTrim");
	S1.SetValue(" aabb"); S1.LeftTrim('b'); if ((S1.Length != 0) || (FNC_STRCMP(S1.PChar(), "") != 0)) return TEnvironment::ShowTestErrorMessage(-1059, "TString::LeftTrim");
	S1.SetValue("aabb"); S1.Trim(); if ((S1.Length != 4) || (FNC_STRCMP(S1.PChar(), "aabb") != 0)) return TEnvironment::ShowTestErrorMessage(-1060, "TString::Trim");
	S1.SetValue("  aabb "); S1.Trim(); if ((S1.Length != 4) || (FNC_STRCMP(S1.PChar(), "aabb") != 0)) return TEnvironment::ShowTestErrorMessage(-1061, "TString::Trim");
	S1.SetValue("  aabb "); S1.Trim('a'); if ((S1.Length != 2) || (FNC_STRCMP(S1.PChar(), "bb") != 0)) return TEnvironment::ShowTestErrorMessage(-1062, "TString::Trim");
	S1.SetValue("  aabb "); S1.Trim('b'); if ((S1.Length != 0) || (FNC_STRCMP(S1.PChar(), "") != 0)) return TEnvironment::ShowTestErrorMessage(-1063, "TString::Trim");

	FNC_SPRINTF(P1, "dsadsadksahdsadshakj [%d] [%.5lf], [%s]", -1, 333.222, "dssadsadadsasa");
	S1.Format("dsadsadksahdsadshakj [%d] [%.5lf], [%s]", -1, 333.222, "dssadsadadsasa");
	if ((S1.Length != (INT64)FNC_STRLEN(P1)) || (S1.Compare(P1) != 0)) return TEnvironment::ShowTestErrorMessage(-1064, "TString::Format ([%ld], [%s], [%s]", S1.Length, S1.PChar(), P1);

	S1.SetValue("abcdabef");
	if (S1.FindChar('a', 0, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1065, "TString::FindChar");
	if (S1.FindChar('a', 1, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-1066, "TString::FindChar");
	if (S1.FindChar('a', 1, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1067, "TString::FindChar");
	if (S1.FindChar('a', 0, -1, 2) != 4) return TEnvironment::ShowTestErrorMessage(-1068, "TString::FindChar");
	if (S1.FindChar('a', 0, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1069, "TString::FindChar");
	if (S1.FindChar('a', 5, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1070, "TString::FindChar");
	if (S1.FindChar('a', 0, 0, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1071, "TString::FindChar");
	if (S1.FindChar('a', 0, 1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1072, "TString::FindChar");
	if (S1.FindChar('a', 1, 2, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1073, "TString::FindChar");
	if (S1.FindChar('z', 0, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1074, "TString::FindChar");
	if (S1.FindChar('e', 0, -1, 1) != 6) return TEnvironment::ShowTestErrorMessage(-1075, "TString::FindChar");
	if (S1.FindChar('e', 0, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1076, "TString::FindChar");
	S1.SetValue("baaaaaaaaaaaaaabxxb");
	if (S1.FindChar('b', 0, 100, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1077, "TString::FindChar");
	if (S1.FindChar('b', 0, 100, 2) != 15) return TEnvironment::ShowTestErrorMessage(-1078, "TString::FindChar");
	if (S1.FindChar('b', 0, 100, 3) != 18) return TEnvironment::ShowTestErrorMessage(-1079, "TString::FindChar");
	if (S1.FindChar('b', 0, 100, 4) != -1) return TEnvironment::ShowTestErrorMessage(-1080, "TString::FindChar");

	for (INT32 i = 1; i < 1024; i++) {
		TString::GenerateRandomBASE64String(P1, i);
		S1.SetValue(P1);

		PCHAR P = FNC_STRCHR(P1 + 1, P1[0]);
		INT64 k1 = P == NULL ? -1 : (INT64)(P - P1);
		INT64 k = S1.FindChar(P1[0], 1, -1, 1);
		if (k != k1) return TEnvironment::ShowTestErrorMessage(-1081, "TString::FindChar (%i)", i);
	}

	S1.SetValue("ABCDABEF");
	if (S1.CaseFindChar('a', 0, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1082, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 1, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-1083, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 1, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1084, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 0, -1, 2) != 4) return TEnvironment::ShowTestErrorMessage(-1085, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 0, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1086, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 5, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1087, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 0, 0, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1088, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 0, 1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1089, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 1, 2, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1090, "TString::CaseFindChar");
	if (S1.CaseFindChar('z', 0, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1091, "TString::CaseFindChar");
	if (S1.CaseFindChar('e', 0, -1, 1) != 6) return TEnvironment::ShowTestErrorMessage(-1092, "TString::CaseFindChar");
	if (S1.CaseFindChar('e', 0, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1093, "TString::CaseFindChar");
	S1.SetValue("BAAAAAAAAAAAAAABXXB");
	if (S1.CaseFindChar('b', 0, 100, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1094, "TString::CaseFindChar");
	if (S1.CaseFindChar('b', 0, 100, 2) != 15) return TEnvironment::ShowTestErrorMessage(-1095, "TString::CaseFindChar");
	if (S1.CaseFindChar('b', 0, 100, 3) != 18) return TEnvironment::ShowTestErrorMessage(-1096, "TString::CaseFindChar");
	if (S1.CaseFindChar('b', 0, 100, 4) != -1) return TEnvironment::ShowTestErrorMessage(-1097, "TString::CaseFindChar");

	for (INT32 i = 1; i < 1024; i++) {
		TString::GenerateRandomBASE64String(P1, i);
		S1.SetValue(P1); S2.SetValue(P1); S2.ToLowercase();

		CHAR C = S2.PChar()[0];
		PCHAR P = FNC_STRCHR((PCHAR)S2.PChar() + 1, C);
		INT64 k1 = P == NULL ? -1 : (INT64)(P - S2.PChar());
		INT64 k = S1.CaseFindChar(C, 1, -1, 1);
		if (k != k1) return TEnvironment::ShowTestErrorMessage(-1098, "TString::CaseFindChar (%i)", i);
	}

	S1.SetValue("abcdabef");
	if (S1.ReverseFindChar('a', -1, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-1099, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('a', -1, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-1100, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('a', -1, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1101, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('a', 4, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-1102, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('a', 4, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-1103, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('a', 4, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1104, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('a', 3, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1105, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('a', 3, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1106, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('e', -1, -1, 1) != 6) return TEnvironment::ShowTestErrorMessage(-1107, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('e', -1, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1108, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('e', 5, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1109, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('e', -1, 2, 1) != 6) return TEnvironment::ShowTestErrorMessage(-1110, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('e', -1, 1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1111, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('z', -1, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1112, "TString::ReverseFindChar");

	S1.SetValue("baaaaaaaaaaaaaabxxb");
	if (S1.ReverseFindChar('b', -1, -1, 1) != 18) return TEnvironment::ShowTestErrorMessage(-1113, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', -1, -1, 2) != 15) return TEnvironment::ShowTestErrorMessage(-1114, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', -1, -1, 3) != 0) return TEnvironment::ShowTestErrorMessage(-1115, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', -1, -1, 4) != -1) return TEnvironment::ShowTestErrorMessage(-1116, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', 17, -1, 1) != 15) return TEnvironment::ShowTestErrorMessage(-1117, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', 17, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-1118, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', 17, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1119, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', -1, 4, 1) != 18) return TEnvironment::ShowTestErrorMessage(-1120, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', -1, 4, 2) != 15) return TEnvironment::ShowTestErrorMessage(-1121, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', -1, 4, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1122, "TString::ReverseFindChar");
	if (S1.ReverseFindChar('b', 17, 1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1123, "TString::ReverseFindChar");

	for (INT32 i = 1; i < 1024; i++) {
		TString::GenerateRandomBASE64String(P1, i);
		S1.SetValue(P1);

		PCHAR P = FNC_STRRCHR(P1, P1[0]);
		INT64 k1 = P == NULL ? -1 : (INT64)(P - P1);
		INT64 k = S1.ReverseFindChar(P1[0], -1, -1, 1);
		if (k != k1) {
			return TEnvironment::ShowTestErrorMessage(-1124, "TString::ReverseFindChar (%i)", i);
		}
	}

	// Shared string
	FNC_STRCPY(P1, "abcdabef"); S1.SetSharedValue(P1);
	if (S1.FindChar('a', 0, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1126, "TString::FindChar");
	if (S1.FindChar('a', 1, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-1127, "TString::FindChar");
	if (S1.FindChar('a', 1, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1128, "TString::FindChar");
	if (S1.FindChar('a', 0, -1, 2) != 4) return TEnvironment::ShowTestErrorMessage(-1129, "TString::FindChar");
	if (S1.FindChar('a', 0, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1130, "TString::FindChar");
	if (S1.FindChar('a', 5, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1131, "TString::FindChar");
	if (S1.FindChar('a', 0, 0, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1132, "TString::FindChar");
	if (S1.FindChar('a', 0, 1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1133, "TString::FindChar");
	if (S1.FindChar('a', 1, 2, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1134, "TString::FindChar");
	if (S1.FindChar('z', 0, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1135, "TString::FindChar");
	if (S1.FindChar('e', 0, -1, 1) != 6) return TEnvironment::ShowTestErrorMessage(-1136, "TString::FindChar");
	if (S1.FindChar('e', 0, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1137, "TString::FindChar");
	FNC_STRCPY(P1, "baaaaaaaaaaaaaabxxb"); S1.SetSharedValue(P1);
	if (S1.FindChar('b', 0, 100, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1138, "TString::FindChar");
	if (S1.FindChar('b', 0, 100, 2) != 15) return TEnvironment::ShowTestErrorMessage(-1139, "TString::FindChar");
	if (S1.FindChar('b', 0, 100, 3) != 18) return TEnvironment::ShowTestErrorMessage(-1140, "TString::FindChar");
	if (S1.FindChar('b', 0, 100, 4) != -1) return TEnvironment::ShowTestErrorMessage(-1141, "TString::FindChar");

	FNC_STRCPY(P1, "ABCDABEF"); S1.SetSharedValue(P1);
	if (S1.CaseFindChar('a', 0, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1142, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 1, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-1143, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 1, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1144, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 0, -1, 2) != 4) return TEnvironment::ShowTestErrorMessage(-1145, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 0, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1146, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 5, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1147, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 0, 0, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1148, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 0, 1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1149, "TString::CaseFindChar");
	if (S1.CaseFindChar('a', 1, 2, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1150, "TString::CaseFindChar");
	if (S1.CaseFindChar('z', 0, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1151, "TString::CaseFindChar");
	if (S1.CaseFindChar('e', 0, -1, 1) != 6) return TEnvironment::ShowTestErrorMessage(-1152, "TString::CaseFindChar");
	if (S1.CaseFindChar('e', 0, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1153, "TString::CaseFindChar");
	FNC_STRCPY(P1, "BAAAAAAAAAAAAAABXXB"); S1.SetSharedValue(P1);
	if (S1.CaseFindChar('b', 0, 100, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1154, "TString::CaseFindChar");
	if (S1.CaseFindChar('b', 0, 100, 2) != 15) return TEnvironment::ShowTestErrorMessage(-1155, "TString::CaseFindChar");
	if (S1.CaseFindChar('b', 0, 100, 3) != 18) return TEnvironment::ShowTestErrorMessage(-1156, "TString::CaseFindChar");
	if (S1.CaseFindChar('b', 0, 100, 4) != -1) return TEnvironment::ShowTestErrorMessage(-1157, "TString::CaseFindChar");

	S1.SetValue("ABCDABEF");
	if (S1.ReverseCaseFindChar('a', -1, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-1158, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('a', -1, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-1159, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('a', -1, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1160, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('a', 4, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-1161, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('a', 4, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-1162, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('a', 4, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1163, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('a', 3, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1164, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('a', 3, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1165, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('e', -1, -1, 1) != 6) return TEnvironment::ShowTestErrorMessage(-1166, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('e', -1, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1167, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('e', 5, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1168, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('e', -1, 2, 1) != 6) return TEnvironment::ShowTestErrorMessage(-1169, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('e', -1, 1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1170, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('z', -1, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1171, "TString::ReverseCaseFindChar");

	S1.SetValue("BAAAAAAAAAAAAAABXXB");
	if (S1.ReverseCaseFindChar('b', -1, -1, 1) != 18) return TEnvironment::ShowTestErrorMessage(-1172, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', -1, -1, 2) != 15) return TEnvironment::ShowTestErrorMessage(-1173, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', -1, -1, 3) != 0) return TEnvironment::ShowTestErrorMessage(-1174, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', -1, -1, 4) != -1) return TEnvironment::ShowTestErrorMessage(-1175, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', 17, -1, 1) != 15) return TEnvironment::ShowTestErrorMessage(-1176, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', 17, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-1177, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', 17, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1178, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', -1, 4, 1) != 18) return TEnvironment::ShowTestErrorMessage(-1179, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', -1, 4, 2) != 15) return TEnvironment::ShowTestErrorMessage(-1180, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', -1, 4, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1181, "TString::ReverseCaseFindChar");
	if (S1.ReverseCaseFindChar('b', 17, 1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1182, "TString::ReverseCaseFindChar");

	for (INT32 i = 1; i < 1024; i++) {
		TString::GenerateRandomBASE64String(P1, i);
		S1.SetValue(P1);

		PCHAR P = FNC_STRRCHR(P1, P1[0]);
		INT64 k1 = P == NULL ? -1 : (INT64)(P - P1);
		INT64 k = S1.ReverseFindChar(P1[0], -1, -1, 1);
		if (k != k1) {
			return TEnvironment::ShowTestErrorMessage(-1124, "TString::ReverseFindChar (%i)", i);
		}
	}

	S1.SetValue("abcdefgh"); S2.SetValue("aBcDeFgH");
	if (S1.GetHashCode() == S2.GetHashCode()) return TEnvironment::ShowTestErrorMessage(-1183, "TString::GetHashCode");
	if (S1.GetCaseHashCode() != S2.GetCaseHashCode()) return TEnvironment::ShowTestErrorMessage(-1184, "TString::GetCaseHashCode");

	S1.SetValue("abc"); S1.AppendValue("def", -1); if ((S1.Length != 6) || (FNC_STRCMP(S1.PChar(), "abcdef") != 0)) return TEnvironment::ShowTestErrorMessage(-1185, "TString::AppendValue");
	S1.SetValue("abc"); S1.AppendValue("def", 2); if ((S1.Length != 5) || (FNC_STRCMP(S1.PChar(), "abcde") != 0)) return TEnvironment::ShowTestErrorMessage(-1186, "TString::AppendValue");
	S1.SetValue("abc "); S1.AppendValue((INT32)-123); if ((S1.Length != 8) || (FNC_STRCMP(S1.PChar(), "abc -123") != 0)) return TEnvironment::ShowTestErrorMessage(-1187, "TString::AppendValue");
	S1.SetValue("abc "); S1.AppendValue((UINT32)123); if ((S1.Length != 7) || (FNC_STRCMP(S1.PChar(), "abc 123") != 0)) return TEnvironment::ShowTestErrorMessage(-1188, "TString::AppendValue");
	S1.SetValue("abc "); S1.AppendValue((INT64)-1234); if ((S1.Length != 9) || (FNC_STRCMP(S1.PChar(), "abc -1234") != 0)) return TEnvironment::ShowTestErrorMessage(-1189, "TString::AppendValue");
	S1.SetValue("abc "); S1.AppendValue((DOUBLE)-1234.25, 6, ','); if ((S1.Length != 16) || (FNC_STRCMP(S1.PChar(), "abc -1234,250000") != 0)) return TEnvironment::ShowTestErrorMessage(-1190, "TString::AppendValue");
	S1.SetValue("abc"); S1.AppendChars('c', 3, false); if ((S1.Length != 6) || (FNC_STRCMP(S1.PChar(), "abcccc") != 0)) return TEnvironment::ShowTestErrorMessage(-1191, "TString::AppendChars");
	S1.SetValue("abc"); S1.AppendChars('c', 3, true); if ((S1.Length != 3) || (FNC_STRCMP(S1.PChar(), "abc") != 0)) return TEnvironment::ShowTestErrorMessage(-1192, "TString::AppendChars");

	S1.SetRandomBASE64Value(1024);
	if (S1.GetHashCode() != TString::GenerateHashCode(S1.PChar(), -1)) return TEnvironment::ShowTestErrorMessage(-1193, "TString::GetHashCode / TString::GenerateHashCode");
	if (S1.GetCaseHashCode() != TString::GenerateCaseHashCode(S1.PChar(), -1)) return TEnvironment::ShowTestErrorMessage(-1194, "TString::GetCaseHashCode / TString::GenerateCaseHashCode");

	CONST_PWCHAR PW1 = L"abcdefghi";
	S1.SetValue(PW1, -1, 0); if (!S1.IsEqual("abcdefghi")) return TEnvironment::ShowTestErrorMessage(-1195, "TString::SetValue");

	S1.SetValue("abc"); S1.TrimQuotes('\''); if (!S1.IsEqual("abc")) return TEnvironment::ShowTestErrorMessage(-1196, "TString::TrimQuotes");
	S1.SetValue("'abc"); S1.TrimQuotes('\''); if (!S1.IsEqual("'abc")) return TEnvironment::ShowTestErrorMessage(-1197, "TString::TrimQuotes");
	S1.SetValue("'abc'"); S1.TrimQuotes('\''); if (!S1.IsEqual("abc")) return TEnvironment::ShowTestErrorMessage(-1198, "TString::TrimQuotes");
	S1.SetValue("abc'"); S1.TrimQuotes('\''); if (!S1.IsEqual("abc'")) return TEnvironment::ShowTestErrorMessage(-1199, "TString::TrimQuotes");
	S1.SetValue("''"); S1.TrimQuotes('\''); if (!S1.IsEqual("")) return TEnvironment::ShowTestErrorMessage(-1200, "TString::TrimQuotes");
	S1.SetValue("''abc''"); S1.TrimQuotes('\''); if (!S1.IsEqual("abc")) return TEnvironment::ShowTestErrorMessage(-1201, "TString::TrimQuotes");
	S1.SetValue("''abc'"); S1.TrimQuotes('\''); if (!S1.IsEqual("'abc")) return TEnvironment::ShowTestErrorMessage(-1202, "TString::TrimQuotes");

	S1.SetValue(""); S1.ExtractNameValuePair(&S2, &S3, '=', '\"', ' '); if ((!S2.IsEqual("")) || (!S3.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-1203, "TString::ExtractNameValuePair");
	S1.SetValue("abc"); S1.ExtractNameValuePair(&S2, &S3, '=', '\"', ' '); if ((!S2.IsEqual("abc")) || (!S3.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-1204, "TString::ExtractNameValuePair");
	S1.SetValue(" abc "); S1.ExtractNameValuePair(&S2, &S3, '=', '\"', ' '); if ((!S2.IsEqual("abc")) || (!S3.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-1205, "TString::ExtractNameValuePair");
	S1.SetValue("abc="); S1.ExtractNameValuePair(&S2, &S3, '=', '\"', ' '); if ((!S2.IsEqual("abc")) || (!S3.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-1206, "TString::ExtractNameValuePair");
	S1.SetValue(" abc    ="); S1.ExtractNameValuePair(&S2, &S3, '=', '\"', ' '); if ((!S2.IsEqual("abc")) || (!S3.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-1207, "TString::ExtractNameValuePair");
	S1.SetValue(" abc    =test"); S1.ExtractNameValuePair(&S2, &S3, '=', '\"', ' '); if ((!S2.IsEqual("abc")) || (!S3.IsEqual("test"))) return TEnvironment::ShowTestErrorMessage(-1208, "TString::ExtractNameValuePair");
	S1.SetValue(" abc    =   test   "); S1.ExtractNameValuePair(&S2, &S3, '=', '\"', ' '); if ((!S2.IsEqual("abc")) || (!S3.IsEqual("test"))) return TEnvironment::ShowTestErrorMessage(-1209, "TString::ExtractNameValuePair");
	S1.SetValue(" abc    =   'test '   "); S1.ExtractNameValuePair(&S2, &S3, '=', '\'', ' '); if ((!S2.IsEqual("abc")) || (!S3.IsEqual("test "))) return TEnvironment::ShowTestErrorMessage(-1210, "TString::ExtractNameValuePair");

	S1.SetValue("aaaaaa"); if ((S1.InsertValue(7, "bb", -1) != 6) || (S1.Length != 8) || (!S1.IsEqual("aaaaaabb"))) return TEnvironment::ShowTestErrorMessage(-1211, "TString::InsertValue");
	S1.SetValue("aaaaaa"); if ((S1.InsertValue(-1, "bb", -1) != 0) || (S1.Length != 8) || (!S1.IsEqual("bbaaaaaa"))) return TEnvironment::ShowTestErrorMessage(-1212, "TString::InsertValue");
	S1.SetValue("aaaaaa"); if ((S1.InsertValue(2, "bb", -1) != 2) || (S1.Length != 8) || (!S1.IsEqual("aabbaaaa"))) return TEnvironment::ShowTestErrorMessage(-1213, "TString::InsertValue");
	S1.SetValue("aaaaaa"); if ((S1.InsertValue(2, (INT32)-12) != 2) || (S1.Length != 9) || (!S1.IsEqual("aa-12aaaa"))) return TEnvironment::ShowTestErrorMessage(-1214, "TString::InsertValue");
	S1.SetValue("aaaaaa"); if ((S1.InsertChars(3, 'b', 4) != 3) || (S1.Length != 10) || (!S1.IsEqual("aaabbbbaaa"))) return TEnvironment::ShowTestErrorMessage(-1215, "TString::InsertValue");

	PCHAR_FREE(P1);
	PCHAR_FREE(P2);
	return true; // All tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TList
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TList(void) {

	TList L1(1), L2(1);
	INT64 R;

	R = L1.Add((UINT64)1); if ((R != 0) || (L1.Count() != 1) || (L1.ItemAsUINT64(0) != 1)) return TEnvironment::ShowTestErrorMessage(-2001, "TList::Add");
	R = L1.Add((UINT64)2); if ((R != 1) || (L1.Count() != 2) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 2)) return TEnvironment::ShowTestErrorMessage(-2002, "TList::Add");
	R = L1.Add((UINT64)3); if ((R != 2) || (L1.Count() != 3) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 2) || (L1.ItemAsUINT64(2) != 3)) return TEnvironment::ShowTestErrorMessage(-2003, "TList::Add");
	R = L1.Insert(0, (UINT64)4); if ((R != 0) || (L1.Count() != 4) || (L1.ItemAsUINT64(0) != 4) || (L1.ItemAsUINT64(1) != 1) || (L1.ItemAsUINT64(2) != 2) || (L1.ItemAsUINT64(3) != 3)) return TEnvironment::ShowTestErrorMessage(-2004, "TList::Add");
	R = L1.Insert(1, (UINT64)5); if ((R != 1) || (L1.Count() != 5) || (L1.ItemAsUINT64(0) != 4) || (L1.ItemAsUINT64(1) != 5) || (L1.ItemAsUINT64(2) != 1) || (L1.ItemAsUINT64(3) != 2) || (L1.ItemAsUINT64(4) != 3)) return TEnvironment::ShowTestErrorMessage(-2005, "TList::Add");
	L1.SetCount(4); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 4) || (L1.ItemAsUINT64(1) != 5) || (L1.ItemAsUINT64(2) != 1) || (L1.ItemAsUINT64(3) != 2)) return TEnvironment::ShowTestErrorMessage(-2006, "TList::SetCount");
	L1.Delete(3); if ((L1.Count() != 3) || (L1.ItemAsUINT64(0) != 4) || (L1.ItemAsUINT64(1) != 5) || (L1.ItemAsUINT64(2) != 1)) return TEnvironment::ShowTestErrorMessage(-2007, "TList::Delete");
	L1.Delete(0); if ((L1.Count() != 2) || (L1.ItemAsUINT64(0) != 5) || (L1.ItemAsUINT64(1) != 1)) return TEnvironment::ShowTestErrorMessage(-2008, "TList::Delete");
	L1.Delete(0); if ((L1.Count() != 1) || (L1.ItemAsUINT64(0) != 1)) return TEnvironment::ShowTestErrorMessage(-2009, "TList::Delete");
	L1.Delete(0); if (L1.Count() != 0) return TEnvironment::ShowTestErrorMessage(-2010, "TList::Delete");

	L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);
	L1.DeleteRange(0, 2); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 3) || (L1.ItemAsUINT64(1) != 4) || (L1.ItemAsUINT64(2) != 5) || (L1.ItemAsUINT64(3) != 6)) return TEnvironment::ShowTestErrorMessage(-2011, "TList::DeleteRange");
	L1.DeleteRange(1, 2); if ((L1.Count() != 2) || (L1.ItemAsUINT64(0) != 3) || (L1.ItemAsUINT64(1) != 6)) return TEnvironment::ShowTestErrorMessage(-2012, "TList::DeleteRange");
	L1.DeleteRange(0, 2); if (L1.Count() != 0) return TEnvironment::ShowTestErrorMessage(-2013, "TList::DeleteRange");

	L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);
	L2.Add((UINT64)11); L2.Add((UINT64)12);
	R = L1.AddList(&L2); if ((R != 6) || (L1.Count() != 8) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 2) || (L1.ItemAsUINT64(2) != 3) || (L1.ItemAsUINT64(3) != 4) || (L1.ItemAsUINT64(4) != 5) || (L1.ItemAsUINT64(5) != 6) || (L1.ItemAsUINT64(6) != 11) || (L1.ItemAsUINT64(7) != 12)) return TEnvironment::ShowTestErrorMessage(-2014, "TList::AddList");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);
	R = L1.InsertList(1, &L2); if ((R != 1) || (L1.Count() != 8) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 11) || (L1.ItemAsUINT64(2) != 12) || (L1.ItemAsUINT64(3) != 2) || (L1.ItemAsUINT64(4) != 3) || (L1.ItemAsUINT64(5) != 4) || (L1.ItemAsUINT64(6) != 5) || (L1.ItemAsUINT64(7) != 6)) return TEnvironment::ShowTestErrorMessage(-2015, "TList::InsertList");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);

	L1.DeleteValue((PVOID)6, 1); if ((L1.Count() != 5) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 2) || (L1.ItemAsUINT64(2) != 3) || (L1.ItemAsUINT64(3) != 4) || (L1.ItemAsUINT64(4) != 5)) return TEnvironment::ShowTestErrorMessage(-2016, "TList::DeleteValue");
	L1.DeleteValue((PVOID)1, 1); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 2) || (L1.ItemAsUINT64(1) != 3) || (L1.ItemAsUINT64(2) != 4) || (L1.ItemAsUINT64(3) != 5)) return TEnvironment::ShowTestErrorMessage(-2017, "TList::DeleteValue");
	L1.DeleteValue((PVOID)10, 1); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 2) || (L1.ItemAsUINT64(1) != 3) || (L1.ItemAsUINT64(2) != 4) || (L1.ItemAsUINT64(3) != 5)) return TEnvironment::ShowTestErrorMessage(-2018, "TList::DeleteValue");

	L1.Clear();
	L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)1); L1.Add((UINT64)5); L1.Add((UINT64)1);
	L1.DeleteValue((PVOID)1, 0); if ((L1.Count() != 3) || (L1.ItemAsUINT64(0) != 2) || (L1.ItemAsUINT64(1) != 3) || (L1.ItemAsUINT64(2) != 5)) return TEnvironment::ShowTestErrorMessage(-2019, "TList::DeleteValue (all)");

	L1.Clear();
	L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)1); L1.Add((UINT64)5); L1.Add((UINT64)1);
	L1.DeleteValue((PVOID)1, 2); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 2) || (L1.ItemAsUINT64(1) != 3) || (L1.ItemAsUINT64(2) != 5) || (L1.ItemAsUINT64(3) != 1)) return TEnvironment::ShowTestErrorMessage(-2020, "TList::DeleteValue (all)");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)1);
	if (L1.Find((UINT64)1, 0, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-2021, "TList::Find");
	if (L1.Find((UINT64)1, 0, -1, 2) != 5) return TEnvironment::ShowTestErrorMessage(-2022, "TList::Find");
	if (L1.Find((UINT64)1, 0, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-2023, "TList::Find");
	if (L1.Find((UINT64)1, 1, -1, 1) != 5) return TEnvironment::ShowTestErrorMessage(-2024, "TList::Find");
	if (L1.Find((UINT64)1, 1, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-2025, "TList::Find");
	if (L1.Find((UINT64)6, 0, -1, -1) != -1) return TEnvironment::ShowTestErrorMessage(-2026, "TList::Find");
	if (L1.Find((UINT64)1, 0, 2, 2) != -1) return TEnvironment::ShowTestErrorMessage(-2027, "TList::Find");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)1);
	if (L1.ReverseFind((UINT64)1, -1, -1, 1) != 5) return TEnvironment::ShowTestErrorMessage(-2028, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, -1, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-2029, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, -1, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-2030, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, 4, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-2031, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, 4, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-2032, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)6, -1, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-2033, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, -1, 2, 2) != -1) return TEnvironment::ShowTestErrorMessage(-2034, "TList::ReverseFind");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2);
	L1.SetItem(0, (UINT64)3); if (L1.ItemAsUINT64(0) != 3) return TEnvironment::ShowTestErrorMessage(-2035, "TList::SetItem");
	L1.SetItem(0, (UINT64)4); if (L1.ItemAsUINT64(0) != 4) return TEnvironment::ShowTestErrorMessage(-2036, "TList::SetItem");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);
	L1.Sort([](PVOID iItem1, PVOID iItem2)->INT32 {
		UINT64 V1 = (UINT64)iItem1;
		UINT64 V2 = (UINT64)iItem2;
		if (V1 < V2) return 1;
		if (V1 > V2) return -1;
		return 0;
		});
	if ((L1.ItemAsUINT64(0) != 6) || (L1.ItemAsUINT64(1) != 5) || (L1.ItemAsUINT64(2) != 4) || (L1.ItemAsUINT64(3) != 3) || (L1.ItemAsUINT64(4) != 2) || (L1.ItemAsUINT64(5) != 1)) return TEnvironment::ShowTestErrorMessage(-2037, "TList::Sort");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)1); L1.Add((UINT64)1); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);
	R = L1.BinaryFindFirst((UINT64)1, [](PVOID iSearchValue, PVOID iItem)->INT32 {
		UINT64 V1 = (UINT64)iSearchValue;
		UINT64 V2 = (UINT64)iItem;
		if (V1 < V2) return -1;
		if (V1 > V2) return 1;
		return 0;
		});
	if (R != 0) return TEnvironment::ShowTestErrorMessage(-2038, "TList::BinaryFind");
	R = L1.BinaryFindFirst((UINT64)10, [](PVOID iSearchValue, PVOID iItem)->INT32 {
		UINT64 V1 = (UINT64)iSearchValue;
		UINT64 V2 = (UINT64)iItem;
		if (V1 < V2) return -1;
		if (V1 > V2) return 1;
		return 0;
		});
	if (R != -1) return TEnvironment::ShowTestErrorMessage(-2038, "TList::BinaryFind");
	R = L1.BinaryFindLast((UINT64)1, [](PVOID iSearchValue, PVOID iItem)->INT32 {
		UINT64 V1 = (UINT64)iSearchValue;
		UINT64 V2 = (UINT64)iItem;
		if (V1 < V2) return -1;
		if (V1 > V2) return 1;
		return 0;
		});
	if (R != 2) return TEnvironment::ShowTestErrorMessage(-2039, "TList::BinaryFindLast");
	R = L1.BinaryFindLast((UINT64)10, [](PVOID iSearchValue, PVOID iItem)->INT32 {
		UINT64 V1 = (UINT64)iSearchValue;
		UINT64 V2 = (UINT64)iItem;
		if (V1 < V2) return -1;
		if (V1 > V2) return 1;
		return 0;
		});
	if (R != -1) return TEnvironment::ShowTestErrorMessage(-2040, "TList::BinaryFindLast");

	//PUINT64 Data = (PUINT64)MEMORY_ALLOC(128 * sizeof(UINT64));
	//PUINT64 Data1 = (PUINT64)MEMORY_ALLOC(128 * sizeof(UINT64));
	//if (Data == NULL) return false;
	//if (Data1 == NULL) return false;

	//for (INT64 i = 0; i < 128; i++) Data[i] = TEnvironment::GenerateRandomUINT64();

	//for (INT64 i = 2; i < 128; i++) {
	//	FNC_MEMCPY(Data1, Data, 128 * sizeof(UINT64));
	//	L1.SetCount(0);
	//	for (INT64 j = 0; j < i; j++) L1.Add(Data1[j]);
	//	qsort(Data1, i, sizeof(UINT64), [](CONST_PVOID i1, CONST_PVOID i2) -> INT32 {
	//		UINT64 u1 = *(PUINT64)i1;
	//		UINT64 u2 = *(PUINT64)i2;
	//		return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
	//		});
	//	L1.Sort([](PVOID iItem1, PVOID iItem2) -> INT32 {
	//		UINT64 u1 = (UINT64)iItem1;
	//		UINT64 u2 = (UINT64)iItem2;
	//		return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
	//		});
	//	for (INT64 j = 0; j < i; j++) {
	//		if (Data1[j] != (UINT64)L1.Item(j)) {
	//			INT32 a = 1;
	//			break;
	//			//return TEnvironment::ShowTestErrorMessage(-2041, "TList::Sort");
	//		}
	//	}
	//}

	//MEMORY_FREE(Data);
	//MEMORY_FREE(Data1);

	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TBytes
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TBytes(void) {

	TBytes B1, B2;

	PBYTE P1 = (PBYTE)MEMORY_ALLOC(1024);
	if (P1 == NULL) return TEnvironment::ShowTestErrorMessage(-3999, "TBytes::Memory allocation failed");
	
	B1.SetBytes('a', 1);
	if ((B1.Count != 1) || (B1.PByte()[0] != 'a')) return TEnvironment::ShowTestErrorMessage(-3001, "TBytes::SetBytes");

	for (INT64 i = 1; i <= 1024; i++) {
		TBytes::GenerateRandomBytes(P1, i); B1.SetValue(P1, i); if ((B1.Count != i) || (FNC_MEMCMP(B1.PByte(), P1, i) != 0)) return TEnvironment::ShowTestErrorMessage(-3002, "TBytes::SetValue");
	}

	TBytes::GenerateRandomBytes(P1, 512); B1.SetValue(P1, 256); B1.AppendBytes(P1 + 256, 256);
	if ((B1.Count != 512) || (FNC_MEMCMP(B1.PByte(), P1, 512) != 0)) return TEnvironment::ShowTestErrorMessage(-3003, "TBytes::AppendBytes");

	TBytes::GenerateRandomBytes(P1, 512); B1.SetValue(P1 + 256, 256); B1.InsertBytes(0, P1, 256);
	if ((B1.Count != 512) || (FNC_MEMCMP(B1.PByte(), P1, 512) != 0)) return TEnvironment::ShowTestErrorMessage(-3004, "TBytes::InsertBytes");

	B1.SetCount(0); if (B1.Compare((PBYTE)"ab", 0, -1) >= 0) return TEnvironment::ShowTestErrorMessage(-3005, "TBytes::Compare");
	B1.SetCount(0); if (B1.Compare((PBYTE)"ab", 0, 0) != 0) return TEnvironment::ShowTestErrorMessage(-3006, "TBytes::Compare");
	B1.SetValue((CONST_PBYTE)"abcd", 4); if (B1.Compare((PBYTE)"ab", 0, 0) <= 0) return TEnvironment::ShowTestErrorMessage(-3007, "TBytes::Compare");
	B1.SetValue((CONST_PBYTE)"abcd", 4); if (B1.Compare((PBYTE)"ab", 0, 1) != 0) return TEnvironment::ShowTestErrorMessage(-3008, "TBytes::Compare");
	B1.SetValue((CONST_PBYTE)"abcd", 4); if (B1.Compare((PBYTE)"ab", 0, 2) != 0) return TEnvironment::ShowTestErrorMessage(-3009, "TBytes::Compare");
	B1.SetValue((CONST_PBYTE)"abcd", 4); if (B1.Compare((PBYTE)"ab", 1, 2) <= 0) return TEnvironment::ShowTestErrorMessage(-3010, "TBytes::Compare");

	for (INT64 i = 1; i < 1024; i++) {
		TBytes::GenerateRandomBytes(P1, 1024);
		B1.SetValue(P1, i);
		INT32 R = FNC_MEMCMP(B1.PByte(), P1, i); if (R != 0) R = R < 0 ? -1 : 1;
		INT32 R1 = B1.Compare(P1, 0, -1); if (R1 != 0) R1 = R1 < 0 ? -1 : 1;
		if (R != R1) return TEnvironment::ShowTestErrorMessage(-3011, "TBytes::Compare (%lld)", i);
	}

	MEMORY_FREE(P1);
	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TDateTime
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TDateTime(void) {

	DATETIME_COMPONENTS DC, DC2;

	TString S1;
	TDateTime DT1; TDateTime DT2;

	PCHAR P1 = PCHAR_ALLOC(1024);
	if (P1 == NULL) return TEnvironment::ShowTestErrorMessage(-4999, "TDateTime::Memory allocation failed");

	DC.Year = 2024; DC.Month = 2; DC.Day = 28; DC.Hour = 23; DC.Minute = 59; DC.Second = 59; DC.Millisecond = 999;
	DATETIME D1 = TDateTime::ComponentsToDATETIME(&DC);
	if (D1 == DATETIME_EMPTY) return TEnvironment::ShowTestErrorMessage(-4001, "TDateTime::ComponentsToDATETIME / TDateTime::IsValidDATETIME");
	if (!TDateTime::DATETIMEToComponents(D1, &DC2)) return TEnvironment::ShowTestErrorMessage(-4002, "TDateTime::ComponentsToDATETIME / TDateTime::IsValidDATETIME");
	if ((DC2.Year != DC.Year) || (DC2.Month != DC.Month) || (DC2.Day != DC.Day) || (DC2.Hour != DC.Hour) || (DC2.Minute != DC.Minute) || (DC2.Second != DC.Second) || (DC2.Millisecond != DC.Millisecond)) return TEnvironment::ShowTestErrorMessage(-4003, "TDateTime::ComponentsToDATETIME / TDateTime::DATETIMEToComponents");

	DT1.SetValue(2005, 2, 3, 0, 1, 2); 
	DT1.FormatDateTime(&S1, "%d.%M.%y"); if (!S1.IsEqual("3.2.05")) return TEnvironment::ShowTestErrorMessage(-4004, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%d.%M.%yy"); if (!S1.IsEqual("3.2.2005")) return TEnvironment::ShowTestErrorMessage(-4005, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%d.%MM.%yy"); if (!S1.IsEqual("3.02.2005")) return TEnvironment::ShowTestErrorMessage(-4006, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy"); if (!S1.IsEqual("03.02.2005")) return TEnvironment::ShowTestErrorMessage(-4007, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy %H:%m:%s"); if (!S1.IsEqual("03.02.2005 0:1:2")) return TEnvironment::ShowTestErrorMessage(-4009, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy %HH:%m:%s"); if (!S1.IsEqual("03.02.2005 00:1:2")) return TEnvironment::ShowTestErrorMessage(-4010, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy %HH:%mm:%s"); if (!S1.IsEqual("03.02.2005 00:01:2")) return TEnvironment::ShowTestErrorMessage(-4011, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy %HH:%mm:%ss"); if (!S1.IsEqual("03.02.2005 00:01:02")) return TEnvironment::ShowTestErrorMessage(-4012, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy %h:%mm:%ss %t"); if (!S1.IsEqual("03.02.2005 12:01:02 AM")) return TEnvironment::ShowTestErrorMessage(-4013, "TDateTime::FormatDateToString");
	DT1.SetValue(2005, 2, 3, 13, 1, 2);
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy %h:%mm:%ss %t"); if (!S1.IsEqual("03.02.2005 1:01:02 PM")) return TEnvironment::ShowTestErrorMessage(-4014, "TDateTime::FormatDateToString");
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy %hh:%mm:%ss %t"); if (!S1.IsEqual("03.02.2005 01:01:02 PM")) return TEnvironment::ShowTestErrorMessage(-4015, "TDateTime::FormatDateToString");
	DT1.SetValue(2005, 2, 3, 1, 1, 2);
	DT1.FormatDateTime(&S1, "%dd.%MM.%yy %hh:%mm:%ss %t"); if (!S1.IsEqual("03.02.2005 01:01:02 AM")) return TEnvironment::ShowTestErrorMessage(-4016, "TDateTime::FormatDateToString");

	FNC_STRCPY(P1, "31.12.2005 23:59:59");  DT1.SetValue(TDateTime::ParseDateTime(P1, "%d.%M.%y %H:%m:%s")); if (!DT1.IsEqual(2005, 12, 31, 23, 59, 59)) return TEnvironment::ShowTestErrorMessage(-4018, "TDateTime::ParseDateTime");
	FNC_STRCPY(P1, "31.11.2005 23:59:59");  DT1.SetValue(TDateTime::ParseDateTime(P1, "%d.%M.%y %H:%m:%s")); if (DT1.IsValid()) return TEnvironment::ShowTestErrorMessage(-4019, "TDateTime::ParseDateTime");
	FNC_STRCPY(P1, "31.12.2005 23:59:59");  DT1.SetValue(TDateTime::ParseDateTime(P1, "%d.%M.%y %h:%m:%s")); if (DT1.IsValid()) return TEnvironment::ShowTestErrorMessage(-4020, "TDateTime::ParseDateTime");
	FNC_STRCPY(P1, "31.12.2005 12:59:59");  DT1.SetValue(TDateTime::ParseDateTime(P1, "%d.%M.%y %h:%m:%s")); if (!DT1.IsEqual(2005, 12, 31, 0, 59, 59)) return TEnvironment::ShowTestErrorMessage(-4021, "TDateTime::ParseDateTime");
	FNC_STRCPY(P1, "31.12.2005 12:59:59 X");  DT1.SetValue(TDateTime::ParseDateTime(P1, "%d.%M.%y %h:%m:%s %t")); if (DT1.IsValid()) return TEnvironment::ShowTestErrorMessage(-4022, "TDateTime::ParseDateTime");
	FNC_STRCPY(P1, "31.12.2005 12:59:59 AM");  DT1.SetValue(TDateTime::ParseDateTime(P1, "%d.%M.%y %h:%m:%s %t")); if (!DT1.IsEqual(2005, 12, 31, 0, 59, 59)) return TEnvironment::ShowTestErrorMessage(-4023, "TDateTime::ParseDateTime");
	FNC_STRCPY(P1, "31.12.2005 12:59:59 pM");  DT1.SetValue(TDateTime::ParseDateTime(P1, "%d.%M.%y %h:%m:%s %t")); if (!DT1.IsEqual(2005, 12, 31, 12, 59, 59)) return TEnvironment::ShowTestErrorMessage(-4024, "TDateTime::ParseDateTime");

	DT1.FormatDateTime(&S1, NULL); if (!S1.IsEmpty()) return TEnvironment::ShowTestErrorMessage(-4025, "TDateTime::FormatDateTime");

	DT1.SetValue(2024, 2, 28, 23, 59, 59);
	if (DT1.GetMillisecond() != 0) return TEnvironment::ShowTestErrorMessage(-4026, "TDateTime::GetMillisecond");
	if (DT1.GetSecond() != 59) return TEnvironment::ShowTestErrorMessage(-4027, "TDateTime::GetSecond");
	if (DT1.GetMinute() != 59) return TEnvironment::ShowTestErrorMessage(-4028, "TDateTime::GetMinute");
	if (DT1.GetHour() != 23) return TEnvironment::ShowTestErrorMessage(-4029, "TDateTime::GetHour");
	if (DT1.GetDay() != 28) return TEnvironment::ShowTestErrorMessage(-4030, "TDateTime::GetDay");
	if (DT1.GetMonth() != 2) return TEnvironment::ShowTestErrorMessage(-4031, "TDateTime::GetMonth");
	if (DT1.GetYear() != 2024) return TEnvironment::ShowTestErrorMessage(-4032, "TDateTime::GetYear");

	DT1.AddMilliseconds(25); if ((DT1.GetMillisecond() != 25) || (!DT1.IsEqual(2024, 2, 28, 23, 59, 59))) return TEnvironment::ShowTestErrorMessage(-4033, "TDateTime::AddMilliseconds");
	DT1.AddMilliseconds(-50); if ((DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 2, 28, 23, 59, 58))) return TEnvironment::ShowTestErrorMessage(-4034, "TDateTime::AddMilliseconds");
	DT1.AddSeconds(25); if ((DT1.GetSecond() != 23) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 2, 29, 0, 0, 23))) return TEnvironment::ShowTestErrorMessage(-4035, "TDateTime::AddSeconds");
	DT1.AddSeconds(-125); if ((DT1.GetSecond() != 18) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 2, 28, 23, 58, 18))) return TEnvironment::ShowTestErrorMessage(-4036, "TDateTime::AddSeconds");
	DT1.AddMinutes(70); if ((DT1.GetMinute() != 8) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 2, 29, 1, 8, 18))) return TEnvironment::ShowTestErrorMessage(-4037, "TDateTime::AddMinutes");
	DT1.AddMinutes(-100); if ((DT1.GetMinute() != 28) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 2, 28, 23, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4038, "TDateTime::AddMinutes");
	DT1.AddHours(50); if ((DT1.GetHour() != 1) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 3, 2, 1, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4039, "TDateTime::AddHours");
	DT1.AddHours(-90); if ((DT1.GetHour() != 7) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 2, 27, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4040, "TDateTime::AddHours");
	DT1.AddDays(31); if ((DT1.GetDay() != 29) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 3, 29, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4041, "TDateTime::AddDays");
	DT1.AddDays(-44); if ((DT1.GetDay() != 14) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2024, 2, 14, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4042, "TDateTime::AddDays");
	DT1.AddMonths(51); if ((DT1.GetMonth() != 5) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2028, 5, 14, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4043, "TDateTime::AddMonths");
	DT1.AddDays(17); if ((DT1.GetDay() != 31) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2028, 5, 31, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4044, "TDateTime::AddDays");
	DT1.AddMonths(49); if ((DT1.GetMonth() != 7) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2032, 7, 1, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4045, "TDateTime::AddMonths");
	DT1.AddMonths(-33); if ((DT1.GetMonth() != 10) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2029, 10, 1, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4046, "TDateTime::AddMonths");
	DT1.AddYears(-33); if ((DT1.GetYear() != 1996) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(1996, 10, 1, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4046, "TDateTime::AddYears");
	DT1.AddYears(100); if ((DT1.GetYear() != 2096) || (DT1.GetMillisecond() != 975) || (!DT1.IsEqual(2096, 10, 1, 7, 28, 18))) return TEnvironment::ShowTestErrorMessage(-4047, "TDateTime::AddYears");
	DT1.AddYears(-3000); if (DT1.IsValid() || (DT1.GetYear() != -1)) return TEnvironment::ShowTestErrorMessage(-4048, "TDateTime::AddYears");

	DT1.SetValue(2004, 2, 29, 12, 11, 10, 112); DT2.SetValue(2005, 2, 11, 12, 44, 50, 777);
	DT1.AddValue(DT2); TDateTime::DATETIMEToComponents(DT1.GetValue(), &DC);
	if (!DT1.IsEqual(2039, 4, 12, 0, 56, 0, 889)) return TEnvironment::ShowTestErrorMessage(-4049, "TDateTime::AddValue");

	PCHAR_FREE(P1);
	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TParamsList
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TParamsList(void) {

	TString S1; 
	TDateTime DT1, DT2;
	TBytes B1, B2;

	TParamsList P1, P2, P3;

	P1.SetParam_INT32("Param1", -1234); if ((P1.Count() != 1) || (P1.GetParam_INT32("paraM1", 0) != -1234)) return TEnvironment::ShowTestErrorMessage(-5001, "TParamsList::SetParam / GetParam");
	P1.SetParam_INT32("Param1", -4234); if ((P1.Count() != 1) || (P1.GetParam_INT32("paraM1", 0) != -4234)) return TEnvironment::ShowTestErrorMessage(-5002, "TParamsList::SetParam / GetParam");
	P1.SetParam_UINT32("Param2", 1234); if ((P1.Count() != 2) || (P1.GetParam_UINT32("paraM2", 0) != 1234)) return TEnvironment::ShowTestErrorMessage(-5003, "TParamsList::SetParam / GetParam");
	P1.SetParam_UINT32("Param2", 4234); if ((P1.Count() != 2) || (P1.GetParam_UINT32("paraM2", 0) != 4234)) return TEnvironment::ShowTestErrorMessage(-5004, "TParamsList::SetParam / GetParam");
	P1.SetParam_INT64("Param3", -123456); if ((P1.Count() != 3) || (P1.GetParam_INT64("paraM3", 0) != -123456)) return TEnvironment::ShowTestErrorMessage(-5005, "TParamsList::SetParam / GetParam");
	P1.SetParam_INT64("Param3", -423456); if ((P1.Count() != 3) || (P1.GetParam_INT64("paraM3", 0) != -423456)) return TEnvironment::ShowTestErrorMessage(-5006, "TParamsList::SetParam / GetParam");
	P1.SetParam_UINT64("Param4", 123456); if ((P1.Count() != 4) || (P1.GetParam_UINT64("paraM4", 0) != 123456)) return TEnvironment::ShowTestErrorMessage(-5007, "TParamsList::SetParam / GetParam");
	P1.SetParam_UINT64("Param4", 423456); if ((P1.Count() != 4) || (P1.GetParam_UINT64("paraM4", 0) != 423456)) return TEnvironment::ShowTestErrorMessage(-5008, "TParamsList::SetParam / GetParam");
	P1.SetParam_DOUBLE("Param5", -1234.22); if ((P1.Count() != 5) || (P1.GetParam_DOUBLE("paraM5", 0) != -1234.22)) return TEnvironment::ShowTestErrorMessage(-5009, "TParamsList::SetParam / GetParam");
	P1.SetParam_DOUBLE("Param5", -4234.22); if ((P1.Count() != 5) || (P1.GetParam_DOUBLE("paraM5", 0) != -4234.22)) return TEnvironment::ShowTestErrorMessage(-5010, "TParamsList::SetParam / GetParam");
	P1.SetParam_BOOL("Param6", true); if ((P1.Count() != 6) || (P1.GetParam_BOOL("paraM6", false) != true)) return TEnvironment::ShowTestErrorMessage(-5011, "TParamsList::SetParam / GetParam");
	P1.SetParam_BOOL("Param6", false); if ((P1.Count() != 6) || (P1.GetParam_BOOL("paraM6", true) != false)) return TEnvironment::ShowTestErrorMessage(-5012, "TParamsList::SetParam / GetParam");
	DT1.SetValue(2025, 11, 11, 1, 1, 1); P1.SetParam_DATETIME("Param7", &DT1); P1.GetParam_DATETIME("paraM7", &DT2, DATETIME_EMPTY); if ((P1.Count() != 7) || (!DT2.IsEqual(2025, 11, 11, 1, 1, 1))) return TEnvironment::ShowTestErrorMessage(-5013, "TParamsList::SetParam / GetParam");
	DT1.SetValue(2025, 11, 12, 1, 1, 1); P1.SetParam_DATETIME("pAraM7", &DT1); P1.GetParam_DATETIME("paraM7", &DT2, DATETIME_EMPTY); if ((P1.Count() != 7) || (!DT2.IsEqual(2025, 11, 12, 1, 1, 1))) return TEnvironment::ShowTestErrorMessage(-5014, "TParamsList::SetParam / GetParam");
	P1.SetParam_STRING("Param8", "abcd"); P1.GetParam_STRING("paraM8", &S1, ""); if ((P1.Count() != 8) || (!S1.IsEqual("abcd"))) return TEnvironment::ShowTestErrorMessage(-5015, "TParamsList::SetParam / GetParam");
	P1.SetParam_STRING("Param8", "abcde"); P1.GetParam_STRING("paraM8", &S1, ""); if ((P1.Count() != 8) || (!S1.IsEqual("abcde"))) return TEnvironment::ShowTestErrorMessage(-5016, "TParamsList::SetParam / GetParam");
	B1.SetRandomBytes(12);
	P1.SetParam_BYTES("Param9", &B1); P1.GetParam_BYTES("paraM9", &B2); if ((P1.Count() != 9) || (B1.Compare(&B2) != 0)) return TEnvironment::ShowTestErrorMessage(-5017, "TParamsList::SetParam / GetParam");
	B1.SetRandomBytes(12);
	P1.SetParam_BYTES("Param9", &B1); P1.GetParam_BYTES("paraM9", &B2); if ((P1.Count() != 9) || (B1.Compare(&B2) != 0)) return TEnvironment::ShowTestErrorMessage(-5018, "TParamsList::SetParam / GetParam");

	P2.CreateCopy(&P1); if (P2.Count() != P1.Count()) return TEnvironment::ShowTestErrorMessage(-5019, "TParamList::CreateCopy");
	if (P2.GetParam_INT32("paraM1", 0) != -4234) return TEnvironment::ShowTestErrorMessage(-5020, "TParamList::CreateCopy");
	if (P2.GetParam_UINT32("paraM2", 0) != 4234) return TEnvironment::ShowTestErrorMessage(-5021, "TParamList::CreateCopy");
	if (P2.GetParam_INT64("paraM3", 0) != -423456) return TEnvironment::ShowTestErrorMessage(-5022, "TParamList::CreateCopy");
	if (P2.GetParam_UINT64("paraM4", 0) != 423456) return TEnvironment::ShowTestErrorMessage(-5023, "TParamList::CreateCopy");
	if (P2.GetParam_DOUBLE("paraM5", 0) != -4234.22) return TEnvironment::ShowTestErrorMessage(-5024, "TParamList::CreateCopy");
	if (P2.GetParam_BOOL("paraM6", true) != false) return TEnvironment::ShowTestErrorMessage(-5025, "TParamList::CreateCopy");
	DT2.SetValue(DATETIME_EMPTY); P2.GetParam_DATETIME("paraM7", &DT2, DATETIME_EMPTY); if (!DT2.IsEqual(2025, 11, 12, 1, 1, 1)) return TEnvironment::ShowTestErrorMessage(-5026, "TParamList::CreateCopy");
	S1.SetLength(0); P2.GetParam_STRING("paraM8", &S1, ""); if (!S1.IsEqual("abcde")) return TEnvironment::ShowTestErrorMessage(-5027, "TParamList::CreateCopy");
	B2.SetCount(0); P2.GetParam_BYTES("paraM9", &B2); if (B1.Compare(&B2) != 0) return TEnvironment::ShowTestErrorMessage(-5028, "TParamList::CreateCopy");

	if (!P2.IsEqual(&P1)) return TEnvironment::ShowTestErrorMessage(-5028, "TParamList::IsEqual");

	P1.SetParam_ParamsList("Param10", &P2); P1.GetParam_ParamsList("param10", &P3); if (!P2.IsEqual(&P3)) return TEnvironment::ShowTestErrorMessage(-5029, "TParamList::SetParam");

	P1.Serialize(&B1); P2.Clear(); P2.Deserialize(&B1); if (!P2.IsEqual(&P1)) return TEnvironment::ShowTestErrorMessage(-5030, "TParamList::Serialize / TParamList::Deserialize");

	if (!P1.ParamExists("param9")) return TEnvironment::ShowTestErrorMessage(-5031, "TParamList::ParamExists");
	if (P1.ParamExists("paramX")) return TEnvironment::ShowTestErrorMessage(-5032, "TParamList::ParamExists");

	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for streams
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_Streams(void) {

	TString S1, S2;
	TBytes B1, B2;
	TMemoryStream MS1;

	INT64 R;

	S1.SetValue("0123456789");
	R = MS1.Write(S1.PChar(), 10); if ((R != 10) || (MS1.GetSize() != 10) || (MS1.GetPosition() != 10)) return TEnvironment::ShowTestErrorMessage(-6001, "TMemoryStream::Write");
	S1.SetValue("9876543210");
	R = MS1.Write(S1.PChar(), 10); if ((R != 10) || (MS1.GetSize() != 20) || (MS1.GetPosition() != 20)) return TEnvironment::ShowTestErrorMessage(-6002, "TMemoryStream::Write");
	MS1.Rewind(); if (MS1.GetPosition() != 0) return TEnvironment::ShowTestErrorMessage(-6003, "TMemoryStream::Rewind");
	MS1.Seek(0, SO_BEGIN); if (MS1.GetPosition() != 0) return TEnvironment::ShowTestErrorMessage(-6004, "TMemoryStream::Seek");
	MS1.Seek(1, SO_CURRENT); if (MS1.GetPosition() != 1) return TEnvironment::ShowTestErrorMessage(-6005, "TMemoryStream::Seek");
	MS1.Seek(1, SO_END); if (MS1.GetPosition() != 20) return TEnvironment::ShowTestErrorMessage(-6006, "TMemoryStream::Seek");
	MS1.Seek(-1, SO_END); if (MS1.GetPosition() != 19) return TEnvironment::ShowTestErrorMessage(-6007, "TMemoryStream::Seek");

	MS1.Rewind(); B2.SetValue("0123456789", 10);
	R = MS1.Read(&B1, 0, 10); if ((R != 10) || (MS1.GetSize() != 20) || (MS1.GetPosition() != 10) || (B1.Compare(&B2) != 0)) return TEnvironment::ShowTestErrorMessage(-6008, "TMemoryStream::Read");
	B2.SetValue("9876543210", 10);
	R = MS1.Read(&B1, 0, 10); 
	if ((R != 10) || (MS1.GetSize() != 20) || (MS1.GetPosition() != 20) || (B1.Compare(&B2) != 0)) return TEnvironment::ShowTestErrorMessage(-6009, "TMemoryStream::Read");
	MS1.Seek(1, SO_BEGIN); B2.SetValue("1234567899", 10);
	R = MS1.Read(&B1, 0, 10); if ((R != 10) || (MS1.GetSize() != 20) || (MS1.GetPosition() != 11) || (B1.Compare(&B2) != 0)) return TEnvironment::ShowTestErrorMessage(-6010, "TMemoryStream::Read");
	B2.SetValue("876543210x", 10);
	R = MS1.Read(&B1, 0, 10); if ((R != 9) || (MS1.GetSize() != 20) || (MS1.GetPosition() != 20) || (B1.Compare(&B2, 0, 9) != 0)) return TEnvironment::ShowTestErrorMessage(-6011, "TMemoryStream::Read");

	MS1.Rewind(); B2.SetValue("01234567899876543210", 20);
	R = MS1.Read(&B1, 0, 100); if ((R != 20) || (MS1.GetSize() != 20) || (MS1.GetPosition() != 20) || (B1.Compare(&B2, 0, 20) != 0)) return TEnvironment::ShowTestErrorMessage(-6012, "TMemoryStream::Read");
	MS1.Seek(-1, SO_END);
	S1.SetValue("abcdefgh");
	R = MS1.Write(S1.PChar(), 8); if ((R != 8) || (MS1.GetSize() != 27) || (MS1.GetPosition() != 27)) return TEnvironment::ShowTestErrorMessage(-6013, "TMemoryStream::Write");
	MS1.Rewind(); B2.SetValue("0123456789987654321abcdefgh", 27);
	R = MS1.Read(&B1, 0, 100); if ((R != 27) || (MS1.GetSize() != 27) || (MS1.GetPosition() != 27) || (B1.Compare(&B2, 0, 27) != 0)) return TEnvironment::ShowTestErrorMessage(-6014, "TMemoryStream::Read");

	TBinaryWriter* BW = new TBinaryWriter(&MS1, true);
	TBinaryReader* BR = new TBinaryReader(&MS1, true);

	MS1.Release();

	for (UINT64 i = 0; i < 256; i++) {
		INT8 I8 = (INT8)i;
		if (!BW->WriteINT8(I8)) return TEnvironment::ShowTestErrorMessage(-6015, "TBinaryWriter::Write");
		UINT8 U8 = (UINT8)i;
		if (!BW->WriteUINT8(U8)) return TEnvironment::ShowTestErrorMessage(-6016, "TBinaryWriter::Write");
		INT16 I16 = (INT16)(i + 0x7f00);
		if (!BW->WriteINT16(I16)) return TEnvironment::ShowTestErrorMessage(-6017, "TBinaryWriter::Write");
		UINT16 U16 = (UINT16)(i + 0x7f00);
		if (!BW->WriteUINT16(U16)) return TEnvironment::ShowTestErrorMessage(-6018, "TBinaryWriter::Write");
		INT32 I32 = (INT32)(i + 0x7fffff00);
		if (!BW->WriteINT32(I32)) return TEnvironment::ShowTestErrorMessage(-6019, "TBinaryWriter::Write");
		UINT32 U32 = (UINT32)(i + 0x7fffff00);
		if (!BW->WriteUINT32(U32)) return TEnvironment::ShowTestErrorMessage(-6020, "TBinaryWriter::Write");
		INT64 I64 = (INT64)(i + 0x4fffffffffffff00);
		if (!BW->WriteINT64(I64)) return TEnvironment::ShowTestErrorMessage(-6021, "TBinaryWriter::Write");
		UINT64 U64 = (UINT64)(i + 0x7fffffffffffff00);
		if (!BW->WriteUINT64(U64)) return TEnvironment::ShowTestErrorMessage(-6022, "TBinaryWriter::Write");
		FLOAT F = (FLOAT)(i + 0.334);
		if (!BW->WriteFLOAT(F)) return TEnvironment::ShowTestErrorMessage(-6023, "TBinaryWriter::Write");
		DOUBLE D = (DOUBLE)(i + 0.467);
		if (!BW->WriteDOUBLE(D)) return TEnvironment::ShowTestErrorMessage(-6024, "TBinaryWriter::Write");
		BOOL B = (i % 1) != 0;
		if (!BW->WriteBOOL(B)) return TEnvironment::ShowTestErrorMessage(-6025, "TBinaryWriter::Write");
		TDateTime DT; DT.SetValue(2004, 2, 2, 1, 2, 3); DT.AddDays((INT32)i);
		if (!BW->WriteDATETIME(DT.GetValue())) return TEnvironment::ShowTestErrorMessage(-6026, "TBinaryWriter::Write");
		DT.AddMonths((INT32)i);
		if (!BW->WriteDATETIME(&DT)) return TEnvironment::ShowTestErrorMessage(-6027, "TBinaryWriter::Write");
		S1.SetValue(i);
		if (!BW->WriteSTRING(&S1)) return TEnvironment::ShowTestErrorMessage(-6028, "TBinaryWriter::Write");
		S1.AppendValue(i); B1.SetCount(0); B1.SetValue(S1.PChar(), S1.Length);
		if (!BW->WriteBYTES(&B1)) return TEnvironment::ShowTestErrorMessage(-6029, "TBinaryWriter::Write");
	}
	MS1.Rewind();
	for (UINT64 i = 0; i < 256; i++) {
		INT8 I8;
		if ((!BR->ReadINT8(&I8)) || (I8 != (INT8)i)) return TEnvironment::ShowTestErrorMessage(-6030, "TBinaryWriter::Read");
		UINT8 U8;
		if ((!BR->ReadUINT8(&U8)) || (U8 != (UINT8)i)) return TEnvironment::ShowTestErrorMessage(-6031, "TBinaryWriter::Read");
		INT16 I16;
		if ((!BR->ReadINT16(&I16)) || (I16 != (INT16)(i + 0x7f00))) return TEnvironment::ShowTestErrorMessage(-6032, "TBinaryWriter::Read");
		UINT16 U16;
		if ((!BR->ReadUINT16(&U16)) || (U16 != (UINT16)(i + 0x7f00))) return TEnvironment::ShowTestErrorMessage(-6033, "TBinaryWriter::Read");
		INT32 I32;
		if ((!BR->ReadINT32(&I32)) || (I32 != (INT32)(i + 0x7fffff00))) return TEnvironment::ShowTestErrorMessage(-6034, "TBinaryWriter::Read");
		UINT32 U32;
		if ((!BR->ReadUINT32(&U32)) || (U32 != (UINT32)(i + 0x7fffff00))) return TEnvironment::ShowTestErrorMessage(-6035, "TBinaryWriter::Read");
		INT64 I64;
		if ((!BR->ReadINT64(&I64)) || (I64 != (INT64)(i + 0x4fffffffffffff00))) return TEnvironment::ShowTestErrorMessage(-6036, "TBinaryWriter::Read");
		UINT64 U64;
		if ((!BR->ReadUINT64(&U64)) || (U64 != (UINT64)(i + 0x7fffffffffffff00))) return TEnvironment::ShowTestErrorMessage(-6037, "TBinaryWriter::Read");
		FLOAT F;
		if ((!BR->ReadFLOAT(&F)) || (F != (FLOAT)((i + 0.334)))) return TEnvironment::ShowTestErrorMessage(-6038, "TBinaryWriter::Read");
		DOUBLE D;
		if ((!BR->ReadDOUBLE(&D)) || (D != (DOUBLE)((i + 0.467)))) return TEnvironment::ShowTestErrorMessage(-6039, "TBinaryWriter::Read");
		BOOL B;
		if ((!BR->ReadBOOL(&B)) || (B != ((i % 1) != 0))) return TEnvironment::ShowTestErrorMessage(-6040, "TBinaryWriter::Read");

		TDateTime DT, DT2; DT.SetValue(2004, 2, 2, 1, 2, 3); DT.AddDays((INT32)i);
		DATETIME DD1;
		if ((!BR->ReadDATETIME(&DD1)) || (DD1 != DT.GetValue())) return TEnvironment::ShowTestErrorMessage(-6041, "TBinaryWriter::Read");
		DT.AddMonths((INT32)i);
		if ((!BR->ReadDATETIME(&DT2)) || (DT2.GetValue() != DT.GetValue())) return TEnvironment::ShowTestErrorMessage(-6042, "TBinaryWriter::Read");
		S1.SetValue(i);
		if ((!BR->ReadSTRING(&S2)) || (!S2.IsEqual(&S1))) return TEnvironment::ShowTestErrorMessage(-6043, "TBinaryWriter::Read");
		S1.AppendValue(i); B1.SetCount(0); B1.SetValue(S1.PChar(), S1.Length);
		if ((!BR->ReadBYTES(&B2)) || (B2.Compare(&B1) != 0)) return TEnvironment::ShowTestErrorMessage(-6044, "TBinaryWriter::Read");
	}

	MS1.Release(); MS1.Write("aaaaaaaaaa", 10);
	MS1.Rewind(); B1.SetBytes('b', 20); R = MS1.Read(&B1, 0, 20);
	if ((R != 10) || (B1.Count != 20) || (B1.Compare((PBYTE)"aaaaaaaaaabbbbbbbbbb", 0, 20) != 0)) return TEnvironment::ShowTestErrorMessage(-6045, "TMemoryStream::Read");
	MS1.Rewind(); B1.SetBytes('b', 20); R = MS1.Read(&B1, 2, 20);
	if ((R != 10) || (B1.Count != 20) || (B1.Compare((PBYTE)"bbaaaaaaaaaabbbbbbbb", 0, 20) != 0)) return TEnvironment::ShowTestErrorMessage(-6046, "TMemoryStream::Read");
	MS1.Rewind(); B1.SetBytes('b', 20); R = MS1.Read(&B1, 15, 20);
	if ((R != 10) || (B1.Count != 25) || (B1.Compare((PBYTE)"bbbbbbbbbbbbbbbaaaaaaaaaa", 0, 25) != 0)) return TEnvironment::ShowTestErrorMessage(-6047, "TMemoryStream::Read");
	MS1.Rewind(); B1.SetBytes('b', 20); R = MS1.Read(&B1, 100, 20);
	if ((R != 10) || (B1.Count != 30) || (B1.Compare((PBYTE)"bbbbbbbbbbbbbbbbbbbbaaaaaaaaaa", 0, 30) != 0)) return TEnvironment::ShowTestErrorMessage(-6048, "TMemoryStream::Read");

	delete BR;
	delete BW;
	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TStringList
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TStringList(void) {

	TStringList L1, L2;
	TString S1;

	INT64 R;

	R = L1.Add("string1"); if ((R != 0) || (L1.Count() != 1) || (!L1.Item(0)->IsEqual("string1"))) return TEnvironment::ShowTestErrorMessage(-6001, "TStringList::Add");
	S1.SetValue("string2"); R = L1.Add(&S1); if ((R != 1) || (L1.Count() != 2) || (!L1.Item(1)->IsEqual("string2"))) return TEnvironment::ShowTestErrorMessage(-6002, "TStringList::Add");
	if (L1.Item(2) != NULL) return TEnvironment::ShowTestErrorMessage(-6003, "TStringList::Item");
	R = L1.Add("string3"); if ((R != 2) || (L1.Count() != 3) || (!L1.Item(2)->IsEqual("string3"))) return TEnvironment::ShowTestErrorMessage(-6004, "TStringList::Add");
	R = L1.Insert(2, "string4"); if ((R != 2) || (L1.Count() != 4) || (!L1.Item(2)->IsEqual("string4")) || (!L1.Item(3)->IsEqual("string3"))) return TEnvironment::ShowTestErrorMessage(-6005, "TStringList::Insert");

	L1.Delete(0, 2); if ((L1.Count() != 2) || (!L1.Item(0)->IsEqual("string4")) || (!L1.Item(1)->IsEqual("string3"))) return TEnvironment::ShowTestErrorMessage(-6006, "TStringList::Delete");
	L1.Clear(); L1.Add("aaa1"); L1.Add("aaa2"); L1.Add("aaa3"); L1.Add("aaa2");  L1.DeleteValue("aaa2", false); 
	if ((L1.Count() != 3) || (!L1.Item(0)->IsEqual("aaa1")) || (!L1.Item(1)->IsEqual("aaa3")) || (!L1.Item(2)->IsEqual("aaa2"))) return TEnvironment::ShowTestErrorMessage(-6007, "TStringList::Delete");
	L1.Clear(); L1.Add("aaa1"); L1.Add("aaa2"); L1.Add("aaa3"); L1.Add("aaa2");  L1.DeleteValue("aaa2", true);
	if ((L1.Count() != 2) || (!L1.Item(0)->IsEqual("aaa1")) || (!L1.Item(1)->IsEqual("aaa3"))) return TEnvironment::ShowTestErrorMessage(-6008, "TStringList::Delete");

	L1.Clear(); L1.Add("a1"); L1.Add("a2"); L1.Add("a3"); L1.Add("a4");
	L2.CreateCopy(&L1);
	if (!L2.IsEqual(&L1)) return TEnvironment::ShowTestErrorMessage(-6008, "TStringList::CreateCopy / IsEqual");

	L1.Clear(); L1.Add("a1"); L1.Add("a2"); L1.Add("a3"); L1.Add("a4"); L1.Add("a1");
	if (L1.Find("a", 0, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-6009, "TStringList::Find");
	if (L1.Find("a1", 0, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-6010, "TStringList::Find");
	if (L1.Find("a1", 0, -1, 2) != 4) return TEnvironment::ShowTestErrorMessage(-6011, "TStringList::Find");
	if (L1.Find("a1", 0, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-6011, "TStringList::Find");
	if (L1.Find("a2", 0, -1, 1) != 1) return TEnvironment::ShowTestErrorMessage(-6012, "TStringList::Find");
	if (L1.Find("a3", 0, -1, 1) != 2) return TEnvironment::ShowTestErrorMessage(-6013, "TStringList::Find");
	if (L1.Find("a4", 0, -1, 1) != 3) return TEnvironment::ShowTestErrorMessage(-6014, "TStringList::Find");
	L1.Clear(); L1.Add("A1"); L1.Add("A2"); L1.Add("A3"); L1.Add("A4"); L1.Add("A1");
	if (L1.CaseFind("a", 0, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-6015, "TStringList::CaseFind");
	if (L1.CaseFind("a1", 0, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-6016, "TStringList::CaseFind");
	if (L1.CaseFind("a1", 0, -1, 2) != 4) return TEnvironment::ShowTestErrorMessage(-6017, "TStringList::CaseFind");
	if (L1.CaseFind("a1", 0, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-6018, "TStringList::CaseFind");
	if (L1.CaseFind("a2", 0, -1, 1) != 1) return TEnvironment::ShowTestErrorMessage(-6019, "TStringList::CaseFind");
	if (L1.CaseFind("a3", 0, -1, 1) != 2) return TEnvironment::ShowTestErrorMessage(-6020, "TStringList::CaseFind");
	if (L1.CaseFind("a4", 0, -1, 1) != 3) return TEnvironment::ShowTestErrorMessage(-6021, "TStringList::CaseFind");

	L1.Clear(); L1.Add("a1"); L1.Add("a2"); L1.Add("a3"); L1.Add("a4"); L1.Add("a1");
	S1.SetValue("a1");
	if (L1.ReverseFind("a", -1, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-6022, "TStringList::ReverseFind");
	if (L1.ReverseFind(&S1, -1, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-6023, "TStringList::ReverseFind");
	if (L1.ReverseFind(&S1, -1, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-6024, "TStringList::ReverseFind");
	if (L1.ReverseFind(&S1, -1, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-6025, "TStringList::ReverseFind");
	if (L1.ReverseFind(&S1, 3, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-6026, "TStringList::ReverseFind");
	if (L1.ReverseFind(&S1, 3, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-6027, "TStringList::ReverseFind");
	if (L1.ReverseFind(&S1, -1, 1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-6028, "TStringList::ReverseFind");
	if (L1.ReverseFind(&S1, -1, 1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-6029, "TStringList::ReverseFind");
	if (L1.ReverseFind("a2", -1, -1, 1) != 1) return TEnvironment::ShowTestErrorMessage(-6030, "TStringList::ReverseFind");
	if (L1.ReverseFind("a3", -1, -1, 1) != 2) return TEnvironment::ShowTestErrorMessage(-6031, "TStringList::ReverseFind");
	if (L1.ReverseFind("a4", -1, -1, 1) != 3) return TEnvironment::ShowTestErrorMessage(-6032, "TStringList::ReverseFind");
	L1.Clear(); L1.Add("A1"); L1.Add("A2"); L1.Add("A3"); L1.Add("A4"); L1.Add("A1");
	if (L1.ReverseCaseFind("a", -1, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-6033, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind(&S1, -1, -1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-6034, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind(&S1, -1, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-6035, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind(&S1, -1, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-6036, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind(&S1, 3, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-6037, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind(&S1, 3, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-6038, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind(&S1, -1, 1, 1) != 4) return TEnvironment::ShowTestErrorMessage(-6039, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind(&S1, -1, 1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-6040, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind("a2", -1, -1, 1) != 1) return TEnvironment::ShowTestErrorMessage(-6041, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind("a3", -1, -1, 1) != 2) return TEnvironment::ShowTestErrorMessage(-6042, "TStringList::ReverseCaseFind");
	if (L1.ReverseCaseFind("a4", -1, -1, 1) != 3) return TEnvironment::ShowTestErrorMessage(-6043, "TStringList::ReverseCaseFind");

	L1.Clear(); L1.Add("a1"); L1.Add("a3"); L1.Add("a4"); L1.Add("a2"); L1.Add("a1");
	L1.Sort(true);
	if ((!L1.Item(0)->IsEqual("a1")) || (!L1.Item(1)->IsEqual("a1")) || (!L1.Item(2)->IsEqual("a2")) || (!L1.Item(3)->IsEqual("a3")) || (!L1.Item(4)->IsEqual("a4"))) return TEnvironment::ShowTestErrorMessage(-6044, "TStringList::Sort");
	L1.Clear(); L1.Add("a1"); L1.Add("a3"); L1.Add("a4"); L1.Add("a2"); L1.Add("a1");
	L1.Sort(false);
	if ((!L1.Item(0)->IsEqual("a4")) || (!L1.Item(1)->IsEqual("a3")) || (!L1.Item(2)->IsEqual("a2")) || (!L1.Item(3)->IsEqual("a1")) || (!L1.Item(4)->IsEqual("a1"))) return TEnvironment::ShowTestErrorMessage(-6045, "TStringList::Sort");

	L1.Clear(); L1.Add("a1"); L1.Add("a3"); L1.Add("a4"); L1.Add("a2"); L1.Add("a1");
	L1.Sort(true);

	if (L1.BinaryFindFirst("a1") != 0) return TEnvironment::ShowTestErrorMessage(-6046, "TStringList::BinaryFindFirst");
	if (L1.BinaryFindLast("a1") != 1) return TEnvironment::ShowTestErrorMessage(-6047, "TStringList::BinaryFindLast");
	if (L1.BinaryFindFirst("a2") != 2) return TEnvironment::ShowTestErrorMessage(-6048, "TStringList::BinaryFindFirst");
	if (L1.BinaryFindFirst("a3") != 3) return TEnvironment::ShowTestErrorMessage(-6049, "TStringList::BinaryFindFirst");
	if (L1.BinaryFindFirst("a4") != 4) return TEnvironment::ShowTestErrorMessage(-6050, "TStringList::BinaryFindFirst");
	if (L1.BinaryFindLast("a2") != 2) return TEnvironment::ShowTestErrorMessage(-6051, "TStringList::BinaryFindLast");
	if (L1.BinaryFindLast("a3") != 3) return TEnvironment::ShowTestErrorMessage(-6052, "TStringList::BinaryFindLast");
	if (L1.BinaryFindLast("a4") != 4) return TEnvironment::ShowTestErrorMessage(-6053, "TStringList::BinaryFindLast");
	if (L1.BinaryFindFirst("aa") != -1) return TEnvironment::ShowTestErrorMessage(-6054, "TStringList::BinaryFindFirst");
	if (L1.BinaryFindLast("aa") != -1) return TEnvironment::ShowTestErrorMessage(-6055, "TStringList::BinaryFindLast");

	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TCommandLineParser
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TCommandLineParser(INT32 iArgc, PCHAR* iArgs) {

	TCommandLineParser P;
	BOOL B = true;

	P.ProcessCommandLine("p1 -p2=1 p3=\"aa\" P4=0", [](INT64 iParamIndex, TString* iParamName, TString* iParamValue, PVOID iUserData) {

		BOOL *BB = (PBOOL)iUserData;
		switch (iParamIndex) {
			case 0: {
				if (!iParamName->IsEqual("p1")) { *BB = false; return; };
				if (!iParamValue->IsEmpty()) { *BB = false; return; };
			} break;
			case 1: {
				if (!iParamName->IsEqual("-p2")) { *BB = false; return; };
				if (!iParamValue->IsEqual("1")) { *BB = false; return; };
			} break;
			case 2: {
				if (!iParamName->IsEqual("p3")) { *BB = false; return; };
				if (!iParamValue->IsEqual("aa")) { *BB = false; return; };
			} break;
			case 3: {
				if (!iParamName->IsEqual("P4")) { *BB = false; return; };
				if (!iParamValue->IsEqual("0")) { *BB = false; return; };
			} break;
		}
		}, (PVOID)&B);

	if (!B) return TEnvironment::ShowTestErrorMessage(-7001, "TCommandLineParser::ProcessCommandLine");

	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TFileSystem
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TFileSystem(void) {

	TString S1, Path, Name, NameOnly, Ext;
	INT32 R;

#ifdef WINDOWS_SYSTEM

	if (TFileSystem::IsValidPath("") != FILE_SYSTEM_ERROR_INVALID_ROOT) return TEnvironment::ShowTestErrorMessage(-8001, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("x") != FILE_SYSTEM_ERROR_INVALID_ROOT) return TEnvironment::ShowTestErrorMessage(-8002, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("x:") != FILE_SYSTEM_ERROR_INVALID_ROOT) return TEnvironment::ShowTestErrorMessage(-8003, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("1:\\") != FILE_SYSTEM_ERROR_INVALID_ROOT) return TEnvironment::ShowTestErrorMessage(-8004, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\") != 0) return TEnvironment::ShowTestErrorMessage(-8005, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\Windows") != 0) return TEnvironment::ShowTestErrorMessage(-8006, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\Windows\\\\") != FILE_SYSTEM_ERROR_FORBIDDEN_CHAR) return TEnvironment::ShowTestErrorMessage(-8007, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\Windows\\") != 0) return TEnvironment::ShowTestErrorMessage(-8008, "TFileSystem::IsValidPath");
	S1.SetValue("c:\\"); S1.AppendChars('a', MAX_PATH_LENGTH); if (TFileSystem::IsValidPath(&S1) != FILE_SYSTEM_ERROR_PATH_TOO_LONG) return TEnvironment::ShowTestErrorMessage(-8009, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\\\Windows") != FILE_SYSTEM_ERROR_FORBIDDEN_CHAR) return TEnvironment::ShowTestErrorMessage(-8010, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\Windows\\LPT1\\a.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8011, "TFileSystem::IsValidPath");

	S1.SetValue("C:\\"); R = TFileSystem::AppendPathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("C:\\"))) return TEnvironment::ShowTestErrorMessage(-8012, "TFileSystem::AppendPathSeparator");
	S1.SetValue("C:\\Windows"); R = TFileSystem::AppendPathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("C:\\Windows\\"))) return TEnvironment::ShowTestErrorMessage(-8013, "TFileSystem::AppendPathSeparator");
	S1.SetValue("C:\\Windows\\"); R = TFileSystem::AppendPathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("C:\\Windows\\"))) return TEnvironment::ShowTestErrorMessage(-8014, "TFileSystem::AppendPathSeparator");
	S1.SetValue("C:\\"); R = TFileSystem::RemovePathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("C:\\"))) return TEnvironment::ShowTestErrorMessage(-8015, "TFileSystem::RemovePathSeparator");
	S1.SetValue("C:\\Windows"); R = TFileSystem::RemovePathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("C:\\Windows"))) return TEnvironment::ShowTestErrorMessage(-8016, "TFileSystem::RemovePathSeparator");
	S1.SetValue("C:\\Windows\\"); R = TFileSystem::RemovePathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("C:\\Windows"))) return TEnvironment::ShowTestErrorMessage(-8017, "TFileSystem::RemovePathSeparator");

	S1.SetValue("c:\\"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("c:\\")) || (!Name.IsEqual("")) || (!NameOnly.IsEqual("")) || (!Ext.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-8018, "TFileSystem::ExtractPathParts");
	S1.SetValue("c:\\windows"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("c:\\")) || (!Name.IsEqual("windows")) || (!NameOnly.IsEqual("windows")) || (!Ext.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-8019, "TFileSystem::ExtractPathParts");
	S1.SetValue("c:\\windows\\"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("c:\\")) || (!Name.IsEqual("windows")) || (!NameOnly.IsEqual("windows")) || (!Ext.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-8020, "TFileSystem::ExtractPathParts");
	S1.SetValue("c:\\windows\\system"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("c:\\windows")) || (!Name.IsEqual("system")) || (!NameOnly.IsEqual("system")) || (!Ext.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-8021, "TFileSystem::ExtractPathParts");
	S1.SetValue("c:\\windows\\system\\a.txt"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("c:\\windows\\system")) || (!Name.IsEqual("a.txt")) || (!NameOnly.IsEqual("a")) || (!Ext.IsEqual("txt"))) return TEnvironment::ShowTestErrorMessage(-8022, "TFileSystem::ExtractPathParts");
	S1.SetValue("c:\\windows\\system\\a.txt\\"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("c:\\windows\\system")) || (!Name.IsEqual("a.txt")) || (!NameOnly.IsEqual("a")) || (!Ext.IsEqual("txt"))) return TEnvironment::ShowTestErrorMessage(-8023, "TFileSystem::ExtractPathParts");

	Path.SetLength(0); Name.SetLength(0); NameOnly.SetLength(0); Ext.SetLength(0);
	S1.SetValue("c:\\windows\\system\\a.txt"); R = TFileSystem::ExtractPathParts(&S1, &Path, NULL, NULL, NULL); if ((R != 0) || (!Path.IsEqual("c:\\windows\\system"))) return TEnvironment::ShowTestErrorMessage(-8024, "TFileSystem::ExtractPathParts");
	Path.SetLength(0); Name.SetLength(0); NameOnly.SetLength(0); Ext.SetLength(0);
	S1.SetValue("c:\\windows\\system\\a.txt"); R = TFileSystem::ExtractPathParts(&S1, NULL, &Name, NULL, NULL); if ((R != 0) || (!Name.IsEqual("a.txt"))) return TEnvironment::ShowTestErrorMessage(-8025, "TFileSystem::ExtractPathParts");
	Path.SetLength(0); Name.SetLength(0); NameOnly.SetLength(0); Ext.SetLength(0);
	S1.SetValue("c:\\windows\\system\\a.txt"); R = TFileSystem::ExtractPathParts(&S1, NULL, NULL, &NameOnly, NULL); if ((R != 0) || (!NameOnly.IsEqual("a"))) return TEnvironment::ShowTestErrorMessage(-8026, "TFileSystem::ExtractPathParts");
	Path.SetLength(0); Name.SetLength(0); NameOnly.SetLength(0); Ext.SetLength(0);
	S1.SetValue("c:\\windows\\system\\a.txt"); R = TFileSystem::ExtractPathParts(&S1, NULL, NULL, NULL, &Ext); if ((R != 0) || (!Ext.IsEqual("txt"))) return TEnvironment::ShowTestErrorMessage(-8028, "TFileSystem::ExtractPathParts");

	R = TFileSystem::DirectoryExists("c:\\"); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8029, "TFileSystem::DirectoryExists");
	R = TFileSystem::DirectoryExists("c:\\windows\\"); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8030, "TFileSystem::DirectoryExists");
	R = TFileSystem::DirectoryExists("c:\\windows2"); if (R != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-8031, "TFileSystem::DirectoryExists");
	R = TFileSystem::DirectoryExists("c:\\windows\\regedit.exe"); if (R != FILE_SYSTEM_ERROR_NOT_DIRECTORY) return TEnvironment::ShowTestErrorMessage(-8033, "TFileSystem::DirectoryExists");

	if (TFileSystem::IsValidRelativePath("") != FILE_SYSTEM_ERROR_EMPTY) return TEnvironment::ShowTestErrorMessage(-8034, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath(".") != FILE_SYSTEM_ERROR_CURRENT) return TEnvironment::ShowTestErrorMessage(-8035, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath(".\\") != FILE_SYSTEM_ERROR_CURRENT) return TEnvironment::ShowTestErrorMessage(-8036, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("..") != FILE_SYSTEM_ERROR_PARENT) return TEnvironment::ShowTestErrorMessage(-8037, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("..\\") != FILE_SYSTEM_ERROR_PARENT) return TEnvironment::ShowTestErrorMessage(-8038, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1") != 0) return TEnvironment::ShowTestErrorMessage(-8039, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1\\") != 0) return TEnvironment::ShowTestErrorMessage(-8040, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1\\test.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8041, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1\\PRN\\test.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8042, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath(".\\dir1\\test.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8043, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("..\\dir2\\test.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8044, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1\\\\test.txt") != FILE_SYSTEM_ERROR_FORBIDDEN_CHAR) return TEnvironment::ShowTestErrorMessage(-8045, "TFileSystem::IsValidRelativePath");

	R = TFileSystem::FileExists("c:\\"); if (R != FILE_SYSTEM_ERROR_NOT_FILE) return TEnvironment::ShowTestErrorMessage(-8045, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("c:\\windows\\"); if (R != FILE_SYSTEM_ERROR_NOT_FILE) return TEnvironment::ShowTestErrorMessage(-8047, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("c:\\windows2"); if (R != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-8048, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("c:\\windows\\regedit.exe"); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8049, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("c:\\windows\\regeditxxxxxxxxxxxxxxxxxxxxx.exe"); if (R != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-8050, "TFileSystem::FileExists");

	if (TFileSystem::IsValidPath("C:\\Windows\\..\\test") != 0) return TEnvironment::ShowTestErrorMessage(-8051, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\Windows\\.\\test") != 0) return TEnvironment::ShowTestErrorMessage(-8052, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\Windows\\..\\test") != 0) return TEnvironment::ShowTestErrorMessage(-8053, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\Windows\\...\\test") != FILE_SYSTEM_ERROR_FORBIDDEN_CHAR) return TEnvironment::ShowTestErrorMessage(-8054, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("C:\\Windows\\..\\test") != 0) return TEnvironment::ShowTestErrorMessage(-8055, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidRelativePath("dir1\\...\\test.txt") != FILE_SYSTEM_ERROR_FORBIDDEN_CHAR) return TEnvironment::ShowTestErrorMessage(-8056, "TFileSystem::IsValidRelativePath");

	S1.SetValue("c:\\.\\windows"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("c:\\windows"))) return TEnvironment::ShowTestErrorMessage(-8057, "TFileSystem::NormalizePath");
	S1.SetValue("c:\\..\\windows"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("c:\\windows"))) return TEnvironment::ShowTestErrorMessage(-8058, "TFileSystem::NormalizePath");
	S1.SetValue("c:\\..\\windows\\system\\..\\"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("c:\\windows"))) return TEnvironment::ShowTestErrorMessage(-8059, "TFileSystem::NormalizePath");
	S1.SetValue("c:\\..\\windows\\system\\..\\system32\\aaa"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("c:\\windows\\system32\\aaa"))) return TEnvironment::ShowTestErrorMessage(-8060, "TFileSystem::NormalizePath");
	S1.SetValue("C:\\Users\\NullInferno\\.\\Documents\\a.txt"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("C:\\Users\\NullInferno\\Documents\\a.txt"))) return TEnvironment::ShowTestErrorMessage(-8061, "TFileSystem::NormalizePath");
	S1.SetValue("C:\\Program Files\\MyApp\\..\\Data\\file"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("C:\\Program Files\\Data\\file"))) return TEnvironment::ShowTestErrorMessage(-8062, "TFileSystem::NormalizePath");
	S1.SetValue("D:\\Games\\Steam\\.\\..\\Origin\\game.exe"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("D:\\Games\\Origin\\game.exe"))) return TEnvironment::ShowTestErrorMessage(-8063, "TFileSystem::NormalizePath");
	S1.SetValue("C:\\Windows\\System32\\..\\Temp\\log.txt"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("C:\\Windows\\Temp\\log.txt"))) return TEnvironment::ShowTestErrorMessage(-8064, "TFileSystem::NormalizePath");
	S1.SetValue("E:\\Projects\\Code\\..\\..\\Docs\\readme.md"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("E:\\Docs\\readme.md"))) return TEnvironment::ShowTestErrorMessage(-8065, "TFileSystem::NormalizePath");
	S1.SetValue("c:\\"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("c:\\"))) return TEnvironment::ShowTestErrorMessage(-8066, "TFileSystem::NormalizePath");
	S1.SetValue("c:\\.\\"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("c:\\"))) return TEnvironment::ShowTestErrorMessage(-8067, "TFileSystem::NormalizePath");
	S1.SetValue("c:\\..\\"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("c:\\"))) return TEnvironment::ShowTestErrorMessage(-8068, "TFileSystem::NormalizePath");
	S1.SetValue("c:\\.\\.\\..\\"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("c:\\"))) return TEnvironment::ShowTestErrorMessage(-8069, "TFileSystem::NormalizePath");

	S1.SetValue("C:\\Users\\NullInferno\\Documents"); R = TFileSystem::AppendToPath(&S1, ".\\file.txt"); if ((R != 0) || (!S1.IsEqual("C:\\Users\\NullInferno\\Documents\\file.txt"))) return TEnvironment::ShowTestErrorMessage(-8070, "TFileSystem::AppendToPath");
	S1.SetValue("C:\\Users\\NullInferno\\Documents"); R = TFileSystem::AppendToPath(&S1, "..\\Pictures\\pic.jpg"); if ((R != 0) || (!S1.IsEqual("C:\\Users\\NullInferno\\Pictures\\pic.jpg"))) return TEnvironment::ShowTestErrorMessage(-8071, "TFileSystem::AppendToPath");
	S1.SetValue("C:\\Program Files\\MyApp\\Config"); R = TFileSystem::AppendToPath(&S1, "..\\..\\Data\\data.db"); if ((R != 0) || (!S1.IsEqual("C:\\Program Files\\Data\\data.db"))) return TEnvironment::ShowTestErrorMessage(-8072, "TFileSystem::AppendToPath");
	S1.SetValue("D:\\Games\\Steam\\bin"); R = TFileSystem::AppendToPath(&S1, "..\\Origin\\game.exe"); if ((R != 0) || (!S1.IsEqual("D:\\Games\\Steam\\Origin\\game.exe"))) return TEnvironment::ShowTestErrorMessage(-8073, "TFileSystem::AppendToPath");
	S1.SetValue("C:\\Windows\\System32"); R = TFileSystem::AppendToPath(&S1, "..\\Temp\\log.txt"); if ((R != 0) || (!S1.IsEqual("C:\\Windows\\Temp\\log.txt"))) return TEnvironment::ShowTestErrorMessage(-8074, "TFileSystem::AppendToPath");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::CreateDirectory(S1.PChar(), false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8075, "TFileSystem::CreateDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::CreateDirectory(S1.PChar(), false); if (R != FILE_SYSTEM_ERROR_DIRECTORY_EXISTS) return TEnvironment::ShowTestErrorMessage(-8076, "TFileSystem::CreateDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2\\tttt");
	R = TFileSystem::CreateDirectory(S1.PChar(), false); if (R != FILE_SYSTEM_ERROR_PATH_NOT_EXISTS) return TEnvironment::ShowTestErrorMessage(-8077, "TFileSystem::CreateDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2\\tttt");
	R = TFileSystem::CreateDirectory(S1.PChar(), true); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8078, "TFileSystem::CreateDirectory");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::IsDirectoryEmpty(S1.PChar()); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8079, "TFileSystem::IsDirectoryEmpty");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2");
	R = TFileSystem::IsDirectoryEmpty(S1.PChar()); if (R != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-8080, "TFileSystem::IsDirectoryEmpty");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false, false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8081, "TFileSystem::DeleteDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2\\tttt");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false, false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8082, "TFileSystem::DeleteDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false, false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8083, "TFileSystem::DeleteDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2\\tttt");
	R = TFileSystem::CreateDirectory(S1.PChar(), true); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8084, "TFileSystem::CreateDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2");
	R = TFileSystem::DeleteDirectory(S1.PChar(), true, false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8085, "TFileSystem::DeleteDirectory");

	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_READ_ONLY)) != FSA_READ_ONLY) return TEnvironment::ShowTestErrorMessage(-8086, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_HIDDEN)) != FSA_HIDDEN) return TEnvironment::ShowTestErrorMessage(-8087, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_SYSTEM)) != FSA_SYSTEM) return TEnvironment::ShowTestErrorMessage(-8088, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_DIRECTORY)) != FSA_DIRECTORY) return TEnvironment::ShowTestErrorMessage(-8089, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_ARCHIVE)) != FSA_ARCHIVE) return TEnvironment::ShowTestErrorMessage(-8090, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_DEVICE)) != FSA_DEVICE) return TEnvironment::ShowTestErrorMessage(-8091, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_NORMAL)) != FSA_NORMAL) return TEnvironment::ShowTestErrorMessage(-8092, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_TEMPORARY)) != FSA_TEMPORARY) return TEnvironment::ShowTestErrorMessage(-8093, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_SPARSE_FILE)) != FSA_SPARSE_FILE) return TEnvironment::ShowTestErrorMessage(-8094, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_REPARSE_POINT)) != FSA_REPARSE_POINT) return TEnvironment::ShowTestErrorMessage(-8095, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_COMPRESSED)) != FSA_COMPRESSED) return TEnvironment::ShowTestErrorMessage(-8096, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_OFFLINE)) != FSA_OFFLINE) return TEnvironment::ShowTestErrorMessage(-8097, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_NOT_CONTENT_INDEXED)) != FSA_NOT_CONTENT_INDEXED) return TEnvironment::ShowTestErrorMessage(-8098, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_ENCRYPTED)) != FSA_ENCRYPTED) return TEnvironment::ShowTestErrorMessage(-8099, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_INTEGRITY_STREAM)) != FSA_INTEGRITY_STREAM) return TEnvironment::ShowTestErrorMessage(-8100, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");
	if (WindowsAttaributes2FileSystemAttributes(FileSystemAttributes2WindowsAttaributes(FSA_NO_SCRUB_DATA)) != FSA_NO_SCRUB_DATA) return TEnvironment::ShowTestErrorMessage(-8101, "WindowsAttaributes2FileSystemAttributes and FileSystemAttributes2WindowsAttaributes");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_file.txt");
	FILE* F = fopen(S1.PChar(), "wb+"); if (F == NULL) return TEnvironment::ShowTestErrorMessage(-8102, "TFileSystem");
	fclose(F); if (TFileSystem::FileExists(S1.PChar()) != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8103, "TFileStream::FileExists");
	R = TFileSystem::DeleteFile(S1.PChar()); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8104, "TFileSystem::DeleteFile");

	TFileSystemAttributes A;
	R = TFileSystem::GetFileAttributes(S1.PChar(), &A); if (R != FILE_SYSTEM_ERROR_FILE_NOT_EXISTS) return TEnvironment::ShowTestErrorMessage(-8105, "TFileSystem::GetFileAttributes");

	F = fopen(S1.PChar(), "wb+"); fclose(F);
	R = TFileSystem::GetFileAttributes(S1.PChar(), &A); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8106, "TFileSystem::GetFileAttributes");
	R = TFileSystem::SetFileAttributes(S1.PChar(), (TFileSystemAttributes)(FSA_ARCHIVE | FSA_HIDDEN | FSA_READ_ONLY | FSA_SYSTEM)); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8107, "TFileSystem::SetFileAttributes");
	R = TFileSystem::GetFileAttributes(S1.PChar(), &A); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8108, "TFileSystem::GetFileAttributes");
	if (A != (TFileSystemAttributes)(FSA_ARCHIVE | FSA_HIDDEN | FSA_READ_ONLY | FSA_SYSTEM)) return TEnvironment::ShowTestErrorMessage(-8109, "TFileSystem::GetFileAttributes");
	R = TFileSystem::DeleteFile(S1.PChar()); if (R != FILE_SYSTEM_ERROR_ACCESS) return TEnvironment::ShowTestErrorMessage(-8110, "TFileSystem::DeleteFile");
	R = TFileSystem::DeleteFile(S1.PChar(), true); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8111, "TFileSystem::DeleteFile");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::CreateDirectory(S1.PChar(), false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8112, "TFileSystem::CreateDirectory");
	R = TFileSystem::GetFileAttributes(S1.PChar(), &A); if (R != FILE_SYSTEM_ERROR_FILE_NOT_EXISTS) return TEnvironment::ShowTestErrorMessage(-8113, "TFileSystem::GetFileAttributes");
	R = TFileSystem::GetDirectoryAttributes(S1.PChar(), &A); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8114, "TFileSystem::GetDirectoryAttributes");
	R = TFileSystem::SetDirectoryAttributes(S1.PChar(), (TFileSystemAttributes)(FSA_ARCHIVE | FSA_HIDDEN | FSA_READ_ONLY | FSA_SYSTEM)); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8115, "TFileSystem::SetDirectoryAttributes");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false, false); if (R != FILE_SYSTEM_ERROR_ACCESS) return TEnvironment::ShowTestErrorMessage(-8116, "TFileSystem::DeleteDirectory");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false, true); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8117, "TFileSystem::DeleteDirectory");

	R = TFileSystem::CreateFullPath(&S1, "c:\\windows", "test", "txt"); if ((R != 0) || (!S1.IsEqual("c:\\windows\\test.txt"))) return TEnvironment::ShowTestErrorMessage(-8119, "TFileSystem::CreateFullPath");

#else
	if (TFileSystem::IsValidPath("") != FILE_SYSTEM_ERROR_INVALID_ROOT) return TEnvironment::ShowTestErrorMessage(-8001, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("x") != FILE_SYSTEM_ERROR_INVALID_ROOT) return TEnvironment::ShowTestErrorMessage(-8002, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("/") != 0) return TEnvironment::ShowTestErrorMessage(-8003, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("//home") != FILE_SYSTEM_ERROR_FORBIDDEN_CHAR) return TEnvironment::ShowTestErrorMessage(-8004, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("/home") != 0) return TEnvironment::ShowTestErrorMessage(-8005, "TFileSystem::IsValidPath");
	if (TFileSystem::IsValidPath("/home/") != 0) return TEnvironment::ShowTestErrorMessage(-8006, "TFileSystem::IsValidPath");

	S1.SetValue("/"); R = TFileSystem::AppendPathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("/"))) return TEnvironment::ShowTestErrorMessage(-8007, "TFileSystem::AppendPathSeparator");
	S1.SetValue("/home"); TFileSystem::AppendPathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("/home/"))) return TEnvironment::ShowTestErrorMessage(-8008, "TFileSystem::AppendPathSeparator");
	S1.SetValue("/home/"); TFileSystem::AppendPathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("/home/"))) return TEnvironment::ShowTestErrorMessage(-8009, "TFileSystem::AppendPathSeparator");
	S1.SetValue("/"); TFileSystem::RemovePathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("/"))) return TEnvironment::ShowTestErrorMessage(-8010, "TFileSystem::RemovePathSeparator");
	S1.SetValue("/home"); TFileSystem::RemovePathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("/home"))) return TEnvironment::ShowTestErrorMessage(-8011, "TFileSystem::RemovePathSeparator");
	S1.SetValue("/home/"); TFileSystem::RemovePathSeparator(&S1); if ((R != 0) || (!S1.IsEqual("/home"))) return TEnvironment::ShowTestErrorMessage(-8012, "TFileSystem::RemovePathSeparator");

	S1.SetValue("/"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("/")) || (!Name.IsEqual("")) || (!NameOnly.IsEqual("")) || (!Ext.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-8013, "TFileSystem::ExtractPathParts");
	S1.SetValue("/home"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("/")) || (!Name.IsEqual("home")) || (!NameOnly.IsEqual("home")) || (!Ext.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-8014, "TFileSystem::ExtractPathParts");
	S1.SetValue("/home/"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("/")) || (!Name.IsEqual("home")) || (!NameOnly.IsEqual("home")) || (!Ext.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-8015, "TFileSystem::ExtractPathParts");
	S1.SetValue("/home/user"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("/home")) || (!Name.IsEqual("user")) || (!NameOnly.IsEqual("user")) || (!Ext.IsEqual(""))) return TEnvironment::ShowTestErrorMessage(-8016, "TFileSystem::ExtractPathParts");
	S1.SetValue("/home/user/a.txt"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); if ((R != 0) || (!Path.IsEqual("/home/user")) || (!Name.IsEqual("a.txt")) || (!NameOnly.IsEqual("a")) || (!Ext.IsEqual("txt"))) return TEnvironment::ShowTestErrorMessage(-8017, "TFileSystem::ExtractPathParts");
	S1.SetValue("/home/user/a.txt/"); R = TFileSystem::ExtractPathParts(&S1, &Path, &Name, &NameOnly, &Ext); 
	if ((R != 0) || (!Path.IsEqual("/home/user")) || (!Name.IsEqual("a.txt")) || (!NameOnly.IsEqual("a")) || (!Ext.IsEqual("txt"))) return TEnvironment::ShowTestErrorMessage(-8018, "TFileSystem::ExtractPathParts");

	Path.SetLength(0); Name.SetLength(0); NameOnly.SetLength(0); Ext.SetLength(0);
	S1.SetValue("/home/user/a.txt"); R = TFileSystem::ExtractPathParts(&S1, &Path, NULL, NULL, NULL); if ((R != 0) || (!Path.IsEqual("/home/user"))) return TEnvironment::ShowTestErrorMessage(-8019, "TFileSystem::ExtractPathParts");
	Path.SetLength(0); Name.SetLength(0); NameOnly.SetLength(0); Ext.SetLength(0);
	S1.SetValue("/home/user/a.txt"); R = TFileSystem::ExtractPathParts(&S1, NULL, &Name, NULL, NULL); if ((R != 0) || (!Name.IsEqual("a.txt"))) return TEnvironment::ShowTestErrorMessage(-8020, "TFileSystem::ExtractPathParts");
	Path.SetLength(0); Name.SetLength(0); NameOnly.SetLength(0); Ext.SetLength(0);
	S1.SetValue("/home/user/a.txt"); R = TFileSystem::ExtractPathParts(&S1, NULL, NULL, &NameOnly, NULL); if ((R != 0) || (!NameOnly.IsEqual("a"))) return TEnvironment::ShowTestErrorMessage(-8021, "TFileSystem::ExtractPathParts");
	Path.SetLength(0); Name.SetLength(0); NameOnly.SetLength(0); Ext.SetLength(0);
	S1.SetValue("/home/user/a.txt"); R = TFileSystem::ExtractPathParts(&S1, NULL, NULL, NULL, &Ext); if ((R != 0) || (!Ext.IsEqual("txt"))) return TEnvironment::ShowTestErrorMessage(-8022, "TFileSystem::ExtractPathParts");

	if (TFileSystem::IsValidRelativePath("") != FILE_SYSTEM_ERROR_EMPTY) return TEnvironment::ShowTestErrorMessage(-8023, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath(".") != FILE_SYSTEM_ERROR_CURRENT) return TEnvironment::ShowTestErrorMessage(-8024, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("./") != FILE_SYSTEM_ERROR_CURRENT) return TEnvironment::ShowTestErrorMessage(-8025, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("..") != FILE_SYSTEM_ERROR_PARENT) return TEnvironment::ShowTestErrorMessage(-8026, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("../") != FILE_SYSTEM_ERROR_PARENT) return TEnvironment::ShowTestErrorMessage(-8027, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1") != 0) return TEnvironment::ShowTestErrorMessage(-8028, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1/") != 0) return TEnvironment::ShowTestErrorMessage(-8029, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1/test.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8030, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1/PRN/test.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8031, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("./dir1/test.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8032, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("../dir2/test.txt") != 0) return TEnvironment::ShowTestErrorMessage(-8033, "TFileSystem::IsValidRelativePath");
	if (TFileSystem::IsValidRelativePath("dir1//test.txt") != FILE_SYSTEM_ERROR_FORBIDDEN_CHAR) return TEnvironment::ShowTestErrorMessage(-8034, "TFileSystem::IsValidRelativePath");

	R = TFileSystem::DirectoryExists("/"); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8035, "TFileSystem::DirectoryExists");
	R = TFileSystem::DirectoryExists("/home"); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8036, "TFileSystem::DirectoryExists");
	R = TFileSystem::DirectoryExists("/home/"); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8037, "TFileSystem::DirectoryExists");
	R = TFileSystem::DirectoryExists("/home2"); if (R != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-8038, "TFileSystem::DirectoryExists");
	R = TFileSystem::DirectoryExists("/etc/netconfig"); if (R != FILE_SYSTEM_ERROR_NOT_DIRECTORY) return TEnvironment::ShowTestErrorMessage(-8039, "TFileSystem::DirectoryExists");

	R = TFileSystem::FileExists("/"); if (R != FILE_SYSTEM_ERROR_NOT_FILE) return TEnvironment::ShowTestErrorMessage(-8040, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("/home"); if (R != FILE_SYSTEM_ERROR_NOT_FILE) return TEnvironment::ShowTestErrorMessage(-8041, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("/home/"); if (R != FILE_SYSTEM_ERROR_NOT_FILE) return TEnvironment::ShowTestErrorMessage(-8042, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("/home2"); if (R != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-8043, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("/etc/netconfig"); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8044, "TFileSystem::FileExists");
	R = TFileSystem::FileExists("/etc/netconfigasasasasassasasasa"); if (R != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-8045, "TFileSystem::FileExists");

	S1.SetValue("/"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/"))) return TEnvironment::ShowTestErrorMessage(-8046, "TFileSystem::NormalizePath");
	S1.SetValue("/./"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/"))) return TEnvironment::ShowTestErrorMessage(-8047, "TFileSystem::NormalizePath (%s)", S1.PChar());
	S1.SetValue("/../"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/"))) return TEnvironment::ShowTestErrorMessage(-8048, "TFileSystem::NormalizePath");
	S1.SetValue("/././../"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/"))) return TEnvironment::ShowTestErrorMessage(-8049, "TFileSystem::NormalizePath");

	S1.SetValue("/home/user/./docs/file.txt"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/home/user/docs/file.txt"))) return TEnvironment::ShowTestErrorMessage(-8050, "TFileSystem::NormalizePath");
	S1.SetValue("/home/user/projects/../docs/a"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/home/user/docs/a"))) return TEnvironment::ShowTestErrorMessage(-8051, "TFileSystem::NormalizePath");
	S1.SetValue("/etc/init.d/./../passwd"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/etc/passwd"))) return TEnvironment::ShowTestErrorMessage(-8052, "TFileSystem::NormalizePath");
	S1.SetValue("/var/log/../tmp/./cache"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/var/tmp/cache"))) return TEnvironment::ShowTestErrorMessage(-8053, "TFileSystem::NormalizePath");
	S1.SetValue("/usr/local/bin/../../lib/libc"); R = TFileSystem::NormalizePath(&S1); if ((R != 0) || (!S1.IsEqual("/usr/lib/libc"))) return TEnvironment::ShowTestErrorMessage(-8054, "TFileSystem::NormalizePath");

	S1.SetValue("/home/user/docs"); R = TFileSystem::AppendToPath(&S1, "./file.txt"); if ((R != 0) || (!S1.IsEqual("/home/user/docs/file.txt"))) return TEnvironment::ShowTestErrorMessage(-8055, "TFileSystem::AppendToPath");
	S1.SetValue("/home/user/docs"); R = TFileSystem::AppendToPath(&S1, "../images/pic.png"); if ((R != 0) || (!S1.IsEqual("/home/user/images/pic.png"))) return TEnvironment::ShowTestErrorMessage(-8056, "TFileSystem::AppendToPath");
	S1.SetValue("/etc/nginx/conf.d"); R = TFileSystem::AppendToPath(&S1, "../../passwd"); if ((R != 0) || (!S1.IsEqual("/etc/passwd"))) return TEnvironment::ShowTestErrorMessage(-8057, "TFileSystem::AppendToPath");
	S1.SetValue("/var/log"); R = TFileSystem::AppendToPath(&S1, "./../tmp/cache"); if ((R != 0) || (!S1.IsEqual("/var/tmp/cache"))) return TEnvironment::ShowTestErrorMessage(-8058, "TFileSystem::AppendToPath");
	S1.SetValue("/usr/local/bin"); R = TFileSystem::AppendToPath(&S1, "../lib/libc.so"); if ((R != 0) || (!S1.IsEqual("/usr/local/lib/libc.so"))) return TEnvironment::ShowTestErrorMessage(-8059, "TFileSystem::AppendToPath");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::CreateDirectory(S1.PChar(), false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8060, "TFileSystem::CreateDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2/ttt");
	R = TFileSystem::CreateDirectory(S1.PChar(), false); if (R != FILE_SYSTEM_ERROR_PATH_NOT_EXISTS) return TEnvironment::ShowTestErrorMessage(-8061, "TFileSystem::CreateDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2/tttt");
	R = TFileSystem::CreateDirectory(S1.PChar(), true); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8062, "TFileSystem::CreateDirectory");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::IsDirectoryEmpty(S1.PChar()); if (R != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8063, "TFileSystem::IsDirectoryEmpty");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2");
	R = TFileSystem::IsDirectoryEmpty(S1.PChar()); if (R != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-8064, "TFileSystem::IsDirectoryEmpty");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8065, "TFileSystem::DeleteDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2/tttt");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false, false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8066, "TFileSystem::DeleteDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false, false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8067, "TFileSystem::DeleteDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2/tttt");
	R = TFileSystem::CreateDirectory(S1.PChar(), true); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8068, "TFileSystem::CreateDirectory");
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir2");
	R = TFileSystem::DeleteDirectory(S1.PChar(), true, false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8069, "TFileSystem::DeleteDirectory");

	UINT32 Attr, Chmod, Ext2Attr;
	
	FileSystemAttributes2LinuxAttaributes(FSA_S_IRUSR, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IRUSR) return TEnvironment::ShowTestErrorMessage(-8070, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_IWUSR, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IWUSR) return TEnvironment::ShowTestErrorMessage(-8071, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_IXUSR, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IXUSR) return TEnvironment::ShowTestErrorMessage(-8072, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_IRGRP, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IRGRP) return TEnvironment::ShowTestErrorMessage(-8073, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_IWGRP, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IWGRP) return TEnvironment::ShowTestErrorMessage(-8074, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_IXGRP, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IXGRP) return TEnvironment::ShowTestErrorMessage(-8075, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_IROTH, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IROTH) return TEnvironment::ShowTestErrorMessage(-8076, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_IWOTH, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IWOTH) return TEnvironment::ShowTestErrorMessage(-8077, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_IXOTH, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_IXOTH) return TEnvironment::ShowTestErrorMessage(-8078, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_ISUID, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_ISUID) return TEnvironment::ShowTestErrorMessage(-8079, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_ISGID, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_ISGID) return TEnvironment::ShowTestErrorMessage(-8080, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");
	FileSystemAttributes2LinuxAttaributes(FSA_S_ISVTX, &Attr, &Chmod, &Ext2Attr); if (LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr) != FSA_S_ISVTX) return TEnvironment::ShowTestErrorMessage(-8081, "LinuxAttaributes2FileSystemAttributes and FileSystemAttributes2LinuxAttaributes");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_file.txt");
	FILE* F = fopen(S1.PChar(), "wb+"); if (F == NULL) return TEnvironment::ShowTestErrorMessage(-8082, "TFileSystem");
	fclose(F); if (TFileSystem::FileExists(S1.PChar()) != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-8083, "TFileStream::FileExists");
	R = TFileSystem::DeleteFile(S1.PChar()); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8084, "TFileSystem::DeleteFile");

	TFileSystemAttributes A;
	R = TFileSystem::GetFileAttributes(S1.PChar(), &A); if (R != FILE_SYSTEM_ERROR_FILE_NOT_EXISTS) return TEnvironment::ShowTestErrorMessage(-8085, "TFileSystem::GetFileAttributes");

	F = fopen(S1.PChar(), "wb+"); fclose(F);
	R = TFileSystem::GetFileAttributes(S1.PChar(), &A); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8086, "TFileSystem::GetFileAttributes");
	R = TFileSystem::SetFileAttributes(S1.PChar(), (TFileSystemAttributes)(FSA_S_IRUSR | FSA_S_IWUSR | FSA_S_IXUSR | FSA_S_IRGRP | FSA_S_IWGRP | FSA_S_IXGRP | FSA_S_IROTH | FSA_S_IWOTH | FSA_S_IXOTH | FSA_S_ISUID | FSA_S_ISGID | FSA_S_ISVTX)); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8087, "TFileSystem::SetFileAttributes");
	R = TFileSystem::GetFileAttributes(S1.PChar(), &A); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8088, "TFileSystem::GetFileAttributes");
	if (A != (TFileSystemAttributes)(FSA_S_IFREG | FSA_S_IRUSR | FSA_S_IWUSR | FSA_S_IXUSR | FSA_S_IRGRP | FSA_S_IWGRP | FSA_S_IXGRP | FSA_S_IROTH | FSA_S_IWOTH | FSA_S_IXOTH | FSA_S_ISUID | FSA_S_ISGID | FSA_S_ISVTX)) return TEnvironment::ShowTestErrorMessage(-8089, "TFileSystem::GetFileAttributes");
	R = TFileSystem::DeleteFile(S1.PChar(), false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8090, "TFileSystem::DeleteFile");

	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_dir");
	R = TFileSystem::CreateDirectory(S1.PChar(), false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8091, "TFileSystem::CreateDirectory");
	R = TFileSystem::GetDirectoryAttributes(S1.PChar(), &A); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8092, "TFileSystem::GetFileAttributes");
	R = TFileSystem::SetDirectoryAttributes(S1.PChar(), (TFileSystemAttributes)(FSA_S_IRUSR | FSA_S_IWUSR | FSA_S_IXUSR | FSA_S_IRGRP | FSA_S_IWGRP | FSA_S_IXGRP | FSA_S_IROTH | FSA_S_IWOTH | FSA_S_IXOTH | FSA_S_ISUID | FSA_S_ISGID | FSA_S_ISVTX)); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8093, "TFileSystem::SetFileAttributes");
	R = TFileSystem::GetDirectoryAttributes(S1.PChar(), &A); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8094, "TFileSystem::GetFileAttributes");
	if (A != (TFileSystemAttributes)(FSA_S_IFDIR | FSA_S_IRUSR | FSA_S_IWUSR | FSA_S_IXUSR | FSA_S_IRGRP | FSA_S_IWGRP | FSA_S_IXGRP | FSA_S_IROTH | FSA_S_IWOTH | FSA_S_IXOTH | FSA_S_ISUID | FSA_S_ISGID | FSA_S_ISVTX)) return TEnvironment::ShowTestErrorMessage(-8095, "TFileSystem::GetFileAttributes");
	R = TFileSystem::DeleteDirectory(S1.PChar(), false, false); if (R != 0) return TEnvironment::ShowTestErrorMessage(-8096, "TFileSystem::DeleteDirectory");

	R = TFileSystem::CreateFullPath(&S1, "/home/user/", "test", "txt"); if ((R != 0) || (!S1.IsEqual("/home/user/test.txt"))) return TEnvironment::ShowTestErrorMessage(-8097, "TFileSystem::CreateFullPath");
#endif

	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run validity tests for TFileStream
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunValidityTests_TFileStream(void) {

	TFileStream FS;
	INT32 R;
	INT64 R64;

	TString S1;
	S1.SetValue(TEST_FOLDER); TFileSystem::AppendToPath(&S1, "test_filestream.dat");

	R = FS.Open(S1.PChar(), AM_READ, OM_CREATE_NEW, CM_BINARY); if (R != 0) return TEnvironment::ShowTestErrorMessage(-9001, "TFileStream::Open");
	FS.Close(); 
	R = FS.Open(S1.PChar(), AM_READ, OM_CREATE_NEW, CM_BINARY); if (R != FILE_SYSTEM_ERROR_FILE_EXISTS) return TEnvironment::ShowTestErrorMessage(-9002, "TFileStream::Open");
	R = FS.Open(S1.PChar(), AM_READ, OM_CREATE_ALWAYS, CM_BINARY); if (R != 0) return TEnvironment::ShowTestErrorMessage(-9003, "TFileStream::Open");
	FS.Close(); TFileSystem::DeleteFile(S1.PChar());

	R = FS.Open(S1.PChar(), AM_READ, OM_OPEN_EXISTING, CM_BINARY); if (R != FILE_SYSTEM_ERROR_FILE_NOT_EXISTS) return TEnvironment::ShowTestErrorMessage(-9004, "TFileStream::Open");
	R = FS.Open(S1.PChar(), AM_READ, OM_OPEN_ALWAYS, CM_BINARY); if (R != 0) return TEnvironment::ShowTestErrorMessage(-9005, "TFileStream::Open");
	FS.Close(); TFileSystem::DeleteFile(S1.PChar());
	R = FS.Open(S1.PChar(), AM_READ, OM_APPEND_TO_END, CM_BINARY); if (R != 0) return TEnvironment::ShowTestErrorMessage(-9006, "TFileStream::Open");
	R = FS.Open(S1.PChar(), AM_READ, OM_OPEN_ALWAYS, CM_BINARY); if (R != 0) return TEnvironment::ShowTestErrorMessage(-9007, "TFileStream::Open");
	FS.Close();
	R = FS.Open(S1.PChar(), AM_READ, OM_APPEND_TO_END, CM_BINARY); if (R != 0) return TEnvironment::ShowTestErrorMessage(-9008, "TFileStream::Open");
	FS.Close();

	TBytes B1; B1.SetRandomBytes(256);
	TBytes B2;

	R = FS.Open(S1.PChar(), AM_READ, OM_CREATE_ALWAYS, CM_BINARY); if (R != 0) return TEnvironment::ShowTestErrorMessage(-9009, "TFileStream::Open");
	R64 = FS.Write(&B1, 0, -1); if (R64 != 256) return TEnvironment::ShowTestErrorMessage(-9010, "TFileStream::Write");
	if ((FS.GetSize() != 256) || (FS.GetPosition() != 256) || (!FS.IsEOF())) return TEnvironment::ShowTestErrorMessage(-9011, "TFileStream::GetSize, GetPosition, IsEOF");
	if (!FS.Rewind()) return TEnvironment::ShowTestErrorMessage(-9012, "TFileStream::Rewind");
	if ((FS.GetSize() != 256) || (FS.GetPosition() != 0) || (FS.IsEOF())) return TEnvironment::ShowTestErrorMessage(-9013, "TFileStream::GetSize, GetPosition, IsEOF");
	B2.Release(); R64 = FS.Read(&B2, 0, 1024); if (R64 != 256) return TEnvironment::ShowTestErrorMessage(-9014, "TFileStream::Read");
	if (B1.Compare(&B2, 0, -1) != 0) return TEnvironment::ShowTestErrorMessage(-9015, "TFileStream::Read");
	if ((FS.GetSize() != 256) || (FS.GetPosition() != 256) || (!FS.IsEOF())) return TEnvironment::ShowTestErrorMessage(-9016, "TFileStream::GetSize, GetPosition, IsEOF");
	R64 = FS.Seek(100, TStreamSeekOrigin::SO_BEGIN); if (R64 != 100) return TEnvironment::ShowTestErrorMessage(-9017, "TFileStream::Seek");
	if ((FS.GetSize() != 256) || (FS.GetPosition() != 100) || (FS.IsEOF())) return TEnvironment::ShowTestErrorMessage(-9018, "TFileStream::GetSize, GetPosition, IsEOF");
	B2.Release(); R64 = FS.Read(&B2, 0, 1024); if (R64 != 156) return TEnvironment::ShowTestErrorMessage(-9019, "TFileStream::Read");
	if (B1.Compare(&B2, 100, 156) != 0) return TEnvironment::ShowTestErrorMessage(-9020, "TFileStream::Read");
	FS.Close();

	if (TFileSystem::FileExists(S1.PChar(), false) != FILE_SYSTEM_TRUE) return TEnvironment::ShowTestErrorMessage(-9021, "TFileStream::FileExists");
	R = FS.Open(S1.PChar(), AM_READ, OM_OPEN_EXISTING, CM_BINARY); if (R != 0) return TEnvironment::ShowTestErrorMessage(-9022, "TFileStream::Open");
	FS.CloseAndDelete(); // close and delete the file
	if (TFileSystem::FileExists(S1.PChar(), false) != FILE_SYSTEM_FALSE) return TEnvironment::ShowTestErrorMessage(-9023, "TFileStream::FileExists");

	return true; // all tests passed
}
//	................................................................................................

//	................................................................................................
//  Run all validity tests
//	Input:
//			none
//	Output:
//			true / false
//	................................................................................................
BOOL RunAllValidityTests(INT32 iArgc, PCHAR* iArgs) {

	printf("\n\tRunning tests - environment... ");
	if (!RunValidityTests_Environment()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TString... ");
	if (!RunValidityTests_TString()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TList... ");
	if (!RunValidityTests_TList()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TBytes... ");
	if (!RunValidityTests_TBytes()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TDateTime... ");
	if (!RunValidityTests_TDateTime()) return false;
	printf("OK.");

	printf("\n\tRunning tests - Streams... ");
	if (!RunValidityTests_Streams()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TParamsList... ");
	if (!RunValidityTests_TParamsList()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TStringList... ");
	if (!RunValidityTests_TStringList()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TCommandLineParser... ");
	if (!RunValidityTests_TCommandLineParser(iArgc, iArgs)) return false;
	printf("OK.");

	printf("\n\tRunning tests - TFileSystem... ");
	if (!RunValidityTests_TFileSystem()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TFileStream... ");
	if (!RunValidityTests_TFileStream()) return false;
	printf("OK.");

	return true; // all tests passed
}
//	................................................................................................
