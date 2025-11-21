#include "NullInfernoCore.h"

BOOL RunAllValidityTests(void);
void RunAllPerformanceTests(void);

//	................................................................................................
//  Main function of the tester application
//	Input:
//			iArgc - Number of command line arguments
// 			iArgs - Array of command line arguments
//	Output:
//			0 or error code
//	................................................................................................
INT32 main(INT32 iArgc, PCHAR* iArgs) {

	printf("\n............................................................................................................");
	printf("\nTester application for library NullInfernoCore");
	printf("\n............................................................................................................");

	if (!TEnvironment::InitEnvironment()) {
		TEnvironment::ShowTestErrorMessages(-99999999, "Environment init error");
		printf("\n............................................................................................................");
		printf("\n\n");
		return -1;
	}

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

	//for (INT32 i = 0; i < 32; i++) {
	//	printf("\n[%08X]", TEnvironment::GenerateRandomUINT32());
	//}
	//for (INT32 i = 0; i < 32; i++) {
	//	printf("\n[%016llX]", TEnvironment::GenerateRandomUINT64());
	//}
	//for (INT32 i = 0; i < 32; i++) {
	//	printf("\n[%.12lf]", TEnvironment::GenerateRandomDOUBLE(-100000, 100000));
	//}

	TEnvironment::CloseEnvironment();
	printf("\n............................................................................................................");
	printf("\n\n");
	return 0;
}
//	................................................................................................
