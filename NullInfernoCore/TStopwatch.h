#pragma once

//	................................................................................................
//	Class TStopwatch
//	................................................................................................
class TStopwatch {
private:
	UINT64 FStartTime;
	UINT64 FElapsedTime;
public:
	TStopwatch(void); // Constructor
	~TStopwatch(void); // Destructor
public:
	void Start(void); // Start stopwatch
	void Pause(void); // Pause stopwatch
	void Continue(void); // Continue stopwatch
public:
	DOUBLE GetElapsedTimeInSeconds(void); // Get elapsed time in seconds
	void PrintPerforanceResult(CONST_PCHAR iOperationDescription, INT64 iIterationsCount = 1); // Print performance result
};
//	................................................................................................
