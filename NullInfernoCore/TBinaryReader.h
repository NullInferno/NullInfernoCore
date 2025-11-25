#pragma once

//	...............................................................................................
//	Class TBinaryReader
//	...............................................................................................
class TBinaryReader : public TStream {
private:
	TStream* FStream; // Base stream
	BOOL FKeepOpen; // Whether to keep the base stream open on destruction
public:
	TBinaryReader(TStream* iStream, BOOL iKeepOpen = false); // Constructor
	~TBinaryReader(void); // Destructor
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
	BOOL ReadINT8(PINT8 oResult); // Read INT8 value
	BOOL ReadUINT8(PUINT8 oResult); // Read UINT8 value
	BOOL ReadINT16(PINT16 oResult); // Read INT16 value
	BOOL ReadUINT16(PUINT16 oResult); // Read UINT16 value
	BOOL ReadINT32(PINT32 oResult); // Read INT32 value
	BOOL ReadUINT32(PUINT32 oResult); // Read UINT32 value
	BOOL ReadINT64(PINT64 oResult); // Read INT64 value
	BOOL ReadUINT64(PUINT64 oResult); // Read UINT64 value
	BOOL ReadFLOAT(PFLOAT oResult); // Read FLOAT value
	BOOL ReadDOUBLE(PDOUBLE oResult); // Read DOUBLE value
	BOOL ReadBOOL(PBOOL oResult); // Read BOOL value
	BOOL ReadDATETIME(PDATETIME oResult); // Read DATETIME value
	BOOL ReadDATETIME(TDateTime* oResult); // Read DATETIME value
	BOOL ReadSTRING(TString* oResult); // Read TString value
	BOOL ReadBYTES(TBytes* oResult); // Read TBytes value
};
//	...............................................................................................
