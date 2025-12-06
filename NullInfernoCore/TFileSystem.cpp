#include "NullInfernoCore.h"
#include "TFileSystem.h"

CONST_PCHAR WIN_RESERVED_NAMES[] = {
	"CON",
	"PRN",
	"AUX",
	"NUL",
	"COM1",
	"COM2",
	"COM3",
	"COM4",
	"COM5",
	"COM6",
	"COM7",
	"COM8",
	"COM9",
	"LPT1",
	"LPT2",
	"LPT3",
	"LPT4",
	"LPT5",
	"LPT6",
	"LPT7",
	"LPT8",
	"LPT9"
};

#ifdef WINDOWS_SYSTEM
//	................................................................................................
//  Convert Windows file attributes to TFileSystemAttributes
//	Input:
//			iValue - Windows file attributes
//	Output:
//			TFIleSystemAttributes value
//	................................................................................................
TFileSystemAttributes WindowsAttaributes2FileSystemAttributes(UINT32 iValue) {
	if (iValue == INVALID_FILE_ATTRIBUTES) return FSA_INVALID_VALUE; // Invalid attributes
	TFileSystemAttributes Result = FSA_NONE_VALUE;
	if ((iValue & FILE_ATTRIBUTE_DIRECTORY) != 0) Result = (TFileSystemAttributes)(Result | FSA_DIRECTORY); // Convert all attributes
	if ((iValue & FILE_ATTRIBUTE_READONLY) != 0) Result = (TFileSystemAttributes)(Result | FSA_READ_ONLY);
	if ((iValue & FILE_ATTRIBUTE_HIDDEN) != 0) Result = (TFileSystemAttributes)(Result | FSA_HIDDEN);
	if ((iValue & FILE_ATTRIBUTE_SYSTEM) != 0) Result = (TFileSystemAttributes)(Result | FSA_SYSTEM);
	if ((iValue & FILE_ATTRIBUTE_ARCHIVE) != 0) Result = (TFileSystemAttributes)(Result | FSA_ARCHIVE);
	if ((iValue & FILE_ATTRIBUTE_DEVICE) != 0) Result = (TFileSystemAttributes)(Result | FSA_DEVICE);
	if ((iValue & FILE_ATTRIBUTE_NORMAL) != 0) Result = (TFileSystemAttributes)(Result | FSA_NORMAL);
	if ((iValue & FILE_ATTRIBUTE_TEMPORARY) != 0) Result = (TFileSystemAttributes)(Result | FSA_TEMPORARY);
	if ((iValue & FILE_ATTRIBUTE_SPARSE_FILE) != 0) Result = (TFileSystemAttributes)(Result | FSA_SPARSE_FILE);
	if ((iValue & FILE_ATTRIBUTE_REPARSE_POINT) != 0) Result = (TFileSystemAttributes)(Result | FSA_REPARSE_POINT);
	if ((iValue & FILE_ATTRIBUTE_COMPRESSED) != 0) Result = (TFileSystemAttributes)(Result | FSA_COMPRESSED);
	if ((iValue & FILE_ATTRIBUTE_OFFLINE) != 0) Result = (TFileSystemAttributes)(Result | FSA_OFFLINE);
	if ((iValue & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) != 0) Result = (TFileSystemAttributes)(Result | FSA_NOT_CONTENT_INDEXED);
	if ((iValue & FILE_ATTRIBUTE_ENCRYPTED) != 0) Result = (TFileSystemAttributes)(Result | FSA_ENCRYPTED);
	if ((iValue & FILE_ATTRIBUTE_INTEGRITY_STREAM) != 0) Result = (TFileSystemAttributes)(Result | FSA_INTEGRITY_STREAM);
	if ((iValue & FILE_ATTRIBUTE_NO_SCRUB_DATA) != 0) Result = (TFileSystemAttributes)(Result | FSA_NO_SCRUB_DATA);
	return Result; // return result
}
//	................................................................................................

//	................................................................................................
//  Convert TFileSystemAttributes to Windows file attributes
//	Input:
//			iValue - TFileSystemAttributes value
//	Output:
//			windows file attributes value
//	................................................................................................
UINT32 FileSystemAttributes2WindowsAttaributes(TFileSystemAttributes iValue) {
	if (iValue == FSA_NONE_VALUE) return 0; // No attributes
	if (iValue == FSA_INVALID_VALUE) return INVALID_FILE_ATTRIBUTES; // Invalid attributes

	UINT32 Result = 0;

	if ((iValue & FSA_DIRECTORY) != 0) Result |= FILE_ATTRIBUTE_DIRECTORY; // Convert all attributes
	if ((iValue & FSA_READ_ONLY) != 0) Result |= FILE_ATTRIBUTE_READONLY;
	if ((iValue & FSA_HIDDEN) != 0) Result |= FILE_ATTRIBUTE_HIDDEN;
	if ((iValue & FSA_SYSTEM) != 0) Result |= FILE_ATTRIBUTE_SYSTEM;
	if ((iValue & FSA_ARCHIVE) != 0) Result |= FILE_ATTRIBUTE_ARCHIVE;
	if ((iValue & FSA_DEVICE) != 0) Result |= FILE_ATTRIBUTE_DEVICE;
	if ((iValue & FSA_NORMAL) != 0) Result |= FILE_ATTRIBUTE_NORMAL;
	if ((iValue & FSA_TEMPORARY) != 0) Result |= FILE_ATTRIBUTE_TEMPORARY;
	if ((iValue & FSA_SPARSE_FILE) != 0) Result |= FILE_ATTRIBUTE_SPARSE_FILE;
	if ((iValue & FSA_REPARSE_POINT) != 0) Result |= FILE_ATTRIBUTE_REPARSE_POINT;
	if ((iValue & FSA_COMPRESSED) != 0) Result |= FILE_ATTRIBUTE_COMPRESSED;
	if ((iValue & FSA_OFFLINE) != 0) Result |= FILE_ATTRIBUTE_OFFLINE;
	if ((iValue & FSA_NOT_CONTENT_INDEXED) != 0) Result |= FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
	if ((iValue & FSA_ENCRYPTED) != 0) Result |= FILE_ATTRIBUTE_ENCRYPTED;
	if ((iValue & FSA_INTEGRITY_STREAM) != 0) Result |= FILE_ATTRIBUTE_INTEGRITY_STREAM;
	if ((iValue & FSA_NO_SCRUB_DATA) != 0) Result |= FILE_ATTRIBUTE_NO_SCRUB_DATA;

	return Result; // return result
}
//	................................................................................................
#else

#include <linux/fs.h>

#define EXT2_SECRM_FL         0x00000001 /* secure deletion */
#define EXT2_UNRM_FL          0x00000002 /* undelete */
#define EXT2_COMPR_FL         0x00000004 /* compressed */
#define EXT2_SYNC_FL          0x00000008 /* synchronous updates */
#define EXT2_IMMUTABLE_FL     0x00000010 /* immutable */
#define EXT2_APPEND_FL        0x00000020 /* append only */
#define EXT2_NODUMP_FL        0x00000040 /* do not dump */
#define EXT2_NOATIME_FL       0x00000080 /* do not update atime */

#define EXT2_DIRTY_FL         0x00000100 /* dirty (modified) */
#define EXT2_COMPRBLK_FL      0x00000200 /* compressed blocks */
#define EXT2_NOCOMP_FL        0x00000400 /* access raw compressed data */
#define EXT2_ECOMPR_FL        0x00000800 /* compression error */

#define EXT2_INDEX_FL         0x00001000 /* hash indexed directory */
#define EXT2_JOURNAL_DATA_FL  0x00002000 /* journal file data */
#define EXT2_NOTAIL_FL        0x00004000 /* file tail should not be merged */
#define EXT2_DIRSYNC_FL       0x00010000 /* directory sync */
#define EXT2_TOPDIR_FL        0x00020000 /* top of directory hierarchy */
#define EXT2_HUGE_FILE_FL     0x00040000 /* huge file */
#define EXT2_EXTENTS_FL       0x00080000 /* extents */
#define EXT2_EA_INODE_FL      0x00200000 /* EA inode */
#define EXT2_EOFBLOCKS_FL     0x00400000 /* EOF blocks */
#define EXT2_INLINE_DATA_FL   0x10000000 /* inline data */
#define EXT2_PROJINHERIT_FL   0x20000000 /* project hierarchy inheritance */

//	................................................................................................
//  Convert Linux file attributes to TFileSystemAttributes
//	Input:
//			iChmod - Linux file attributes for chmod
//	Output:
//			TFIleSystemAttributes value
//	................................................................................................
TFileSystemAttributes LinuxAttaributes2FileSystemAttributes(UINT32 iAttr, UINT32 iChmod, UINT32 iExt2Attr) {
	TFileSystemAttributes Result = FSA_NONE_VALUE;

	//if ((iAttr & S_IFMT) != 0) Result = (TFileSystemAttributes)(Result | FSA_S_IFMT); // Convert all attributes
	if ((iAttr & S_IFDIR) == S_IFDIR) Result = (TFileSystemAttributes)(Result | FSA_S_IFDIR);
	if ((iAttr & S_IFCHR) == S_IFCHR) Result = (TFileSystemAttributes)(Result | FSA_S_IFCHR);
	if ((iAttr & S_IFBLK) == S_IFBLK) Result = (TFileSystemAttributes)(Result | FSA_S_IFBLK);
	if ((iAttr & S_IFREG) == S_IFREG) Result = (TFileSystemAttributes)(Result | FSA_S_IFREG);
	if ((iAttr & S_IFIFO) == S_IFIFO) Result = (TFileSystemAttributes)(Result | FSA_S_IFIFO);
	if ((iAttr & S_IFLNK) == S_IFLNK) Result = (TFileSystemAttributes)(Result | FSA_S_IFLNK);
	if ((iAttr & S_IFSOCK) == S_IFSOCK) Result = (TFileSystemAttributes)(Result | FSA_S_IFSOCK);

	if ((iChmod & S_IRUSR) == S_IRUSR) Result = (TFileSystemAttributes)(Result | FSA_S_IRUSR); // Convert all chmod attributes
	if ((iChmod & S_IWUSR) == S_IWUSR) Result = (TFileSystemAttributes)(Result | FSA_S_IWUSR);
	if ((iChmod & S_IXUSR) == S_IXUSR) Result = (TFileSystemAttributes)(Result | FSA_S_IXUSR);
	if ((iChmod & S_IRGRP) == S_IRGRP) Result = (TFileSystemAttributes)(Result | FSA_S_IRGRP);
	if ((iChmod & S_IWGRP) == S_IWGRP) Result = (TFileSystemAttributes)(Result | FSA_S_IWGRP);
	if ((iChmod & S_IXGRP) == S_IXGRP) Result = (TFileSystemAttributes)(Result | FSA_S_IXGRP);
	if ((iChmod & S_IROTH) == S_IROTH) Result = (TFileSystemAttributes)(Result | FSA_S_IROTH);
	if ((iChmod & S_IWOTH) == S_IWOTH) Result = (TFileSystemAttributes)(Result | FSA_S_IWOTH);
	if ((iChmod & S_IXOTH) == S_IXOTH) Result = (TFileSystemAttributes)(Result | FSA_S_IXOTH);
	if ((iChmod & S_ISUID) == S_ISUID) Result = (TFileSystemAttributes)(Result | FSA_S_ISUID);
	if ((iChmod & S_ISGID) == S_ISGID) Result = (TFileSystemAttributes)(Result | FSA_S_ISGID);
	if ((iChmod & S_ISVTX) == S_ISVTX) Result = (TFileSystemAttributes)(Result | FSA_S_ISVTX);

	if ((iExt2Attr & EXT2_SECRM_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_SECRM_FL); // Convert all ext2 attributes
	if ((iExt2Attr & EXT2_UNRM_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_UNRM_FL);
	if ((iExt2Attr & EXT2_COMPR_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_COMPR_FL);
	if ((iExt2Attr & EXT2_SYNC_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_SYNC_FL);
	if ((iExt2Attr & EXT2_IMMUTABLE_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_IMMUTABLE_FL);
	if ((iExt2Attr & EXT2_APPEND_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_APPEND_FL);
	if ((iExt2Attr & EXT2_NODUMP_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_NODUMP_FL);
	if ((iExt2Attr & EXT2_NOATIME_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_NOATIME_FL);
	if ((iExt2Attr & EXT2_DIRTY_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_DIRTY_FL);
	if ((iExt2Attr & EXT2_COMPRBLK_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_COMPRBLK_FL);
	if ((iExt2Attr & EXT2_NOCOMP_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_NOCOMP_FL);
	if ((iExt2Attr & EXT2_ECOMPR_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_ECOMPR_FL);
	if ((iExt2Attr & EXT2_INDEX_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_INDEX_FL);
	if ((iExt2Attr & EXT2_JOURNAL_DATA_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_JOURNAL_DATA_FL);
	if ((iExt2Attr & EXT2_NOTAIL_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_NOTAIL_FL);
	if ((iExt2Attr & EXT2_DIRSYNC_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_DIRSYNC_FL);
	if ((iExt2Attr & EXT2_TOPDIR_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_TOPDIR_FL);
	if ((iExt2Attr & EXT2_HUGE_FILE_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_HUGE_FILE_FL);
	if ((iExt2Attr & EXT2_EXTENTS_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_EXTENTS_FL);
	if ((iExt2Attr & EXT2_EA_INODE_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_EA_INODE_FL);
	if ((iExt2Attr & EXT2_EOFBLOCKS_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_EOFBLOCKS_FL);
	if ((iExt2Attr & EXT2_INLINE_DATA_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_INLINE_DATA_FL);
	if ((iExt2Attr & EXT2_PROJINHERIT_FL) != 0) Result = (TFileSystemAttributes)(Result | FSA_EXT2_PROJINHERIT_FL);

	return Result; // return result
}
//	................................................................................................

//	................................................................................................
//  Convert TFileSystemAttributes to Linux file attributes
//	Input:
//			iValue - TFileSystemAttributes value
// 			oAttr - output Linux file attributes
// 			oChmod - output Linux chmod attributes
// 			oExt2Attr - output Linux ext2 attributes
//	Output:
//			none
//	................................................................................................
void FileSystemAttributes2LinuxAttaributes(TFileSystemAttributes iValue, UINT32 *oAttr, UINT32 *oChmod, UINT32 *oExt2Attr) {
	*oAttr = *oChmod = *oExt2Attr = 0; // Initialize outputs

	//if ((iValue & FSA_S_IFMT) != 0) *oAttr |= S_IFMT; // Convert all attributes
	if ((iValue & FSA_S_IFDIR) != 0) *oAttr |= S_IFDIR;
	if ((iValue & FSA_S_IFCHR) != 0) *oAttr |= S_IFCHR;
	if ((iValue & FSA_S_IFBLK) != 0) *oAttr |= S_IFBLK;
	if ((iValue & FSA_S_IFREG) != 0) *oAttr |= S_IFREG;
	if ((iValue & FSA_S_IFIFO) != 0) *oAttr |= S_IFIFO;
	if ((iValue & FSA_S_IFLNK) != 0) *oAttr |= S_IFLNK;
	if ((iValue & FSA_S_IFSOCK) != 0) *oAttr |= S_IFSOCK;

	if ((iValue & FSA_S_IRUSR) != 0) *oChmod |= S_IRUSR; // Convert all chmod attributes
	if ((iValue & FSA_S_IWUSR) != 0) *oChmod |= S_IWUSR;
	if ((iValue & FSA_S_IXUSR) != 0) *oChmod |= S_IXUSR;
	if ((iValue & FSA_S_IRGRP) != 0) *oChmod |= S_IRGRP;
	if ((iValue & FSA_S_IWGRP) != 0) *oChmod |= S_IWGRP;
	if ((iValue & FSA_S_IXGRP) != 0) *oChmod |= S_IXGRP;
	if ((iValue & FSA_S_IROTH) != 0) *oChmod |= S_IROTH;
	if ((iValue & FSA_S_IWOTH) != 0) *oChmod |= S_IWOTH;
	if ((iValue & FSA_S_IXOTH) != 0) *oChmod |= S_IXOTH;
	if ((iValue & FSA_S_ISUID) != 0) *oChmod |= S_ISUID;
	if ((iValue & FSA_S_ISGID) != 0) *oChmod |= S_ISGID;
	if ((iValue & FSA_S_ISVTX) != 0) *oChmod |= S_ISVTX;

	if ((iValue & FSA_EXT2_SECRM_FL) != 0) *oExt2Attr |= EXT2_SECRM_FL; // Convert all ext2 attributes
	if ((iValue & FSA_EXT2_UNRM_FL) != 0) *oExt2Attr |= EXT2_UNRM_FL;
	if ((iValue & FSA_EXT2_COMPR_FL) != 0) *oExt2Attr |= EXT2_COMPR_FL;
	if ((iValue & FSA_EXT2_SYNC_FL) != 0) *oExt2Attr |= EXT2_SYNC_FL;
	if ((iValue & FSA_EXT2_IMMUTABLE_FL) != 0) *oExt2Attr |= EXT2_IMMUTABLE_FL;
	if ((iValue & FSA_EXT2_APPEND_FL) != 0) *oExt2Attr |= EXT2_APPEND_FL;
	if ((iValue & FSA_EXT2_NODUMP_FL) != 0) *oExt2Attr |= EXT2_NODUMP_FL;
	if ((iValue & FSA_EXT2_NOATIME_FL) != 0) *oExt2Attr |= EXT2_NOATIME_FL;
	if ((iValue & FSA_EXT2_DIRTY_FL) != 0) *oExt2Attr |= EXT2_DIRTY_FL;
	if ((iValue & FSA_EXT2_COMPRBLK_FL) != 0) *oExt2Attr |= EXT2_COMPRBLK_FL;
	if ((iValue & FSA_EXT2_NOCOMP_FL) != 0) *oExt2Attr |= EXT2_NOCOMP_FL;
	if ((iValue & FSA_EXT2_ECOMPR_FL) != 0) *oExt2Attr |= EXT2_ECOMPR_FL;
	if ((iValue & FSA_EXT2_INDEX_FL) != 0) *oExt2Attr |= EXT2_INDEX_FL;
	if ((iValue & FSA_EXT2_JOURNAL_DATA_FL) != 0) *oExt2Attr |= EXT2_JOURNAL_DATA_FL;
	if ((iValue & FSA_EXT2_NOTAIL_FL) != 0) *oExt2Attr |= EXT2_NOTAIL_FL;
	if ((iValue & FSA_EXT2_DIRSYNC_FL) != 0) *oExt2Attr |= EXT2_DIRSYNC_FL;
	if ((iValue & FSA_EXT2_TOPDIR_FL) != 0) *oExt2Attr |= EXT2_TOPDIR_FL;
	if ((iValue & FSA_EXT2_HUGE_FILE_FL) != 0) *oExt2Attr |= EXT2_HUGE_FILE_FL;
	if ((iValue & FSA_EXT2_EXTENTS_FL) != 0) *oExt2Attr |= EXT2_EXTENTS_FL;
	if ((iValue & FSA_EXT2_EA_INODE_FL) != 0) *oExt2Attr |= EXT2_EA_INODE_FL;
	if ((iValue & FSA_EXT2_EOFBLOCKS_FL) != 0) *oExt2Attr |= EXT2_EOFBLOCKS_FL;
	if ((iValue & FSA_EXT2_INLINE_DATA_FL) != 0) *oExt2Attr |= EXT2_INLINE_DATA_FL;
	if ((iValue & FSA_EXT2_PROJINHERIT_FL) != 0) *oExt2Attr |= EXT2_PROJINHERIT_FL;
}
//	................................................................................................

#endif

//	................................................................................................
//  Check if a path is valid
//	Input:
//			iPath - string with path
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::IsValidPath(TString* iPath) {
	if (iPath == NULL) return FILE_SYSTEM_ERROR_INVALID_INPUT; // invalid pointer
#ifdef WINDOWS_SYSTEM
	if (iPath->Length < 3) return FILE_SYSTEM_ERROR_INVALID_ROOT; // path too short
#else
	if (iPath->Length < 1) return FILE_SYSTEM_ERROR_INVALID_ROOT; // path too short
#endif
	return IsValidPath(iPath->PChar()); // check path validity
}
//	................................................................................................
//	................................................................................................
//  Check if a path is valid
//	Input:
//			iPath - string with path
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::IsValidPath(CONST_PCHAR iPath) {
	if (iPath == NULL) return FILE_SYSTEM_ERROR_INVALID_INPUT; // invalid pointer or empty path
#ifdef WINDOWS_SYSTEM
	if (!(((*iPath >= 'A') && (*iPath <= 'Z')) || ((*iPath >= 'a') && (*iPath <= 'z')))) return FILE_SYSTEM_ERROR_INVALID_ROOT; // invalid drive letter
	if (iPath[1] != ':') return FILE_SYSTEM_ERROR_INVALID_ROOT; // missing colon after drive letter
	if (iPath[2] != PATH_SEPARATOR_CHAR) return FILE_SYSTEM_ERROR_INVALID_ROOT; // missing path separator after drive letter and colon

	CONST_PCHAR P = iPath + 3;
	CONST_PCHAR P1 = P;

	TString S;

	while (*P != 0) {
		switch (*P) {
			case '<':
			case '>':
			case ':':
			case '\"':
			case '/':
			case '|':
			case '?':
			case '*':
				return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR; // invalid character in path
			case '.': {
				if ((P[-1] == '.') && (P[-2] == '.')) return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR; // forbidden "..." sequence
			} break;
			case PATH_SEPARATOR_CHAR: {
				if (P[-1] == PATH_SEPARATOR_CHAR) return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR; // double path separator
				//if (TString::FindStringIndex(P1, (INT64)(P - P1), WIN_RESERVED_NAMES, 22) != -1) return FILE_SYSTEM_ERROR_FORBIDDEN_NAME; // reserved file name
				P1 = P + 1;
			} break;
		}
		P++;
	}

	if ((INT64)(P - iPath) > MAX_PATH_LENGTH) return FILE_SYSTEM_ERROR_PATH_TOO_LONG; // path too long

	return FILE_SYSTEM_SUCCESS; // path is valid
#else
	if (*iPath != '/') return FILE_SYSTEM_ERROR_INVALID_ROOT; // invalid drive letter

	CONST_PCHAR P = iPath + 1;
	CONST_PCHAR P1 = P;
	while (*P != 0) {
		switch (*P) {
			case '.': {
			} break;
			case '/': {
				if (P[-1] == '/') return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR; // double path separator
				if ((INT64)(P - P1) > MAX_FILE_NAME_LENGTH) return FILE_SYSTEM_ERROR_NAME_TOO_LONG; // file name too long
				P1 = P + 1;
			} break;
		}
		P++;
	}
#endif
	if ((INT64)(P - iPath) > MAX_PATH_LENGTH) return FILE_SYSTEM_ERROR_PATH_TOO_LONG; // path too long
	return 0; // OK
}
//	................................................................................................
//	................................................................................................
//  Check if a relative path is valid
//	Input:
//			iPath - string with path
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::IsValidRelativePath(TString* iPath) {
	if (iPath == NULL) return FILE_SYSTEM_ERROR_INVALID_INPUT; // invalid pointer
	return IsValidRelativePath(iPath->PChar()); // check path validity
}
//	................................................................................................
//	................................................................................................
//  Check if a relative path is valid
//	Input:
//			iPath - string with path
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::IsValidRelativePath(CONST_PCHAR iPath) {
	if (iPath == NULL) return FILE_SYSTEM_ERROR_INVALID_INPUT; // invalid pointer or empty path
#ifdef WINDOWS_SYSTEM

	CONST_PCHAR P = iPath; // start of path
	if (*P == 0) return FILE_SYSTEM_ERROR_EMPTY; // empty?

	if (*P == PATH_SEPARATOR_CHAR) return FILE_SYSTEM_ERROR_INVALID_ROOT; // missing path separator after drive letter and colon

	if (*P == '.') { // possible relative path?
		if (P[1] == 0) return FILE_SYSTEM_ERROR_CURRENT; // "."
		if (P[1] == '.') { // ..
			if (P[2] == 0) return FILE_SYSTEM_ERROR_PARENT; // ".."
			if (P[2] == PATH_SEPARATOR_CHAR) {
				if (P[3] == 0) return FILE_SYSTEM_ERROR_PARENT; // "..\"
				P += 3;
			}
		}
		else {
			if (P[1] == PATH_SEPARATOR_CHAR) {
				if (P[2] == 0) return FILE_SYSTEM_ERROR_CURRENT; // ".\"
				P += 2;
			} else return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR;
		}
	}

	CONST_PCHAR P1 = P;

	TString S;

	while (*P != 0) {
		switch (*P) {
		case '<':
		case '>':
		case ':':
		case '\"':
		case '/':
		case '|':
		case '?':
		case '*':
			return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR; // invalid character in path
		case '.': {
			if ((P >= iPath + 2) && (P[-1] == '.') && (P[-2] == '.')) return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR; // forbidden "..." sequence
		} break;
		case PATH_SEPARATOR_CHAR: {
			if (P[-1] == PATH_SEPARATOR_CHAR) return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR; // double path separator
			//if (TString::FindStringIndex(P1, (INT64)(P - P1), WIN_RESERVED_NAMES, 22) != -1) return FILE_SYSTEM_ERROR_FORBIDDEN_NAME; // reserved file name
			P1 = P + 1;
		} break;
		}
		P++;
	}

	if ((INT64)(P - iPath) > MAX_PATH_LENGTH) return FILE_SYSTEM_ERROR_PATH_TOO_LONG; // path too long

	return FILE_SYSTEM_SUCCESS; // path is valid
#else
	CONST_PCHAR P = iPath; // start of path
	if (*P == 0) return FILE_SYSTEM_ERROR_EMPTY; // empty?

	if (*P == PATH_SEPARATOR_CHAR) return FILE_SYSTEM_ERROR_INVALID_ROOT; // missing path separator after drive letter and colon

	if (*P == '.') { // possible relative path?
		if (P[1] == 0) return FILE_SYSTEM_ERROR_CURRENT; // "."
		if (P[1] == '.') { // ..
			if (P[2] == 0) return FILE_SYSTEM_ERROR_PARENT; // ".."
			if (P[2] == PATH_SEPARATOR_CHAR) {
				if (P[3] == 0) return FILE_SYSTEM_ERROR_PARENT; // "..\"
				P += 3;
			}
		}
		else {
			if (P[1] == PATH_SEPARATOR_CHAR) {
				if (P[2] == 0) return FILE_SYSTEM_ERROR_CURRENT; // ".\"
				P += 2;
			}
			else return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR;
		}
	}

	CONST_PCHAR P1 = P;
	while (*P != 0) {
		switch (*P) {
		case PATH_SEPARATOR_CHAR: {
			if (P[-1] == PATH_SEPARATOR_CHAR) return FILE_SYSTEM_ERROR_FORBIDDEN_CHAR; // double path separator
			if ((INT64)(P - P1) > MAX_FILE_NAME_LENGTH) return FILE_SYSTEM_ERROR_NAME_TOO_LONG; // file name too long
			P1 = P + 1;
		} break;
		}
		P++;
	}
#endif
	if ((INT64)(P - iPath) > MAX_PATH_LENGTH) return FILE_SYSTEM_ERROR_PATH_TOO_LONG; // path too long
	return 0; // OK
}
//	................................................................................................
//	................................................................................................
//  Append a path separator to the path if it does not end with one
//	Input:
//			ioPath - string with path
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::AppendPathSeparator(TString* ioPath, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(ioPath); // check path validity
		if (R != 0) return R; // invalid path?
	}
	ioPath->AppendChars(PATH_SEPARATOR_CHAR, 1, true); // append path separator if it does not exist
	return 0; // OK
}
//	................................................................................................
//	................................................................................................
//  Remove trailing path separator from the path if it exists
//	Input:
//			ioPath - string with path
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::RemovePathSeparator(TString* ioPath, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(ioPath); // check path validity
		if (R != 0) return R; // invalid path?
	}
#ifdef WINDOWS_SYSTEM
	if (ioPath->Length <= 3) return 0; // cannot remove path separator from root path
#else
	if (ioPath->Length <= 1) return 0; // cannot remove path separator
#endif
	if (ioPath->Value[ioPath->Length - 1] != PATH_SEPARATOR_CHAR) return 0; // no trailing path separator
	ioPath->SetLength(ioPath->Length - 1); // remove trailing path separator
	return 0; // OK
}
//	................................................................................................
//	................................................................................................
//  Extract directory path, file name and file extension from a full file path
//	Input:
//			iFullPath - full file path
// 			oDirectoryPath - output directory path
// 			oFileName - output file name with extension
// 			oFileNameOnly - output file name without extension
// 			oFileExtension - output file extension
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::ExtractPathParts(CONST_PCHAR iFullPath, TString* oDirectoryPath, TString* oFileName, TString* oFileNameOnly, TString* oFileExtension, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iFullPath); // check path validity
		if (R != 0) return R; // invalid path?
	}

	TString S = TString(iFullPath); // full path string

#ifdef WINDOWS_SYSTEM
	if (S.Length == 3) { // root path?
		if (oDirectoryPath != NULL) oDirectoryPath->SetValue(&S); // directory path is the full path
		if (oFileName != NULL) oFileName->SetLength(0); // empty file name
		if (oFileNameOnly != NULL) oFileNameOnly->SetLength(0); // empty file name only
		if (oFileExtension != NULL) oFileExtension->SetLength(0); // empty file extension
		return 0;
	}

	if (S.LastChar() == PATH_SEPARATOR_CHAR) { // path ends with separator?
		S.SetLength(S.Length - 1); // remove trailing separator for processing
	}
	INT64 LastSepIndex = S.ReverseFindChar(PATH_SEPARATOR_CHAR, -1);
	if (LastSepIndex <= 3) { // only root?
		if (oDirectoryPath != NULL) oDirectoryPath->SetValue(S.PChar(), 3); // directory path is the root
		if (oFileName != NULL) oFileName->SetValue(S.PChar() + 3, S.Length - 3); // file name is the rest
	}
	else {
		if (oDirectoryPath != NULL) oDirectoryPath->SetValue(S.PChar(), LastSepIndex); // directory path
		if (oFileName != NULL) oFileName->SetValue(S.PChar() + LastSepIndex + 1, S.Length - LastSepIndex - 1); // file name
	}
#else
	if (S.Length == 1) { // root path?
		if (oDirectoryPath != NULL) oDirectoryPath->SetValue(&S); // directory path is the full path
		if (oFileName != NULL) oFileName->SetLength(0); // empty file name
		if (oFileNameOnly != NULL) oFileNameOnly->SetLength(0); // empty file name only
		if (oFileExtension != NULL) oFileExtension->SetLength(0); // empty file extension
		return 0;
	}

	if (S.LastChar() == PATH_SEPARATOR_CHAR) { // path ends with separator?
		S.SetLength(S.Length - 1); // remove trailing separator for processing
	}

	INT64 LastSepIndex = S.ReverseFindChar(PATH_SEPARATOR_CHAR, -1);
	if (LastSepIndex <= 1) { // only root?
		if (oDirectoryPath != NULL) oDirectoryPath->SetValue(S.PChar(), LastSepIndex + 1); // directory path is the root
		if (oFileName != NULL) oFileName->SetValue(S.PChar() + 1, S.Length - 1); // file name is the rest
	}
	else {
		if (oDirectoryPath != NULL) oDirectoryPath->SetValue(S.PChar(), LastSepIndex); // directory path
		if (oFileName != NULL) oFileName->SetValue(S.PChar() + LastSepIndex + 1, S.Length - LastSepIndex - 1); // file name
	}
#endif
	if ((oFileNameOnly == NULL) && (oFileExtension == NULL)) return 0; // no need to extract further parts

	INT64 LastSepIndex1 = S.ReverseFindChar('.', -1);
	if (LastSepIndex1 < 0) { // no extension?
		if (oFileNameOnly != NULL) oFileNameOnly->SetValue(S.PChar() + LastSepIndex + 1, S.Length - LastSepIndex - 1); // file name only is the same as file name
		if (oFileExtension != NULL) oFileExtension->SetLength(0); // empty file extension
	}
	else {
		if (oFileNameOnly != NULL) oFileNameOnly->SetValue(S.PChar() + LastSepIndex + 1, LastSepIndex1 - LastSepIndex - 1); // file name only
		if (oFileExtension != NULL) oFileExtension->SetValue(S.PChar() + LastSepIndex1 + 1, S.Length - LastSepIndex1 - 1); // file extension
	}

	return 0; // OK
}
//	................................................................................................
//	................................................................................................
//  Extract directory path, file name and file extension from a full file path
//	Input:
//			iFullPath - full file path
// 			oDirectoryPath - output directory path
// 			oFileName - output file name with extension
// 			oFileNameOnly - output file name without extension
// 			oFileExtension - output file extension
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::ExtractPathParts(TString* iFullPath, TString* oDirectoryPath, TString* oFileName, TString* oFileNameOnly, TString* oFileExtension, BOOL iCheckPath) {
	if (iFullPath == NULL) return FILE_SYSTEM_ERROR_INVALID_INPUT; // invalid pointer
	return ExtractPathParts(iFullPath->PChar(), oDirectoryPath, oFileName, oFileNameOnly, oFileExtension, iCheckPath); // extract path parts
}
//	................................................................................................
//	................................................................................................
//  Normalize a file path
//	Input:
//			iPath - string with path
// 			oResult - string with normalized path
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::NormalizePath(CONST_PCHAR iPath, TString* oResult, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iPath); // check path validity
		if (R != 0) return R; // invalid path?
	}

	oResult->SetValue(iPath); // set result to input path

	CONST_PCHAR P;

#ifdef WINDOWS_SYSTEM
	if (oResult->Length == 3) return 0; // root path, nothing to normalize
	P = oResult->Value + 2; // start after "C:\"
#else
	if (oResult->Length == 1) return 0; // root path, nothing to normalize
	P = oResult->Value + 0; // start after "/"
#endif

	PCHAR S = (PCHAR)P;
	PCHAR P1 = S;

	while (*P != 0) {
		if (*P == PATH_SEPARATOR_CHAR) {
			if (P[1] == 0) break; // end of string?
			if (P[1] == '.') { // ".\" or "..\"
				if (P[2] == 0) break; // ends "\."?
				if (P[2] == PATH_SEPARATOR_CHAR) { // "\.\"
					*P1 = *P;
					P += 2; // skip ".\"
					continue;
				}
				if (P[2] == '.') { // "..\"
					if (P[3] == 0) break; // ends "\.."?
					if (P[3] == PATH_SEPARATOR_CHAR) { // "\..\"
						// go back to previous path separator
						if (P1 > S)
						{
							P1--; // move back from current path separator
							while ((P1 > S) && (P1[-1] != PATH_SEPARATOR_CHAR)) P1--; // move back to previous path separator
							P--; P1--;
						}
						else P1++;
						P += 4; // skip "..\"
						continue;
					}
				}
			}
		}
		*P1++ = *P++; // copy character
	}

	INT64 L = (INT64)(P1 - oResult->Value);
#ifdef WINDOWS_SYSTEM
	if (L <= 3) oResult->SetLength(3); // set new length
	else {
		oResult->SetLength(L); // set new length
		if (oResult->Value[L-1] == PATH_SEPARATOR_CHAR) { // trailing path separator?
			oResult->SetLength(L-1); // remove it
		}
	}
#else
	if (L <= 1) oResult->SetLength(1); // set new length
	else {
		oResult->SetLength(L); // set new length
		if (oResult->Value[L - 1] == PATH_SEPARATOR_CHAR) { // trailing path separator?
			oResult->SetLength(L - 1); // remove it
		}
	}
#endif

	return 0; // OK
}
//	................................................................................................
//	................................................................................................
//  Normalize a file path
//	Input:
//			iPath - string with path
//			ioResult - string with normalized path
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::NormalizePath(TString* ioResult, BOOL iCheckPath) {
	TString Res; 
	INT32 R = NormalizePath(ioResult->PChar(), &Res, iCheckPath); // normalize path
	if (R != 0) return R; // error?	
	ioResult->SetValue(Res); // set normalized path
	return 0; // OK
}
//	................................................................................................
//	................................................................................................
//  Append value to path
//	Input:
//			iPath - string with path
//			iValue - value to append
//			oResult - output string with resulting path
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::AppendToPath(CONST_PCHAR iPath, CONST_PCHAR iValue, TString* oResult, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iPath); // check path validity
		if (R != 0) return R; // invalid path?

		R = IsValidRelativePath(iValue); // check relative path validity
		if (R != 0) return R; // invalid relative path?
	}

	oResult->SetValue(iPath); // set initial path
	oResult->AppendChars(PATH_SEPARATOR_CHAR, 1, true); // append path separator if it does not exist

	oResult->AppendValue(iValue); // append value
	return NormalizePath(oResult); // normalize resulting path
}
//	................................................................................................
//	................................................................................................
//  Append value to path
//	Input:
//			ioPath - string with path and output
//			iValue - value to append
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::AppendToPath(TString* ioPath, CONST_PCHAR iValue, BOOL iCheckPath) {
	if (ioPath == NULL) return FILE_SYSTEM_ERROR_INVALID_INPUT; // invalid pointer
	TString Res;
	INT32 R = AppendToPath(ioPath->PChar(), iValue, &Res, iCheckPath);
	if (R != 0) return R; // error?	
	ioPath->SetValue(Res); // set resulting path
	return 0;
}
//	................................................................................................
//	................................................................................................
//  Create a full file path from directory path, file name and file extension
//	Input:
//			oResult - output full file path
//			iPath - directory path
// 			iFileNameOnly - file name without extension
// 			iExt - file extension
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::CreateFullPath(TString* oResult, CONST_PCHAR iPath, CONST_PCHAR iFileNameOnly, CONST_PCHAR iExt) {
	if (!IS_PCHAR_EMPTY(iPath)) { // Check path validity only if iPath not empty
		INT32 R = IsValidPath(iPath); // check path validity
		if (R != 0) return R; // invalid path?
	}

	oResult->SetValue(iPath); // set initial path
	AppendPathSeparator(oResult); // append path separator if it does not exist
	
	if (IS_PCHAR_EMPTY(iFileNameOnly)) {
		if (IS_PCHAR_EMPTY(iExt)) return 0;
		oResult->AppendChars('.', 1); // append dot for extension
		oResult->AppendValue(iExt); // append extension
		return 0;
	}
	oResult->AppendValue(iFileNameOnly); // append file name
	if (IS_PCHAR_EMPTY(iExt)) return 0;
	oResult->AppendChars('.', 1); // append dot for extension
	oResult->AppendValue(iExt); // append extension
	return 0;
}
//	................................................................................................
//	................................................................................................
//  Append file extension to file name
//	Input:
//			ioFileName - input/output file name
//			iExt - file extension
// 			iReplace - whether to replace existing extension
// 			iOnlyIfNoetExists - append only if no extension exists
//	Output:
//			none
//	................................................................................................
void TFileSystem::ApppendExt(TString* ioFileName, CONST_PCHAR iExt, BOOL iReplace, BOOL iOnlyIfNoetExists) {
	TString N, E;
	INT32 R = ExtractPathParts(ioFileName, NULL, NULL, &N, &E, false); // extract file name and extension
	if (R != 0) return; // error?

	if (iOnlyIfNoetExists) {
		if (E.IsEqual(iExt)) return; // extension already exists
	}
	if (iReplace) {
		if (!E.IsEqual(iExt)) {
			INT64 I = ioFileName->ReverseFindChar('.', -1);
			if (I >= 0) {
				ioFileName->SetLength(I); // remove existing extension
			}
		}
	}

	ioFileName->AppendChars('.', 1); // append dot for extension
	ioFileName->AppendValue(iExt); // append extension
}
//	................................................................................................
//	................................................................................................
//  Get current working directory
//	Input:
//			oDirectoryPath - output directory path
//	Output:
//			none
//	................................................................................................
void TFileSystem::GetCurrentDirectory(TString* oDirectoryPath) {
	oDirectoryPath->Reallocate(MAX_PATH_LENGTH + 1, false); // allocate buffer
#ifdef WINDOWS_SYSTEM
	UINT32 L = ::GetCurrentDirectoryA(MAX_PATH_LENGTH, oDirectoryPath->Value);
	oDirectoryPath->Value[oDirectoryPath->Length = L] = 0;
#else
	if (getcwd(oDirectoryPath->Value, MAX_PATH_LENGTH) == NULL) {
		oDirectoryPath->Length = 0;
		return;
	}
	oDirectoryPath->Length = FNC_STRLEN(oDirectoryPath->Value);
#endif
}
//	................................................................................................
//	................................................................................................
//  Create a directory
//	Input:
//			iDirectoryPath - directory path
//			iCreateFullPath - create full path if intermediate directories do not exist
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::CreateDirectory(CONST_PCHAR iDirectoryPath, BOOL iCreateFullPath, BOOL iCheckPath) {

	if (iCheckPath) { // check path validity?
		INT32 R = IsValidPath(iDirectoryPath);
		if (R != 0) return R;
	}

#ifdef WINDOWS_SYSTEM
	if (!iCreateFullPath) {
		if (::CreateDirectoryA(iDirectoryPath, NULL) != 0) return 0; // directory created successfully
		INT32 R = GetLastError();
		if (R == ERROR_PATH_NOT_FOUND) return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		if (R == ERROR_ALREADY_EXISTS) return FILE_SYSTEM_ERROR_DIRECTORY_EXISTS; // directory already exists
		return 0; // directory already exists
	}

	TString Parent;
	INT32 R = ExtractPathParts(iDirectoryPath, &Parent, NULL, NULL, NULL, false); // check path validity
	if (R != 0) return R; // invalid path?

	R = DirectoryExists(Parent.PChar(), false); // check if parent directory exists
	if (R != FILE_SYSTEM_TRUE) {
		R = CreateDirectory(Parent.PChar(), true, false);
		if ((R != 0) && (R != FILE_SYSTEM_ERROR_DIRECTORY_EXISTS)) return R;
	}

	if (::CreateDirectoryA(iDirectoryPath, NULL) != 0) return 0; // directory created successfully
	if (GetLastError() != ERROR_PATH_NOT_FOUND) return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
	return 0; // directory already exists
#else
	if (!iCreateFullPath) {
		INT32 R = mkdir(iDirectoryPath, 0777); // create directory
		if (R == 0) return 0; // directory created successfully
		switch(errno) {
			case EEXIST:
				return 0; // directory already exists
			case ENOENT:
				return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
			default:
				return FILE_SYSTEM_ERROR_DIRECTORY_CREATE; // unknown error
		}
	}
	TString Parent;
	INT32 R = ExtractPathParts(iDirectoryPath, &Parent, NULL, NULL, NULL, false); // check path validity
	if (R != 0) return R; // invalid path?

	R = DirectoryExists(Parent.PChar(), false); // check if parent directory exists
	if (R != FILE_SYSTEM_TRUE) {
		R = CreateDirectory(Parent.PChar(), true, false);
		if (R != 0) return R;
	}

	R = mkdir(iDirectoryPath, 0777); // create directory
	if (R == 0) return 0; // directory created successfully
	switch (errno) {
	case EEXIST:
		return FILE_SYSTEM_ERROR_DIRECTORY_EXISTS; // directory already exists
	case ENOENT:
		return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
	default:
		return FILE_SYSTEM_ERROR_DIRECTORY_CREATE; // unknown error
	}
#endif
}
//	................................................................................................
//	................................................................................................
//  Check if a directory exists
//	Input:
//			iDirectoryPath - directory path
// 			iCheckPath - whether to check path validity
//	Output:
//			FILE_SYSTEM_FALSE, FILE_SYSTEM_TRUE or error code
//	................................................................................................
INT32 TFileSystem::DirectoryExists(CONST_PCHAR iDirectoryPath, BOOL iCheckPath) {
#ifdef WINDOWS_SYSTEM

	if (iCheckPath) {
		INT32 R = IsValidPath(iDirectoryPath); // check path validity
		if (R != 0) return R; // invalid path?
	}

	TString S(iDirectoryPath); RemovePathSeparator(&S); // remove trailing path separator if it exists

	UINT32 Attributes = ::GetFileAttributesA(S.PChar());
	if (Attributes == INVALID_FILE_ATTRIBUTES) return FILE_SYSTEM_FALSE; // cannot get attributes
	return ((Attributes & FILE_ATTRIBUTE_DIRECTORY) != 0) ? FILE_SYSTEM_TRUE : FILE_SYSTEM_ERROR_NOT_DIRECTORY; // not a directory
#else
	if (iCheckPath) {
		INT32 R = IsValidPath(iDirectoryPath); // check path validity
		if (R != 0) return R; // invalid path?
	}

	struct stat info;
	if (stat(iDirectoryPath, &info) != 0) return FILE_SYSTEM_FALSE;
	return S_ISDIR(info.st_mode) ? FILE_SYSTEM_TRUE : FILE_SYSTEM_ERROR_NOT_DIRECTORY;
#endif
}
//	................................................................................................
//	................................................................................................
//  Check if a directory is empty
//	Input:
//			iDirectoryPath - directory path
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::IsDirectoryEmpty(CONST_PCHAR iDirectoryPath, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iDirectoryPath); // check path validity
		if (R != 0) return R; // invalid path?
	}

	if (DirectoryExists(iDirectoryPath, false) != FILE_SYSTEM_TRUE) return FILE_SYSTEM_ERROR_NOT_DIRECTORY; // not a directory

#ifdef WINDOWS_SYSTEM
	WIN32_FIND_DATAA FindData;
	TString SearchPath = TString(iDirectoryPath); AppendPathSeparator(&SearchPath, false); AppendToPath(&SearchPath, "*", false); // create search path

	HANDLE hFind = FindFirstFileA(SearchPath.PChar(), &FindData); // start searching
	if (hFind == INVALID_HANDLE_VALUE) return FILE_SYSTEM_ERROR_DIRECTORY_READ; // cannot read directory

	INT32 Res  = FILE_SYSTEM_TRUE;
	do {
		if (FindData.cFileName[0] == '.') {
			if (FindData.cFileName[1] == 0) continue; // skip "."
			if (FindData.cFileName[1] == '.') {
				if (FindData.cFileName[2] == 0) continue; // skip ".."
			}
		}
		Res = FILE_SYSTEM_FALSE; // found a file or directory
		break;
	} while (FindNextFileA(hFind, &FindData)); // continue searching
	
	FindClose(hFind); // close search handle
	return Res; // return result
#else

	struct dirent* entry;
	DIR* dir = opendir(iDirectoryPath); // open directory
	if (dir == NULL) return FILE_SYSTEM_ERROR_DIRECTORY_READ;

	INT32 Res = FILE_SYSTEM_TRUE;
	while ((entry = readdir(dir)) != NULL) { // read directory entries...
		if (entry->d_name[0] == '.') {
			if (entry->d_name[1] == 0) continue; // skip "."
			if (entry->d_name[1] == '.') {
				if (entry->d_name[2] == 0) continue; // skip ".."
			}
		}
		Res = FILE_SYSTEM_FALSE; // found a file or directory
		break;
	}

	closedir(dir); // close directory
	return Res; // return result
#endif
}
//	................................................................................................
//	................................................................................................
//  Delete a directory
//	Input:
//			iDirectoryPath - directory path
// 			iRecursive - whether to delete contents recursively
// 			iForceDelete - whether to force delete (ignore read-only attribute)
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::DeleteDirectory(CONST_PCHAR iDirectoryPath, BOOL iRecursive, BOOL iForceDelete, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iDirectoryPath); // check path validity
		if (R != 0) return R; // invalid path?
	}
#ifdef WINDOWS_SYSTEM

	if (!iRecursive) {
		if (iForceDelete) ::SetFileAttributesA(iDirectoryPath, FILE_ATTRIBUTE_NORMAL); // set normal attributes

		if (::RemoveDirectoryA(iDirectoryPath) != 0) return 0; // directory removed successfully
		switch (GetLastError()) {
			case ERROR_PATH_NOT_FOUND:
			case ERROR_FILE_NOT_FOUND:
			case ERROR_DIRECTORY:
				return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
			case ERROR_DIR_NOT_EMPTY:
				return FILE_SYSTEM_ERROR_DIRECTORY_NOT_EMPTY; // directory not empty
			case ERROR_ACCESS_DENIED: // access denied
				return FILE_SYSTEM_ERROR_ACCESS;
			default:
				return FILE_SYSTEM_ERROR_DIRECTORY_DELETE; // unknown error
		}
	}

	WIN32_FIND_DATAA FindData;
	TString SearchPath = TString(iDirectoryPath); AppendPathSeparator(&SearchPath, false); AppendToPath(&SearchPath, "*", false); // create search path

	HANDLE hFind = FindFirstFileA(SearchPath.PChar(), &FindData); // start searching
	if (hFind == INVALID_HANDLE_VALUE) {
		return DeleteDirectory(iDirectoryPath, false, iForceDelete, false); // try deleting empty directory
	}

	INT32 Res = FILE_SYSTEM_TRUE;
	do {
		if (FindData.cFileName[0] == '.') {
			if (FindData.cFileName[1] == 0) continue; // skip "."
			if (FindData.cFileName[1] == '.') {
				if (FindData.cFileName[2] == 0) continue; // skip ".."
			}
		}

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // directory?
			SearchPath.SetValue(iDirectoryPath); AppendPathSeparator(&SearchPath, false); AppendToPath(&SearchPath, FindData.cFileName, false); // create subdirectory path
			Res = DeleteDirectory(SearchPath.PChar(), true, iForceDelete, false); // delete subdirectory recursively
			if (Res != 0) {
				FindClose(hFind); // close search handle
				return Res; // error?
			}
		}
		else { // file
			SearchPath.SetValue(iDirectoryPath); AppendPathSeparator(&SearchPath, false); AppendToPath(&SearchPath, FindData.cFileName, false); // create subdirectory path
			INT32 R = DeleteFile(SearchPath.PChar(), iForceDelete, false);
			if (R != 0) {
				FindClose(hFind); // close search handle
				return R; // cannot delete file
			}
		}

	} while (FindNextFileA(hFind, &FindData)); // continue searching

	FindClose(hFind); // close search handle

	return DeleteDirectory(iDirectoryPath, false, iForceDelete, false); // try deleting empty directory
#else
	if (!iRecursive) {
		if (iForceDelete) chmod(iDirectoryPath, 0755); // set write permissions
		if (rmdir(iDirectoryPath) == 0) return 0; // directory removed successfully
		return FILE_SYSTEM_ERROR_DIRECTORY_DELETE; // error
	}

	struct dirent* entry;
	DIR* dir = opendir(iDirectoryPath); // open directory
	if (dir == NULL) return DeleteDirectory(iDirectoryPath, false, iForceDelete, false); // try deleting empty directory

	INT32 Res = FILE_SYSTEM_TRUE;
	while ((entry = readdir(dir)) != NULL) { // read directory entries...
		if (entry->d_name[0] == '.') {
			if (entry->d_name[1] == 0) continue; // skip "."
			if (entry->d_name[1] == '.') {
				if (entry->d_name[2] == 0) continue; // skip ".."
			}
		}

		TString SubDirPath = TString(iDirectoryPath); AppendPathSeparator(&SubDirPath, false); AppendToPath(&SubDirPath, entry->d_name, false); // create subdirectory path

		struct stat st;
		if (stat(SubDirPath.PChar(), &st) == -1) { // get file/dir status
			closedir(dir); // close directory
			return DeleteDirectory(iDirectoryPath, false, iForceDelete, false); // try delete directory
		}

		if (S_ISDIR(st.st_mode)) { // directory?
			Res = DeleteDirectory(SubDirPath.PChar(), true, iForceDelete, false); // delete subdirectory recursively
			if (Res != 0) {
				closedir(dir); // close directory
				return Res; // error?
			}
		}
		else { // file
			INT32 R = DeleteFile(SubDirPath.PChar(), iForceDelete, false);
			if (R != 0) {
				closedir(dir); // close directory
				return R; // cannot delete file
			}
		}
	}

	closedir(dir); // close directory

	return DeleteDirectory(iDirectoryPath, false, iForceDelete, false); // try deleting empty directory
#endif
}
//	................................................................................................
//	................................................................................................
//  Check if a file exists
//	Input:
//			iFilePath - file path
// 			iCheckPath - whether to check path validity
//	Output:
//			FILE_SYSTEM_FALSE, FILE_SYSTEM_TRUE or error code
//	................................................................................................
INT32 TFileSystem::FileExists(CONST_PCHAR iFilePath, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iFilePath); // check path validity
		if (R != 0) return R; // invalid path?
	}
#ifdef WINDOWS_SYSTEM

	TString S(iFilePath); RemovePathSeparator(&S); // remove trailing path separator if it exists

	UINT32 Attributes = ::GetFileAttributesA(S.PChar());
	if (Attributes == INVALID_FILE_ATTRIBUTES) return FILE_SYSTEM_FALSE; // cannot get attributes
	return ((Attributes & FILE_ATTRIBUTE_DIRECTORY) == 0) ? FILE_SYSTEM_TRUE : FILE_SYSTEM_ERROR_NOT_FILE; // not a directory
#else
	struct stat info;
	if (stat(iFilePath, &info) != 0) return FILE_SYSTEM_FALSE;
	return S_ISREG(info.st_mode) ? FILE_SYSTEM_TRUE : FILE_SYSTEM_ERROR_NOT_FILE;
#endif
}
//	................................................................................................
//	................................................................................................
//  Delete a file
//	Input:
//			iFilePath - file path
// 			iForceDelete - whether to force delete (ignore read-only attribute)
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::DeleteFile(CONST_PCHAR iFilePath, BOOL iForceDelete, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iFilePath); // check path validity
		if (R != 0) return R; // invalid path?
	}
#ifdef WINDOWS_SYSTEM
	if (iForceDelete) ::SetFileAttributesA(iFilePath, FILE_ATTRIBUTE_NORMAL); // set normal attributes
	if (::DeleteFileA(iFilePath) != 0) return 0; // file deleted successfully
	INT32 LE = GetLastError();
	switch (LE) {
		case ERROR_FILE_NOT_FOUND:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		case ERROR_PATH_NOT_FOUND:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		case ERROR_DIRECTORY:
			return FILE_SYSTEM_ERROR_NOT_FILE; // no a file?
		case ERROR_ACCESS_DENIED:
			return FILE_SYSTEM_ERROR_ACCESS; // access denied
		default:
			return FILE_SYSTEM_ERROR_FILE_DELETE; // unknown error
	}
#else
	if (iForceDelete) chmod(iFilePath, 0755); // set write permissions
	if (remove(iFilePath) == 0) return 0; // file deleted successfully
	switch (errno) {
		case ENOENT:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		case EISDIR:
			return FILE_SYSTEM_ERROR_NOT_FILE; // no a file?
		default:
			return FILE_SYSTEM_ERROR_FILE_DELETE; // unknown error
	}
	return 0;
#endif
}
//	................................................................................................
//	................................................................................................
//  Rename a file
//	Input:
//			iOldFilePath - old file path (full path)
// 			iNewFilePath - new file path (name only)
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::RenameFile(CONST_PCHAR iOldFilePath, CONST_PCHAR iNewFilePath, BOOL iCheckPath) {
	INT32 R = FileExists(iOldFilePath, iCheckPath); // check if old file exists
	if (R != FILE_SYSTEM_TRUE) return R; // old file does not exist

	R = FileExists(iNewFilePath, iCheckPath); // check if new file exists
	if (R != FILE_SYSTEM_FALSE) return R; // new file exist

#ifdef WINDOWS_SYSTEM
	if (::MoveFileA(iOldFilePath, iNewFilePath) != 0) return 0; // file renamed successfully
	INT32 LE = GetLastError();
	switch (LE) {
		case ERROR_FILE_NOT_FOUND:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		case ERROR_PATH_NOT_FOUND:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		case ERROR_ALREADY_EXISTS:
			return FILE_SYSTEM_ERROR_FILE_EXISTS; // new file already exists
		case ERROR_ACCESS_DENIED:
			return FILE_SYSTEM_ERROR_ACCESS; // access denied
		default:
			return FILE_SYSTEM_ERROR_FILE_RENAME; // unknown error
	}
#else
	if (rename(iOldFilePath, iNewFilePath) == 0) return 0; // file renamed successfully
	switch (errno) {
		case ENOENT:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		case EEXIST:
			return FILE_SYSTEM_ERROR_FILE_EXISTS; // new file already exists
		case EACCES:
			return FILE_SYSTEM_ERROR_ACCESS; // access denied
		default:
			return FILE_SYSTEM_ERROR_FILE_RENAME; // unknown error
	}
#endif

	return 0; // OK
}
//	................................................................................................
//	................................................................................................
//  Generate a temporary file name
//	Input:
//			oTempFileName - resulting temporary file name
// 			iDirectoryPath - directory path for the temp file
// 			iExt - file extension
//	Output:
//			none
//	................................................................................................
void TFileSystem::GenerateTempFileName(TString* oTempFileName, CONST_PCHAR iDirectoryPath, CONST_PCHAR iExt) {
	TString FN; FN.Format("%llu%llu", (UINT64)TDateTime::GetCurrentDateTime(true)/10000, TEnvironment::GenerateRandomUINT64()); // generate file name based on tick count
	CreateFullPath(oTempFileName, iDirectoryPath, FN.PChar(), iExt); // create full path
}
//	................................................................................................
//	................................................................................................
//  Get file attributes
//	Input:
//			iPath - file path
// 			oAttr - output attributes
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::GetFileAttributes(CONST_PCHAR iPath, TFileSystemAttributes* oAttr, BOOL iCheckPath) {
	*oAttr = FSA_INVALID_VALUE; // default invalid value

	if (iCheckPath) {
		INT32 R = IsValidPath(iPath); // check path validity
		if (R != 0) return R; // invalid path?
	}
#ifdef WINDOWS_SYSTEM
	UINT32 A = ::GetFileAttributesA(iPath); // get attributes
	if (A != INVALID_FILE_ATTRIBUTES) {
		if ((A & FILE_ATTRIBUTE_DIRECTORY) != 0) return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS;
		*oAttr = WindowsAttaributes2FileSystemAttributes(A); // convert and return
		return 0;
	}
	switch (GetLastError()) {
		case ERROR_FILE_NOT_FOUND:
			return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS; // path not found?
		case ERROR_PATH_NOT_FOUND:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		default:
			return FILE_SYSTEM_ERROR_GET_ATTRIBUTES; // unknown error
	}
#else
	struct stat st;

	if (stat(iPath, &st) != 0) { // get attributes
		switch(errno) {
			case ENOENT:
				return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS; // path not found?
			case ENOTDIR:
				return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
			default:
				return FILE_SYSTEM_ERROR_GET_ATTRIBUTES;
		}
	}

	if ((st.st_mode & S_IFDIR) != 0) return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS;

	UINT32 Attr, Chmod, Ext2Attr;
	Attr = (UINT64)(st.st_mode & S_IFMT);
	Chmod = (UINT64)st.st_mode;
	Ext2Attr = 0;

	*oAttr = LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr); // convert 
	return 0; // OK
#endif
}
//	................................................................................................
//	................................................................................................
//  Set file attributes
//	Input:
//			iPath - file path
// 			iAttr - attributes to set
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::SetFileAttributes(CONST_PCHAR iPath, TFileSystemAttributes iAttr, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iPath); // check path validity
		if (R != 0) return R; // invalid path?
	}
#ifdef WINDOWS_SYSTEM
	if (::SetFileAttributesA(iPath, FileSystemAttributes2WindowsAttaributes(iAttr)) != 0) return 0; // set attributes
	switch (GetLastError()) {
		case ERROR_FILE_NOT_FOUND:
			return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS; // path not found?
		case ERROR_PATH_NOT_FOUND:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		default:
			return FILE_SYSTEM_ERROR_SET_ATTRIBUTES;
	}
#else
	UINT32 Attr, Chmod, Ext2Attr;
	FileSystemAttributes2LinuxAttaributes(iAttr, &Attr, &Chmod, &Ext2Attr);

	if (chmod(iPath, Chmod) != 0) { // set chmod
		switch (errno) {
		case ENOENT:
			return FILE_SYSTEM_ERROR_FILE_NOT_EXISTS; // path not found?
		case ENOTDIR:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		default:
			return FILE_SYSTEM_ERROR_SET_ATTRIBUTES;
		}
	}
	return 0;
#endif
}
//	................................................................................................
//	................................................................................................
//  Get directory attributes
//	Input:
//			iPath - directory path
// 			oAttr - output attributes
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::GetDirectoryAttributes(CONST_PCHAR iPath, TFileSystemAttributes* oAttr, BOOL iCheckPath) {
	*oAttr = FSA_INVALID_VALUE; // default invalid value

	if (iCheckPath) {
		INT32 R = IsValidPath(iPath); // check path validity
		if (R != 0) return R; // invalid path?
	}
#ifdef WINDOWS_SYSTEM
	UINT32 A = ::GetFileAttributesA(iPath); // get attributes
	if (A != INVALID_FILE_ATTRIBUTES) {
		if ((A & FILE_ATTRIBUTE_DIRECTORY) == 0) return FILE_SYSTEM_ERROR_DIRECTORY_NOT_EXISTS;
		*oAttr = WindowsAttaributes2FileSystemAttributes(A); // convert and return
		return 0;
	}
	switch (GetLastError()) {
	case ERROR_FILE_NOT_FOUND:
		return FILE_SYSTEM_ERROR_DIRECTORY_NOT_EXISTS; // path not found?
	case ERROR_PATH_NOT_FOUND:
		return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
	default:
		return FILE_SYSTEM_ERROR_GET_ATTRIBUTES; // unknown error
	}
#else
	struct stat st;

	if (stat(iPath, &st) != 0) { // get attributes
		return FILE_SYSTEM_ERROR_GET_ATTRIBUTES;
	}

	if ((st.st_mode & S_IFDIR) == 0) return FILE_SYSTEM_ERROR_DIRECTORY_NOT_EXISTS;

	UINT32 Attr, Chmod, Ext2Attr;
	Attr = (UINT64)(st.st_mode & S_IFMT);
	Chmod = (UINT64)st.st_mode;
	Ext2Attr = 0;

	*oAttr = LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr); // convert 
	return 0; // OK
#endif
}
//	................................................................................................
//	................................................................................................
//  Set directory attributes
//	Input:
//			iPath - directory path
// 			iAttr - attributes to set
// 			iCheckPath - whether to check path validity
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::SetDirectoryAttributes(CONST_PCHAR iPath, TFileSystemAttributes iAttr, BOOL iCheckPath) {
	if (iCheckPath) {
		INT32 R = IsValidPath(iPath); // check path validity
		if (R != 0) return R; // invalid path?
	}
#ifdef WINDOWS_SYSTEM
	if (::SetFileAttributesA(iPath, FileSystemAttributes2WindowsAttaributes(iAttr) | FILE_ATTRIBUTE_DIRECTORY) != 0) return 0; // set attributes
	switch (GetLastError()) {
	case ERROR_FILE_NOT_FOUND:
		return FILE_SYSTEM_ERROR_DIRECTORY_NOT_EXISTS; // path not found?
	case ERROR_PATH_NOT_FOUND:
		return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
	default:
		return FILE_SYSTEM_ERROR_SET_ATTRIBUTES;
	}
#else
	UINT32 Attr, Chmod, Ext2Attr;
	FileSystemAttributes2LinuxAttaributes(iAttr, &Attr, &Chmod, &Ext2Attr);

	if (chmod(iPath, Chmod) != 0) { // set chmod
		switch (errno) {
		case ENOENT:
			return FILE_SYSTEM_ERROR_DIRECTORY_NOT_EXISTS; // path not found?
		case ENOTDIR:
			return FILE_SYSTEM_ERROR_PATH_NOT_EXISTS; // path not found?
		default:
			return FILE_SYSTEM_ERROR_SET_ATTRIBUTES;
		}
	}
	return 0;
#endif
}
//	................................................................................................

//	................................................................................................
//  Enumerate files and directories in a directory - internal implementation
//	Input:
//			iPath - directory path
// 			iUserData - user data pointer passed to filter function
// 			iFilterFunction - filter function called for each file/directory found
//	Output:
//			0 or error code
//	................................................................................................
INT32 _Enumerate(BOOL iIsDir, CONST_PCHAR iPath, PENUM_ITEM iParent, PVOID iUserData, TEnumerateFilterFunction iFilterFunction) {

#ifdef WINDOWS_SYSTEM

	WIN32_FIND_DATAA FindData;
	ENUM_ITEM EntryInfo;
	ULARGE_INTEGER U;
	INT32 R;
	TString P;

	INT64 C_Accepted = 0; // count of items found and accepted
	INT64 C_Skipped = 0; // count of items found and skipped

	TString SearchPath = TString(iPath); 

	if (iIsDir) { // directory?
		TFileSystem::AppendPathSeparator(&SearchPath, false); SearchPath.AppendChars('*', 1); // create search path
	}
	HANDLE hFind = FindFirstFileA(SearchPath.PChar(), &FindData); // start searching
	if (hFind == INVALID_HANDLE_VALUE) { // error?
		if (iFilterFunction == NULL) return iParent == NULL ? FILE_SYSTEM_ERROR_DIRECTORY_READ : 0; // cannot read directory

		EntryInfo.Path = iPath;
		EntryInfo.NameOnly = "";

		R = iFilterFunction(ENUMERATE_STATE_ERROR, &EntryInfo, iUserData); // call filter function for handle error
		switch (R) {
			case ENUMERATE_ACTION_ABORT:
				return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // abort enumeration
			default:
				return 0; // return and continue enumeration
		}
	}

	if (iIsDir) {
		SearchPath.SetLength(SearchPath.Length - 1); // remove '*'
	}

	do {
		if (FindData.cFileName[0] == '.') {
			if (FindData.cFileName[1] == 0) continue; // skip "."
			if (FindData.cFileName[1] == '.') {
				if (FindData.cFileName[2] == 0) continue; // skip ".."
			}
		}

		if (!iIsDir) { // not directory?
			TFileSystem::ExtractPathParts(iPath, &P, NULL, NULL, NULL, false); // extract path part
			EntryInfo.Path = P.PChar(); // Set path
		}
		else {
			EntryInfo.Path = iPath;
		}

		EntryInfo.NameOnly = (CONST_PCHAR)FindData.cFileName; // Set founded name only
		EntryInfo.IsDirectory = (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY; // is directory?
		EntryInfo.AcceptedSubItemsCount = EntryInfo.SkippedSubItemsCount = 0; // initialize counts

		R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_FOUND, &EntryInfo, iUserData); // call filter function
		switch (R) {
			case ENUMERATE_ACTION_CONTINUE: {
			} break;
			case ENUMERATE_ACTION_SKIP: {
				C_Skipped++; // increase count of skipped items
				continue;
			} break;
			default: {
				FindClose(hFind); // close search handle
				return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
			}
		}

		EntryInfo.Attributes = WindowsAttaributes2FileSystemAttributes(FindData.dwFileAttributes);

		U.HighPart = FindData.ftCreationTime.dwHighDateTime; U.LowPart = FindData.ftCreationTime.dwLowDateTime; EntryInfo.CreationTime = U.QuadPart;
		U.HighPart = FindData.ftLastAccessTime.dwHighDateTime; U.LowPart = FindData.ftLastAccessTime.dwLowDateTime; EntryInfo.LastAccessTime = U.QuadPart;
		U.HighPart = FindData.ftLastWriteTime.dwHighDateTime; U.LowPart = FindData.ftLastWriteTime.dwLowDateTime; EntryInfo.ModificationTime = U.QuadPart;
		U.HighPart = FindData.nFileSizeHigh; U.LowPart = FindData.nFileSizeLow; EntryInfo.Size = U.QuadPart;

		if (!EntryInfo.IsDirectory) { // file?
			R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_RETRIEVE_DATA, &EntryInfo, iUserData); // call filter function
			switch (R) {
				case ENUMERATE_ACTION_CONTINUE: {
					C_Accepted++; // increase count of accepted items
				} break;
				case ENUMERATE_ACTION_SKIP: {
					C_Skipped++; // increase count of skipped items
				} break;
				default: {
					FindClose(hFind); // close search handle
					return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
				}
			}
		}
		else { // directory
			R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_RETRIEVE_DATA, &EntryInfo, iUserData); // call filter function
			switch (R) {
				case ENUMERATE_ACTION_CONTINUE: {
				} break;
				case ENUMERATE_ACTION_SKIP: {
					C_Skipped++; // increase count of skipped items
					continue;
				} break;
				default: {
					FindClose(hFind); // close search handle
					return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
				}
			}

			// enumerate subdirectory
			TString S(SearchPath); TFileSystem::AppendToPath(&S, FindData.cFileName, false); // create subirectory path

			R = _Enumerate(true, S.PChar(), &EntryInfo, iUserData, iFilterFunction); // enumerate subdirectory
			if (R == FILE_SYSTEM_ERROR_ENUMERATE_ABORT) {
				FindClose(hFind); // close search handle
				return R; // stop enumeration
			}

			C_Accepted += EntryInfo.AcceptedSubItemsCount; // add accepted subitems count
			C_Skipped += EntryInfo.SkippedSubItemsCount; // add skipped subitems count

			R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_AFTER_ENUMERATE, &EntryInfo, iUserData); // call filter function
			switch (R) {
				case ENUMERATE_ACTION_CONTINUE: {
					C_Accepted++; // increase count of accepted items
				} break;
				case ENUMERATE_ACTION_SKIP: {
					C_Skipped++; // increase count of skipped items
				} break;
				default: {
					FindClose(hFind); // close search handle
					return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
				}
			}
		}

	} while (FindNextFileA(hFind, &FindData)); // continue searching

	FindClose(hFind); // close search handle

	if (iParent != NULL) { // parent info provided?
		iParent->AcceptedSubItemsCount += C_Accepted;
		iParent->SkippedSubItemsCount += C_Skipped;
	}
	return 0; // OK
#else

	ENUM_ITEM EntryInfo;
	INT32 R;

	INT64 C_Accepted = 0; // count of items found and accepted
	INT64 C_Skipped = 0; // count of items found and skipped

	TString SearchPath = TString(iPath);
	
	if (!iIsDir) { // file?
		TString N; TFileSystem::ExtractPathParts(&SearchPath, NULL, &N, NULL, NULL, false); // extract name only

		EntryInfo.Path = iPath; // Set path
		EntryInfo.NameOnly = N.PChar(); // Set founded name only
		EntryInfo.IsDirectory = false; // is directory?
		EntryInfo.AcceptedSubItemsCount = EntryInfo.SkippedSubItemsCount = 0; // initialize counts

		R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_FOUND, &EntryInfo, iUserData); // call filter function
		switch (R) {
			case ENUMERATE_ACTION_CONTINUE: {
			} break;
			case ENUMERATE_ACTION_SKIP: {
				return 0; // End enumeration
			} break;
			default: {
				return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
			}
		}

		struct stat st;
		if (stat(SearchPath.PChar(), &st) == -1) { // get attributes
			INT32 R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_ERROR, &EntryInfo, iUserData); // call filter function
			switch (R) {
				case ENUMERATE_ACTION_CONTINUE: {
				} break;
				case ENUMERATE_ACTION_SKIP: {
					return 0; // End enumeration
				} break;
				default: {
					return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
				}
			}
		}

		UINT32 Attr, Chmod, Ext2Attr;
		Attr = (UINT64)(st.st_mode & S_IFMT);
		Chmod = (UINT64)st.st_mode;
		Ext2Attr = 0;

		EntryInfo.Attributes = LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr); // convert 
		EntryInfo.Size = EntryInfo.IsDirectory ? 0 : (UINT64)st.st_size;

		EntryInfo.CreationTime = TDateTime::FromLinuxTime((UINT64)st.st_ctime); // convert to DATETIME
		EntryInfo.LastAccessTime = TDateTime::FromLinuxTime((UINT64)st.st_atime); // convert to DATETIME
		EntryInfo.ModificationTime = TDateTime::FromLinuxTime((UINT64)st.st_mtime); // convert to DATETIME

		R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_RETRIEVE_DATA, &EntryInfo, iUserData); // call filter function
		switch (R) {
			case ENUMERATE_ACTION_CONTINUE: {
				return 0; // End enumeration
			} break;
			case ENUMERATE_ACTION_SKIP: {
				return 0; // End enumeration
			} break;
			default: {
				return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
			}
		}

	}
	
	TFileSystem::RemovePathSeparator(&SearchPath, false); // remove trailing path separator if it exists

	DIR* dir = opendir(SearchPath.PChar()); // open directory
	if (dir == NULL) {
		if (iFilterFunction == NULL) return iParent == NULL ? FILE_SYSTEM_ERROR_DIRECTORY_READ : 0; // cannot read directory

		EntryInfo.Path = iPath;
		EntryInfo.NameOnly = "";

		R = iFilterFunction(ENUMERATE_STATE_ERROR, &EntryInfo, iUserData); // call filter function for handle error
		switch (R) {
			case ENUMERATE_ACTION_ABORT:
				return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // abort enumeration
			default:
				return 0; // return and continue enumeration
		}
	}

	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL) { // enumerate
		if (entry->d_name[0] == '.') {
			if (entry->d_name[1] == 0) continue; // skip "."
			if (entry->d_name[1] == '.') {
				if (entry->d_name[2] == 0) continue; // skip ".."
			}
		}

		EntryInfo.Path = iPath; // Set path
		EntryInfo.NameOnly = (CONST_PCHAR)entry->d_name; // Set founded name only
		EntryInfo.IsDirectory = entry->d_type == DT_DIR; // is directory?
		EntryInfo.AcceptedSubItemsCount = EntryInfo.SkippedSubItemsCount = 0; // initialize counts

		R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_FOUND, &EntryInfo, iUserData); // call filter function
		switch (R) {
			case ENUMERATE_ACTION_CONTINUE: {
			} break;
			case ENUMERATE_ACTION_SKIP: {
				C_Skipped++; // increase count of skipped items
				continue;
			} break;
			default: {
				closedir(dir); // close directory
				return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
			}
		}

		TString S(SearchPath); TFileSystem::AppendToPath(&S, entry->d_name, false); // create subirectory path

		struct stat st;
		if (stat(S.PChar(), &st) == -1) { // get attributes
			INT32 R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_ERROR, &EntryInfo, iUserData); // call filter function
			switch (R) {
				case ENUMERATE_ACTION_CONTINUE: {
				} break;
				case ENUMERATE_ACTION_SKIP: {
					C_Skipped++; // increase count of skipped items
					continue;
				} break;
				default: {
					closedir(dir); // close directory
					return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
				}
			}
		}

		UINT32 Attr, Chmod, Ext2Attr;
		Attr = (UINT64)(st.st_mode & S_IFMT);
		Chmod = (UINT64)st.st_mode;
		Ext2Attr = 0;

		EntryInfo.Attributes = LinuxAttaributes2FileSystemAttributes(Attr, Chmod, Ext2Attr); // convert 
		EntryInfo.Size = EntryInfo.IsDirectory ? 0 : (UINT64)st.st_size;

		EntryInfo.CreationTime = TDateTime::FromLinuxTime((UINT64)st.st_ctime); // convert to DATETIME
		EntryInfo.LastAccessTime = TDateTime::FromLinuxTime((UINT64)st.st_atime); // convert to DATETIME
		EntryInfo.ModificationTime = TDateTime::FromLinuxTime((UINT64)st.st_mtime); // convert to DATETIME

		if (!EntryInfo.IsDirectory) { // file?
			R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_RETRIEVE_DATA, &EntryInfo, iUserData); // call filter function
			switch (R) {
				case ENUMERATE_ACTION_CONTINUE: {
					C_Accepted++; // increase count of accepted items
				} break;
				case ENUMERATE_ACTION_SKIP: {
					C_Skipped++; // increase count of skipped items
				} break;
				default: {
					closedir(dir); // close directory
					return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
				}
			}
		}
		else { // directory
			R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_RETRIEVE_DATA, &EntryInfo, iUserData); // call filter function
			switch (R) {
				case ENUMERATE_ACTION_CONTINUE: {
				} break;
				case ENUMERATE_ACTION_SKIP: {
					C_Skipped++; // increase count of skipped items
					continue;
				} break;
				default: {
					closedir(dir); // close directory
					return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
				}
			}

			// enumerate subdirectory
			TString S(SearchPath); TFileSystem::AppendToPath(&S, entry->d_name, false); // create subirectory path

			R = _Enumerate(true, S.PChar(), &EntryInfo, iUserData, iFilterFunction); // enumerate subdirectory
			if (R == FILE_SYSTEM_ERROR_ENUMERATE_ABORT) {
				closedir(dir); // close directory
				return R; // stop enumeration
			}

			C_Accepted += EntryInfo.AcceptedSubItemsCount; // add accepted subitems count
			C_Skipped += EntryInfo.SkippedSubItemsCount; // add skipped subitems count

			R = iFilterFunction == NULL ? ENUMERATE_ACTION_CONTINUE : iFilterFunction(ENUMERATE_STATE_AFTER_ENUMERATE, &EntryInfo, iUserData); // call filter function
				switch (R) {
				case ENUMERATE_ACTION_CONTINUE: {
					C_Accepted++; // increase count of accepted items
				} break;
				case ENUMERATE_ACTION_SKIP: {
					C_Skipped++; // increase count of skipped items
				} break;
				default: {
					closedir(dir); // close directory
					return FILE_SYSTEM_ERROR_ENUMERATE_ABORT; // stop enumeration
				}
			}
		}
	}
	closedir(dir); // close directory

	if (iParent != NULL) { // parent info provided?
		iParent->AcceptedSubItemsCount += C_Accepted;
		iParent->SkippedSubItemsCount += C_Skipped;
	}
	return 0; // OK
#endif
}
//	................................................................................................

//	................................................................................................
//  Enumerate files and directories in a directory
//	Input:
//			iPath - directory path
// 			iUserData - user data pointer passed to filter function
// 			iFilterFunction - filter function called for each file/directory found
//	Output:
//			0 or error code
//	................................................................................................
INT32 TFileSystem::Enumerate(CONST_PCHAR iPath, PVOID iUserData, TEnumerateFilterFunction iFilterFunction) {
	INT32 R = DirectoryExists(iPath, true); // check path validity
	if (R == FILE_SYSTEM_TRUE) {
		R = _Enumerate(true, iPath, NULL, iUserData, iFilterFunction); // call internal enumeration function
		return R == FILE_SYSTEM_ERROR_ENUMERATE_EMPTY ? 0 : R; // return result (first level empty directory is not an error)
	}

	INT32 R1 = FileExists(iPath, false); // check path validity
	if (R1 == FILE_SYSTEM_TRUE) {
		return _Enumerate(false, iPath, NULL, iUserData, iFilterFunction); // call internal file enumeration function
	}

	if (R == FILE_SYSTEM_FALSE) return FILE_SYSTEM_ERROR_DIRECTORY_NOT_EXISTS; // checking directory existence not failed?
	return R; // return error
}
//	................................................................................................
//	................................................................................................
//  Format size in bytes to human-readable string
//	Input:
//			iSizeInBytes - size in bytes
// 			oResult - output string with formatted size
// 			iLanguageStrings - language strings for formatting
//	Output:
//			none
//	................................................................................................
void TFileSystem::FormatSizeInBytes(UINT64 iSizeInBytes, TString* oResult, CONST_PCHAR iLanguageStrings) {
}
//	................................................................................................
