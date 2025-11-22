#include "NullInfernoCore.h"

BOOL RunAllValidityTests(void);
void RunAllPerformanceTests(void);

//	................................................................................................
//	................................................................................................
void Temp(void) {

#ifdef WINDOWS_SYSTEM

	CHAR BUF[512], BUF2[512];
	for (INT32 i = 0; i < 255; i++) BUF[i] = i + 1;
	BUF[255] = 0;

	wchar_t BUFW[512];

	INT32 L = MultiByteToWideChar(1252, 0, BUF, -1, NULL, 0);
	MultiByteToWideChar(1252, 0, BUF, -1, BUFW, L);
	CharUpperW(BUFW);
	L = WideCharToMultiByte(1252, 0, BUFW, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(1252, 0, BUFW, -1, BUF2, L, NULL, NULL);

	printf("\n");
	for (INT32 i = 0; i < 256; i++) {
		if (BUF[i] != BUF2[i]) printf("[%x, %x]", (BYTE)BUF[i], (BYTE)BUF2[i]);
	}

	printf("\nconst BYTE UPPER_CASE_TABLE_1252[] = {");
	for (INT32 i = 0; i < 256; i++) {
		printf("0x%X,", (BYTE)BUF2[i]);
	}
	printf("};");

	//for (INT32 i = 0; i < 32; i++) {
	//	printf("\n[%08X]", TEnvironment::GenerateRandomUINT32());
	//}
	//for (INT32 i = 0; i < 32; i++) {
	//	printf("\n[%016llX]", TEnvironment::GenerateRandomUINT64());
	//}
	//for (INT32 i = 0; i < 32; i++) {
	//	printf("\n[%.12lf]", TEnvironment::GenerateRandomDOUBLE(-100000, 100000));
	//}
#endif
}
//	................................................................................................

//	................................................................................................
//  Main function of the tester application
//	Input:
//			iArgc - Number of command line arguments
// 			iArgs - Array of command line arguments
//	Output:
//			0 or error code
//	................................................................................................
INT32 main(INT32 iArgc, PCHAR* iArgs) {

	setvbuf(stdout, NULL, _IONBF, 0); // Autoflush for stdout

	printf("\n............................................................................................................");
	printf("\nTester application for library NullInfernoCore");
	printf("\n............................................................................................................");

	if (!TEnvironment::InitEnvironment()) {
		TEnvironment::ShowTestErrorMessage(-99999999, "Environment init error");
		printf("\n............................................................................................................");
		printf("\n\n");
		return -1;
	}

	//Temp();
	//return 0;

	printf("\nRunning validity tests...");
	if (!RunAllValidityTests()) {
		TEnvironment::CloseEnvironment();
		printf("\n............................................................................................................");
		printf("\n\n");
		return -1;
	}
	printf("\nValidity tests completed successfully.");
	printf("\n............................................................................................................");

	printf("\nRunning performance tests...");
	RunAllPerformanceTests();
	printf("\nPerformance tests completed.");

	TEnvironment::CloseEnvironment();
	printf("\n............................................................................................................");
	printf("\n\n");
	return 0;
}
//	................................................................................................
