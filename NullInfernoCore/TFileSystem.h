#pragma once

#ifdef WINDOWS_SYSTEM
#define MAX_PATH_LENGTH MAX_PATH
#define MAX_FILE_NAME_LENGTH MAX_PATH
#define PATH_SEPARATOR_CHAR '\\'
#else
#define MAX_PATH_LENGTH PATH_MAX
#define MAX_FILE_NAME_LENGTH NAME_MAX
#define PATH_SEPARATOR_CHAR '/'

#endif

#define FILE_SYSTEM_SUCCESS 0
#define FILE_SYSTEM_TRUE 1
#define FILE_SYSTEM_FALSE 0

#define FILE_SYSTEM_ERROR_INVALID_INPUT -1
#define FILE_SYSTEM_ERROR_INVALID_ROOT -2
#define FILE_SYSTEM_ERROR_FORBIDDEN_CHAR -3
#define FILE_SYSTEM_ERROR_PATH_TOO_LONG -4
#define FILE_SYSTEM_ERROR_NAME_TOO_LONG -5
#define FILE_SYSTEM_ERROR_FORBIDDEN_NAME -6
#define FILE_SYSTEM_ERROR_ACCESS_DENIED -7
#define FILE_SYSTEM_ERROR_NOT_DIRECTORY -8
#define FILE_SYSTEM_ERROR_NOT_FILE -9
#define FILE_SYSTEM_ERROR_EMPTY -10
#define FILE_SYSTEM_ERROR_CURRENT -11
#define FILE_SYSTEM_ERROR_PARENT -12
#define FILE_SYSTEM_ERROR_FILE_CREATE -13
#define FILE_SYSTEM_ERROR_FILE_WRITE -14
#define FILE_SYSTEM_ERROR_INVALID_PATH -15
#define FILE_SYSTEM_ERROR_DIRECTORY_EXISTS -16
#define FILE_SYSTEM_ERROR_DIRECTORY_CREATE -17
#define FILE_SYSTEM_ERROR_PATH_NOT_EXISTS -18
#define FILE_SYSTEM_ERROR_DIRECTORY_NOT_EMPTY -19
#define FILE_SYSTEM_ERROR_DIRECTORY_NOT_EXISTS -20
#define FILE_SYSTEM_ERROR_DIRECTORY_DELETE -21
#define FILE_SYSTEM_ERROR_ACCESS -22
#define FILE_SYSTEM_ERROR_DIRECTORY_READ -23
#define FILE_SYSTEM_ERROR_FILE_DELETE -24
#define FILE_SYSTEM_ERROR_GET_ATTRIBUTES -25
#define FILE_SYSTEM_ERROR_SET_ATTRIBUTES -26
#define FILE_SYSTEM_ERROR_FILE_EXISTS -27
#define FILE_SYSTEM_ERROR_FILE_NOT_EXISTS -28
#define FILE_SYSTEM_ERROR_FILE_OPEN -29
#define FILE_SYSTEM_ERROR_ENUMERATE_ABORT -30
#define FILE_SYSTEM_ERROR_ENUMERATE_EMPTY -31

enum TFileSystemAttributes : UINT64 {
	FSA_NONE_VALUE = (UINT64)0,
	FSA_INVALID_VALUE = (UINT64)-1,

	FSA_READ_ONLY = 0x1,
	FSA_HIDDEN = 0x2,
	FSA_SYSTEM = 0x4,
	FSA_DIRECTORY = 0x8,
	FSA_ARCHIVE = 0x10,
	FSA_DEVICE = 0x20,
	FSA_NORMAL = 0x40,
	FSA_TEMPORARY = 0x80,
	FSA_SPARSE_FILE = 0x100,
	FSA_REPARSE_POINT = 0x200,
	FSA_COMPRESSED = 0x400,
	FSA_OFFLINE = 0x800,
	FSA_NOT_CONTENT_INDEXED = 0x1000,
	FSA_ENCRYPTED = 0x2000,
	FSA_INTEGRITY_STREAM = 0x4000,
	FSA_NO_SCRUB_DATA = 0x8000,

	FSA_S_IRUSR = 0x10000,
	FSA_S_IWUSR = 0x20000,
	FSA_S_IXUSR = 0x40000,
	FSA_S_IRGRP = 0x80000,
	FSA_S_IWGRP = 0x100000,
	FSA_S_IXGRP = 0x200000,
	FSA_S_IROTH = 0x400000,
	FSA_S_IWOTH = 0x800000,
	FSA_S_IXOTH = 0x1000000,
	FSA_S_ISUID = 0x2000000,
	FSA_S_ISGID = 0x4000000,
	FSA_S_ISVTX = 0x8000000,

	FSA_S_IFMT = 0x10000000,
	FSA_S_IFDIR = 0x20000000,
	FSA_S_IFCHR = 0x40000000,
	FSA_S_IFBLK = 0x80000000,
	FSA_S_IFREG = 0x100000000,
	FSA_S_IFIFO = 0x200000000,
	FSA_S_IFLNK = 0x400000000,
	FSA_S_IFSOCK = 0x800000000,


	FSA_EXT2_SECRM_FL = 0x1000000000ull,
	FSA_EXT2_UNRM_FL = 0x2000000000ull,
	FSA_EXT2_COMPR_FL = 0x4000000000ull,
	FSA_EXT2_SYNC_FL = 0x8000000000ull,
	FSA_EXT2_IMMUTABLE_FL = 0x10000000000ull,
	FSA_EXT2_APPEND_FL = 0x20000000000ull,
	FSA_EXT2_NODUMP_FL = 0x40000000000ull,
	FSA_EXT2_NOATIME_FL = 0x80000000000ull,
	FSA_EXT2_DIRTY_FL = 0x100000000000ull,
	FSA_EXT2_COMPRBLK_FL = 0x200000000000ull,
	FSA_EXT2_NOCOMP_FL = 0x400000000000ull,
	FSA_EXT2_ECOMPR_FL = 0x800000000000ull,
	FSA_EXT2_INDEX_FL = 0x1000000000000ull,
	FSA_EXT2_JOURNAL_DATA_FL = 0x2000000000000ull,
	FSA_EXT2_NOTAIL_FL = 0x4000000000000ull,
	FSA_EXT2_DIRSYNC_FL = 0x8000000000000ull,
	FSA_EXT2_TOPDIR_FL = 0x10000000000000ull,
	FSA_EXT2_HUGE_FILE_FL = 0x20000000000000ull,
	FSA_EXT2_EXTENTS_FL = 0x40000000000000ull,
	FSA_EXT2_EA_INODE_FL = 0x80000000000000ull,
	FSA_EXT2_EOFBLOCKS_FL = 0x100000000000000ull,
	FSA_EXT2_INLINE_DATA_FL = 0x200000000000000ull,
	FSA_EXT2_PROJINHERIT_FL = 0x400000000000000ull,
};

#undef GetCurrentDirectory
#undef CreateDirectory
#undef DeleteFile
#undef GetFileAttributes
#undef SetFileAttributes
#undef DeleteFile

typedef struct {
	CONST_PCHAR NameOnly;
	CONST_PCHAR Path;
	TFileSystemAttributes Attributes;
	UINT64 Size;
	DATETIME CreationTime;
	DATETIME LastAccessTime;
	DATETIME ModificationTime;
	BOOL IsDirectory;
	INT32 DirectoryState;
} ENUM_ITEM, *PENUM_ITEM;

typedef INT32(*TEnumerateFilterFunction)(INT32 iState, PENUM_ITEM iItem, PVOID iUserData);

#define ENUMERATE_STATE_OK 0
#define ENUMERATE_STATE_ERROR 1

#define ENUMERATE_RETURN_CONTINUE 0
#define ENUMERATE_RETURN_SKIP 1
#define ENUMERATE_RETURN_ABORT 2

#define ENUMERATE_DIRECTORY_STATE_NOT_ENUMERATED 0
#define ENUMERATE_DIRECTORY_STATE_NOT_EMPTY 1
#define ENUMERATE_DIRECTORY_STATE_EMPTY 2

//	...............................................................................................
//	Class TFileSystem
//	...............................................................................................
class TFileSystem {
public:
	static INT32 IsValidPath(TString *iPath); // Check if a path is valid
	static INT32 IsValidPath(CONST_PCHAR iPath); // Check if a path is valid
	static INT32 IsValidRelativePath(TString* iPath); // Check if a relative path is valid
	static INT32 IsValidRelativePath(CONST_PCHAR iPath); // Check if a relative path is valid
public:
	static INT32 AppendPathSeparator(TString *ioPath, BOOL iCheckPath = false); // Append a path separator to the path if it does not end with one
	static INT32 RemovePathSeparator(TString* ioPath, BOOL iCheckPath = false); // Remove trailing path separator from the path if it exists
	static INT32 ExtractPathParts(CONST_PCHAR iFullPath, TString* oDirectoryPath, TString* oFileName, TString* oFileNameOnly, TString* oFileExtension, BOOL iCheckPath = false); // Extract directory path, file name and file extension from a full file path
	static INT32 ExtractPathParts(TString* iFullPath, TString* oDirectoryPath, TString* oFileName, TString* oFileNameOnly, TString* oFileExtension, BOOL iCheckPath = false); // Extract directory path, file name and file extension from a full file path
	static INT32 NormalizePath(CONST_PCHAR iPath, TString* oResult, BOOL iCheckPath = false); // Normalize a file path
	static INT32 NormalizePath(TString* ioResult, BOOL iCheckPath = false); // Normalize a file path
	static INT32 AppendToPath(CONST_PCHAR iPath, CONST_PCHAR iValue, TString* oResult, BOOL iCheckPath = false); // Append value to path
	static INT32 AppendToPath(TString* ioPath, CONST_PCHAR iValue, BOOL iCheckPath = false); // Append value to path
	static INT32 CreateFullPath(TString* oResult, CONST_PCHAR iPath, CONST_PCHAR iFileNameOnly, CONST_PCHAR iExt); // Create a full file path from directory path, file name and file extension
	static void ApppendExt(TString* ioFileName, CONST_PCHAR iExt); // Append file extension to file name
public:
	static void GetCurrentDirectory(TString* oDirectoryPath); // Get current working directory
public:
	static INT32 CreateDirectory(CONST_PCHAR iDirectoryPath, BOOL iCreateFullPath = false, BOOL iCheckPath = false); // Create a directory
	static INT32 DirectoryExists(CONST_PCHAR iDirectoryPath, BOOL iCheckPath = false); // Check if a directory exists
	static INT32 IsDirectoryEmpty(CONST_PCHAR iDirectoryPath, BOOL iCheckPath = false); // Check if a directory is empty
	static INT32 DeleteDirectory(CONST_PCHAR iDirectoryPath, BOOL iRecursive = false, BOOL iForceDelete = false, BOOL iCheckPath = false); // Delete a directory
public:
	static INT32 FileExists(CONST_PCHAR iFilePath, BOOL iCheckPath = true); // Check if a file exists
	static INT32 DeleteFile(CONST_PCHAR iFilePath, BOOL iForceDelete = false, BOOL iCheckPath = false); // Delete a file
public:
	static INT32 GetFileAttributes(CONST_PCHAR iPath, TFileSystemAttributes *oAttr, BOOL iCheckPath = false); // Get file attributes
	static INT32 SetFileAttributes(CONST_PCHAR iPath, TFileSystemAttributes iAttr, BOOL iCheckPath = false); // Set file attributes
	static INT32 GetDirectoryAttributes(CONST_PCHAR iPath, TFileSystemAttributes* oAttr, BOOL iCheckPath = false); // Get directory attributes
	static INT32 SetDirectoryAttributes(CONST_PCHAR iPath, TFileSystemAttributes iAttr, BOOL iCheckPath = false); // Set directory attributes
public:
	static INT32 Enumerate(CONST_PCHAR iPath, PVOID iUserData, TEnumerateFilterFunction iFilterFunction = NULL); // Enumerate files and directories in a directory
public:
	static void FormatSizeInBytes(UINT64 iSizeInBytes, TString* oResult, CONST_PCHAR iLanguageStrings); // Format size in bytes to human-readable string
};
//	...............................................................................................
