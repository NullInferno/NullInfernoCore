#pragma once

//	...............................................................................................
//	Class TString
//	...............................................................................................
class TString {
private:
	INT64 FCapacity; // Capacity of allocated memory
public:
	PCHAR Value; // Content
	INT64 Length; // Length of current content
public:
	TString(); // Constructor
	TString(CONST_PCHAR iValue, INT64 iLength = -1); // Constructor
	TString(TString* iValue); // Constructor
	TString(TString& iValue); // Constructor
	TString(INT32 iValue); // Constructor
	TString(UINT32 iValue); // Constructor
	TString(INT64 iValue); // Constructor
	TString(UINT64 iValue); // Constructor
	TString(DOUBLE iValue, INT32 iDecimalPlaces = 6); // Constructor
	~TString(); // Destructor
public:
	void Release(void); // Release the memory
	BOOL Reallocate(INT64 iNewCapacity, BOOL iKeepContent = false); // Reallocate the memory
public:
	void SetValue(CONST_PCHAR iValue, INT64 iLength = -1); // Set value
	void SetValue(TString* iValue); // Set value
	void SetValue(TString& iValue); // Set value
	void SetValue(INT32 iValue); // Set value
	void SetValue(UINT32 iValue); // Set value
	void SetValue(INT64 iValue); // Set value
	void SetValue(UINT64 iValue); // Set value
	void SetValue(DOUBLE iValue, INT32 iDecimalPlaces = 6, CHAR iDecimalPointChar = '.'); // Set value
	void SetSharedValue(PCHAR iValue, INT64 iLength = -1); // Set shared value
	void SetRandomBASE64Value(INT64 iLength); // Set random BASE64 string value
public:
	CONST_PCHAR PChar(void); // Get value
	INT32 AsINT32(void); // Get value
	UINT32 AsUINT32(void); // Get value
	INT64 AsINT64(void); // Get value
	UINT64 AsUINT64(void); // Get value
	DOUBLE AsDOUBLE(void); // Get value
public:
	INT32 Compare(CONST_PCHAR iValue, INT64 iStart = 0, INT64 iMaxLength = -1); // Compare with a value
	INT32 Compare(TString* iValue, INT64 iStart = 0, INT64 iMaxLength = -1); // Compare with a value
	INT32 Compare(TString& iValue, INT64 iStart = 0, INT64 iMaxLength = -1); // Compare with a value
	INT32 CaseCompare(CONST_PCHAR iValue, INT64 iStart = 0, INT64 iMaxLength = -1, INT32 iCodePage = 28591); // Compare with a value case insensitive
	INT32 CaseCompare(TString* iValue, INT64 iStart = 0, INT64 iMaxLength = -1, INT32 iCodePage = 28591); // Compare with a value case insensitive
	INT32 CaseCompare(TString& iValue, INT64 iStart = 0, INT64 iMaxLength = -1, INT32 iCodePage = 28591); // Compare with a value case insensitive
public:
	void AppendValue(CONST_PCHAR iValue, INT64 iLength = -1); // Append value to the end
	void AppendValue(TString& iValue); // Append value to the end
	void AppendValue(TString* iValue); // Append value to the end
	void AppendValue(INT32 iValue); // Append value to the end
	void AppendValue(UINT32 iValue); // Append value to the end
	void AppendValue(INT64 iValue); // Append value to the end
	void AppendValue(UINT64 iValue); // Append value to the end
	void AppendValue(DOUBLE iValue, INT32 iDecimalPlaces = 6, CHAR iDecimalPointChar = '.'); // Append value to the end
	void AppendChars(CHAR iValue, INT64 iCount = 1, BOOL iAppendOnlyIfNotExists = false); // Append chars to the end
public:
	void ToLowercase(INT32 iCodePage = 28591); // Convert to lower case
	void ToUppercase(INT32 iCodePage = 28591); // Convert to upper case
	void Format(CONST_PCHAR iFormattedString, ...); // Format the string
	UINT64 GetHashCode(void); // Get hash code of the string
	UINT64 GetCaseHashCode(INT32 iCodePage = 28591); // Get hash code of the string case insensitive
public:
	INT64 FindChar(CHAR iValue, INT64 iStartIndex = 0, INT64 iMaxCharsCount = -1, INT64 iOccurrenceIndex = 1); // Find character in the string
	INT64 CaseFindChar(CHAR iValue, INT64 iStartIndex = 0, INT64 iMaxCharsCount = -1, INT64 iOccurrenceIndex = 1, INT32 iCodePage = 28591); // Find character in the string case insensitive
	INT64 ReverseFindChar(CHAR iValue, INT64 iStartIndex = -1, INT64 iMaxCharsCount = -1, INT64 iOccurrenceIndex = 1); // Find character in the string in reverse order
	INT64 ReverseCaseFindChar(CHAR iValue, INT64 iStartIndex = -1, INT64 iMaxCharsCount = -1, INT64 iOccurrenceIndex = 1, INT32 iCodePage = 28591); // Find character in the string case insensitive in reverse order
public:
	void Substring(TString* oSubstr, INT64 iStartIndex, INT64 iLength = -1); // Get substring
	void LeftSubstring(TString* oSubstr, INT64 iLength = -1); // Get substring from the left side
	void RightSubstring(TString* oSubstr, INT64 iLength = -1); // Get substring from the right side
	void Trim(CHAR iTrimChar = ' '); // Trim the string
	void LeftTrim(CHAR iTrimChar = ' '); // Trim the string from the left side
	void RightTrim(CHAR iTrimChar = ' '); // Trim the string from the right side
public:
	void SetLength(INT64 iLength); // Set the length of the string
public:
	static INT64 GenerateRandomBASE64String(PCHAR oBuffer, INT64 iLength); // Generate a random BASE64 string
};
//	...............................................................................................
