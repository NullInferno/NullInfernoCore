#pragma once

//	...............................................................................................
//	Class TStringList
//	...............................................................................................
class TStringList {
private:
	TList* FItems; // List of strings objects
public:
	TStringList(void); // Constructor
	~TStringList(void); // Destructor
public:
	void Clear(void); // Clear the list and free memory
	void CreateCopy(TStringList* iSourceList); // Create a copy of another string list
public:
	INT64 Count(void); // Get number of strings in the list
	TString* Item(INT64 iIndex); // Get string at specified index
	BOOL IsEqual(TStringList* iOtherList); // Check equality with another string list
public:
	INT64 Add(CONST_PCHAR iValue, INT64 iLength = -1); // Add string to the end of the list
	INT64 Add(TString* iValue); // Add string to the end of the list
	INT64 Insert(INT64 iIndex, CONST_PCHAR iValue, INT64 iLength = -1); // Insert string at specified index
	INT64 Insert(INT64 iIndex, TString* iValue); // Insert string at specified index
	void Delete(INT64 iIndex, INT64 iCount); // Delete strings from specified index
	void DeleteValue(CONST_PCHAR iValue, BOOL iAllOccurences = false); // Delete strings by value
	void DeleteValue(TString* iValue, BOOL iAllOccurences = false); // Delete strings by value
public:
	INT64 Find(CONST_PCHAR iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified string
	INT64 Find(TString* iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified string
	INT64 CaseFind(CONST_PCHAR iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified string case insensitive
	INT64 CaseFind(TString* iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified string case insensitive
	INT64 ReverseFind(CONST_PCHAR iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified string searching backwards
	INT64 ReverseFind(TString* iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified string searching backwards
	INT64 ReverseCaseFind(CONST_PCHAR iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified string searching backwards case insensitive
	INT64 ReverseCaseFind(TString* iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified string searching backwards case insensitive
	INT64 BinaryFindFirst(CONST_PCHAR iValue); // Find index of the first occurrence of the specified string using binary search (list must be sorted)
	INT64 BinaryFindFirst(TString* iValue); // Find index of the first occurrence of the specified string using binary search (list must be sorted)
	INT64 BinaryFindLast(CONST_PCHAR iValue); // Find index of the last occurrence of the specified string using binary search (list must be sorted)
	INT64 BinaryFindLast(TString* iValue); // Find index of the last occurrence of the specified string using binary search (list must be sorted)
public:
	void Sort(BOOL iAscending = true); // Sort the string list
public:
	PCHAR* CreatePCharArray(void); // Create an array of PCHAR strings from the string list
};
//	...............................................................................................
