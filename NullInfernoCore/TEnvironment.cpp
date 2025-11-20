#include "NullInfernoCore.h"
#include "TEnvironment.h"

//	................................................................................................
//  Initialize environment
//	Input:
//			none
// 	Output:
// 			true / false
//	................................................................................................
BOOL TEnvironment::InitEnvironment(void) {
	srand((UINT32)time(NULL)); // Seed random number generator
	return true;
}
//	................................................................................................
//	................................................................................................
//  Close environment
//	Input:
//			none
// 	Output:
// 			none
//	................................................................................................
void TEnvironment::CloseEnvironment(void) {
}
//	................................................................................................
//	................................................................................................
//  Generate random UINT32
//	Input:
//			none
// 	Output:
// 			random UINT32 value
//	................................................................................................
UINT32 TEnvironment::GenerateRandomUINT32(void) {
#ifdef WINDOWS_SYSTEM
	return (UINT32)rand() | ((UINT32)rand() << 15) | ((UINT32)rand() << 30);
#else
	return (UINT32)rand() | ((UINT32)rand() << 31);
#endif
}
//	................................................................................................
//	................................................................................................
//  Generate random UINT64
//	Input:
//			none
// 	Output:
// 			random UINT64 value
//	................................................................................................
UINT64 TEnvironment::GenerateRandomUINT64(void) {
#ifdef WINDOWS_SYSTEM
	return (UINT64)rand() | ((UINT64)rand() << 15) | ((UINT64)rand() << 30) | ((UINT64)rand() << 45) | ((UINT64)rand() << 60);
#else
	return (UINT64)rand() | ((UINT64)rand() << 31) | ((UINT64)rand() << 62);
#endif
}
//	................................................................................................
//	................................................................................................
//  Generate random DOUBLE
//	Input:
//			iMin - minimum value
// 			iMax - maximum value
// 	Output:
// 			random DOUBLE value
//	................................................................................................
DOUBLE TEnvironment::GenerateRandomDOUBLE(DOUBLE iMin, DOUBLE iMax) {
	if (iMax < iMin) { // Swap values if needed
		EXCHANGE_DOUBLE(iMin, iMax);
	}
	if (iMax == iMin) { // Same values?
		return iMin;
	}

	UINT64 r = GenerateRandomUINT64(); // Get random UINT64
	const DOUBLE D = static_cast<DOUBLE>(~static_cast<UINT64>(0)) + 1.0; // UINT64 max + 1
	DOUBLE unit = static_cast<DOUBLE>(r) / D;

	return iMin + unit * (iMax - iMin); // return random value in range
}
//	................................................................................................
//	................................................................................................
//  Show test error messages
//	Input:
//			iErrorCode - error code
// 			iErrorMessage - formatted error message
//			... - additional parameters
// 	Output:
// 			false
//	................................................................................................
BOOL TEnvironment::ShowTestErrorMessages(INT32 iErrorCode, CONST_PCHAR iErrorMessage, ...) {
	if (IS_PCHAR_EMPTY(iErrorMessage)) { // No message?
		FNC_PRINTF("Error with code: %d!", iErrorCode); // Show error code only
		return false;
	}

	PCHAR BUF = PCHAR_ALLOC(FNC_STRLEN(iErrorMessage) + 128); // Allocate buffer
	if (BUF == NULL) return false; // Allocation failed?

	FNC_SPRINTF(BUF, "Error with code: %d (%s)! ", iErrorCode, iErrorMessage); // Write error message to buffer
	
	va_list args; // Start variable arguments processing
	va_start(args, iErrorMessage);
	FNC_VPRINTF(BUF, args); // Print formatted message
	va_end(args); // End variable arguments processing

	PCHAR_FREE(BUF); // Free buffer
	return false;
}
//	................................................................................................
