#include "NullInfernoCore.h"
#include "TStringList.h"

//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TStringList::TStringList(void) {
	FItems = new TList(); // Create the list object
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TStringList::~TStringList(void) {
	Clear(); // Clear the list and free memory
	delete FItems; // Delete the list object
}
//	...............................................................................................
//	...............................................................................................
//	Clear the list and free memory
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TStringList::Clear(void) {
	FItems->Clear([](PVOID iItem, INT64 iIndex) {
		delete (TString*)iItem;
		});
}
//	...............................................................................................
//	...............................................................................................
//	Create a copy of another string list
//	Input:
// 			iSourceList - source string list to copy
//	Output:
//			none
//	...............................................................................................
void TStringList::CreateCopy(TStringList* iSourceList) {
	Clear(); // Clear the current list
	for (INT64 i = 0; i < iSourceList->Count(); i++) { 	// Copy items from the source list
		TString* srcString = iSourceList->Item(i);
		FItems->Add(new TString(srcString)); // Add a copy of the string to the list
	}
}
//	...............................................................................................
//	...............................................................................................
//	Get number of strings in the list
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
INT64 TStringList::Count(void) {
	return FItems->Count();
}
//	...............................................................................................
//	...............................................................................................
//	Get string at specified index
//	Input:
// 			iIndex - index of the string to get
//	Output:
//			string at specified index or NULL if index is out of bounds
//	...............................................................................................
TString* TStringList::Item(INT64 iIndex) {
	return (TString*)FItems->Item(iIndex, NULL); // Get item from the list
}
//	...............................................................................................
//	...............................................................................................
//	Check equality with another string list
//	Input:
// 			iOtherList - other string list to compare with
//	Output:
//			true / false
//	...............................................................................................
BOOL TStringList::IsEqual(TStringList* iOtherList) {
	if (iOtherList == NULL) return false;
	
	if (FItems->Count() != iOtherList->Count()) return false; // Different number of items
	for (INT64 i = 0; i < FItems->Count(); i++) {
		TString* str1 = (TString*)FItems->Item(i);
		TString* str2 = iOtherList->Item(i);
		if (str1->Compare(str2) != 0) return false; // Items are different
	}
	return true; // Lists are equal
}
//	...............................................................................................
//	...............................................................................................
//	Add string to the end of the list
//	Input:
// 			iValue - string value to add
// 			iLength - length of the string to add or -1 to calculate length automatically
//	Output:
//			position of the added string in the list
//	...............................................................................................
INT64 TStringList::Add(CONST_PCHAR iValue, INT64 iLength) {
	return FItems->Add(new TString(iValue, iLength)); // Add new string to the list
}
//	...............................................................................................
//	...............................................................................................
//	Add string to the end of the list
//	Input:
// 			iValue - string value to add
//	Output:
//			position of the added string in the list
//	...............................................................................................
INT64 TStringList::Add(TString* iValue) {
	return FItems->Add(new TString(iValue)); // Add new string to the list
}
//	...............................................................................................
//	...............................................................................................
//	Insert string at specified index
//	Input:
// 			iIndex - index at which to insert the string
// 			iValue - string value to insert
// 			iLength - length of the string to add or -1 to calculate length automatically
//	Output:
//			position of the added string in the list
//	...............................................................................................
INT64 TStringList::Insert(INT64 iIndex, CONST_PCHAR iValue, INT64 iLength) {
	return FItems->Insert(iIndex, new TString(iValue, iLength)); // Insert new string to the list
}
//	...............................................................................................
//	...............................................................................................
//	Insert string at specified index
//	Input:
// 			iIndex - index at which to insert the string
// 			iValue - string value to insert
//	Output:
//			position of the added string in the list
//	...............................................................................................
INT64 TStringList::Insert(INT64 iIndex, TString* iValue) {
	return FItems->Insert(iIndex, new TString(iValue)); // Insert new string to the list
}
//	...............................................................................................
//	...............................................................................................
//	Delete strings from specified index
//	Input:
// 			iIndex - index at which to start deleting strings
// 			iCount - number of strings to delete
//	Output:
//			none
//	...............................................................................................
void TStringList::Delete(INT64 iIndex, INT64 iCount) {
	FItems->DeleteRange(iIndex, iCount, [](PVOID iItem, INT64 iIndex) {
		delete (TString*)iItem;
		});
}
//	...............................................................................................
//	...............................................................................................
//	Delete strings by value
//	Input:
// 			iValue - string value to delete
// 			iAllOccurences - if TRUE, delete all occurences of the string, otherwise delete only the first occurence
//	Output:
//			none
//	...............................................................................................
void TStringList::DeleteValue(CONST_PCHAR iValue, BOOL iAllOccurences) {
	FItems->DeleteValue((PVOID)iValue, iAllOccurences ? -1 : 1, [](PVOID iItem, INT64 iIndex) {
		delete (TString*)iItem;
		}, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
			return ((TString*)iItem)->Compare((CONST_PCHAR) iSearchValue);
			});
}
//	...............................................................................................
//	...............................................................................................
//	Delete strings by value
//	Input:
// 			iValue - string value to delete
// 			iAllOccurences - if TRUE, delete all occurences of the string, otherwise delete only the first occurence
//	Output:
//			none
//	...............................................................................................
void TStringList::DeleteValue(TString* iValue, BOOL iAllOccurences) {
	FItems->DeleteValue((PVOID)iValue, iAllOccurences ? -1 : 1, [](PVOID iItem, INT64 iIndex) {
		delete (TString*)iItem;
		}, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
			return ((TString*)iItem)->Compare((TString*)iSearchValue);
			});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified string
//	Input:
// 			iValue - string value to find
// 			iStartIndex - index at which to start searching
// 			iMaxCount - maximum number of items to search or -1 to search all items until the end of the list
// 			iOccurrenceIndex - occurrence index to find (1 = first occurrence, 2 = second occurrence, etc.)
//	Output:
//			index of the found string or -1 if not found
//	...............................................................................................
INT64 TStringList::Find(CONST_PCHAR iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return FItems->Find((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iItem)->Compare((CONST_PCHAR)iSearchValue);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified string
//	Input:
// 			iValue - string value to find
// 			iStartIndex - index at which to start searching
// 			iMaxCount - maximum number of items to search or -1 to search all items until the end of the list
// 			iOccurrenceIndex - occurrence index to find (1 = first occurrence, 2 = second occurrence, etc.)
//	Output:
//			index of the found string or -1 if not found
//	...............................................................................................
INT64 TStringList::Find(TString* iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return FItems->Find((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iItem)->Compare((TString*)iSearchValue);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified string case insensitive
//	Input:
// 			iValue - string value to find
// 			iStartIndex - index at which to start searching
// 			iMaxCount - maximum number of items to search or -1 to search all items until the end of the list
// 			iOccurrenceIndex - occurrence index to find (1 = first occurrence, 2 = second occurrence, etc.)
//	Output:
//			index of the found string or -1 if not found
//	...............................................................................................
INT64 TStringList::CaseFind(CONST_PCHAR iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return FItems->Find((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iItem)->CaseCompare((CONST_PCHAR)iSearchValue);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified string searching backwards
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from (<0 means from the end)
// 			iMaxCount - maximum number of items to search (<0 means all items till the beginning)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TStringList::CaseFind(TString* iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return FItems->Find((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iItem)->CaseCompare((TString*)iSearchValue);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified string case insensitive
//	Input:
// 			iValue - string value to find
// 			iStartIndex - index at which to start searching
// 			iMaxCount - maximum number of items to search or -1 to search all items until the end of the list
// 			iOccurrenceIndex - occurrence index to find (1 = first occurrence, 2 = second occurrence, etc.)
//	Output:
//			index of the found string or -1 if not found
//	...............................................................................................
INT64 TStringList::ReverseFind(CONST_PCHAR iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return FItems->ReverseFind((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iItem)->Compare((CONST_PCHAR)iSearchValue);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified string case insensitive
//	Input:
// 			iValue - string value to find
// 			iStartIndex - index at which to start searching
// 			iMaxCount - maximum number of items to search or -1 to search all items until the end of the list
// 			iOccurrenceIndex - occurrence index to find (1 = first occurrence, 2 = second occurrence, etc.)
//	Output:
//			index of the found string or -1 if not found
//	...............................................................................................
INT64 TStringList::ReverseFind(TString* iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return FItems->ReverseFind((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iItem)->Compare((TString*)iSearchValue);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified string case insensitive case insensitive
//	Input:
// 			iValue - string value to find
// 			iStartIndex - index at which to start searching
// 			iMaxCount - maximum number of items to search or -1 to search all items until the end of the list
// 			iOccurrenceIndex - occurrence index to find (1 = first occurrence, 2 = second occurrence, etc.)
//	Output:
//			index of the found string or -1 if not found
//	...............................................................................................
INT64 TStringList::ReverseCaseFind(CONST_PCHAR iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return FItems->ReverseFind((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iItem)->CaseCompare((CONST_PCHAR)iSearchValue);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified string case insensitive case insensitive
//	Input:
// 			iValue - string value to find
// 			iStartIndex - index at which to start searching
// 			iMaxCount - maximum number of items to search or -1 to search all items until the end of the list
// 			iOccurrenceIndex - occurrence index to find (1 = first occurrence, 2 = second occurrence, etc.)
//	Output:
//			index of the found string or -1 if not found
//	...............................................................................................
INT64 TStringList::ReverseCaseFind(TString* iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return FItems->ReverseFind((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iItem)->CaseCompare((TString*)iSearchValue);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the first occurence of specified item of a sorted list using binary search
//	Input:
// 			iValue - value to find
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TStringList::BinaryFindFirst(CONST_PCHAR iValue) {
	return FItems->BinaryFindFirst((PVOID)iValue, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iSearchValue)->Compare((CONST_PCHAR)iItem);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the first occurence of specified item of a sorted list using binary search
//	Input:
// 			iValue - value to find
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TStringList::BinaryFindFirst(TString* iValue) {
	return FItems->BinaryFindFirst((PVOID)iValue, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iSearchValue)->Compare((TString*)iItem);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the last occurence of specified item of a sorted list using binary search
//	Input:
// 			iValue - value to find
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TStringList::BinaryFindLast(CONST_PCHAR iValue) {
	return FItems->BinaryFindLast((PVOID)iValue, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iSearchValue)->Compare((CONST_PCHAR)iItem);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the last occurence of specified item of a sorted list using binary search
//	Input:
// 			iValue - value to find
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TStringList::BinaryFindLast(TString* iValue) {
	return FItems->BinaryFindLast((PVOID)iValue, [](PVOID iSearchValue, PVOID iItem) -> INT32 {
		return ((TString*)iSearchValue)->Compare((TString*)iItem);
		});
}
//	...............................................................................................
//	...............................................................................................
//	Sort the string list
//	Input:
// 			iAscending - if TRUE, sort in ascending order, otherwise sort in descending order
//	Output:
//			none
//	...............................................................................................
void TStringList::Sort(BOOL iAscending) {
	if (iAscending) {
		FItems->Sort([](PVOID iItem1, PVOID iItem2) -> INT32 {
			return ((TString*)iItem1)->Compare((TString*)iItem2);
			});
	}
	else {
		FItems->Sort([](PVOID iItem1, PVOID iItem2) -> INT32 {
			return -((TString*)iItem1)->Compare((TString*)iItem2);
			});
	}
}
//	...............................................................................................
//	...............................................................................................
//	Create an array of PCHAR strings from the string list
//	Input:
// 			none
//	Output:
//			array of PCHAR strings or NULL on failure
//	...............................................................................................
PCHAR* TStringList::CreatePCharArray(void) {
	if (FItems->Count() == 0) return NULL;
	PCHAR* Result = (PCHAR*)MEMORY_ALLOC(FItems->Count() * sizeof(PCHAR));
	if (Result != NULL) {
		for (INT64 i = 0; i < FItems->Count(); i++) {
			TString* Str = (TString*)FItems->Item(i);
			Result[i] = (PCHAR)Str->PChar();
		}
	}
	return Result;
}
//	...............................................................................................
