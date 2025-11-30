#include "NullInfernoCore.h"
#include "TFileStream.h"

//	...............................................................................................
//	Update cached size
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TFileStream::UpdateSize(void) {
	INT64 CurrentPos = FNC_FTELL((FILE*)FHandle); // save current position
	FNC_FSEEK((FILE*)FHandle, 0, SEEK_END); // seek to end
	FSize = FNC_FTELL((FILE*)FHandle); // update size from file handle
	FNC_FSEEK((FILE*)FHandle, CurrentPos, SEEK_SET); // restore position
}
//	...............................................................................................
//	...............................................................................................
//	Update cached position
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TFileStream::UpdatePosition(void) {
	FPosition = FNC_FTELL((FILE*)FHandle); // update position from file handle
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TFileStream::TFileStream(void) {
	FHandle = NULL; // Initialize variables
	FAccessMode = AM_READ;
	FOpenMode = OM_OPEN_EXISTING;
	FContentMode = CM_BINARY;
	FPosition = FSize = -1;
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TFileStream::~TFileStream(void) {
	Close(); // Close the stream
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream is open
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TFileStream::IsOpen(void) {
	return FHandle != NULL; // return whether the file handle is valid
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream is at the end
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TFileStream::IsEOF(void) {
	if (FHandle == NULL) return true; // invalid file handle
	return GetPosition() >= GetSize(); // at end if position >= size
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports seeking
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TFileStream::CanSeek(void) {
	if (FHandle == NULL) return false; // invalid file handle
	return FOpenMode != OM_APPEND_TO_END; // can seek if not in append mode
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports reading
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TFileStream::CanRead(void) {
	if (FHandle == NULL) return false; // invalid file handle
	return FAccessMode != AM_WRITE; // can read if not write-only
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports writing
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TFileStream::CanWrite(void) {
	if (FHandle == NULL) return false; // invalid file handle
	return FAccessMode != AM_READ; // can write if not read-only
}
//	...............................................................................................
//	...............................................................................................
//	Get the base stream
//	Input:
// 			none
//	Output:
//			pointer to the base stream or NULL
//	...............................................................................................
TStream* TFileStream::GetBaseStream(void) {
	return NULL; // no base stream
}
//	...............................................................................................
//	...............................................................................................
//	Close the stream
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TFileStream::Close(void) {
	if (FHandle != NULL) fclose((FILE*)FHandle); // close the file handle

	FHandle = NULL; // Initialize variables
	FAccessMode = AM_READ;
	FOpenMode = OM_OPEN_EXISTING;
	FContentMode = CM_BINARY;
	FPosition = FSize = -1;
}
//	...............................................................................................
//	...............................................................................................
//	Close the stream
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TFileStream::CloseAndDelete(void) {
	TString S(FFilePath); // save file path
	Close(); // close the stream
	return TFileSystem::DeleteFile(S.PChar(), true, false) == 0; // delete the file
}
//	...............................................................................................
//	...............................................................................................
//	Flush the stream
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TFileStream::Flush(void) {
	if ((FHandle != NULL) && (FAccessMode != AM_READ))  fflush((FILE*)FHandle); // flush the file handle
}
//	...............................................................................................
//	...............................................................................................
//	Read bytes from the stream
//	Input:
// 			oBuffer - output buffer
// 			iBytesToRead - number of bytes to read
//	Output:
//			real number of bytes read
//	...............................................................................................
INT64 TFileStream::Read(PVOID oBuffer, INT64 iBytesToRead) {
	if (oBuffer == NULL) return -1; // invalid buffer
	if (iBytesToRead <= 0) return 0; // nothing to read
	FPosition = -1; // Invalidate cached position
	return (INT64)fread(oBuffer, 1, (INT64)iBytesToRead, (FILE*)FHandle); // read bytes
}
//	...............................................................................................
//	...............................................................................................
//	Read bytes from the stream
//	Input:
// 			oBuffer - output buffer
// 			iBytesToRead - number of bytes to read
//	Output:
//			real number of bytes read
//	...............................................................................................
INT64 TFileStream::Read(TBytes* oBuffer, INT64 iStartIndex, INT64 iBytesToRead) {
	if (oBuffer == NULL) return -1; // invalid output buffer

	if (iStartIndex < 0) iStartIndex = 0; // correct start index
	if (iStartIndex > oBuffer->Count) iStartIndex = oBuffer->Count; // correct start index

	if (iStartIndex + iBytesToRead > oBuffer->Count) { // need to expand output buffer?
		if (!oBuffer->Reallocate(iStartIndex + iBytesToRead, true)) return -1; // cannot reallocate output buffer
	}
	FPosition = -1; // Invalidate cached position
	INT64 R = (INT64)fread((PVOID)(oBuffer->PByte() + iStartIndex), 1, (INT64)iBytesToRead, (FILE*)FHandle); // read bytes to the output buffer
	if (R + iStartIndex > oBuffer->Count) oBuffer->Count = iStartIndex + R; // update output buffer count
	return R; // return number of bytes readed
}
//	...............................................................................................
//	...............................................................................................
//	Write bytes to the stream
//	Input:
// 			iBuffer - input buffer
// 			iBytesToWrite - number of bytes to write
//	Output:
//			real number of bytes written
//	...............................................................................................
INT64 TFileStream::Write(CONST_PVOID iBuffer, INT64 iBytesToWrite) {
	if (iBuffer == NULL) return -1; // invalid buffer
	if (iBytesToWrite <= 0) return 0; // nothing to write
	FSize = FPosition = -1; // Invalidate cached size and position
	return (INT64)fwrite(iBuffer, 1, (INT64)iBytesToWrite, (FILE*)FHandle); // write bytes
}
//	...............................................................................................
//	...............................................................................................
//	Write bytes to the stream
//	Input:
// 			iBuffer - input buffer
// 			iStartIndex - start index in the buffer
// 			iBytesToWrite - number of bytes to write
//	Output:
//			real number of bytes written
//	...............................................................................................
INT64 TFileStream::Write(TBytes* iBuffer, INT64 iStartIndex, INT64 iBytesToWrite) {
	if (iBuffer == NULL) return -1; // Invalid input buffer
	if (iStartIndex < 0 || iStartIndex >= iBuffer->Count) return -1; // Invalid start index
	INT64 BytesToWrite = iBytesToWrite < 0 ? iBuffer->Count - iStartIndex : MIN(iBytesToWrite, iBuffer->Count - iStartIndex); // Calculate bytes to write
	FSize = FPosition = -1; // Invalidate cached size and position
	return fwrite(iBuffer->PByte() + iStartIndex, 1, (INT64)BytesToWrite, (FILE*)FHandle); // write bytes
}
//	...............................................................................................
//	...............................................................................................
//	Seek to position in the stream
//	Input:
// 			iOffset - offset to seek
// 			iOrigin - origin of the offset
//	Output:
//			new position in the stream
//	...............................................................................................
INT64 TFileStream::Seek(INT64 iOffset, TStreamSeekOrigin iOrigin) {
	if (FHandle == NULL) return -1; // invalid file handle

	FPosition = -1; // Invalidate cached position
	switch (iOrigin)		
	{
		case SO_BEGIN: { // 
			if (FNC_FSEEK((FILE*)FHandle, iOffset, SEEK_SET) != 0) return -1; // seek to position
			return GetPosition(); // return new position
		}
		case SO_CURRENT: {
			if (FNC_FSEEK((FILE*)FHandle, iOffset, SEEK_CUR) != 0) return -1; // seek to position
			return GetPosition(); // return new position
		}
		case SO_END: {
			if (FNC_FSEEK((FILE*)FHandle, iOffset, SEEK_END) != 0) return -1; // seek to position
			return GetPosition(); // return new position
		}
		default: 
			return -1; // invalid origin
	}
}
//	...............................................................................................
//	...............................................................................................
//	Get current position in the stream
//	Input:
// 			none
//	Output:
//			current position in the stream
//	...............................................................................................
INT64 TFileStream::GetPosition(void) {
	if (FHandle == NULL) return -1; // invalid file handle

	if (FPosition < 0) UpdatePosition(); // update position if needed
	return FPosition; // return position
}
//	...............................................................................................
//	...............................................................................................
//	Get size of the stream
//	Input:
// 			none
//	Output:
//			current size of the stream
//	...............................................................................................
INT64 TFileStream::GetSize(void) {
	if (FHandle == NULL) return -1; // invalid file handle

	if (FSize < 0) UpdateSize(); // update size if needed 
	return FSize; // return size
}
//	...............................................................................................
//	...............................................................................................
//	Rewind the stream to the beginning
//	Input:
// 			none
//	Output:
//			current size of the stream
//	...............................................................................................
BOOL TFileStream::Rewind(void) {
	if (FHandle == NULL) return false; // invalid file handle

	BOOL R = FNC_FSEEK((FILE*)FHandle, 0, SEEK_SET) == 0; // seek to the beginning
	FSize = FPosition = -1; // invalidate cached size and position
	return R; // return result
}
//	...............................................................................................
//	...............................................................................................
//	Open file stream
//	Input:
// 			iFilePath - file path
// 			iAccessMode - access mode
// 			iOpenMode - open mode
// 			iContentMode - content mode
//	Output:
//			0 or error code
//	...............................................................................................
INT32 TFileStream::Open(CONST_PCHAR iFilePath, TFileStreamAccessMode iAccessMode, TFileStreamOpenMode iOpenMode, TFileStreamContentMode iContentMode) {
	Close(); // close existing stream

	INT32 R = TFileSystem::IsValidPath(iFilePath); // check path validity
	if (R != 0) return R; // invalid path?

	INT32 FER = TFileSystem::FileExists(iFilePath, false); // check if file exists
	if ((FER != FILE_SYSTEM_TRUE) && (FER != FILE_SYSTEM_FALSE)) return FER; // error?

	FILE* F = NULL;

	switch (iOpenMode) {
		case OM_CREATE_ALWAYS: {
			F = fopen(iFilePath, (iContentMode == CM_TEXT) ? "wt+" : "wb+"); // create or overwrite existing
			if (F == NULL) return FILE_SYSTEM_ERROR_FILE_CREATE; // cannot open file
		} break;
		case OM_CREATE_NEW: {
			if (FER == FILE_SYSTEM_TRUE) return FILE_SYSTEM_ERROR_FILE_EXISTS; // file already exists
			F = fopen(iFilePath, (iContentMode == CM_TEXT) ? "wt+" : "wb+"); // create or overwrite existing
			if (F == NULL) return FILE_SYSTEM_ERROR_FILE_CREATE; // cannot open file
		} break;
		case OM_OPEN_ALWAYS: {
			if (FER == FILE_SYSTEM_TRUE) F = fopen(iFilePath, (iContentMode == CM_TEXT) ? "rt+" : "rb+"); // open existing
			else F = fopen(iFilePath, (iContentMode == CM_TEXT) ? "wt+" : "wb+"); // create new
			if (F == NULL) return (FER == FILE_SYSTEM_TRUE) ? FILE_SYSTEM_ERROR_FILE_OPEN : FILE_SYSTEM_ERROR_FILE_CREATE; // cannot open file
		} break;
		case OM_OPEN_EXISTING: {
			if (FER == FILE_SYSTEM_FALSE) return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS; // file not exists
			F = fopen(iFilePath, (iContentMode == CM_TEXT) ? "rt+" : "rb+"); // open existing
			if (F == NULL) return FILE_SYSTEM_ERROR_FILE_OPEN; // cannot open file
		} break;
		case OM_TRUNCATE_EXISTING: {
			if (FER == FILE_SYSTEM_FALSE) return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS; // file not exists
			F = fopen(iFilePath, (iContentMode == CM_TEXT) ? "wt+" : "wb+"); // open existing
			if (F == NULL) return FILE_SYSTEM_ERROR_FILE_OPEN; // cannot open file
		} break;
		case OM_APPEND_TO_END: {
			if (FER == FILE_SYSTEM_FALSE) return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS; // file not exists
			F = fopen(iFilePath, (iContentMode == CM_TEXT) ? "rt+" : "rb+"); // open existing
			if (F == NULL) return FILE_SYSTEM_ERROR_FILE_OPEN; // cannot open file
			if (FNC_FSEEK(F, 0, SEEK_END) != 0) { // seek to end
				fclose(F);
				return FILE_SYSTEM_ERROR_FILE_OPEN; // cannot seek to end
			}
		} break;
		default:
			return FILE_SYSTEM_ERROR_INVALID_INPUT; // invalid open mode
	}

	FHandle = (PVOID)F; // set file handle
	FAccessMode = iAccessMode;
	FOpenMode = iOpenMode;
	FContentMode = iContentMode;
	FFilePath.SetValue(iFilePath); // save file path
	return 0; // OK
}
//	...............................................................................................
