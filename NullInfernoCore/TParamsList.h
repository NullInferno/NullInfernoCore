#pragma once

enum TParamType {
	PTYPE_NONE = 0,
	PTYPE_INT32 = 1,
	PTYPE_UINT32 = 2,
	PTYPE_INT64 = 3,
	PTYPE_UINT64 = 4,
	PTYPE_DOUBLE = 5,
	PTYPE_STRING = 6,
	PTYPE_BOOL = 7,
	PTYPE_DATETIME = 8,
	PTYPE_BYTES = 9
};

//	...............................................................................................
// Class TParamsList
//	...............................................................................................
class TParamsList {
private:
	PVOID FParams; // Parameters memory
	INT64 FCapacity; // Capacity of allocated memory
	INT64 FCount; // Number of parameters
private:
	BOOL Reallocate(INT64 iNewCapacity, BOOL iKeepContent = false); // Reallocate the memory
	CONST_PVOID FindParamEntry(CONST_PCHAR iName); // Find parameter entry by name
	CONST_PVOID AddParamEntry(CONST_PCHAR iName, TParamType iType); // Add parameter entry
	void ClearParamEntry(CONST_PVOID iParamEntry); // Clear parameter entry
public:
	TParamsList(void); // Constructor
	~TParamsList(void); // Destructor
public:
	void Release(void); // Release the memory
	void Clear(void); // Clear all parameters
public:
	INT64 Count(void); // Get number of parameters
public:
	void SetParam_INT32(CONST_PCHAR iName, INT32 iValue); // Set INT32 parameter
	void SetParam_UINT32(CONST_PCHAR iName, UINT32 iValue); // Set UINT32 parameter
	void SetParam_INT64(CONST_PCHAR iName, INT64 iValue); // Set INT64 parameter
	void SetParam_UINT64(CONST_PCHAR iName, UINT64 iValue); // Set UINT64 parameter
	void SetParam_DOUBLE(CONST_PCHAR iName, DOUBLE iValue); // Set DOUBLE parameter
	void SetParam_BOOL(CONST_PCHAR iName, BOOL iValue); // Set BOOL parameter
	void SetParam_DATETIME(CONST_PCHAR iName, DATETIME iValue); // Set DATETIME parameter
	void SetParam_STRING(CONST_PCHAR iName, CONST_PCHAR iValue); // Set STRING parameter
	void SetParam_STRING(CONST_PCHAR iName, TString* iValue); // Set STRING parameter
	void SetParam_BYTES(CONST_PCHAR iName, CONST_PBYTE iValue, INT64 iLength); // Set BYTES parameter
	void SetParam_BYTES(CONST_PCHAR iName, TBytes *iValue); // Set BYTES parameter
public:
	INT32 GetParam_INT32(CONST_PCHAR iName, INT32 iDefaultValue = 0); // Get INT32 parameter
	UINT32 GetParam_UINT32(CONST_PCHAR iName, UINT32 iDefaultValue = 0); // Get UINT32 parameter
	INT64 GetParam_INT64(CONST_PCHAR iName, INT64 iDefaultValue = 0); // Get INT64 parameter
	UINT64 GetParam_UINT64(CONST_PCHAR iName, UINT64 iDefaultValue = 0); // Get UINT64 parameter
	DOUBLE GetParam_DOUBLE(CONST_PCHAR iName, DOUBLE iDefaultValue = 0); // Get DOUBLE parameter
	BOOL GetParam_BOOL(CONST_PCHAR iName, BOOL iDefaultValue = false); // Get BOOL parameter
	DATETIME GetParam_DATETIME(CONST_PCHAR iName, DATETIME iDefaultValue = DATETTIME_EMPTY); // Get DATETIME parameter
	void GetParam_STRING(CONST_PCHAR iName, TString *oResult, CONST_PCHAR iDefaultValue = ""); // Get STRING parameter
	void GetParam_BYTES(CONST_PCHAR iName, TBytes* oResult); // Get BYTES parameter
};
//	...............................................................................................
