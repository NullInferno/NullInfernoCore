#include "NullInfernoCore.h"
#include "TCommandLineParser.h"

#ifdef LINUX_SYSTEM
#include <wordexp.h>
#endif

//	...............................................................................................
//	Constructor
//	Input:
// 			iParamValueSeparator - parameter value separator
// 			iParamQuoteChar - parameter quote character
//	Output:
//			none
//	...............................................................................................
TCommandLineParser::TCommandLineParser(CHAR iParamValueSeparator, CHAR iParamQuoteChar) {
	FParamValueSeparator = iParamValueSeparator; // Save parameters
	FParamQuoteChar = iParamQuoteChar;
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TCommandLineParser::~TCommandLineParser(void) {
}
//	...............................................................................................
//	...............................................................................................
//	Process command line
//	Input:
// 			iCommandLine - command line string
// 			iProcessCommandLineFunction - callback function to process each parameter
// 			iUserData - user data pointer
//	Output:
//			none
//	...............................................................................................
void TCommandLineParser::ProcessCommandLine(CONST_PCHAR iCommandLine, TProcessCommandLineCallback iProcessCommandLineFunction, PVOID iUserData) {
	PCHAR* ArgsPChar;
	TStringList *ArgsList;

#ifdef WINDOWS_SYSTEM

	TString S; S.SetValue(iCommandLine);  // Convert command line to PWCHAR
	PWCHAR CommandLineW = (PWCHAR)MEMORY_ALLOC((S.Length+1) * sizeof(WCHAR));
	if (CommandLineW == NULL) return;

	S.AsPWChar((LPWSTR)CommandLineW, S.Length + 1); // Convert command line to wide char string

	INT32 Argc = 0;
	LPWSTR* Args = CommandLineToArgvW(CommandLineW, &Argc); // Parse command line into arguments

	ArgsList = new TStringList(); // Create list to hold arguments
	for (INT32 i = 0; i < Argc; i++) { // Process each argument
		TString ArgS; ArgS.SetValue((PWCHAR)Args[i], -1); // Convert argument to TString
		ArgsList->Add(&ArgS); // Add argument to the list
	}

	LocalFree(Args); // Free memory allocated by CommandLineToArgvW
	MEMORY_FREE(CommandLineW); // Free allocated memory
#else
	wordexp_t p;
	if (wordexp(iCommandLine, &p, 0) != 0) { // Parsing
		//wordfree(&p);
		return;
	}

	ArgsList = new TStringList(); // Create list to hold arguments
	for (size_t i = 0; i < p.we_wordc; i++) {
		ArgsList->Add(p.we_wordv[i]); // Add argument to the list
	}
	wordfree(&p); // Free allocated memory
#endif
	ArgsPChar = ArgsList->CreatePCharArray(); // Create array of PCHAR strings

	if (ArgsPChar != NULL) {
		ProcessCommandLine(ArgsList->Count(), ArgsPChar, iProcessCommandLineFunction, iUserData, 0); // Process command line arguments
		MEMORY_FREE(ArgsPChar); // Free allocated array
	}

	delete ArgsList; // Delete arguments list
}
//	...............................................................................................
//	...............................................................................................
//	Process command line
//	Input:
// 			iArgc - number of command line arguments
//			iArgs - array of command line arguments
// 			iProcessCommandLineFunction - callback function to process each parameter
// 			iUserData - user data pointer
// 			iSkipCount - number of initial arguments to skip
//	Output:
//			none
//	...............................................................................................
void TCommandLineParser::ProcessCommandLine(INT64 iArgc, PCHAR* iArgs, TProcessCommandLineCallback iProcessCommandLineFunction, PVOID iUserData, INT64 iSkipCount) {

	TString S, N, V;
	for (INT64 i = iSkipCount; i < iArgc; i++) { // Process each argument
		S.SetValue(iArgs[i]); // Get argument string
		S.ExtractNameValuePair(&N, &V, FParamValueSeparator, FParamQuoteChar, ' '); // Extract name and value
		if (!N.IsEmpty()) { // Is name is not empty?
			iProcessCommandLineFunction(i, &N, &V, iUserData);
		}
	}
}
//	...............................................................................................
