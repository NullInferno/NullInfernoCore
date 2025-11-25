#include "NullInfernoCore.h"
#include "TMemoryStream.h"

//	...............................................................................................
//	Constructor
//	Input:
// 			iPageSize - size of each memory page
//	Output:
//			none
//	...............................................................................................
TMemoryStream::TMemoryStream(INT64 iPageSize) {
	FMemoryPages = new TList(128); FSize = 0; FPosition = 0; // Initialize variables
	FPageSize = iPageSize < 1024 ? 1024 : iPageSize; // Set page size with minimum of 1024 bytes
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TMemoryStream::~TMemoryStream(void) {
	Release(); // Release the memory
	delete FMemoryPages; // Delete the memory pages list
}
//	...............................................................................................
//	...............................................................................................
//	Release the memory
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TMemoryStream::Release(void) {
	for (INT64 i = 0; i < FMemoryPages->Count(); i++) { // Free all memory pages
		PBYTE Page = (PBYTE)FMemoryPages->Item(i); // Get memory page
		if (Page != NULL) MEMORY_FREE(Page); // Free the memory page
	}
	FMemoryPages->Clear(); // Clear the memory pages list
	FSize = 0; FPosition = 0; // Initialize variables
}
//	...............................................................................................
//	...............................................................................................
//	Allocate memory for the stream
//	Input:
// 			iCapacity - capacity to allocate
//	Output:
//			true / false
//	...............................................................................................
BOOL TMemoryStream::Allocate(INT64 iCapacity) {
	INT64 RequiredPages = (iCapacity + FPageSize - 1) / FPageSize; // Calculate required number of pages
	if (RequiredPages <= FMemoryPages->Count()) return true; // Already have enough pages

	while (FMemoryPages->Count() < RequiredPages) { // Allocate new pages
		PBYTE NewPage = (PBYTE)MEMORY_ALLOC(FPageSize); // Allocate memory page
		if (NewPage == NULL) return false; // Allocation failed?
		FMemoryPages->Add((PVOID)NewPage); // Add memory page to the list
	}
	return true; // Success
}
//	...............................................................................................
//	...............................................................................................
//	Get the entire content of the memory stream
//	Input:
// 			oBuffer - output buffer
//	Output:
//			none
//	...............................................................................................
void TMemoryStream::GetContent(TBytes* oBuffer) {
	if (oBuffer == NULL) return; // Invalid output buffer
	oBuffer->Reallocate(FSize, false); // Reallocate output buffer
	INT64 MemBank = 0; // Memory bank index
	PBYTE BufferPtr = (PBYTE)oBuffer->PByte(); // Pointer to output buffer
	INT64 RemainingSize = FSize; // Remaining size to copy
	while (RemainingSize > 0) {
		INT64 R = MIN(RemainingSize, FPageSize); // Calculate bytes to copy from this bank
		PBYTE BankPtr = (PBYTE)FMemoryPages->Item(MemBank); // Get memory bank pointer
		FNC_MEMCPY(BufferPtr, BankPtr, R); // Copy bytes to output buffer
		BufferPtr += R; // Advance output buffer pointer
		RemainingSize -= R; // Decrease remaining size to copy
		MemBank++; // Move to the next memory bank
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set the entire content of the memory stream
//	Input:
// 			iBuffer - input buffer
//	Output:
//			none
//	...............................................................................................
void TMemoryStream::SetContent(TBytes* iBuffer) {
	FPosition = 0; FSize = 0; // Reset position and size
	if (iBuffer == NULL) return; // Invalid input buffer
	Write(iBuffer->PByte(), iBuffer->Count); // Write the input buffer to the stream
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream is open
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TMemoryStream::IsOpen(void) {
	return true; // Memory stream is always open
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream is at the end
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TMemoryStream::IsEOF(void) {
	return FPosition >= FSize; // Check if position is at or beyond the size
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports seeking
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TMemoryStream::CanSeek(void) {
	return true; // Memory stream supports seeking
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports reading
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TMemoryStream::CanRead(void) {
	return true; // Memory stream supports reading
}
//	...............................................................................................
//	...............................................................................................
//	Check if the stream supports writing
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TMemoryStream::CanWrite(void) {
	return true; // Memory stream supports writing
}
//	...............................................................................................
//	...............................................................................................
//	Get the base stream
//	Input:
// 			none
//	Output:
//			base stream or NULL if there is no base stream
//	...............................................................................................
TStream* TMemoryStream::GetBaseStream(void) {
	return NULL;
}
//	...............................................................................................
//	...............................................................................................
//	Close the stream
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TMemoryStream::Close(void) {
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
INT64 TMemoryStream::Read(PVOID oBuffer, INT64 iBytesToRead) {
	if (oBuffer == NULL) return -1; // Invalid output buffer
	if (iBytesToRead <= 0) return 0; // Nothing to read
	if (FPosition >= FSize) return -1; // At the end of the stream

	INT64 MemBank = FPosition / FPageSize; // Calculate memory bank index
	PBYTE BufferPtr = (PBYTE)oBuffer; // Pointer to output buffer
	INT64 PosInBank = FPosition % FPageSize; // Position within the memory bank
	INT64 ToRead = iBytesToRead; // Remaining bytes to read
	INT64 BanksCount = FMemoryPages->Count(); // Total number of memory banks

	while (ToRead > 0) {
		INT64 R = MIN(ToRead, MIN(FSize - FPosition, FPageSize - PosInBank)); // Calculate bytes to read from this bank
		if (R == 0) break; // Nothing to read from this bank?
		if (MemBank >= BanksCount) break; // No more memory banks to read from?
		PBYTE BankPtr = (PBYTE)FMemoryPages->Item(MemBank); // Get memory bank pointer
		FNC_MEMCPY(BufferPtr, BankPtr + PosInBank, R); // Copy bytes to output buffer
		BufferPtr += R; // Advance output buffer pointer
		FPosition += R; // Advance stream position
		PosInBank = 0;
		ToRead -= R; // Decrease remaining bytes to read
		MemBank++; // Move to the next memory bank
	}

	return (INT64)(BufferPtr - (PBYTE)oBuffer); // Return total bytes readed
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
INT64 TMemoryStream::Read(TBytes* oBuffer, INT64 iBytesToRead) {
	if (oBuffer == NULL) return -1; // Invalid output buffer
	if (!oBuffer->Reallocate(iBytesToRead, false)) return -1; // Reallocate output buffer
	INT64 L = Read((PVOID)oBuffer->PByte(), iBytesToRead); // Read bytes into the output buffer
	if (L >= 0) oBuffer->SetCount(L); // Update input buffer count
	return L; // Return number of bytes written
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
INT64 TMemoryStream::Write(CONST_PVOID iBuffer, INT64 iBytesToWrite) {
	if (iBuffer == NULL) return -1; // Invalid input buffer
	if (iBytesToWrite <= 0) return 0; // Nothing to write

	INT64 MemBank = FPosition / FPageSize; // Calculate memory bank index
	PBYTE BufferPtr = (PBYTE)iBuffer; // Pointer to output buffer
	INT64 PosInBank = FPosition % FPageSize; // Position within the memory bank
	INT64 ToWrite = iBytesToWrite; // Remaining bytes to read
	INT64 BanksCount = FMemoryPages->Count(); // Total number of memory banks
	PBYTE BankPtr;

	while (ToWrite > 0) {
		INT64 R = MIN(ToWrite, FPageSize - PosInBank); // Calculate bytes to read from this bank
		if (R == 0) break; // Nothing to read from this bank?
		if (MemBank >= BanksCount) { // Need to allocate new memory bank?
			BankPtr = (PBYTE)MEMORY_ALLOC(FPageSize); // Allocate new memory bank
			if (BankPtr == NULL) break; // Allocation failed?
			FMemoryPages->Add((PVOID)BankPtr); // Add new memory bank to the list
			BanksCount++;
		}
		else { // Use existing memory bank
			BankPtr = (PBYTE)FMemoryPages->Item(MemBank); // Get memory bank pointer
		}
		FNC_MEMCPY(BankPtr + PosInBank, BufferPtr, R); // Copy bytes to output buffer
		BufferPtr += R; // Advance output buffer pointer
		FPosition += R; // Advance stream position
		ToWrite -= R; // Decrease remaining bytes to write
		PosInBank = 0;
		MemBank++; // Move to the next memory bank
	}

	if (FPosition > FSize) FSize = FPosition; // Update size if needed
	return (INT64)(BufferPtr - (PBYTE)iBuffer); // Return total bytes readed
}
//	...............................................................................................
//	...............................................................................................
//	Write bytes to the stream
//	Input:
// 			iBuffer - input buffer
// 			iBytesToWrite - number of bytes to write or <0 to write the whole buffer
//	Output:
//			real number of bytes written or -1 on error
//	...............................................................................................
INT64 TMemoryStream::Write(TBytes* iBuffer, INT64 iBytesToWrite) {
	if (iBuffer == NULL) return -1; // Invalid input buffer
	return Write(iBuffer->PByte(), iBytesToWrite < 0 ? iBuffer->Count : MIN(iBuffer->Count, iBytesToWrite)); // Write bytes from the input buffer
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
INT64 TMemoryStream::Seek(INT64 iOffset, TStreamSeekOrigin iOrigin) {
	switch (iOrigin) { // Adjust position based on origin
		case SO_BEGIN:
			FPosition = iOffset;
			break;
		case SO_CURRENT:
			FPosition += iOffset;
			break;
		default:
			FPosition = FSize + iOffset;
			break;
	}
	if (FPosition < 0) FPosition = 0; // Clamp to the beginning
	else if (FPosition > FSize) FPosition = FSize; // Clamp to the end

	return FPosition; // Return the new position
}
//	...............................................................................................
//	...............................................................................................
//	Get current position in the stream
//	Input:
// 			none
//	Output:
//			current position in the stream or -1 on error
//	...............................................................................................
INT64 TMemoryStream::GetPosition(void) {
	return FPosition; // Return the current position
}
//	...............................................................................................
//	...............................................................................................
//	Get size of the stream
//	Input:
// 			none
//	Output:
//			size of the stream or -1 on error
//	...............................................................................................
INT64 TMemoryStream::GetSize(void) {
	return FSize; // Return the size of the memory buffer
}
//	...............................................................................................
//	...............................................................................................
//	Rewind the stream to the beginning
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TMemoryStream::Rewind(void) {
	FPosition = 0; // Rewind to the beginning
	return FPosition < FSize; // Return true if not at the end
}
//	...............................................................................................
