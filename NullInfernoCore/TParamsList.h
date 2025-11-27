#pragma once

enum TParamType {
	PTYPE_NONE = 0,
	PTYPE_INT32 = 1,
	PTYPE_UINT32 = 2,
	PTYPE_INT64 = 3,
	PTYPE_UINT64 = 4,
	PTYPE_DOUBLE = 5,
	PTYPE_BOOL = 6,
	PTYPE_DATETIME = 7,
	PTYPE_STRING = 8,
	PTYPE_BYTES = 9,
	PTYPE_PARAMSLIST = 10
};

//	...............................................................................................
// Class TParamsList
//	...............................................................................................
class TParamsList {
private:
	PVOID FParams; // Parameters memory
	INT64 FCapacity; // Capacity of allocated memory
	INT64 FCount; // Number of parameters
	BOOL FIgnoreCase; // Ignore case for parameter names
private:
	BOOL Reallocate(INT64 iNewCapacity, BOOL iKeepContent = false); // Reallocate the memory
	CONST_PVOID FindParamEntry(CONST_PCHAR iName); // Find parameter entry by name
	CONST_PVOID FindParamEntry(UINT64 iID); // Find parameter entry by ID
	CONST_PVOID AddParamEntry(CONST_PCHAR iName, TParamType iType); // Add parameter entry
	CONST_PVOID AddParamEntry(UINT64 iID, TParamType iType); // Add parameter entry
	void ClearParamEntry(CONST_PVOID iParamEntry); // Clear parameter entry
public:
	TParamsList(BOOL iIgnoreCase = true); // Constructor
	TParamsList(TParamsList* iSource); // Constructor
	~TParamsList(void); // Destructor
public:
	void Release(void); // Release the memory
	void Clear(void); // Clear all parameters
	void CreateCopy(TParamsList* iSource); // Create a copy of another parameters list
public:
	void Serialize(TBytes* oBytes); // Serialize parameters to bytes
	void Deserialize(TBytes* iBytes); // Deserialize parameters from bytes
public:
	INT64 Count(void); // Get number of parameters
	BOOL IsEqual(TParamsList* iOtherList); // Check equality with another parameters list
	BOOL ParamExists(CONST_PCHAR iName); // Check if parameter exists
public:
	void SetParam_INT32(CONST_PCHAR iName, INT32 iValue, PVOID iUserData = NULL); // Set INT32 parameter
	void SetParam_UINT32(CONST_PCHAR iName, UINT32 iValue, PVOID iUserData = NULL); // Set UINT32 parameter
	void SetParam_INT64(CONST_PCHAR iName, INT64 iValue, PVOID iUserData = NULL); // Set INT64 parameter
	void SetParam_UINT64(CONST_PCHAR iName, UINT64 iValue, PVOID iUserData = NULL); // Set UINT64 parameter
	void SetParam_DOUBLE(CONST_PCHAR iName, DOUBLE iValue, PVOID iUserData = NULL); // Set DOUBLE parameter
	void SetParam_BOOL(CONST_PCHAR iName, BOOL iValue, PVOID iUserData = NULL); // Set BOOL parameter
	void SetParam_DATETIME(CONST_PCHAR iName, DATETIME iValue, PVOID iUserData = NULL); // Set DATETIME parameter
	void SetParam_DATETIME(CONST_PCHAR iName, TDateTime* iValue, PVOID iUserData = NULL); // Set DATETIME parameter
	void SetParam_STRING(CONST_PCHAR iName, CONST_PCHAR iValue, PVOID iUserData = NULL); // Set STRING parameter
	void SetParam_STRING(CONST_PCHAR iName, TString* iValue, PVOID iUserData = NULL); // Set STRING parameter
	void SetParam_BYTES(CONST_PCHAR iName, CONST_PVOID iValue, INT64 iLength, PVOID iUserData = NULL); // Set BYTES parameter
	void SetParam_BYTES(CONST_PCHAR iName, TBytes *iValue, PVOID iUserData = NULL); // Set BYTES parameter
	void SetParam_ParamsList(CONST_PCHAR iName, TParamsList* iValue, PVOID iUserData = NULL); // Set PARAMSLIST parameter
public:
	INT32 GetParam_INT32(CONST_PCHAR iName, INT32 iDefaultValue = 0); // Get INT32 parameter
	UINT32 GetParam_UINT32(CONST_PCHAR iName, UINT32 iDefaultValue = 0); // Get UINT32 parameter
	INT64 GetParam_INT64(CONST_PCHAR iName, INT64 iDefaultValue = 0); // Get INT64 parameter
	UINT64 GetParam_UINT64(CONST_PCHAR iName, UINT64 iDefaultValue = 0); // Get UINT64 parameter
	DOUBLE GetParam_DOUBLE(CONST_PCHAR iName, DOUBLE iDefaultValue = 0); // Get DOUBLE parameter
	BOOL GetParam_BOOL(CONST_PCHAR iName, BOOL iDefaultValue = false); // Get BOOL parameter
	DATETIME GetParam_DATETIME(CONST_PCHAR iName, DATETIME iDefaultValue = DATETIME_EMPTY); // Get DATETIME parameter
	void GetParam_DATETIME(CONST_PCHAR iName, TDateTime* oResult, DATETIME iDefaultValue = DATETIME_EMPTY); // Get DATETIME parameter
	void GetParam_STRING(CONST_PCHAR iName, TString *oResult, CONST_PCHAR iDefaultValue = ""); // Get STRING parameter
	void GetParam_BYTES(CONST_PCHAR iName, TBytes* oResult); // Get BYTES parameter
	void GetParam_ParamsList(CONST_PCHAR iName, TParamsList* oResult); // Get PARAMSLIST parameter
	PVOID GetParam_UserData(CONST_PCHAR iName); // Get parameter user data
public:
	INT32 TryGetParam_INT32(CONST_PCHAR iName, INT32 iDefaultValue = 0); // Get INT32 parameter or try convert
	UINT32 TryGetParam_UINT32(CONST_PCHAR iName, UINT32 iDefaultValue = 0); // Get UINT32 parameter or try convert
	INT64 TryGetParam_INT64(CONST_PCHAR iName, INT64 iDefaultValue = 0); // Get INT64 parameter or try convert
	UINT64 TryGetParam_UINT64(CONST_PCHAR iName, UINT64 iDefaultValue = 0); // Get UINT64 parameter or try convert
	DOUBLE TryGetParam_DOUBLE(CONST_PCHAR iName, DOUBLE iDefaultValue = 0); // Get DOUBLE parameter or try convert
	BOOL TryGetParam_BOOL(CONST_PCHAR iName, BOOL iDefaultValue = false); // Get BOOL parameter or try convert
	DATETIME TryGetParam_DATETIME(CONST_PCHAR iName, DATETIME iDefaultValue = DATETIME_EMPTY); // Get DATETIME parameter or try convert
	void TryGetParam_DATETIME(CONST_PCHAR iName, TDateTime* oResult, DATETIME iDefaultValue = DATETIME_EMPTY); // Get DATETIME parameter or try convert
	void TryGetParam_STRING(CONST_PCHAR iName, TString* oResult, CONST_PCHAR iDefaultValue = ""); // Get STRING parameter or try convert
};
//	...............................................................................................
