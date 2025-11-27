#pragma once

typedef void (*TProcessCommandLineCallback)(INT64 iParamIndex, TString *iParamName, TString *iParamValue, PVOID iUserData);

//	...............................................................................................
//	Class TCommandLineParser
//	...............................................................................................
class TCommandLineParser {
private:
	CHAR FParamValueSeparator; // Parameter value separator
	CHAR FParamQuoteChar; // Parameter quote character
public:
	TCommandLineParser(CHAR iParamValueSeparator = '=', CHAR iParamQuoteChar = '\"'); // Constructor
	~TCommandLineParser(void); // Destructor
public:
	void ProcessCommandLine(CONST_PCHAR iCommandLine, TProcessCommandLineCallback iProcessCommandLineFunction, PVOID iUserData); // Process command line
	void ProcessCommandLine(INT64 iArgc, PCHAR *iArgs, TProcessCommandLineCallback iProcessCommandLineFunction, PVOID iUserData, INT64 iSkipCount = 1); // Process command line
public:
	INT64 Count(void); // Get number of parameters
	BOOL ParamExists(CONST_PCHAR iName); // Check if parameter exists
};
//	...............................................................................................
