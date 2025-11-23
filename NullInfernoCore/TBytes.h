#pragma once

//	...............................................................................................
//	Class TBytes
//	...............................................................................................
class TBytes {
private:
	INT64 FCapacity; // Capacity of allocated memory
public:
	PBYTE Value; // Content
	INT64 Count; // Length of current content
public:
	TBytes(void); // Constructor
	TBytes(CONST_PBYTE iValue, INT64 iBytesCount); // Constructor
	TBytes(TBytes* iValue); // Constructor
	TBytes(TBytes& iValue); // Constructor
	~TBytes(void); // Destructor
public:
	CONST_PBYTE PByte(void); // Get value
	UINT64 GetHashCode(void); // Get hash code of the data
public:
	void Release(void); // Release the memory
	BOOL Reallocate(INT64 iNewCapacity, BOOL iKeepContent = false); // Reallocate the memory
public:
	void SetValue(CONST_PBYTE iValue, INT64 iBytesCount); // Set value
	void SetValue(TBytes* iValue); // Set value
	void SetValue(TBytes& iValue); // Set value
	void SetSharedValue(PBYTE iValue, INT64 iBytesCount); // Set shared value
	void SetRandomBytes(INT64 iBytesCount); // Set random bytes
	void SetCount(INT64 iBytesCount); // Set count
	void SetBytes(BYTE iValue, INT64 iBytesCount); // Set bytes to a specific value
public:
	INT64 AppendBytes(CONST_PBYTE iValue, INT64 iBytesCount); // Add bytes to the end
	INT64 InsertBytes(INT64 iIndex, CONST_PBYTE iValue, INT64 iBytesCount); // Insert bytes at position
public:
	INT32 Compare(CONST_PBYTE iValue, INT64 iStartIndex = 0, INT64 iMaxBytesCount = -1); // Compare with a value
public:
	static INT64 GenerateRandomBytes(PBYTE oBytes, INT64 iBytesCount); // Generate random bytes
};
//	...............................................................................................
