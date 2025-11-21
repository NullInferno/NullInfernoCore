#include "NullInfernoCore.h"

//	................................................................................................
//  Constructor
//	Input:
//			none
// 	Output:
// 			none
//	................................................................................................
TStopwatch::TStopwatch(void) {
	FStartTime = 0;
	FElapsedTime = 0;
}
//	................................................................................................
//	................................................................................................
//  Destructor
//	Input:
//			none
// 	Output:
// 			none
//	................................................................................................
TStopwatch::~TStopwatch(void) {
}
//	................................................................................................
//	................................................................................................
//  Start stopwatch
//	Input:
//			none
// 	Output:
// 			none
//	................................................................................................
void TStopwatch::Start(void) {
#ifdef WINDOWS_SYSTEM
	SYSTEMTIME ST; FILETIME FT; ULARGE_INTEGER U;
	GetSystemTime(&ST); SystemTimeToFileTime(&ST, &FT);
	U.LowPart = FT.dwLowDateTime; U.HighPart = FT.dwHighDateTime;
	FStartTime = U.QuadPart; 
#else
	struct timeval tv;
	gettimeofday(&tv, NULL); 
	FStartTime = ((UINT64)tv.tv_sec * 1000000 + (UINT64)tv.tv_usec) * 10;
#endif // WINDOWS_SYSTEM
	FElapsedTime = 0;
}
//	................................................................................................
//	................................................................................................
//  Pause stopwatch
//	Input:
//			none
// 	Output:
// 			none
//	................................................................................................
void TStopwatch::Pause(void) {
#ifdef WINDOWS_SYSTEM
	SYSTEMTIME ST; FILETIME FT; ULARGE_INTEGER U;
	GetSystemTime(&ST); SystemTimeToFileTime(&ST, &FT);
	U.LowPart = FT.dwLowDateTime; U.HighPart = FT.dwHighDateTime;
	FElapsedTime += U.QuadPart - FStartTime;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	FElapsedTime += ((UINT64)tv.tv_sec * 1000000 + (UINT64)tv.tv_usec) * 10 - FStartTime;
#endif // WINDOWS_SYSTEM
}
//	................................................................................................
//	................................................................................................
//  Continue stopwatch
//	Input:
//			none
// 	Output:
// 			none
//	................................................................................................
void TStopwatch::Continue(void) {
#ifdef WINDOWS_SYSTEM
	SYSTEMTIME ST; FILETIME FT; ULARGE_INTEGER U;
	GetSystemTime(&ST); SystemTimeToFileTime(&ST, &FT);
	U.LowPart = FT.dwLowDateTime; U.HighPart = FT.dwHighDateTime;
	FStartTime = U.QuadPart; 
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	FStartTime = ((UINT64)tv.tv_sec * 1000000 + (UINT64)tv.tv_usec) * 10;
#endif // WINDOWS_SYSTEM
}
//	................................................................................................
//	................................................................................................
//  Get elapsed time in seconds
//	Input:
//			none
// 	Output:
// 			elapsed time in seconds
//	................................................................................................
DOUBLE TStopwatch::GetElapsedTimeInSeconds(void) {
	return (DOUBLE)FElapsedTime / 10000000.0;
}
//	................................................................................................
//	................................................................................................
//  Print performance result
//	Input:
//			iOperationDescription - operation description
// 			iIterationsCount - number of iterations
// 	Output:
// 			none
//	................................................................................................
void TStopwatch::PrintPerforanceResult(CONST_PCHAR iOperationDescription, INT64 iIterationsCount) {
	DOUBLE T = GetElapsedTimeInSeconds();
	DOUBLE Perf = (iIterationsCount > 0) ? (DOUBLE)iIterationsCount / T : 0.0;
	if (IS_PCHAR_EMPTY(iOperationDescription)) {
		FNC_PRINTF("\n\tPerformance result: Elapsed time: %.6lf sec; Iters: %lld; Perf: %.0lf iters/sec.", T, iIterationsCount, Perf);
	} else {
		FNC_PRINTF("\n\tPerformance result (%s): Elapsed time: %.6lf sec; Iters: %lld; Perf: %.0lf iters/sec.", iOperationDescription, T, iIterationsCount, Perf);
	}
}
//	................................................................................................
