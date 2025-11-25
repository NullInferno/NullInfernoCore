#pragma once

//	...............................................................................................
//	Class TMemoryStream
//	...............................................................................................
class TMemoryStream : public TStream {
private:
	TList* FMemoryPages; // List of memory pages
	INT64 FSize; // Size of the memory buffer
	INT64 FPosition; // Current position in the memory buffer
	INT64 FPageSize; // Size of each memory page
public:
	TMemoryStream(INT64 iPageSize = 65536); // Constructor
	virtual ~TMemoryStream(void); // Destructor
public:
	void Release(void); // Release the memory
	BOOL Allocate(INT64 iCapacity); // Allocate memory for the stream
	void GetContent(TBytes* oBuffer); // Get the entire content of the memory stream
	void SetContent(TBytes* iBuffer); // Set the entire content of the memory stream
public:
	virtual BOOL IsOpen(void); // Check if the stream is open
	virtual BOOL IsEOF(void); // Check if the stream is at the end
	virtual BOOL CanSeek(void); // Check if the stream supports seeking
	virtual BOOL CanRead(void); // Check if the stream supports reading
	virtual BOOL CanWrite(void); // Check if the stream supports writing
	virtual TStream* GetBaseStream(void); // Get the base stream
public:
	virtual void Close(void); // Close the stream
public:
	virtual INT64 Read(PVOID oBuffer, INT64 iBytesToRead); // Read bytes from the stream
	virtual INT64 Read(TBytes* oBuffer, INT64 iBytesToRead); // Read bytes from the stream
	virtual INT64 Write(CONST_PVOID iBuffer, INT64 iBytesToWrite); // Write bytes to the stream
	virtual INT64 Write(TBytes* iBuffer, INT64 iBytesToWrite = -1); // Write bytes to the stream
public:
	virtual INT64 Seek(INT64 iOffset, TStreamSeekOrigin iOrigin = SO_CURRENT); // Seek to position in the stream
	virtual INT64 GetPosition(void); // Get current position in the stream
	virtual INT64 GetSize(void); // Get size of the stream
	virtual BOOL Rewind(void); // Rewind the stream to the beginning
};
//	...............................................................................................
