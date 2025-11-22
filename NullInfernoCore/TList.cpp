#include "NullInfernoCore.h"
#include "TList.h"

//	...............................................................................................
//	Constructor
//	Input:
// 			iCapacityIncrement - capacity increment step
//	Output:
//			none
//	...............................................................................................
TList::TList(INT64 iFCapacityIncrement) {
	FCapacity = FCount = 0; FValues = NULL; // Initialize variables
	FCapacityIncrement = (iFCapacityIncrement < 1) ? 16 : iFCapacityIncrement; // Set capacity increment step
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TList::~TList(void) {
	Clear(NULL); // Clear the list and free memory
}
//	...............................................................................................
//	...............................................................................................
//	Clear the list and free memory
//	Input:
// 			iNotifyFunction - notification function called for each item
//	Output:
//			none
//	...............................................................................................
void TList::Clear(TListNotifyFunction iNotifyFunction) {
	if (iNotifyFunction != NULL) { // Is notification function is specified?
		for (INT64 i = 0; i < FCount; i++) iNotifyFunction(FValues[i], i); // Call notification function
	}
	if (FValues != NULL) MEMORY_FREE(FValues); // Free memory
	FCapacity = FCount = 0; FValues = NULL; // Initialize variables
}
//	...............................................................................................
//	...............................................................................................
//	Reallocate memory for the list
//	Input:
// 			iNewCapacity - new capacity of the list
// 			iKeepContent - keep existing content flag
//	Output:
//			true / false
//	...............................................................................................
BOOL TList::Reallocate(INT64 iNewCapacity, BOOL iKeepContent) {
	if (iNewCapacity <= FCapacity) return true; // Is new capacity less than or equal to current capacity?

	INT64 NewCapacity = ((iNewCapacity / FCapacityIncrement) + 1)* FCapacityIncrement; // Calculate new capacity aligned FCapacityIncrement
	PVOID* NewValues = (PVOID*)MEMORY_ALLOC(NewCapacity * sizeof(PVOID)); // Allocate memory for new values
	if (NewValues == NULL) return false; // Is memory allocation failed?

	if ((iKeepContent) && (FCount > 0)) { // Is existing content should be kept?
		FNC_MEMCPY(NewValues, FValues, FCount * sizeof(PVOID)); // Copy existing content to new memory
	}

	MEMORY_FREE(FValues); // Free old memory
	FValues = NewValues; // Set new values pointer
	FCapacity = NewCapacity; // Set new capacity

	return true; // Success
}
//	...............................................................................................
//	...............................................................................................
//	Set number of elements in the list
//	Input:
// 			iNewCount - New number of elements
// 			iNotifyFunction - notification function called for each item
//	Output:
//			none
//	...............................................................................................
void TList::SetCount(INT64 iNewCount, TListNotifyFunction iNotifyFunction) {
	if (IS_INDEX_OUT(iNewCount, 0, FCount)) return; // Is new count out of current capacity?
	if (iNotifyFunction != NULL) { // Is notification function is specified?
		for (INT64 i = iNewCount; i < FCount; i++) iNotifyFunction(FValues[i], i); // Call notification function
	}
	FCount = iNewCount; // Set new count
}
//	...............................................................................................
//	...............................................................................................
//	Set capacity increment step
//	Input:
// 			iFCapacityIncrement - capacity increment step
//	Output:
//			none
//	...............................................................................................
void TList::SetCapacityIncrement(INT64 iFCapacityIncrement) {
	FCapacityIncrement = (iFCapacityIncrement < 1) ? 16 : iFCapacityIncrement; // Set capacity increment step
}
//	...............................................................................................
//	...............................................................................................
//	Create a copy of another list
//	Input:
// 			iSourceList - pointer to source list
//	Output:
//			none
//	...............................................................................................
void TList::CreateCopy(TList* iSourceList) {
	if ((iSourceList == NULL) || (iSourceList->FCount < 1)) { // Is source list is NULL or empty?
		SetCount(0);
		return; 
	}
	if (Reallocate(iSourceList->FCount, false)) { // Reallocate memory
		FNC_MEMCPY(FValues, iSourceList->FValues, iSourceList->FCount * sizeof(PVOID)); // Copy values
		FCount = iSourceList->FCount; // Set count
	}
}
//	...............................................................................................
//	...............................................................................................
//	Get number of elements in the list
//	Input:
// 			none
//	Output:
//			number of elements
//	...............................................................................................
INT64 TList::Count(void) {
	return FCount;
}
//	...............................................................................................
//	...............................................................................................
//	Get item at specified index
//	Input:
// 			iIndex - index of the item
// 			iDefaultValue - default value pointer
//	Output:
//			item at specified index or default value
//	...............................................................................................
PVOID TList::Item(INT64 iIndex, PVOID iDefaultValue) {
	return IS_INDEX_IN(iIndex, 0, FCount) ? FValues[iIndex] : iDefaultValue;
}
//	...............................................................................................
//	...............................................................................................
//	Get item at specified index as INT32
//	Input:
// 			iIndex - index of the item
// 			iDefaultValue - default value
//	Output:
//			item at specified index or default value
//	...............................................................................................
INT32 TList::ItemAsINT32(INT64 iIndex, INT32 iDefaultValue) {
	return IS_INDEX_IN(iIndex, 0, FCount) ? (INT32)(intptr_t)FValues[iIndex] : iDefaultValue;
}
//	...............................................................................................
//	...............................................................................................
//	Get item at specified index as UINT32
//	Input:
// 			iIndex - index of the item
// 			iDefaultValue - default value
//	Output:
//			item at specified index or default value
//	...............................................................................................
UINT32 TList::ItemAsUINT32(INT64 iIndex, UINT32 iDefaultValue) {
	return IS_INDEX_IN(iIndex, 0, FCount) ? (UINT32)(uintptr_t)FValues[iIndex] : iDefaultValue;
}
//	...............................................................................................
//	...............................................................................................
//	Get item at specified index as INT64
//	Input:
// 			iIndex - index of the item
// 			iDefaultValue - default value
//	Output:
//			item at specified index or default value
//	...............................................................................................
INT64 TList::ItemAsINT64(INT64 iIndex, INT64 iDefaultValue) {
	return IS_INDEX_IN(iIndex, 0, FCount) ? (INT64)FValues[iIndex] : iDefaultValue;
}
//	...............................................................................................
//	...............................................................................................
//	Get item at specified index as UINT64
//	Input:
// 			iIndex - index of the item
// 			iDefaultValue - default value
//	Output:
//			item at specified index or default value
//	...............................................................................................
UINT64 TList::ItemAsUINT64(INT64 iIndex, UINT64 iDefaultValue) {
	return IS_INDEX_IN(iIndex, 0, FCount) ? (UINT64)FValues[iIndex] : iDefaultValue;
}
//	...............................................................................................
//	...............................................................................................
//	Set item at specified index
//	Input:
// 			iIndex - position to set the item at
// 			iValue - value to set
//			iNotifyFunction - notification function
//	Output:
//			none
//	...............................................................................................
void TList::SetItem(INT64 iIndex, PVOID iValue, TListNotifyFunction iNotifyFunction) {
	if (IS_INDEX_IN(iIndex, 0, FCount)) { // Is index is valid?
		if (iNotifyFunction != NULL) iNotifyFunction(FValues[iIndex], iIndex); // Call notification function
		FValues[iIndex] = iValue; // Set value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set item at specified index
//	Input:
// 			iIndex - position to set the item at
// 			iValue - value to set
//			iNotifyFunction - notification function
//	Output:
//			none
//	...............................................................................................
void TList::SetItem(INT64 iIndex, INT32 iValue, TListNotifyFunction iNotifyFunction) {
	SetItem(iIndex, (PVOID)(intptr_t)iValue, iNotifyFunction); // Set as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Set item at specified index
//	Input:
// 			iIndex - position to set the item at
// 			iValue - value to set
//			iNotifyFunction - notification function
//	Output:
//			none
//	...............................................................................................
void TList::SetItem(INT64 iIndex, UINT32 iValue, TListNotifyFunction iNotifyFunction) {
	SetItem(iIndex, (PVOID)(uintptr_t)iValue, iNotifyFunction); // Set as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Set item at specified index
//	Input:
// 			iIndex - position to set the item at
// 			iValue - value to set
//			iNotifyFunction - notification function
//	Output:
//			none
//	...............................................................................................
void TList::SetItem(INT64 iIndex, INT64 iValue, TListNotifyFunction iNotifyFunction) {
	SetItem(iIndex, (PVOID)iValue, iNotifyFunction); // Set as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Set item at specified index
//	Input:
// 			iIndex - position to set the item at
// 			iValue - value to set
//			iNotifyFunction - notification function
//	Output:
//			none
//	...............................................................................................
void TList::SetItem(INT64 iIndex, UINT64 iValue, TListNotifyFunction iNotifyFunction) {
	SetItem(iIndex, (PVOID)iValue, iNotifyFunction); // Set as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Add item to the end of the list
//	Input:
// 			iValue - value to add
//	Output:
//			position of the added item or -1 on error
//	...............................................................................................
INT64 TList::Add(PVOID iValue) {
	if (Reallocate(FCount + 1, true)) {
		FValues[FCount] = iValue; // Set new value
		FCount++; // Increase count
		return FCount - 1; // Return position of the added item
	}
	return -1; // Error
}
//	...............................................................................................
//	...............................................................................................
//	Add INT32 value to the end of the list
//	Input:
// 			iValue - INT32 value to add
//	Output:
//			position of the added item or -1 on error
//	...............................................................................................
INT64 TList::Add(INT32 iValue) {
	return Add((PVOID)(intptr_t)iValue); // Add as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Add UINT32 value to the end of the list
//	Input:
// 			iValue - UINT32 value to add
//	Output:
//			position of the added item or -1 on error
//	...............................................................................................
INT64 TList::Add(UINT32 iValue) {
	return Add((PVOID)(uintptr_t)iValue); // Add as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Add INT64 value to the end of the list
//	Input:
// 			iValue - INT64 value to add
//	Output:
//			position of the added item or -1 on error
//	...............................................................................................
INT64 TList::Add(INT64 iValue) {
	return Add((PVOID)iValue); // Add as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Add UINT64 value to the end of the list
//	Input:
// 			iValue - UINT64 value to add
//	Output:
//			position of the added item or -1 on error
//	...............................................................................................
INT64 TList::Add(UINT64 iValue) {
	return Add((PVOID)iValue); // Add as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Add all items from another list to the end of this list
//	Input:
// 			iList - pointer to another TList instance
//	Output:
//			position of the first added item or -1 on error
//	...............................................................................................
INT64 TList::AddList(TList* iList) {
	if (iList == NULL) return -1; // Is input list is NULL?
	if (iList->FCount == 0) return FCount; // Is input list is empty?

	if (Reallocate(FCount + iList->FCount, true)) {
		FNC_MEMCPY(FValues + FCount, iList->FValues, iList->FCount * sizeof(PVOID)); // Copy items from input list
		FCount += iList->FCount; // Increase count
		return FCount - iList->FCount; // Return position of the added item
	}
	return -1; // Error
}
//	...............................................................................................
//	...............................................................................................
//	Insert item at specified index
//	Input:
// 			iIndex - index to insert the item at
// 			iValue - value to insert
//	Output:
//			position of the inserted item or -1 on error
//	...............................................................................................
INT64 TList::Insert(INT64 iIndex, PVOID iValue) {
	if (IS_INDEX_OUT(iIndex, 0, FCount)) return Add(iValue); // Index is out of range, add to the end
	if (Reallocate(FCount + 1, true)) {
		FNC_MEMMOVE(&FValues[iIndex + 1], &FValues[iIndex], (FCount - iIndex) * sizeof(PVOID)); // Shift items to the right
		FValues[iIndex] = iValue; // Set new value
		FCount++; // Increase count
		return iIndex; // Return position of the added item
	}
	return -1; // Error
}
//	...............................................................................................
//	...............................................................................................
//	Insert INT32 value at specified index
//	Input:
// 			iIndex - index to insert the INT32 value at
// 			iValue - INT32 value to insert
//	Output:
//			position of the inserted item or -1 on error
//	...............................................................................................
INT64 TList::Insert(INT64 iIndex, INT32 iValue) {
	return Insert(iIndex, (PVOID)(intptr_t)iValue); // Insert as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Insert UINT32 value at specified index
//	Input:
// 			iIndex - index to insert the UINT32 value at
// 			iValue - UINT32 value to insert
//	Output:
//			position of the inserted item or -1 on error
//	...............................................................................................
INT64 TList::Insert(INT64 iIndex, UINT32 iValue) {
	return Insert(iIndex, (PVOID)(uintptr_t)iValue); // Insert as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Insert INT64 value at specified index
//	Input:
// 			iIndex - index to insert the INT64 value at
// 			iValue - INT64 value to insert
//	Output:
//			position of the inserted item or -1 on error
//	...............................................................................................
INT64 TList::Insert(INT64 iIndex, INT64 iValue) {
	return Insert(iIndex, (PVOID)iValue); // Insert as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Insert UINT64 value at specified index
//	Input:
// 			iIndex - index to insert the UINT64 value at
// 			iValue - UINT64 value to insert
//	Output:
//			position of the inserted item or -1 on error
//	...............................................................................................
INT64 TList::Insert(INT64 iIndex, UINT64 iValue) {
	return Insert(iIndex, (PVOID)iValue); // Insert as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Insert all items from another list at specified index
//	Input:
// 			iIndex - index to insert the items at
// 			iList - pointer to another TList instance
//	Output:
//			position of the first inserted item or -1 on error
//	...............................................................................................
INT64 TList::InsertList(INT64 iIndex, TList* iList) {
	if (iList == NULL) return -1; // Is input list is NULL?

	if (IS_INDEX_OUT(iIndex, 0, FCount)) return AddList(iList); // Index is out of range, add to the end
	if (iList->FCount == 0) return iIndex; // Is input list is empty?

	if (Reallocate(FCount + iList->FCount, true)) {
		FNC_MEMCPY(&FValues[iIndex + iList->FCount], &FValues[iIndex], (FCount - iIndex) * sizeof(PVOID)); // Shift items to the right
		FNC_MEMCPY(&FValues[iIndex], iList->FValues, iList->FCount * sizeof(PVOID)); // Copy items from input list
		FCount += iList->FCount; // Increase count
		return iIndex; // Return position of the added item
	}
	return -1; // Error
}
//	...............................................................................................
//	...............................................................................................
//	Delete item at specified index
//	Input:
// 			iIndex - index to delete the item at
// 			iNotifyFunction - notification function called for the deleted item
//	Output:
//			none
//	...............................................................................................
void TList::Delete(INT64 iIndex, TListNotifyFunction iNotifyFunction) {
	if (IS_INDEX_OUT(iIndex, 0, FCount)) return; // Is index out of range?
	if (iNotifyFunction != NULL) iNotifyFunction(FValues[iIndex], iIndex); // Call notification function
	FNC_MEMMOVE(&FValues[iIndex], &FValues[iIndex + 1], (FCount - iIndex - 1) * sizeof(PVOID)); // Shift items to the left
	FCount--; // Decrease count
}
//	...............................................................................................
//	...............................................................................................
//	Delete range of items
//	Input:
// 			iStart - start index of the range
// 			iCount - number of items to delete (-1 means all items till the end)
// 			iNotifyFunction - notification function called for each deleted item
//	Output:
//			none
//	...............................................................................................
void TList::DeleteRange(INT64 iStart, INT64 iCount, TListNotifyFunction iNotifyFunction) {
	if (iStart < 0) iStart = 0; // Adjust start index
	if (iStart >= FCount) return; // Is start index out of range?
	INT64 CountToDelete = (iCount < 0) ? (FCount - iStart) : (MIN(iCount, FCount - iStart)); // Calculate number of items to delete
	if (iNotifyFunction != NULL) { // Is notification function is specified?
		for (INT64 i = 0; i < CountToDelete; i++) iNotifyFunction(FValues[i], i + iStart); // Call notification function
	}
	if (CountToDelete == FCount) SetCount(0); // Is all items are deleted?
	else {
		FNC_MEMMOVE(&FValues[iStart], &FValues[iStart + CountToDelete], (FCount - iStart - CountToDelete) * sizeof(PVOID)); // Shift items to the left
		FCount -= CountToDelete; // Decrease count
	}
}
//	...............................................................................................
//	...............................................................................................
//	Delete items with specified value
//	Input:
// 			iValue - value to delete
// 			iMaxRemovals - maximum number of items to delete (<= 0 means all occurrences)
// 			iNotifyFunction - notification function called for the deleted item
//	Output:
//			none
//	...............................................................................................
void TList::DeleteValue(PVOID iValue, INT64 iMaxRemovals, TListNotifyFunction iNotifyFunction) {
	if (iMaxRemovals <= 0) iMaxRemovals = FCount; // No removals required
	INT64 FirstIndex;
	
	for (FirstIndex = 0; FirstIndex < FCount; FirstIndex++) { // Find first occurrence
		if (FValues[FirstIndex] == iValue) break; // Value found?
	}
	if (FirstIndex >= FCount) return; // Value not found?

	INT64 CurrIndex = FirstIndex;
	for (; FirstIndex < FCount; FirstIndex++) {
		if (FValues[FirstIndex] == iValue) { // Value found?
			if (iNotifyFunction != NULL) iNotifyFunction(FValues[FirstIndex], FirstIndex); // Call notification function
			if (--iMaxRemovals == 0) {
				if (FirstIndex < FCount - 1) { // Are there remaining items?
					FNC_MEMMOVE(&FValues[CurrIndex], &FValues[FirstIndex + 1], (FCount - FirstIndex - 1) * sizeof(PVOID)); // Shift remaining items to the left
				}
				FCount = CurrIndex + (FCount - FirstIndex - 1); // Update count
				return;
			}
		}
		else {
			FValues[CurrIndex++] = FValues[FirstIndex]; // Keep the item
		}
	}
	FCount = CurrIndex; // Update count
}
//	...............................................................................................
//	...............................................................................................
//	Delete items with specified value
//	Input:
// 			iValue - value to delete
// 			iMaxRemovals - maximum number of items to delete (<= 0 means all occurrences)
// 			iNotifyFunction - notification function called for the deleted item
//	Output:
//			none
//	...............................................................................................
void TList::DeleteValue(INT32 iValue, INT64 iMaxRemovals, TListNotifyFunction iNotifyFunction) {
	DeleteValue((PVOID)(intptr_t)iValue, iMaxRemovals, iNotifyFunction); // Delete as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Delete items with specified value
//	Input:
// 			iValue - value to delete
// 			iMaxRemovals - maximum number of items to delete (<= 0 means all occurrences)
// 			iNotifyFunction - notification function called for the deleted item
//	Output:
//			none
//	...............................................................................................
void TList::DeleteValue(UINT32 iValue, INT64 iMaxRemovals, TListNotifyFunction iNotifyFunction) {
	DeleteValue((PVOID)(uintptr_t)iValue, iMaxRemovals, iNotifyFunction); // Delete as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Delete items with specified value
//	Input:
// 			iValue - value to delete
// 			iMaxRemovals - maximum number of items to delete (<= 0 means all occurrences)
// 			iNotifyFunction - notification function called for the deleted item
//	Output:
//			none
//	...............................................................................................
void TList::DeleteValue(INT64 iValue, INT64 iMaxRemovals, TListNotifyFunction iNotifyFunction) {
	DeleteValue((PVOID)iValue, iMaxRemovals, iNotifyFunction); // Delete as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Delete items with specified value
//	Input:
// 			iValue - value to delete
// 			iMaxRemovals - maximum number of items to delete (<= 0 means all occurrences)
// 			iNotifyFunction - notification function called for the deleted item
//	Output:
//			none
//	...............................................................................................
void TList::DeleteValue(UINT64 iValue, INT64 iMaxRemovals, TListNotifyFunction iNotifyFunction) {
	DeleteValue((PVOID)iValue, iMaxRemovals, iNotifyFunction); // Delete as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified item
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from
// 			iMaxCount - maximum number of items to search (<0 means all items till the end)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::Find(PVOID iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	if (iStartIndex < 0) iStartIndex = 0; // Adjust start index
	if (iStartIndex >= FCount) return -1; // Is start index out of range?

	INT64 C = iMaxCount < 0 ? (FCount - iStartIndex) : (MIN(iMaxCount, FCount - iStartIndex)); // Calculate number of items to search
	for (INT64 i = 0; i < C; i++) {
		if (FValues[iStartIndex + i] == iValue) { // Value found?
			if (--iOccurrenceIndex == 0) return iStartIndex + i; // Is this the required occurrence?
		}
	}
	return -1; // Not found
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified item
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from
// 			iMaxCount - maximum number of items to search (<0 means all items till the end)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::Find(INT32 iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return Find((PVOID)(intptr_t)iValue, iStartIndex, iMaxCount, iOccurrenceIndex); // Find as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified item
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from
// 			iMaxCount - maximum number of items to search (<0 means all items till the end)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::Find(UINT32 iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return Find((PVOID)(uintptr_t)iValue, iStartIndex, iMaxCount, iOccurrenceIndex); // Find as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified item
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from
// 			iMaxCount - maximum number of items to search (<0 means all items till the end)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::Find(INT64 iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return Find((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex); // Find as pointer
}
//	...............................................................................................
//	...............................................................................................
//	Find index of the specified item
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from
// 			iMaxCount - maximum number of items to search (<0 means all items till the end)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::Find(UINT64 iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return Find((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex); // Find as pointer
}
//	...............................................................................................
//	...............................................................................................
//	// Find index of the specified item in reverse order
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from (<0 means from the end)
// 			iMaxCount - maximum number of items to search (<0 means all items till the beginning)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::ReverseFind(PVOID iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	if (FCount == 0) return -1; // Is the list empty?
	if ((iStartIndex < 0) || (iStartIndex >= FCount)) iStartIndex = FCount - 1; // Adjust start index

	INT64 C = iMaxCount < 0 ? iStartIndex + 1 : (MIN(iMaxCount, iStartIndex + 1)); // Calculate number of items to search
	for (INT64 i = 0; i < C; i++) {
		if (FValues[iStartIndex - i] == iValue) { // Value found?
			if (--iOccurrenceIndex == 0) return iStartIndex - i; // Is this the required occurrence?
		}
	}
	return -1; // Not found
}
//	...............................................................................................
//	...............................................................................................
//	// Find index of the specified item in reverse order
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from (<0 means from the end)
// 			iMaxCount - maximum number of items to search (<0 means all items till the beginning)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::ReverseFind(INT32 iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return ReverseFind((PVOID)(intptr_t)iValue, iStartIndex, iMaxCount, iOccurrenceIndex); // Find as pointer
}
//	...............................................................................................
//	...............................................................................................
//	// Find index of the specified item in reverse order
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from (<0 means from the end)
// 			iMaxCount - maximum number of items to search (<0 means all items till the beginning)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::ReverseFind(UINT32 iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return ReverseFind((PVOID)(uintptr_t)iValue, iStartIndex, iMaxCount, iOccurrenceIndex); // Find as pointer
}
//	...............................................................................................
//	...............................................................................................
//	// Find index of the specified item in reverse order
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from (<0 means from the end)
// 			iMaxCount - maximum number of items to search (<0 means all items till the beginning)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::ReverseFind(INT64 iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return ReverseFind((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex); // Find as pointer
}
//	...............................................................................................
//	...............................................................................................
//	// Find index of the specified item in reverse order
//	Input:
// 			iValue - value to find
// 			iStartIndex - start index to search from (<0 means from the end)
// 			iMaxCount - maximum number of items to search (<0 means all items till the beginning)
// 			iOccurrenceIndex - occurrence index to find (1 means first occurrence, 2 means second occurrence, etc.)
//	Output:
//			position of the found item or -1 if not found
//	...............................................................................................
INT64 TList::ReverseFind(UINT64 iValue, INT64 iStartIndex, INT64 iMaxCount, INT64 iOccurrenceIndex) {
	return ReverseFind((PVOID)iValue, iStartIndex, iMaxCount, iOccurrenceIndex); // Find as pointer
}
//	...............................................................................................
