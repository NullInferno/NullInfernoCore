#include "NullInfernoCore.h"
#include "TParamsList.h"

typedef struct {
	UINT64 ID;
	enum TParamType Type;
	union {
		INT32 ValueAsINT32;
		UINT32 ValueAsUINT32;
		INT64 ValueAsINT64;
		UINT64 ValueAsUINT64;
		DOUBLE ValueAsDOUBLE;
		BOOL ValueAsBOOL;
		DATETIME ValueAsDATETIME;
		TString* ValueAsSTRING;
		TBytes* ValueAsBYTES;
		TParamsList* ValueAsPARAMSLIST;
	} Data;
} PARAM_ENTRY, * PPARAM_ENTRY;

//	...............................................................................................
//	Reallocate the memory
//	Input:
// 			iNewCapacity - new capacity
// 			iKeepContent - whether to keep the current content
//	Output:
//			true / false
//	...............................................................................................
BOOL TParamsList::Reallocate(INT64 iNewCapacity, BOOL iKeepContent) {
	if (iNewCapacity <= FCapacity) return true; // No need to reallocate?
	
	INT64 NewCapacity = ALIGN128(iNewCapacity); // Align to 128 bytes
	PPARAM_ENTRY NewParams = (PPARAM_ENTRY)MEMORY_ALLOC(NewCapacity * sizeof(PARAM_ENTRY)); // Allocate new memory
	if (NewParams == NULL) return false; // Allocation failed?

	if ((iKeepContent) && (FCount > 0)) { // Copy content?
		FNC_MEMCPY(NewParams, FParams, FCount * sizeof(PARAM_ENTRY)); // Copy the content
	}

	MEMORY_FREE(FParams); // Free old memory
	FParams = NewParams; FCapacity = NewCapacity; // Update members

	return true; // Success
}
//	...............................................................................................
//	...............................................................................................
//	Find parameter entry by name
//	Input:
// 			iName - parameter name
//	Output:
//			pointer to parameter entry or NULL if not found
//	...............................................................................................
CONST_PVOID TParamsList::FindParamEntry(CONST_PCHAR iName) {
	UINT64 NameID = TString::GenerateCaseHashCode(iName); // Generate name ID
	for (INT64 i = 0; i < FCount; i++) { // Search all parameters
		PPARAM_ENTRY PE = &((PPARAM_ENTRY)FParams)[i]; // Get parameter entry
		if (PE->ID == NameID) return PE; // Found?
	}
	return NULL; // Not found
}
//	...............................................................................................
//	...............................................................................................
//	Add parameter entry
//	Input:
// 			iName - parameter name
// 			iType - parameter type
//	Output:
//			pointer to new parameter entry or NULL if failed
//	...............................................................................................
CONST_PVOID TParamsList::AddParamEntry(CONST_PCHAR iName, TParamType iType) {
	if (!Reallocate(FCount + 1, true)) return NULL; // Reallocate memory if needed
	PPARAM_ENTRY PE = &((PPARAM_ENTRY)FParams)[FCount]; // Get parameter entry
	PE->ID = TString::GenerateCaseHashCode(iName); // Generate name ID
	PE->Type = iType; // Set parameter type
	FCount++; // Increase the count
	return PE; // Return the parameter entry
}
//	...............................................................................................
//	...............................................................................................
//	Clear parameter entry
//	Input:
// 			iParamEntry - parameter entry pointer
//	Output:
//			none
//	...............................................................................................
void TParamsList::ClearParamEntry(CONST_PVOID iParamEntry) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)iParamEntry; // Get parameter entry
	if (PE->Type == PTYPE_STRING) { // String parameter?
		if (PE->Data.ValueAsSTRING != NULL) {
			delete PE->Data.ValueAsSTRING; // Delete the string
			PE->Data.ValueAsSTRING = NULL;
		}
	}
	else if (PE->Type == PTYPE_BYTES) { // Bytes parameter?
		if (PE->Data.ValueAsBYTES != NULL) {
			delete PE->Data.ValueAsBYTES; // Delete the bytes
			PE->Data.ValueAsBYTES = NULL;
		}
	}
	else if (PE->Type == PTYPE_PARAMSLIST) { // Bytes parameter?
		if (PE->Data.ValueAsPARAMSLIST != NULL) {
			delete PE->Data.ValueAsPARAMSLIST; // Delete the bytes
			PE->Data.ValueAsPARAMSLIST = NULL;
		}
	}
	PE->Type = PTYPE_NONE; // Reset the type
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TParamsList::TParamsList(void) {
	FParams = NULL; FCount = FCapacity = 0; // Initialize members
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iSource - source parameters list
//	Output:
//			none
//	...............................................................................................
TParamsList::TParamsList(TParamsList* iSource) {
	FParams = NULL; FCount = FCapacity = 0; // Initialize members
	CreateCopy(iSource); // Create a copy of the source parameters list
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TParamsList::~TParamsList(void) {
	Release(); // Release the memory
}
//	...............................................................................................
//	...............................................................................................
//	Release the memory
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TParamsList::Release(void) {
	Clear(); // Clear all parameters
	if (FParams != NULL) MEMORY_FREE(FParams); // Free the memory
	FParams = NULL; FCount = FCapacity = 0; // Initialize members
}
//	...............................................................................................
//	...............................................................................................
//	Clear all parameters
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TParamsList::Clear(void) {
	for (INT64 i = 0; i < FCount; i++) { // Free all parameters
		PPARAM_ENTRY PE = &((PPARAM_ENTRY)FParams)[i]; // Get parameter entry
		ClearParamEntry(PE);
	}
	FCount = 0; // Reset the count
}
//	...............................................................................................
//	...............................................................................................
//	Create a copy of another parameters list
//	Input:
// 			iSource - source parameters list
//	Output:
//			none
//	...............................................................................................
void TParamsList::CreateCopy(TParamsList* iSource) {
	if (iSource == NULL) Clear(); // Empty source?
	else {
		TBytes Bytes;
		iSource->Serialize(&Bytes); // Serialize source parameters list
		Deserialize(&Bytes); // Deserialize into this parameters list
	}
}
//	...............................................................................................
//	...............................................................................................
//	Serialize parameters to bytes
//	Input:
// 			oBytes - output bytes
//	Output:
//			none
//	...............................................................................................
void TParamsList::Serialize(TBytes* oBytes) {
}
//	...............................................................................................
//	...............................................................................................
//	Deserialize parameters from bytes
//	Input:
// 			iBytes - input bytes
//	Output:
//			none
//	...............................................................................................
void TParamsList::Deserialize(TBytes* iBytes) {
}
//	...............................................................................................
//	...............................................................................................
//	Get number of parameters
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
INT64 TParamsList::Count(void) {
	return FCount; // Return the number of parameters
}
//	...............................................................................................
//	...............................................................................................
//	Set INT32 parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_INT32(CONST_PCHAR iName, INT32 iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_INT32) { // Same type?
			PE->Data.ValueAsINT32 = iValue; // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_INT32; // Set new type
			PE->Data.ValueAsINT32 = iValue; // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_INT32); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsINT32 = iValue; // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set UINT32 parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_UINT32(CONST_PCHAR iName, UINT32 iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_UINT32) { // Same type?
			PE->Data.ValueAsUINT32 = iValue; // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_UINT32; // Set new type
			PE->Data.ValueAsUINT32 = iValue; // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_UINT32); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsUINT32 = iValue; // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set INT64 parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_INT64(CONST_PCHAR iName, INT64 iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_INT64) { // Same type?
			PE->Data.ValueAsINT64 = iValue; // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_INT64; // Set new type
			PE->Data.ValueAsINT64 = iValue; // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_INT64); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsINT64 = iValue; // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set UINT64 parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_UINT64(CONST_PCHAR iName, UINT64 iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_UINT64) { // Same type?
			PE->Data.ValueAsUINT64 = iValue; // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_UINT64; // Set new type
			PE->Data.ValueAsUINT64 = iValue; // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_UINT64); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsUINT64 = iValue; // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set DOUBLE parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_DOUBLE(CONST_PCHAR iName, DOUBLE iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_DOUBLE) { // Same type?
			PE->Data.ValueAsDOUBLE = iValue; // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_DOUBLE; // Set new type
			PE->Data.ValueAsDOUBLE = iValue; // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_DOUBLE); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsDOUBLE = iValue; // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set BOOL parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_BOOL(CONST_PCHAR iName, BOOL iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_BOOL) { // Same type?
			PE->Data.ValueAsBOOL = iValue; // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_BOOL; // Set new type
			PE->Data.ValueAsBOOL = iValue; // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_BOOL); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsBOOL = iValue; // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set DATETIME parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_DATETIME(CONST_PCHAR iName, DATETIME iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_DATETIME) { // Same type?
			PE->Data.ValueAsDATETIME = iValue; // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_DATETIME; // Set new type
			PE->Data.ValueAsDATETIME = iValue; // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_DATETIME); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsDATETIME = iValue; // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set DATETIME parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_DATETIME(CONST_PCHAR iName, TDateTime* iValue) {
	SetParam_DATETIME(iName, iValue == NULL ? DATETIME_EMPTY : iValue->GetValue()); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Set STRING parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_STRING(CONST_PCHAR iName, CONST_PCHAR iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_STRING) { // Same type?
			PE->Data.ValueAsSTRING->SetValue(iValue); // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_STRING; // Set new type
			PE->Data.ValueAsSTRING = new TString(iValue); // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_STRING); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsSTRING = new TString(iValue); // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set STRING parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_STRING(CONST_PCHAR iName, TString* iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_STRING) { // Same type?
			PE->Data.ValueAsSTRING->SetValue(iValue); // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_STRING; // Set new type
			PE->Data.ValueAsSTRING = new TString(iValue); // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_STRING); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsSTRING = new TString(iValue); // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set BYTES parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//			iLength - length of the value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_BYTES(CONST_PCHAR iName, CONST_PBYTE iValue, INT64 iLength) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_BYTES) { // Same type?
			PE->Data.ValueAsBYTES->SetValue(iValue, iLength); // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_BYTES; // Set new type
			PE->Data.ValueAsBYTES = new TBytes(iValue, iLength); // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_BYTES); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsBYTES = new TBytes(iValue, iLength); // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set BYTES parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_BYTES(CONST_PCHAR iName, TBytes* iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_BYTES) { // Same type?
			PE->Data.ValueAsBYTES->SetValue(iValue); // Update the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_BYTES; // Set new type
			PE->Data.ValueAsBYTES = new TBytes(iValue); // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_BYTES); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsBYTES = new TBytes(iValue); // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set PARAMSLIST parameter
//	Input:
// 			iName - parameter name
// 			iValue - parameter value
//	Output:
//			none
//	...............................................................................................
void TParamsList::SetParam_ParamsList(CONST_PCHAR iName, TParamsList* iValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_PARAMSLIST) { // Same type?
			PE->Data.ValueAsPARAMSLIST->CreateCopy(iValue); // Create a copy of the value
		}
		else { // Different type?
			ClearParamEntry(PE); // Clear the existing entry
			PE->Type = PTYPE_BYTES; // Set new type
			PE->Data.ValueAsPARAMSLIST = new TParamsList(iValue); // Set the value
		}
	}
	else {
		PE = (PPARAM_ENTRY)AddParamEntry(iName, PTYPE_BYTES); // Add new parameter entry
		if (PE != NULL) PE->Data.ValueAsPARAMSLIST = new TParamsList(iValue); // Set the value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Get INT32 parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
INT32 TParamsList::GetParam_INT32(CONST_PCHAR iName, INT32 iDefaultValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		return PE->Type == PTYPE_INT32 ? PE->Data.ValueAsINT32 : iDefaultValue; // Return the value or default value
	}
	return iDefaultValue; // Not found, return default value
}
//	...............................................................................................
//	...............................................................................................
//	Get UINT32 parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
UINT32 TParamsList::GetParam_UINT32(CONST_PCHAR iName, UINT32 iDefaultValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		return PE->Type == PTYPE_UINT32 ? PE->Data.ValueAsUINT32 : iDefaultValue; // Return the value or default value
	}
	return iDefaultValue; // Not found, return default value
}
//	...............................................................................................
//	...............................................................................................
//	Get INT64 parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
INT64 TParamsList::GetParam_INT64(CONST_PCHAR iName, INT64 iDefaultValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		return PE->Type == PTYPE_INT64 ? PE->Data.ValueAsINT64 : iDefaultValue; // Return the value or default value
	}
	return iDefaultValue; // Not found, return default value
}
//	...............................................................................................
//	...............................................................................................
//	Get UINT64 parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
UINT64 TParamsList::GetParam_UINT64(CONST_PCHAR iName, UINT64 iDefaultValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		return PE->Type == PTYPE_UINT64 ? PE->Data.ValueAsUINT64 : iDefaultValue; // Return the value or default value
	}
	return iDefaultValue; // Not found, return default value
}
//	...............................................................................................
//	...............................................................................................
//	Get DOUBLE parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
DOUBLE TParamsList::GetParam_DOUBLE(CONST_PCHAR iName, DOUBLE iDefaultValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		return PE->Type == PTYPE_DOUBLE ? PE->Data.ValueAsDOUBLE : iDefaultValue; // Return the value or default value
	}
	return iDefaultValue; // Not found, return default value
}
//	...............................................................................................
//	...............................................................................................
//	Get BOOL parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
BOOL TParamsList::GetParam_BOOL(CONST_PCHAR iName, BOOL iDefaultValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		return PE->Type == PTYPE_BOOL ? PE->Data.ValueAsBOOL : iDefaultValue; // Return the value or default value
	}
	return iDefaultValue; // Not found, return default value
}
//	...............................................................................................
//	...............................................................................................
//	Get DATETIME parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
DATETIME TParamsList::GetParam_DATETIME(CONST_PCHAR iName, DATETIME iDefaultValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		return PE->Type == PTYPE_DATETIME ? PE->Data.ValueAsDATETIME : iDefaultValue; // Return the value or default value
	}
	return iDefaultValue; // Not found, return default value
}
//	...............................................................................................
//	...............................................................................................
//	Get DATETIME parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
void TParamsList::GetParam_DATETIME(CONST_PCHAR iName, TDateTime* oResult, DATETIME iDefaultValue) {
	if (oResult == NULL) return; // Invalid output pointer
	oResult->SetValue(GetParam_DATETIME(iName, iDefaultValue)); // Get the value
}
//	...............................................................................................
//	...............................................................................................
//	Get STRING parameter
//	Input:
// 			iName - parameter name
//			oResult - output result
// 			iDefaultValue - default value
//	Output:
//			none
//	...............................................................................................
void TParamsList::GetParam_STRING(CONST_PCHAR iName, TString* oResult, CONST_PCHAR iDefaultValue) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		oResult->SetValue(PE->Type == PTYPE_STRING ? PE->Data.ValueAsSTRING->PChar() : iDefaultValue); // Return the stored value
	}
	else {
		oResult->SetValue(iDefaultValue); // Not found, return default value
	}
}
//	...............................................................................................
//	...............................................................................................
//	Get BYTES parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
void TParamsList::GetParam_BYTES(CONST_PCHAR iName, TBytes* oResult) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_BYTES) oResult->SetValue(PE->Data.ValueAsBYTES); // Return the stored value
		else oResult->SetCount(0); // Different type, return empty bytes
	}
	else oResult->SetCount(0); // Not found, return empty bytes
}
//	...............................................................................................
//	...............................................................................................
//	Get PARAMSLIST parameter
//	Input:
// 			iName - parameter name
// 			iDefaultValue - default value
//	Output:
//			stored value or default value
//	...............................................................................................
void TParamsList::GetParam_ParamsList(CONST_PCHAR iName, TParamsList* oResult) {
	PPARAM_ENTRY PE = (PPARAM_ENTRY)FindParamEntry(iName); // Find parameter entry
	if (PE != NULL) { // Found?
		if (PE->Type == PTYPE_PARAMSLIST) oResult->CreateCopy(PE->Data.ValueAsPARAMSLIST); // Return the stored value
		else oResult->Clear(); // Different type, return empty bytes
	}
	else oResult->Clear(); // Not found, return empty bytes
}
//	...............................................................................................
