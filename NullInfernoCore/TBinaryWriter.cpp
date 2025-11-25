#include "NullInfernoCore.h"
#include "TBinaryWriter.h"

//	...............................................................................................
//	Constructor
//	Input:
// 			iStream - base stream
// 			iKeepOpen - whether to keep the base stream open on destruction
//	Output:
//			none
//	...............................................................................................
TBinaryWriter::TBinaryWriter(TStream* iStream, BOOL iKeepOpen) {
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
TBinaryWriter::~TBinaryWriter(void) {
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
BOOL TBinaryWriter::IsOpen(void) {
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
BOOL TBinaryWriter::IsEOF(void) {
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
BOOL TBinaryWriter::CanSeek(void) {
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
BOOL TBinaryWriter::CanRead(void) {
	return false;
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports writing
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::CanWrite(void) {
	return true;
}
//	...............................................................................................
//	Get the base stream
//	Input:
// 			none
//	Output:
//			base stream or NULL if there is no base stream
//	...............................................................................................
TStream* TBinaryWriter::GetBaseStream(void) {
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
void TBinaryWriter::Close(void) {
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
INT64 TBinaryWriter::Read(PVOID oBuffer, INT64 iBytesToRead) {
	return -1; // Reading is not supported
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
INT64 TBinaryWriter::Read(TBytes* oBuffer, INT64 iBytesToRead) {
	return -1; // Reading is not supported
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
INT64 TBinaryWriter::Write(CONST_PVOID iBuffer, INT64 iBytesToWrite) {
	return FStream == NULL ? -1 : FStream->Write(iBuffer, iBytesToWrite);
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
INT64 TBinaryWriter::Write(TBytes* iBuffer, INT64 iBytesToWrite) {
	return FStream == NULL ? -1 : FStream->Write(iBuffer, iBytesToWrite);
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
INT64 TBinaryWriter::Seek(INT64 iOffset, TStreamSeekOrigin iOrigin) {
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
INT64 TBinaryWriter::GetPosition(void) {
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
INT64 TBinaryWriter::GetSize(void) {
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
BOOL TBinaryWriter::Rewind(void) {
	return FStream == NULL ? false : FStream->Rewind();
}
//	...............................................................................................
//	...............................................................................................
//	Write INT8 value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteINT8(INT8 iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write UINT8 value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteUINT8(UINT8 iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write INT16 value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteINT16(INT16 iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write UINT16 value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteUINT16(UINT16 iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write INT32 value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteINT32(INT32 iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write UINT32 value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteUINT32(UINT32 iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write INT64 value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteINT64(INT64 iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write UINT64 value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteUINT64(UINT64 iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write FLOAT value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteFLOAT(FLOAT iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write DOUBLE value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteDOUBLE(DOUBLE iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write BOOL value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteBOOL(BOOL iValue) {
	BYTE B = iValue ? 1 : 0; // Convert BOOL to BYTE
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(B)) == sizeof(B); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write DATETIME value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteDATETIME(DATETIME iValue) {
	return FStream == NULL ? false : FStream->Write(&iValue, sizeof(iValue)) == sizeof(iValue); // Write the value to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Write DATETIME value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteDATETIME(TDateTime* iValue) {
	if (iValue == NULL) return false; // Invalid value
	return WriteDATETIME(iValue->GetValue()); // Write the date and time value
}
//	...............................................................................................
//	...............................................................................................
//	Write TString value
//	Input:
// 			iValue - value to write
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteSTRING(TString* iValue) {
	if (iValue == NULL) return false; // Invalid value
	if (FStream == NULL) return false; // Invalid stream

	if (FStream->Write(&iValue->Length, sizeof(iValue->Length)) != sizeof(iValue->Length)) return false; // Write the length
	return iValue->Length > 0 ? FStream->Write(iValue->Value, iValue->Length) == iValue->Length : true; // Write the content
}
//	...............................................................................................
//	...............................................................................................
//	Write TBytes value
//	Input:
// 			iValue - value to write
// 			iStart - start position in the bytes
// 			iLength - number of bytes to write or -1 to write all bytes from start position
//	Output:
//			true / false
//	...............................................................................................
BOOL TBinaryWriter::WriteBYTES(TBytes* iValue, INT64 iStart, INT64 iLength) {
	if (iValue == NULL) return false; // Invalid value
	if (FStream == NULL) return false; // Invalid stream
	if ((iStart < 0) || (iStart >= iValue->Count)) return false; // Invalid start position

	INT64 L = iLength < 0 ? iValue->Count - iStart : MIN(iLength, iValue->Count - iStart); // Length to write

	if (FStream->Write(&L, sizeof(L)) != sizeof(L)) return false; // Write the length
	return L > 0 ? FStream->Write(iValue->Value + iStart, L) == L : true; // Write the content
}
//	...............................................................................................
