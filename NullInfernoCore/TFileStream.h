#pragma once

enum TFileStreamContentMode {
	CM_TEXT = 0,
	CM_BINARY = 1
};

enum TFileStreamAccessMode {
	AM_READ = 0,
	AM_WRITE = 1,
	AM_READ_WRITE = 2
};

enum TFileStreamOpenMode {
	OM_CREATE_ALWAYS = 0, // Create a new file or overwrite existing
	OM_CREATE_NEW = 1, // Create a new file, fail if exists
	OM_OPEN_ALWAYS = 2, // Open existing file or create new
	OM_OPEN_EXISTING = 3, // Open existing file, fail if not exists
	OM_TRUNCATE_EXISTING = 4, // Open existing file and truncate to zero length
	OM_APPEND_TO_END = 5 // Open existing file and set position to end
};

//	...............................................................................................
//	Class TFileStream
//	...............................................................................................
class TFileStream : public TStream {
protected:
	TFileStreamContentMode FContentMode; // Content mode
	TFileStreamAccessMode FAccessMode; // Access mode
	TFileStreamOpenMode FOpenMode; // Open mode
	PVOID FHandle; // File handle
	INT64 FPosition; // Cached current position
	INT64 FSize; // Cached size of the file
	TString FFilePath; // File path
private:
	void UpdateSize(void); // Update cached size
	void UpdatePosition(void); // Update cached position
public:
	TFileStream(void); // Constructor
	virtual ~TFileStream(void); // Destructor
public:
	virtual BOOL IsOpen(void); // Check if the stream is open
	virtual BOOL IsEOF(void); // Check if the stream is at the end
	virtual BOOL CanSeek(void); // Check if the stream supports seeking
	virtual BOOL CanRead(void); // Check if the stream supports reading
	virtual BOOL CanWrite(void); // Check if the stream supports writing
	virtual TStream* GetBaseStream(void); // Get the base stream
public:
	virtual void Close(void); // Close the stream
	virtual BOOL CloseAndDelete(void); // Close the stream and delete file
	virtual void Flush(void); // Flush the stream
public:
	virtual INT64 Read(PVOID oBuffer, INT64 iBytesToRead); // Read bytes from the stream
	virtual INT64 Read(TBytes* oBuffer, INT64 iStartIndex, INT64 iBytesToRead); // Read bytes from the stream
	virtual INT64 Write(CONST_PVOID iBuffer, INT64 iBytesToWrite); // Write bytes to the stream
	virtual INT64 Write(TBytes* iBuffer, INT64 iStartIndex = 0, INT64 iBytesToWrite = -1); // Write bytes to the stream
public:
	virtual INT64 Seek(INT64 iOffset, TStreamSeekOrigin iOrigin = SO_CURRENT); // Seek to position in the stream
	virtual INT64 GetPosition(void); // Get current position in the stream
	virtual INT64 GetSize(void); // Get size of the stream
	virtual BOOL Rewind(void); // Rewind the stream to the beginning
public:
	virtual INT32 Open(CONST_PCHAR iFilePath, TFileStreamAccessMode iAccessMode, TFileStreamOpenMode iOpenMode, TFileStreamContentMode iContentMode = CM_BINARY); // Open file stream
};
//	...............................................................................................
