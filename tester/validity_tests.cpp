#include "NullInfernoCore.h"

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

	TString S1, S2;

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

	R = L1.Add((UINT64)1); if ((R != 0) || (L1.Count() != 1) || (L1.ItemAsUINT64(0) != 1)) return TEnvironment::ShowTestErrorMessage(-1201, "TList::Add");
	R = L1.Add((UINT64)2); if ((R != 1) || (L1.Count() != 2) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 2)) return TEnvironment::ShowTestErrorMessage(-1202, "TList::Add");
	R = L1.Add((UINT64)3); if ((R != 2) || (L1.Count() != 3) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 2) || (L1.ItemAsUINT64(2) != 3)) return TEnvironment::ShowTestErrorMessage(-1203, "TList::Add");
	R = L1.Insert(0, (UINT64)4); if ((R != 0) || (L1.Count() != 4) || (L1.ItemAsUINT64(0) != 4) || (L1.ItemAsUINT64(1) != 1) || (L1.ItemAsUINT64(2) != 2) || (L1.ItemAsUINT64(3) != 3)) return TEnvironment::ShowTestErrorMessage(-1204, "TList::Add");
	R = L1.Insert(1, (UINT64)5); if ((R != 1) || (L1.Count() != 5) || (L1.ItemAsUINT64(0) != 4) || (L1.ItemAsUINT64(1) != 5) || (L1.ItemAsUINT64(2) != 1) || (L1.ItemAsUINT64(3) != 2) || (L1.ItemAsUINT64(4) != 3)) return TEnvironment::ShowTestErrorMessage(-1205, "TList::Add");
	L1.SetCount(4); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 4) || (L1.ItemAsUINT64(1) != 5) || (L1.ItemAsUINT64(2) != 1) || (L1.ItemAsUINT64(3) != 2)) return TEnvironment::ShowTestErrorMessage(-1206, "TList::SetCount");
	L1.Delete(3); if ((L1.Count() != 3) || (L1.ItemAsUINT64(0) != 4) || (L1.ItemAsUINT64(1) != 5) || (L1.ItemAsUINT64(2) != 1)) return TEnvironment::ShowTestErrorMessage(-1207, "TList::Delete");
	L1.Delete(0); if ((L1.Count() != 2) || (L1.ItemAsUINT64(0) != 5) || (L1.ItemAsUINT64(1) != 1)) return TEnvironment::ShowTestErrorMessage(-1208, "TList::Delete");
	L1.Delete(0); if ((L1.Count() != 1) || (L1.ItemAsUINT64(0) != 1)) return TEnvironment::ShowTestErrorMessage(-1209, "TList::Delete");
	L1.Delete(0); if (L1.Count() != 0) return TEnvironment::ShowTestErrorMessage(-1210, "TList::Delete");

	L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);
	L1.DeleteRange(0, 2); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 3) || (L1.ItemAsUINT64(1) != 4) || (L1.ItemAsUINT64(2) != 5) || (L1.ItemAsUINT64(3) != 6)) return TEnvironment::ShowTestErrorMessage(-1211, "TList::DeleteRange");
	L1.DeleteRange(1, 2); if ((L1.Count() != 2) || (L1.ItemAsUINT64(0) != 3) || (L1.ItemAsUINT64(1) != 6)) return TEnvironment::ShowTestErrorMessage(-1212, "TList::DeleteRange");
	L1.DeleteRange(0, 2); if (L1.Count() != 0) return TEnvironment::ShowTestErrorMessage(-1213, "TList::DeleteRange");

	L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);
	L2.Add((UINT64)11); L2.Add((UINT64)12);
	R = L1.AddList(&L2); if ((R != 6) || (L1.Count() != 8) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 2) || (L1.ItemAsUINT64(2) != 3) || (L1.ItemAsUINT64(3) != 4) || (L1.ItemAsUINT64(4) != 5) || (L1.ItemAsUINT64(5) != 6) || (L1.ItemAsUINT64(6) != 11) || (L1.ItemAsUINT64(7) != 12)) return TEnvironment::ShowTestErrorMessage(-1214, "TList::AddList");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);
	R = L1.InsertList(1, &L2); if ((R != 1) || (L1.Count() != 8) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 11) || (L1.ItemAsUINT64(2) != 12) || (L1.ItemAsUINT64(3) != 2) || (L1.ItemAsUINT64(4) != 3) || (L1.ItemAsUINT64(5) != 4) || (L1.ItemAsUINT64(6) != 5) || (L1.ItemAsUINT64(7) != 6)) return TEnvironment::ShowTestErrorMessage(-1215, "TList::InsertList");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)6);

	L1.DeleteValue((PVOID)6, 1); if ((L1.Count() != 5) || (L1.ItemAsUINT64(0) != 1) || (L1.ItemAsUINT64(1) != 2) || (L1.ItemAsUINT64(2) != 3) || (L1.ItemAsUINT64(3) != 4) || (L1.ItemAsUINT64(4) != 5)) return TEnvironment::ShowTestErrorMessage(-1216, "TList::DeleteValue");
	L1.DeleteValue((PVOID)1, 1); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 2) || (L1.ItemAsUINT64(1) != 3) || (L1.ItemAsUINT64(2) != 4) || (L1.ItemAsUINT64(3) != 5)) return TEnvironment::ShowTestErrorMessage(-1217, "TList::DeleteValue");
	L1.DeleteValue((PVOID)10, 1); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 2) || (L1.ItemAsUINT64(1) != 3) || (L1.ItemAsUINT64(2) != 4) || (L1.ItemAsUINT64(3) != 5)) return TEnvironment::ShowTestErrorMessage(-1218, "TList::DeleteValue");

	L1.Clear();
	L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)1); L1.Add((UINT64)5); L1.Add((UINT64)1);
	L1.DeleteValue((PVOID)1, 0); if ((L1.Count() != 3) || (L1.ItemAsUINT64(0) != 2) || (L1.ItemAsUINT64(1) != 3) || (L1.ItemAsUINT64(2) != 5)) return TEnvironment::ShowTestErrorMessage(-1219, "TList::DeleteValue (all)");

	L1.Clear();
	L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)1); L1.Add((UINT64)5); L1.Add((UINT64)1);
	L1.DeleteValue((PVOID)1, 2); if ((L1.Count() != 4) || (L1.ItemAsUINT64(0) != 2) || (L1.ItemAsUINT64(1) != 3) || (L1.ItemAsUINT64(2) != 5) || (L1.ItemAsUINT64(3) != 1)) return TEnvironment::ShowTestErrorMessage(-1220, "TList::DeleteValue (all)");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)1);
	if (L1.Find((UINT64)1, 0, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1221, "TList::Find");
	if (L1.Find((UINT64)1, 0, -1, 2) != 5) return TEnvironment::ShowTestErrorMessage(-1222, "TList::Find");
	if (L1.Find((UINT64)1, 0, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1223, "TList::Find");
	if (L1.Find((UINT64)1, 1, -1, 1) != 5) return TEnvironment::ShowTestErrorMessage(-1224, "TList::Find");
	if (L1.Find((UINT64)1, 1, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1225, "TList::Find");
	if (L1.Find((UINT64)6, 0, -1, -1) != -1) return TEnvironment::ShowTestErrorMessage(-1226, "TList::Find");
	if (L1.Find((UINT64)1, 0, 2, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1227, "TList::Find");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2); L1.Add((UINT64)3); L1.Add((UINT64)4); L1.Add((UINT64)5); L1.Add((UINT64)1);
	if (L1.ReverseFind((UINT64)1, -1, -1, 1) != 5) return TEnvironment::ShowTestErrorMessage(-1228, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, -1, -1, 2) != 0) return TEnvironment::ShowTestErrorMessage(-1229, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, -1, -1, 3) != -1) return TEnvironment::ShowTestErrorMessage(-1230, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, 4, -1, 1) != 0) return TEnvironment::ShowTestErrorMessage(-1231, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, 4, -1, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1232, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)6, -1, -1, 1) != -1) return TEnvironment::ShowTestErrorMessage(-1233, "TList::ReverseFind");
	if (L1.ReverseFind((UINT64)1, -1, 2, 2) != -1) return TEnvironment::ShowTestErrorMessage(-1234, "TList::ReverseFind");

	L1.Clear(); L1.Add((UINT64)1); L1.Add((UINT64)2);
	L1.SetItem(0, (UINT64)3); if (L1.ItemAsUINT64(0) != 3) return TEnvironment::ShowTestErrorMessage(-1235, "TList::SetItem");
	L1.SetItem(0, (UINT64)4); if (L1.ItemAsUINT64(0) != 4) return TEnvironment::ShowTestErrorMessage(-1236, "TList::SetItem");

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
BOOL RunAllValidityTests(void) {

	printf("\n\tRunning tests - environment... ");
	if (!RunValidityTests_Environment()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TString... ");
	if (!RunValidityTests_TString()) return false;
	printf("OK.");

	printf("\n\tRunning tests - TList... ");
	if (!RunValidityTests_TList()) return false;
	printf("OK.");

	return true; // all tests passed
}
//	................................................................................................
