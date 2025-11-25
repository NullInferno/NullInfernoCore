#include "NullInfernoCore.h"
#include "TBytes.h"

//	................................................................................................
//  Generate random bytes
//	Input:
//			oBytes - output buffer
// 			iBytesCount - number of bytes to generate
//	Output:
//			number of bytes generated
//	................................................................................................
INT64 TBytes::GenerateRandomBytes(PBYTE oBytes, INT64 iBytesCount) {
	PBYTE P = (PBYTE)oBytes; PBYTE E = P + iBytesCount; // P - current position, E - end position
	while (P < E) { // While there is space in the buffer
		UINT64 U = TEnvironment::GenerateRandomUINT64(); // Get random UINT64
		*P++ = (BYTE)(U & 0xFF); U >>= 8; if (P >= E) break; // Extract bytes one by one
		*P++ = (BYTE)(U & 0xFF); U >>= 8; if (P >= E) break;
		*P++ = (BYTE)(U & 0xFF); U >>= 8; if (P >= E) break;
		*P++ = (BYTE)(U & 0xFF); U >>= 8; if (P >= E) break;
		*P++ = (BYTE)(U & 0xFF); U >>= 8; if (P >= E) break;
		*P++ = (BYTE)(U & 0xFF); U >>= 8; if (P >= E) break;
		*P++ = (BYTE)(U & 0xFF); U >>= 8; if (P >= E) break;
		*P++ = (BYTE)(U & 0xFF);
	}
	return iBytesCount; // Return the size of the byte array
}
//	................................................................................................
//	................................................................................................
//  Constructor
//	Input:
//			none
//	Output:
//			none
//	................................................................................................
TBytes::TBytes(void) {
	FCapacity = 0; Value = NULL; Count = 0; // Initialize members
}
//	................................................................................................
//	................................................................................................
//  Constructor
//	Input:
//			iValue - value to set
// 			iBytesCount - number of bytes to set
//	Output:
//			none
//	................................................................................................
TBytes::TBytes(CONST_PBYTE iValue, INT64 iBytesCount) {
	FCapacity = 0; Value = NULL; Count = 0; // Initialize members
	SetValue(iValue, iBytesCount); // Set the value
}
//	................................................................................................
//	................................................................................................
//  Constructor
//	Input:
//			iValue - value to set
//	Output:
//			none
//	................................................................................................
TBytes::TBytes(TBytes* iValue) {
	FCapacity = 0; Value = NULL; Count = 0; // Initialize members
	SetValue(iValue); // Set the value
}
//	................................................................................................
//	................................................................................................
//  Constructor
//	Input:
//			iValue - value to set
//	Output:
//			none
//	................................................................................................
TBytes::TBytes(TBytes& iValue) {
	FCapacity = 0; Value = NULL; Count = 0; // Initialize members
	SetValue(iValue); // Set the value
}
//	................................................................................................
//	................................................................................................
//  Destructor
//	Input:
//			none
//	Output:
//			none
//	................................................................................................
TBytes::~TBytes(void) {
	Release(); // Release the memory
}
//	................................................................................................
//	................................................................................................
//  Get value
//	Input:
//			none
//	Output:
//			pointer to the byte array or NULL if count is zero
//	................................................................................................
CONST_PBYTE TBytes::PByte(void) {
	return FCapacity == 0 ? NULL : (CONST_PBYTE)Value;
}
//	................................................................................................
//	................................................................................................
//   Get hash code of the data
//	Input:
//			none
//	Output:
//			hash code
//	................................................................................................
UINT64 TBytes::GetHashCode(void) {
	return Count == 0 ? 0 : GenerateHash64(Value, Count); // Generate hash code
}
//	................................................................................................
//	................................................................................................
//  Release the memory
//	Input:
//			none
//	Output:
//			none
//	................................................................................................
void TBytes::Release(void) {
	if ((Value != NULL) && (FCapacity > 0)) MEMORY_FREE(Value); // Free the memory
	FCapacity = 0; Value = NULL; Count = 0; // Initialize members
}
//	................................................................................................
//	................................................................................................
//  Reallocate the memory
//	Input:
//			iNewCapacity - new capacity
// 			iKeepContent - whether to keep the current content
//	Output:
//			true / false
//	................................................................................................
BOOL TBytes::Reallocate(INT64 iNewCapacity, BOOL iKeepContent) {
	if (iNewCapacity <= FCapacity) return true; // No need to reallocate?
	INT64 NewCapacity = ALIGN16(iNewCapacity); // Align to 16 bytes
	PBYTE NewValue = (PBYTE)MEMORY_ALLOC(NewCapacity); // Allocate new memory
	if (NewValue == NULL) return false; // Allocation failed?
	if ((iKeepContent) && (Count > 0)) { // Copy content?
		FNC_MEMCPY(NewValue, Value, Count); // Copy the content
	}
	if (FCapacity > 0) MEMORY_FREE(Value); // Free old memory
	FCapacity = NewCapacity; Value = NewValue; // Update members

	return true; // Success
}
//	................................................................................................
//	................................................................................................
//  Set value
//	Input:
//			iValue - value to set
// 			iBytesCount - number of bytes to set
//	Output:
//			none
//	................................................................................................
void TBytes::SetValue(CONST_PVOID iValue, INT64 iBytesCount) {
	if ((iBytesCount <= 0) || (iValue == NULL)) { // Empty byte array?
		Count = 0; // Set count to zero
		return;
	}
	if (Reallocate(iBytesCount, false)) { // Reallocate memory
		FNC_MEMCPY(Value, iValue, iBytesCount); // Copy the content
		Count = iBytesCount; // Set count
	}
}
//	................................................................................................
//	................................................................................................
//  Set value
//	Input:
//			iValue - value to set
//	Output:
//			none
//	................................................................................................
void TBytes::SetValue(TBytes* iValue) {
	if (iValue == NULL) Count = 0; // NULL value?
	else SetValue(iValue->Value, iValue->Count); // Set the value
}
//	................................................................................................
//	................................................................................................
//  Set value
//	Input:
//			iValue - value to set
//	Output:
//			none
//	................................................................................................
void TBytes::SetValue(TBytes& iValue) {
	SetValue(iValue.Value, iValue.Count); // Set the value
}
//	................................................................................................
//	................................................................................................
//  Set shared value
//	Input:
//			iValue - value to set
// 			iBytesCount - number of bytes to set
//	Output:
//			none
//	................................................................................................
void TBytes::SetSharedValue(PBYTE iValue, INT64 iBytesCount) {
	Release(); // Release current memory
	if ((iValue == NULL) || (iBytesCount <= 0)) { // Empty byte array?
		Count = 0; // Set count to zero
		return;
	}
	Value = iValue;
	Count = iBytesCount; // Set count
}
//	................................................................................................
//	................................................................................................
//  Set random bytes
//	Input:
// 			iBytesCount - number of bytes to set
//	Output:
//			none
//	................................................................................................
void TBytes::SetRandomBytes(INT64 iBytesCount) {
	if (iBytesCount <= 0) Count = 0; // Empty byte array?
	else {
		if (Reallocate(iBytesCount, false)) { // Reallocate memory
			GenerateRandomBytes(Value, iBytesCount); // Generate random bytes
			Count = iBytesCount; // Set count
		}
	}
}
//	................................................................................................
//	................................................................................................
//  Set count
//	Input:
// 			iBytesCount - new count
//	Output:
//			none
//	................................................................................................
void TBytes::SetCount(INT64 iBytesCount) {
	if (IS_INDEX_OUT(iBytesCount, 0, FCapacity)) return; // Is new count out of current capacity?
	Count = iBytesCount; // Set new count
}
//	................................................................................................
//	................................................................................................
//  Set bytes to a specific value
//	Input:
// 			iValue - value to set
// 			iBytesCount - new count
//	Output:
//			none
//	................................................................................................
void TBytes::SetBytes(BYTE iValue, INT64 iBytesCount) {
	if (iBytesCount <= 0) Count = 0; // Empty byte array?
	else {
		if (Reallocate(iBytesCount, false)) { // Reallocate memory
			FNC_MEMSET(Value, iValue, iBytesCount); // Set bytes to the specified value
			Count = iBytesCount; // Set count
		}
	}
}
//	................................................................................................
//	................................................................................................
//  Append bytes to the end
//	Input:
//			iValue - value to append
// 			iBytesCount - number of bytes to append
//	Output:
//			position of the first appended byte or -1 on error
//	................................................................................................
INT64 TBytes::AppendBytes(CONST_PBYTE iValue, INT64 iBytesCount) {
	if ((iValue == NULL) || (iBytesCount <= 0)) return -1; // Nothing to append?

	if (!Reallocate(Count + iBytesCount, true)) return -1; // Reallocate memory

	FNC_MEMCPY(Value + Count, iValue, iBytesCount); // Copy the content
	Count += iBytesCount; // Update count
	return Count - iBytesCount; // Return position of the first appended byte
}
//	................................................................................................
//	................................................................................................
//  Insert bytes at position
//	Input:
//			iValue - value to insert
// 			iBytesCount - number of bytes to insert
//	Output:
//			position of the first inserted byte or -1 on error
//	................................................................................................
INT64 TBytes::InsertBytes(INT64 iIndex, CONST_PBYTE iValue, INT64 iBytesCount) {
	if ((iValue == NULL) || (iBytesCount <= 0)) return -1; // Nothing to append?

	if (iIndex < 0) iIndex = 0; // Adjust index
	if (iIndex >= Count) return AppendBytes(iValue, iBytesCount); // Append to the end

	if (!Reallocate(Count + iBytesCount, true)) return -1; // Reallocate memory
	FNC_MEMMOVE(Value + iIndex + iBytesCount, Value + iIndex, Count - iIndex); // Shift existing bytes to the right
	FNC_MEMCPY(Value + iIndex, iValue, iBytesCount); // Copy the content
	Count += iBytesCount; // Update count
	return iIndex; // Return position of the first inserted byte
}
//	................................................................................................
//	................................................................................................
//  Generate random bytes
//	Input:
//			iValue - value to compare with
// 			iStartIndex - start index for comparison
// 			iMaxBytesCount - maximum number of bytes to compare or -1 for full length
//	Output:
//			0 if equal, <0 if less, >0 if greater
//	................................................................................................
INT32 TBytes::Compare(CONST_PBYTE iValue, INT64 iStartIndex, INT64 iMaxBytesCount) {
	if ((iValue == NULL) || (iMaxBytesCount == 0)) return Count == 0 ? 0 : 1; // NULL value?
	if (Count == 0) return -1; // Empty content?
	if (iStartIndex < 0) iStartIndex = 0; // Adjust start index
	if (iStartIndex >= Count) return Count == 0 ? 0 : -1; // Start index beyond the content?

	if (iMaxBytesCount < 0) iMaxBytesCount = Count - iStartIndex; // Adjust max bytes count
	return FNC_MEMCMP(Value + iStartIndex, iValue, (MIN(Count - iStartIndex, iMaxBytesCount)));	
}
//	................................................................................................
//	................................................................................................
//  Generate random bytes
//	Input:
//			iValue - value to compare with
// 			iStartIndex - start index for comparison
// 			iMaxBytesCount - maximum number of bytes to compare or -1 for full length
//	Output:
//			0 if equal, <0 if less, >0 if greater
//	................................................................................................
INT32 TBytes::Compare(TBytes* iValue, INT64 iStartIndex, INT64 iMaxBytesCount) {
	if (iValue == NULL) return Count == 0 ? 0 : 1; // NULL value?
	return Compare(iValue->Value, iStartIndex, iMaxBytesCount < 0 ? iValue->Count : MIN(iValue->Count, iMaxBytesCount)); // Compare with the value
}
//	................................................................................................
