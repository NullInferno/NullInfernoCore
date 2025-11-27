#pragma once

typedef void (*TListNotifyFunction)(PVOID iItem, INT64 iIndex); // Function prototype for list notification functions
typedef INT32(*TListCompareItemsFunction)(PVOID iItem1, PVOID iItem2); // Function prototype for item comparison functions
typedef INT32(*TListBinarySearchCompareFunction)(PVOID iSearchValue, PVOID iItem); // Function prototype for binary search comparison functions

//	................................................................................................
//	Class TList
//	................................................................................................
class TList {
private:
	INT64 FCapacity; // Capacity of the list
	PVOID* FValues; // Pointer to the list values
	INT64 FCount; // Number of elements in the list
	INT64 FCapacityIncrement; // Capacity increment step
public:
	TList(INT64 iFCapacityIncrement = 16); // Constructor
	~TList(void); // Destructor
public:
	void Clear(TListNotifyFunction iNotifyFunction = NULL); // Clear the list and free memory
	BOOL Reallocate(INT64 iNewCapacity, BOOL iKeepContent = false); // Reallocate memory for the list
	void SetCount(INT64 iNewCount, TListNotifyFunction iNotifyFunction = NULL); // Set number of elements in the list
	void SetCapacityIncrement(INT64 iFCapacityIncrement); // Set capacity increment step
	void CreateCopy(TList* iSourceList); // Create a copy of another list
	void Sort(TListCompareItemsFunction iCompareFunction); // Sort the list using the specified comparison function
public:
	INT64 Count(void); // Get number of elements in the list
	PVOID Item(INT64 iIndex, PVOID iDefaultValue = NULL); // Get item at specified index
	INT32 ItemAsINT32(INT64 iIndex, INT32 iDefaultValue = 0); // Get item at specified index as INT32
	UINT32 ItemAsUINT32(INT64 iIndex, UINT32 iDefaultValue = 0); // Get item at specified index as UINT32
	INT64 ItemAsINT64(INT64 iIndex, INT64 iDefaultValue = 0); // Get item at specified index as INT64
	UINT64 ItemAsUINT64(INT64 iIndex, UINT64 iDefaultValue = 0); // Get item at specified index as UINT64
public:
	void SetItem(INT64 iIndex, PVOID iValue, TListNotifyFunction iNotifyFunction = NULL); // Set item at specified index
	void SetItem(INT64 iIndex, INT32 iValue, TListNotifyFunction iNotifyFunction = NULL); // Set item at specified index
	void SetItem(INT64 iIndex, UINT32 iValue, TListNotifyFunction iNotifyFunction = NULL); // Set item at specified index
	void SetItem(INT64 iIndex, INT64 iValue, TListNotifyFunction iNotifyFunction = NULL); // Set item at specified index
	void SetItem(INT64 iIndex, UINT64 iValue, TListNotifyFunction iNotifyFunction = NULL); // Set item at specified index
public:
	INT64 Add(PVOID iValue); // Add item to the end of the list
	INT64 Add(INT32 iValue); // Add INT32 value to the end of the list
	INT64 Add(UINT32 iValue); // AddUINT32 value to the end of the list
	INT64 Add(INT64 iValue); // Add INT64 value to the end of the list
	INT64 Add(UINT64 iValue); // Add UINT64 valueto the end of the list
	INT64 AddList(TList* iList); // Add all items from another list to the end of this list
	INT64 Insert(INT64 iIndex, PVOID iValue); // Insert item at specified index
	INT64 Insert(INT64 iIndex, INT32 iValue); // Insert INT32 value at specified index
	INT64 Insert(INT64 iIndex, UINT32 iValue); // Insert UINT32 value at specified index
	INT64 Insert(INT64 iIndex, INT64 iValue); // Insert INT64 value at specified index
	INT64 Insert(INT64 iIndex, UINT64 iValue); // Insert UINT64 value at specified index
	INT64 InsertList(INT64 iIndex, TList* iList); // Insert all items from another list at specified index
	void Delete(INT64 iIndex, TListNotifyFunction iNotifyFunction = NULL); // Delete item at specified index
	void DeleteRange(INT64 iStart, INT64 iCount = -1, TListNotifyFunction iNotifyFunction = NULL); // Delete range of items
	void DeleteValue(PVOID iValue, INT64 iMaxRemovals = -1, TListNotifyFunction iNotifyFunction = NULL, TListBinarySearchCompareFunction iCompareFunction = NULL); // Delete items with specified value
	void DeleteValue(INT32 iValue, INT64 iMaxRemovals = -1, TListNotifyFunction iNotifyFunction = NULL); // Delete items with specified value
	void DeleteValue(UINT32 iValue, INT64 iMaxRemovals = -1, TListNotifyFunction iNotifyFunction = NULL); // Delete items with specified value
	void DeleteValue(INT64 iValue, INT64 iMaxRemovals = -1, TListNotifyFunction iNotifyFunction = NULL); // Delete items with specified value
	void DeleteValue(UINT64 iValue, INT64 iMaxRemovals = -1, TListNotifyFunction iNotifyFunction = NULL); // Delete items with specified value
public:
	INT64 Find(PVOID iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1, TListBinarySearchCompareFunction iCompareFunction = NULL); // Find index of the specified item
	INT64 Find(INT32 iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified item
	INT64 Find(UINT32 iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified item
	INT64 Find(INT64 iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified item
	INT64 Find(UINT64 iValue, INT64 iStartIndex = 0, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified item
	INT64 ReverseFind(PVOID iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1, TListBinarySearchCompareFunction iCompareFunction = NULL); // Find index of the specified item in reverse order
	INT64 ReverseFind(INT32 iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified item in reverse order
	INT64 ReverseFind(UINT32 iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified item in reverse order
	INT64 ReverseFind(INT64 iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified item in reverse order
	INT64 ReverseFind(UINT64 iValue, INT64 iStartIndex = -1, INT64 iMaxCount = -1, INT64 iOccurrenceIndex = 1); // Find index of the specified item in reverse order
	INT64 BinaryFindFirst(PVOID iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the first occurence of specified item of a sorted list using binary search
	INT64 BinaryFindFirst(INT32 iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the first occurence of specified item of a sorted list using binary search
	INT64 BinaryFindFirst(UINT32 iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the first occurence of specified item of a sorted list using binary search
	INT64 BinaryFindFirst(INT64 iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the first occurence of specified item of a sorted list using binary search
	INT64 BinaryFindFirst(UINT64 iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the first occurence of specified item of a sorted list using binary search
	INT64 BinaryFindLast(PVOID iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the last occurence of specified item of a sorted list using binary search
	INT64 BinaryFindLast(INT32 iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the last occurence of specified item of a sorted list using binary search
	INT64 BinaryFindLast(UINT32 iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the last occurence of specified item of a sorted list using binary search
	INT64 BinaryFindLast(INT64 iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the last occurence of specified item of a sorted list using binary search
	INT64 BinaryFindLast(UINT64 iValue, TListBinarySearchCompareFunction iCompareFunction); // Find index of the last occurence of specified item of a sorted list using binary search
};
//	................................................................................................
