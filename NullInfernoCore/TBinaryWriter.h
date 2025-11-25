#pragma once

//	...............................................................................................
//	Class TBinaryWriter
//	...............................................................................................
class TBinaryWriter : public TStream {
private:
	TStream* FStream; // Base stream
	BOOL FKeepOpen; // Whether to keep the base stream open on destruction
public:
	TBinaryWriter(TStream* iStream, BOOL iKeepOpen = false); // Constructor
	~TBinaryWriter(void); // Destructor
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
public:
	BOOL WriteINT8(INT8 iValue); // Write INT8 value
	BOOL WriteUINT8(UINT8 iValue); // Write UINT8 value
	BOOL WriteINT16(INT16 iValue); // Write INT16 value
	BOOL WriteUINT16(UINT16 iValue); // Write UINT16 value
	BOOL WriteINT32(INT32 iValue); // Write INT32 value
	BOOL WriteUINT32(UINT32 iValue); // Write UINT32 value
	BOOL WriteINT64(INT64 iValue); // Write INT64 value
	BOOL WriteUINT64(UINT64 iValue); // Write UINT64 value
	BOOL WriteFLOAT(FLOAT iValue); // Write FLOAT value
	BOOL WriteDOUBLE(DOUBLE iValue); // Write DOUBLE value
	BOOL WriteBOOL(BOOL iValue); // Write BOOL value
	BOOL WriteDATETIME(DATETIME iValue); // Write DATETIME value
	BOOL WriteDATETIME(TDateTime* iValue); // Write DATETIME value
	BOOL WriteSTRING(TString* iValue); // Write TString value
	BOOL WriteBYTES(TBytes* iValue, INT64 iStart = 0, INT64 iLength = -1); // Write TBytes value
};
//	...............................................................................................
