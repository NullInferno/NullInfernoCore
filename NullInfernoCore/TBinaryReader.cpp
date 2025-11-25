#include "NullInfernoCore.h"
#include "TBinaryReader.h"

//	...............................................................................................
//	Constructor
//	Input:
// 			iStream - base stream
// 			iKeepOpen - whether to keep the base stream open on destruction
//	Output:
//			none
//	...............................................................................................
TBinaryReader::TBinaryReader(TStream* iStream, BOOL iKeepOpen) {
	FStream = iStream; // Save the base stream
	FKeepOpen = iKeepOpen; // Save the keep open flag
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TBinaryReader::~TBinaryReader(void) {
	Close();
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream is open
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::IsOpen(void) {
	return FStream == NULL ? false : FStream->IsOpen();
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream is at the end
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::IsEOF(void) {
	return FStream == NULL ? false : FStream->IsEOF();
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports seeking
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::CanSeek(void) {
	return FStream == NULL ? false : FStream->CanSeek();
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports reading
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::CanRead(void) {
	return true;
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports writing
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::CanWrite(void) {
	return false;
}
//	...............................................................................................
//	Get the base stream
//	Input:
// 			none
//	Output:
//			base stream or NULL if there is no base stream
//	...............................................................................................
TStream* TBinaryReader::GetBaseStream(void) {
	return FStream;
}
//	...............................................................................................
//	...............................................................................................
//	Close the stream
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TBinaryReader::Close(void) {
	if ((FStream != NULL) && (!FKeepOpen)) { // Close the base stream if needed
		FStream->Close(); // Close the base stream
		delete FStream; // Delete the base stream
	}
	FStream = NULL; // Clear the base stream pointer
}
//	...............................................................................................
//	...............................................................................................
//	Read bytes from the stream
//	Input:
// 			oBuffer - output buffer
// 			iBytesToRead - number of bytes to read
//	Output:
//			real number of bytes readed or -1 on error
//	...............................................................................................
INT64 TBinaryReader::Read(PVOID oBuffer, INT64 iBytesToRead) {
	return FStream == NULL ? -1 : FStream->Read(oBuffer, iBytesToRead);
}
//	...............................................................................................
//	...............................................................................................
//	Read bytes from the stream
//	Input:
// 			oBuffer - output buffer
// 			iBytesToRead - number of bytes to read
//	Output:
//			real number of bytes readed or -1 on error
//	...............................................................................................
INT64 TBinaryReader::Read(TBytes* oBuffer, INT64 iBytesToRead) {
	return FStream == NULL ? -1 : FStream->Read(oBuffer, iBytesToRead);
}
//	...............................................................................................
//	...............................................................................................
//	Write bytes to the stream
//	Input:
// 			iBuffer - input buffer
// 			iBytesToWrite - number of bytes to write
//	Output:
//			real number of bytes written or -1 on error
//	...............................................................................................
INT64 TBinaryReader::Write(CONST_PVOID iBuffer, INT64 iBytesToWrite) {
	return -1;
}
//	...............................................................................................
//	...............................................................................................
//	Write bytes to the stream
//	Input:
// 			iBuffer - input buffer
// 			iBytesToWrite - number of bytes to write
//	Output:
//			real number of bytes written or -1 on error
//	...............................................................................................
INT64 TBinaryReader::Write(TBytes* iBuffer, INT64 iBytesToWrite) {
	return -1;
}
//	...............................................................................................
//	...............................................................................................
//	Seek to position in the stream
//	Input:
// 			iOffset - offset
// 			iOrigin - origin
//	Output:
//			position in the stream after seeking or -1 on error
//	...............................................................................................
INT64 TBinaryReader::Seek(INT64 iOffset, TStreamSeekOrigin iOrigin) {
	return FStream == NULL ? -1 : FStream->Seek(iOffset, iOrigin);
}
//	...............................................................................................
//	...............................................................................................
//	Get current position in the stream
//	Input:
// 			none
//	Output:
//			current position in the stream or -1 on error
//	...............................................................................................
INT64 TBinaryReader::GetPosition(void) {
	return FStream == NULL ? -1 : FStream->GetPosition();
}
//	...............................................................................................
//	...............................................................................................
//	Get size of the stream
//	Input:
// 			none
//	Output:
//			size of the stream or -1 on error
//	...............................................................................................
INT64 TBinaryReader::GetSize(void) {
	return FStream == NULL ? -1 : FStream->GetSize();
}
//	...............................................................................................
//	...............................................................................................
//	Rewind the stream to the beginning
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::Rewind(void) {
	return FStream == NULL ? false : FStream->Rewind();
}
//	...............................................................................................
//	...............................................................................................
//	Read INT8 value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadINT8(PINT8 oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read UINT8 value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadUINT8(PUINT8 oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read INT16 value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadINT16(PINT16 oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read UINT16 value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadUINT16(PUINT16 oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read INT32 value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadINT32(PINT32 oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read UINT32 value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadUINT32(PUINT32 oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read INT64 value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadINT64(PINT64 oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read UINT64 value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadUINT64(PUINT64 oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read FLOAT value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadFLOAT(PFLOAT oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read DOUBLE value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadDOUBLE(PDOUBLE oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(*oResult)) == sizeof(*oResult);
}
//	...............................................................................................
//	...............................................................................................
//	Read BOOL value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadBOOL(PBOOL oResult) {
	BYTE B;
	if (FStream == NULL) return false; // Check if the base stream is valid
	if (FStream->Read(&B, sizeof(B)) != sizeof(B)) return false; // Read the BYTE value
	*oResult = B != 0; // Convert BYTE to BOOL
	return true; // Return success
}
//	...............................................................................................
//	...............................................................................................
//	Read DATETIME value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadDATETIME(PDATETIME oResult) {
	return FStream == NULL ? false : FStream->Read(oResult, sizeof(DATETIME)) == sizeof(DATETIME);
}
//	...............................................................................................
//	...............................................................................................
//	Read DATETIME value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadDATETIME(TDateTime* oResult) {
	DATETIME DT;
	if (!ReadDATETIME(&DT)) return false; // Read the DATETIME value
	oResult->SetValue(DT); // Set the value
	return true; // Return success
}
//	...............................................................................................
//	...............................................................................................
//	Read TString value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadSTRING(TString* oResult) {
	if (oResult == NULL) return false; // Invalid value
	if (FStream == NULL) return false; // Invalid stream

	INT64 L;
	if (FStream->Read(&L, sizeof(L)) != sizeof(L)) return false; // Read the length
	if (L <= 0) { // Empty string
		oResult->SetLength(0); // Set length to zero
		return true; // Return success
	}

	if (!oResult->Reallocate(L, false)) return false; // Reallocate the string
	if (FStream->Read(oResult->Value, L) != L) {
		oResult->SetLength(0); // Set length to zero
		return false; // Read error
	}

	oResult->Value[oResult->Length = L] = 0; // Set the length and terminate the string
	return true; // Return success
}
//	...............................................................................................
//	...............................................................................................
//	Read TBytes value
//	Input:
// 			oResult - output result
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryReader::ReadBYTES(TBytes* oResult) {
	if (oResult == NULL) return false; // Invalid value
	if (FStream == NULL) return false; // Invalid stream

	INT64 L;
	if (FStream->Read(&L, sizeof(L)) != sizeof(L)) return false; // Read the length
	if (L <= 0) { // Empty string
		oResult->Count = 0; // Set count to zero
		return true; // Return success
	}

	if (!oResult->Reallocate(L, false)) return false; // Reallocate the string
	if (FStream->Read(oResult->Value, L) != L) {
		oResult->Count = 0; // Set count to zero
		return false; // Read error
	}

	oResult->Count = L; // Set count to zero
	return true; // Return success
}
//	...............................................................................................
