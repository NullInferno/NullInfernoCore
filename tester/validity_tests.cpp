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
	if (P1 == NULL) return TEnvironment::ShowTestErrorMessages(-999, "Memory allocation error");
	PCHAR P2 = PCHAR_ALLOC(10240);
	if (P2 == NULL) return TEnvironment::ShowTestErrorMessages(-999, "Memory allocation error");

	UINT32 U32; INT32 I32;
	UINT64 U64; INT64 I64;
	DOUBLE Dbl;

	if ((UINT32ToStr(0, P1) != 1) || (FNC_STRCMP(P1, "0") != 0)) return TEnvironment::ShowTestErrorMessages(-1, "UINT32ToStr");
	U32 = 1;
	for (INT32 i = 1; i < 11; i++) {
		FNC_SPRINTF(P2, "%u", U32);
		if ((UINT32ToStr(U32, P1) != i) || (FNC_STRCMP(P1, P2) != 0)) return TEnvironment::ShowTestErrorMessages(-2, "UINT32ToStr");
		U32 *= 10;
	}
	I32 = -1;
	for (INT32 i = 2; i < 12; i++) {
		FNC_SPRINTF(P2, "%d", I32);
		if ((INT32ToStr(I32, P1) != i) || (FNC_STRCMP(P1, P2) != 0)) return TEnvironment::ShowTestErrorMessages(-3, "INT32ToStr");
		I32 *= 10;
	}

	for (INT32 i = 0; i < 10240; i++) {
		U32 = TEnvironment::GenerateRandomUINT32();
		UINT32ToStr(U32, P1); FNC_SPRINTF(P2, "%u", U32); if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessages(-4, "UINT32ToStr");
		I32 = (INT32)TEnvironment::GenerateRandomUINT32();
		INT32ToStr(I32, P1); FNC_SPRINTF(P2, "%d", I32); if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessages(-5, "INT32ToStr");
	}

	if ((UINT64ToStr(0, P1) != 1) || (FNC_STRCMP(P1, "0") != 0)) return TEnvironment::ShowTestErrorMessages(-6, "UINT64ToStr");
	U64 = 1;
	for (INT32 i = 1; i < 21; i++) {
		FNC_SPRINTF(P2, "%llu", U64);
		if ((UINT64ToStr(U64, P1) != i) || (FNC_STRCMP(P1, P2) != 0)) return TEnvironment::ShowTestErrorMessages(-7, "UINT64ToStr");
		U64 *= 10;
	}

	I64 = -1;
	for (INT32 i = 2; i < 20; i++) {
		FNC_SPRINTF(P2, "%lld", I64);
		if ((INT64ToStr(I64, P1) != i) || (FNC_STRCMP(P1, P2) != 0)) return TEnvironment::ShowTestErrorMessages(-8, "INT64ToStrm (%d)", i);
		I64 *= 10;
	}

	for (INT32 i = 0; i < 10240; i++) {
		U64 = TEnvironment::GenerateRandomUINT64();
		UINT64ToStr(U64, P1); FNC_SPRINTF(P2, "%llu", U64); if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessages(-9, "UINT64ToStr (%llu)", U64);
		I64 = (INT64)TEnvironment::GenerateRandomUINT64();
		INT64ToStr(I64, P1); FNC_SPRINTF(P2, "%lld", I64); if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessages(-10, "INT64ToStr");
	}

	Dbl = RoundDOUBLE(1.255, 0); if (!IsEqualDOUBLES(Dbl, 1)) return TEnvironment::ShowTestErrorMessages(-11, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.255, 1); if (!IsEqualDOUBLES(Dbl, 1.3)) return TEnvironment::ShowTestErrorMessages(-12, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.255, 2); if (!IsEqualDOUBLES(Dbl, 1.26)) return TEnvironment::ShowTestErrorMessages(-13, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.255, 3); if (!IsEqualDOUBLES(Dbl, 1.255)) return TEnvironment::ShowTestErrorMessages(-14, "RoundDOUBLE (%lf)", Dbl);
	Dbl = RoundDOUBLE(1.255, 4); if (!IsEqualDOUBLES(Dbl, 1.255)) return TEnvironment::ShowTestErrorMessages(-15, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 0); if (!IsEqualDOUBLES(Dbl, 2)) return TEnvironment::ShowTestErrorMessages(-16, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 1); if (!IsEqualDOUBLES(Dbl, 2)) return TEnvironment::ShowTestErrorMessages(-17, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 2); if (!IsEqualDOUBLES(Dbl, 2)) return TEnvironment::ShowTestErrorMessages(-18, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 3); if (!IsEqualDOUBLES(Dbl, 1.999)) return TEnvironment::ShowTestErrorMessages(-19, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 4); if (!IsEqualDOUBLES(Dbl, 1.9985)) return TEnvironment::ShowTestErrorMessages(-20, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985, 5); if (!IsEqualDOUBLES(Dbl, 1.9985)) return TEnvironment::ShowTestErrorMessages(-21, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985123422349, 12); if (!IsEqualDOUBLES(Dbl, 1.998512342235)) return TEnvironment::ShowTestErrorMessages(-22, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985123422345, 12); if (!IsEqualDOUBLES(Dbl, 1.998512342235)) return TEnvironment::ShowTestErrorMessages(-23, "RoundDOUBLE");
	Dbl = RoundDOUBLE(1.9985123422344, 12); if (!IsEqualDOUBLES(Dbl, 1.998512342234)) return TEnvironment::ShowTestErrorMessages(-24, "RoundDOUBLE");

	for (INT32 i = 0; i < 13; i++) {
		Dbl = 0;
		DOUBLEToStr(Dbl, P1, i); FNC_SPRINTF(P2, "%.*lf", i, Dbl);
		if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessages(-25, "DOUBLEToStr");
		Dbl = 0.001234567;
		DOUBLEToStr(Dbl, P1, i); FNC_SPRINTF(P2, "%.*lf", i, Dbl);
		if (FNC_STRCMP(P1, P2) != 0) return TEnvironment::ShowTestErrorMessages(-26, "DOUBLEToStr");
		for (INT32 j = 0; j < 10240; j++) {
			Dbl = RoundDOUBLE(TEnvironment::GenerateRandomDOUBLE(-1, 1), i);
			//Dbl = -551827.99113683111500;
			DOUBLEToStr(Dbl, P1, i); FNC_SPRINTF(P2, "%.*lf", i, Dbl);
			if (FNC_STRCMP(P1, P2) != 0) {
				DOUBLEToStr(Dbl, P1, i); 
				FNC_SPRINTF(P2, "%.*lf", i, Dbl);
				return TEnvironment::ShowTestErrorMessages(-27, "DOUBLEToStr (%d, %.14lf, %s, %s)", i, Dbl, P1, P2);
			}
		}
	}

	FNC_SPRINTF(P1, "%u", MAX_UINT32);
	if (StrToUINT32(P1, 0, ' ') != MAX_UINT32) return TEnvironment::ShowTestErrorMessages(-28, "StrToUINT32");
	if (StrToUINT32("9999", 0, ' ') != 9999) return TEnvironment::ShowTestErrorMessages(-29, "StrToUINT32");
	if (StrToUINT32("99999999", 0, ' ') != 99999999) return TEnvironment::ShowTestErrorMessages(-30, "StrToUINT32");
	if (StrToUINT32("999999999", 0, ' ') != 999999999) return TEnvironment::ShowTestErrorMessages(-31, "StrToUINT32");

	FNC_SPRINTF(P1, "%d", MAX_INT32);
	if (StrToINT32(P1, 0, ' ') != MAX_INT32) return TEnvironment::ShowTestErrorMessages(-32, "StrToINT32");
	if (StrToINT32("-9999", 0, ' ') != -9999) return TEnvironment::ShowTestErrorMessages(-33, "StrToINT32");
	if (StrToINT32("-99999999", 0, ' ') != -99999999) return TEnvironment::ShowTestErrorMessages(-34, "StrToINT32");
	if (StrToINT32("-999999999", 0, ' ') != -999999999) return TEnvironment::ShowTestErrorMessages(-35, "StrToINT32");

	if (StrToUINT32("99 99", 0, ' ') != 99) return TEnvironment::ShowTestErrorMessages(-36, "StrToUINT32");

	for (INT32 i = 0; i < 10240; i++) {
		U32 = TEnvironment::GenerateRandomUINT32();
		UINT32ToStr(U32, P1); if (StrToUINT32(P1, 0, ' ') != U32) return TEnvironment::ShowTestErrorMessages(-37, "UINT32ToStr + StrToUINT32");
		I32 = (INT32)TEnvironment::GenerateRandomUINT32();
		INT32ToStr(I32, P1); if (StrToINT32(P1, 0, ' ') != I32) return TEnvironment::ShowTestErrorMessages(-38, "INT32ToStr + StrToINT32");
	}

	FNC_SPRINTF(P1, "%llu", MAX_UINT64);
	if (StrToUINT64(P1, 0, ' ') != MAX_UINT64) return TEnvironment::ShowTestErrorMessages(-39, "StrToUINT64");
	if (StrToUINT64("9999", 0, ' ') != 9999) return TEnvironment::ShowTestErrorMessages(-40, "StrToUINT64");
	if (StrToUINT64("99999999", 0, ' ') != 99999999) return TEnvironment::ShowTestErrorMessages(-41, "StrToUINT64");
	if (StrToUINT64("999999999", 0, ' ') != 999999999) return TEnvironment::ShowTestErrorMessages(-42, "StrToUINT64");

	FNC_SPRINTF(P1, "%lld", MAX_INT64);
	if (StrToINT64(P1, 0, ' ') != MAX_INT64) return TEnvironment::ShowTestErrorMessages(-43, "StrToINT64");
	if (StrToINT64("-9999", 0, ' ') != -9999) return TEnvironment::ShowTestErrorMessages(-44, "StrToINT64");
	if (StrToINT64("-99999999", 0, ' ') != -99999999) return TEnvironment::ShowTestErrorMessages(-45, "StrToINT64");
	if (StrToINT64("-999999999", 0, ' ') != -999999999) return TEnvironment::ShowTestErrorMessages(-46, "StrToINT64");

	if (StrToUINT64("99 99", 0, ' ') != 99) return TEnvironment::ShowTestErrorMessages(-47, "StrToUINT64");

	for (INT64 i = 0; i < 10240; i++) {
		U64 = TEnvironment::GenerateRandomUINT64();
		UINT64ToStr(U64, P1); if (StrToUINT64(P1, 0, ' ') != U64) return TEnvironment::ShowTestErrorMessages(-37, "UINT64ToStr + StrToUINT64");
		I64 = (INT64)TEnvironment::GenerateRandomUINT64();
		INT64ToStr(I64, P1); if (StrToINT64(P1, 0, ' ') != I64) return TEnvironment::ShowTestErrorMessages(-38, "INT64ToStr + StrToINT64");
	}

	Dbl = StrToDOUBLE("1.255", 0, '.', ' '); if (!IsEqualDOUBLES(Dbl, 1.255)) return TEnvironment::ShowTestErrorMessages(-39, "StrToDOUBLE");
	Dbl = StrToDOUBLE("1.999999999999", 0, '.', ' '); if (!IsEqualDOUBLES(Dbl, 1.999999999999)) return TEnvironment::ShowTestErrorMessages(-40, "StrToDOUBLE");

	for (INT64 i = 0; i < 10240; i++) {
		Dbl = TEnvironment::GenerateRandomDOUBLE();
		DOUBLEToStr(Dbl, P1, 12); 
		DOUBLE Dbl2 = StrToDOUBLE(P1, 0, '.', ' '); 
		if (!IsEqualDOUBLES(Dbl, Dbl2, 1e-12)) return TEnvironment::ShowTestErrorMessages(-37, "DOUBLEToStr + StrToDOUBLE (%.12lf, %.12lf)", Dbl, Dbl2);
	}

	PCHAR_FREE(P1);
	PCHAR_FREE(P2);
	return true;
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

	return true; // all tests passed
}
//	................................................................................................
