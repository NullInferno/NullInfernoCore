#pragma once

enum TStreamSeekOrigin {
	SO_BEGIN = 0,
	SO_CURRENT = 1,
	SO_END = 2
};

//	...............................................................................................
//	Class TStream
//	...............................................................................................
class TStream {
public:
	TStream(void); // Constructor
	virtual ~TStream(void); // Destructor
public:
	virtual BOOL IsOpen(void) = 0; // Check if the stream is open
	virtual BOOL IsEOF(void) = 0; // Check if the stream is at the end
	virtual BOOL CanSeek(void) = 0; // Check if the stream supports seeking
	virtual BOOL CanRead(void) = 0; // Check if the stream supports reading
	virtual BOOL CanWrite(void) = 0; // Check if the stream supports writing
	virtual TStream* GetBaseStream(void) = 0; // Get the base stream
public:
	virtual void Close(void) = 0; // Close the stream
	virtual void Flush(void) = 0; // Flush the stream
public:
	virtual INT64 Read(PVOID oBuffer, INT64 iBytesToRead) = 0; // Read bytes from the stream
	virtual INT64 Read(TBytes* oBuffer, INT64 iStartIndex, INT64 iBytesToRead) = 0; // Read bytes from the stream
	virtual INT64 Write(CONST_PVOID iBuffer, INT64 iBytesToWrite) = 0; // Write bytes to the stream
	virtual INT64 Write(TBytes* iBuffer, INT64 iStartIndex = 0, INT64 iBytesToWrite = -1) = 0; // Write bytes to the stream
public:
	virtual INT64 Seek(INT64 iOffset, TStreamSeekOrigin iOrigin = SO_CURRENT) = 0; // Seek to position in the stream
	virtual INT64 GetPosition(void) = 0; // Get current position in the stream
	virtual INT64 GetSize(void) = 0; // Get size of the stream
	virtual BOOL Rewind(void) = 0; // Rewind the stream to the beginning
};
//	...............................................................................................
