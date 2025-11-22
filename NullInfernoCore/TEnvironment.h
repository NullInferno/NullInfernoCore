#pragma once

//	................................................................................................
//	Class TEnvironment
//	................................................................................................
class TEnvironment {
public:
	static BOOL InitEnvironment(void); // Initialize environment
	static void CloseEnvironment(void); // Close environment
public:
	static UINT32 GenerateRandomUINT32(void); // Generate random UINT32
	static UINT64 GenerateRandomUINT64(void); // Generate random UINT64
	static DOUBLE GenerateRandomDOUBLE(DOUBLE iMin = 0, DOUBLE iMax = 1); // Generate random DOUBLE
public:
	static BOOL ShowTestErrorMessage(INT32 iErrorCode, CONST_PCHAR iErrorMessage, ...); // Show test error messages
};
//	................................................................................................
