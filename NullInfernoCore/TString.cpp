#include "NullInfernoCore.h"
#include "TString.h"

#pragma region DATA
CONST_PCHAR BASE64_CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const BYTE LOWER_CASE_TABLE_28591[] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xD7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xDF,0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF};
const BYTE LOWER_CASE_TABLE_1250[] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x9A,0x8B,0x9C,0x9D,0x9E,0x9F,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,0xA0,0xA1,0xA2,0xB3,0xA4,0xB9,0xA6,0xA7,0xA8,0xA9,0xBA,0xAB,0xAC,0xAD,0xAE,0xBF,0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBE,0xBD,0xBE,0xBF,0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xD7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xDF,0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF};
const BYTE LOWER_CASE_TABLE_1252[] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x9A,0x8B,0x9C,0x8D,0x9E,0x8F,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0xFF,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xD7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xDF,0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF};

const BYTE UPPER_CASE_TABLE_28591[] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x7B,0x7C,0x7D,0x7E,0x7F,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xF7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0x59};
const BYTE UPPER_CASE_TABLE_1250[] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x7B,0x7C,0x7D,0x7E,0x7F,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x8A,0x9B,0x8C,0x8D,0x8E,0x8F,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,0xB2,0xA3,0xB4,0xB5,0xB6,0xB7,0xB8,0xA5,0xAA,0xBB,0xBC,0xBD,0xBC,0xAF,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xF7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xFF};
const BYTE UPPER_CASE_TABLE_1252[] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x7B,0x7C,0x7D,0x7E,0x7F,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x8A,0x9B,0x8C,0x9D,0x8E,0x9F,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xF7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0x9F};
#pragma endregion

#define MAKE_UPPER_CASE_TABLE_POINTER(_CaseTable, _CodePage) \
	CONST_PBYTE _CaseTable = NULL; \
	switch (_CodePage) { \
		case 1250: _CaseTable = UPPER_CASE_TABLE_1250; break; \
		case 1252: _CaseTable = UPPER_CASE_TABLE_1252; break; \
		default: _CaseTable = UPPER_CASE_TABLE_28591; break; \
	} \

#define MAKE_LOWER_CASE_TABLE_POINTER(_CaseTable, _CodePage) \
	CONST_PBYTE _CaseTable = NULL; \
	switch (_CodePage) { \
		case 1250: _CaseTable = LOWER_CASE_TABLE_1250; break; \
		case 1252: _CaseTable = LOWER_CASE_TABLE_1252; break; \
		default: _CaseTable = LOWER_CASE_TABLE_28591; break; \
	} \

//	...............................................................................................
//	Get substring
//	Input:
// 			oSubstr - output substring
//			iStartIndex - start index of the substring
// 			iLength - length of the substring
//	Output:
//			none
//	...............................................................................................
void TString::Substring(TString * oSubstr, INT64 iStartIndex, INT64 iLength) {
	if (IS_INDEX_OUT(iStartIndex, 0, Length - 1) || (iLength <= 0)) { // Invalid start index or length?
		oSubstr->SetLength(0); // Empty substring
		return;
	}
	oSubstr->SetValue(Value + iStartIndex, MIN(iLength, Length - iStartIndex)); // Copy the substring
}
//	...............................................................................................
//	...............................................................................................
//	Get substring from the left side
//	Input:
// 			oSubstr - output substring
// 			iLength - length of the substring
//	Output:
//			none
//	...............................................................................................
void TString::LeftSubstring(TString * oSubstr, INT64 iLength) {
	if (iLength <= 0) { // Empty substring
		oSubstr->SetLength(0);
		return;
	}

	if (iLength >= Length) { // Entire string?
		oSubstr->SetValue(Value, Length); // Copy entire string
		return;
	}

	oSubstr->SetValue(Value, iLength); // Copy the left substring
}
//	...............................................................................................
//	...............................................................................................
//	Get substring from the right side
//	Input:
// 			oSubstr - output substring
// 			iLength - length of the substring
//	Output:
//			none
//	...............................................................................................
void TString::RightSubstring(TString* oSubstr, INT64 iLength) {
	if (iLength <= 0) { // Empty substring
		oSubstr->SetLength(0);
		return;
	}

	if (iLength >= Length) { // Entire string?
		oSubstr->SetValue(Value, Length); // Copy entire string
		return;
	}

	oSubstr->SetValue(Value + Length - iLength, iLength); // Copy the right substring
}
//	...............................................................................................
//	...............................................................................................
//	Trim the string
//	Input:
// 			iTrimChar - character to trim
//	Output:
//			none
//	...............................................................................................
void TString::Trim(CHAR iTrimChar) {
	if (Length == 0) return; // Empty string

	CONST_PCHAR S = Value; // Start of the string
	CONST_PCHAR E = Value + Length - 1; // End of the string

	while (S <= E) { // Scan from the start
		if (*S > iTrimChar) break; // Non-trim character found
		S++;
	}
	if (S > E) SetLength(0); // Entire string trimmed
	else {
		while (E >= S) { // Scan from the end
			if (*E > iTrimChar) break; // Non-trim character found
			E--;
		}
		INT64 NewLength = E - S + 1; // New length of the string
		if (NewLength == Length) return; // No change?

		if (S > Value) FNC_MEMMOVE(Value, S, NewLength); // Move the remaining string
		if (FCapacity != 0) { // Shared string cannot be modified
			Value[NewLength] = 0; // Terminate the string
		}
		Length = NewLength; // Update length
	}
}
//	...............................................................................................
//	...............................................................................................
//	Trim the string from the left side
//	Input:
// 			iTrimChar - character to trim
//	Output:
//			none
//	...............................................................................................
void TString::LeftTrim(CHAR iTrimChar) {
	if (FCapacity == 0) return; // Shared string cannot be modified
	if (Length == 0) return; // Empty string

	INT64 i;
	for (i = 0; i < Length; i++) { // Scan from the end
		if (Value[i] > iTrimChar) break; // Non-trim character found
	}
	if (i == Length) SetLength(0); // Entire string trimmed
	else {
		FNC_MEMMOVE(Value, Value + i, Length - i + 1); // Move the remaining string including terminator
		Length -= i; // Update length
	}
}
//	...............................................................................................
//	...............................................................................................
//	Trim the string from the right side
//	Input:
// 			iTrimChar - character to trim
//	Output:
//			none
//	...............................................................................................
void TString::RightTrim(CHAR iTrimChar) {
	if (Length == 0) return; // Empty string

	INT64 i;
	for (i = Length - 1; i >= 0; i--) { // Scan from the end
		if (Value[i] > iTrimChar) break; // Non-trim character found
	}
	if (FCapacity > 0) Value[Length = i + 1] = 0; // Is shared? Update length and terminate the string
	else Length = i + 1; // Update length
}
//	...............................................................................................
//	...............................................................................................
//	Set the length of the string
//	Input:
// 			iLength - new length of the string
//	Output:
//			none
//	...............................................................................................
void TString::SetLength(INT64 iLength) {
	if (IS_INDEX_IN(iLength, 0, Length)) { // Within current length?
		if (FCapacity > 0) Value[iLength] = 0; // Truncate the string
		Length = iLength; // Update length
	}
}
//	...............................................................................................
//	...............................................................................................
//	Generate a random BASE64 string
//	Input:
// 			oBuffer - output buffer
// 			iLength - length of the string to generate
//	Output:
//			size of the string
//	...............................................................................................
INT64 TString::GenerateRandomBASE64String(PCHAR oBuffer, INT64 iLength) {
	PCHAR P = oBuffer; PCHAR E = oBuffer + iLength; // P - current position, E - end position
	while (P < E) { // Generate characters in blocks of 6
		UINT32 U = TEnvironment::GenerateRandomUINT32();
		*P++ = BASE64_CHARACTERS[U & 0x3F]; U >>= 6; if (P >= E) break;
		*P++ = BASE64_CHARACTERS[U & 0x3F]; U >>= 6; if (P >= E) break;
		*P++ = BASE64_CHARACTERS[U & 0x3F]; U >>= 6; if (P >= E) break;
		*P++ = BASE64_CHARACTERS[U & 0x3F]; U >>= 6; if (P >= E) break;
		*P++ = BASE64_CHARACTERS[U & 0x3F]; if (P >= E) break;
	}
	*P = 0; // Terminate the string
	return iLength; // Return the size of the string
}
//	...............................................................................................
//	...............................................................................................
//	Generate hash code of the string data
//	Input:
// 			iValue - value to generate hash code for
// 			iLength - length of the value or -1 for null-terminated string
//	Output:
//			hash code
//	...............................................................................................
UINT64 TString::GenerateHashCode(CONST_PCHAR iValue, INT64 iLength) {
	if (IS_PCHAR_EMPTY(iValue)) return 0; // Null string?
	return iLength < 0 ? GenerateHash64(iValue, -1, NULL, 0) : GenerateHash64(iValue, iLength, NULL, -1); // Generate hash code
}
//	...............................................................................................
//	...............................................................................................
//	Generate hash code of the string data ignoring case
//	Input:
// 			iValue - value to generate hash code for
// 			iLength - length of the value or -1 for null-terminated string
// 			iCodePage - code page to use for case conversion
//	Output:
//			hash code
//	...............................................................................................
UINT64 TString::GenerateCaseHashCode(CONST_PCHAR iValue, INT64 iLength, INT32 iCodePage) {
	if (IS_PCHAR_EMPTY(iValue)) return 0; // Null string?
	MAKE_LOWER_CASE_TABLE_POINTER(CaseTable, iCodePage); // Get the case conversion table
	return iLength < 0 ? GenerateHash64(iValue, -1, CaseTable, 0) : GenerateHash64(iValue, iLength, CaseTable, -1); // Generate hash code
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TString::TString(void) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - value to set
// 			iLength - length of the value or -1 for null-terminated string
//	Output:
//			none
//	...............................................................................................
TString::TString(CONST_PCHAR iValue, INT64 iLength) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
	SetValue(iValue, iLength); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
TString::TString(TString* iValue) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
	SetValue(iValue); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
TString::TString(TString& iValue) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
	SetValue(iValue); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
TString::TString(INT32 iValue) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
	SetValue(iValue); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
TString::TString(UINT32 iValue) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
	SetValue(iValue); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
TString::TString(INT64 iValue) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
	SetValue(iValue); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
TString::TString(UINT64 iValue) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
	SetValue(iValue); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - value to set
//			iDecimalPlaces - number of decimal places
//	Output:
//			none
//	...............................................................................................
TString::TString(DOUBLE iValue, INT32 iDecimalPlaces) {
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
	SetValue(iValue, iDecimalPlaces); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TString::~TString() {
	Release(); // Release the memory
}
//	...............................................................................................
//	...............................................................................................
//	Release the memory
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
void TString::Release(void) {
	if ((Value != NULL) && (FCapacity > 0)) MEMORY_FREE(Value); // Free the memory
	FCapacity = 0; Length = 0; Value = NULL; // Initialize members
}
//	...............................................................................................
//	...............................................................................................
//	Reallocate the memory
//	Input:
// 			iNewCapacity - new capacity
// 			iKeepContent - whether to keep the current content
//	Output:
//			true / false
//	...............................................................................................
BOOL TString::Reallocate(INT64 iNewCapacity, BOOL iKeepContent) {
	if (iNewCapacity <= 0) return false; // Invalid capacity?
	if (iNewCapacity <= FCapacity) return true; // No need to reallocate?

	INT64 NewCapacity = ALIGN16(iNewCapacity); // Align to 16 bytes
	PCHAR NewValue = (PCHAR)MEMORY_ALLOC(NewCapacity + 1); // Allocate new memory
	if (NewValue == NULL) return false; // Allocation failed?

	if ((Length > 0) && (iKeepContent)) { // Copy content?
		FNC_MEMCPY(NewValue, Value, Length); // Copy the content
		NewValue[Length] = 0; // Terminate the string
	}
	if (FCapacity > 0) PCHAR_FREE(Value); // Free old memory
	FCapacity = NewCapacity; Value = NewValue; // Update members

	return true; // Success
}
//	...............................................................................................
//	...............................................................................................
//	Set value
//	Input:
// 			iValue - value to set
// 			iLength - length of the value or -1 for null-terminated string
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(CONST_PCHAR iValue, INT64 iLength) {
	if (IS_PCHAR_EMPTY(iValue)) { // Empty string?
		SetLength(0); // Set length to zero
		return;
	}
	INT64 L = (iLength < 0) ? FNC_STRLEN(iValue) : iLength; // Determine length
	if (L == 0) SetLength(0); // Empty string?
	else {
		if (Reallocate(L, false)) { // Reallocate memory
			FNC_MEMCPY(Value, iValue, L); // Copy the content
			Value[Length = L] = 0; // Terminate the string and set length
		}
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set value
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(TString* iValue) {
	if (iValue == NULL) SetLength(0);
	else SetValue(iValue->Value, iValue->Length);
}
//	...............................................................................................
//	...............................................................................................
//	Set value
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(TString& iValue) {
	SetValue(iValue.Value, iValue.Length);
}
//	...............................................................................................
//	...............................................................................................
//	Set value
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(INT32 iValue) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = INT32ToStr(iValue, BUF); // Convert to string
	SetValue(BUF, L); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Set value
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(UINT32 iValue) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = UINT32ToStr(iValue, BUF); // Convert to string
	SetValue(BUF, L); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Set value
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(INT64 iValue) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = INT64ToStr(iValue, BUF); // Convert to string
	SetValue(BUF, L); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Set value
//	Input:
// 			iValue - value to set
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(UINT64 iValue) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = UINT64ToStr(iValue, BUF); // Convert to string
	SetValue(BUF, L); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Set value
//	Input:
// 			iValue - value to set
//			iDecimalPlaces - number of decimal places
// 			iDecimalPointChar - character to use as decimal point
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(DOUBLE iValue, INT32 iDecimalPlaces, CHAR iDecimalPointChar) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = DOUBLEToStr(iValue, BUF, iDecimalPlaces, iDecimalPointChar); // Convert to string
	SetValue(BUF, L); // Set the value
}
//	...............................................................................................
//	...............................................................................................
//	Set shared value
//	Input:
// 			iValue - value to set
// 			iLength - length of the value or -1 for null-terminated string
//	Output:
//			none
//	...............................................................................................
void TString::SetSharedValue(PCHAR iValue, INT64 iLength) {
	Release(); // Release current memory
	if (IS_PCHAR_EMPTY(iValue)) return; // Empty string?
	Value = iValue;
	Length = (iLength < 0) ? FNC_STRLEN(iValue) : iLength; // Determine length
}
//	...............................................................................................
//	...............................................................................................
//	Set random BASE64 string value
//	Input:
// 			iLength - length of the string to generate
//	Output:
//			none
//	...............................................................................................
void TString::SetRandomBASE64Value(INT64 iLength) {
	if (iLength <= 0) SetLength(0); // Empty string
	else {
		if (Reallocate(iLength, false)) { // Reallocate memory
			GenerateRandomBASE64String(Value, iLength); // Generate random BASE64 string
			Length = iLength; // Set length
		}
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set shared value
//	Input:
// 			iValue - value to set
// 			iLength - length of the value or -1 for null-terminated string
// 			iCodePage - code page of the input value for conversion or -1 for user default
//	Output:
//			none
//	...............................................................................................
void TString::SetValue(CONST_PWCHAR iValue, INT64 iLength, INT32 iCodePage) {
	if ((iValue == NULL) || (*iValue == 0)) { // Empty input?
		SetLength(0); // Set length to zero
		return;
	}

#ifdef WINDOWS_SYSTEM
	INT64 InLen = (iLength < 0) ? (INT64)FNC_WCSLEN(iValue) : iLength; // Determine input length

	INT32 L = WideCharToMultiByte(iCodePage == -1 ? CP_ACP : iCodePage, 0, iValue, (iLength < 0) ? -1 : (INT32)InLen, NULL, 0, NULL, NULL); // Determine required length
	if (L == 0) { // Conversion failed?
		SetLength(0); // Set length to zero
		return;
	}

	if (!Reallocate(L, false)) { // Reallocate memory
		SetLength(0); // Set length to zero
		return;
	}

	if (WideCharToMultiByte(iCodePage == -1 ? CP_ACP : iCodePage, 0, iValue, (INT32)InLen, Value, L, NULL, NULL) != (INT32)InLen) { // Perform conversion
		SetLength(0); // Set length to zero
		return;
	}
	Value[Length = (L - 1)] = 0; // Terminate the string and set length
#else
	UINT32 L = wcstombs(NULL, iValue, 0);
	if (L == (UINT32)-1) { // Conversion failed?
		SetLength(0); // Set length to zero
		return;
	}

	if (!Reallocate(L, false)) { // Reallocate memory
		SetLength(0); // Set length to zero
		return;
	}

	if (wcstombs(Value, iValue, L + 1) == (UINT32)-1) { // Perform conversion
		SetLength(0); // Set length to zero
		return;
	}
	Value[Length = L] = 0; // Terminate the string and set length
#endif
}
//	...............................................................................................
//	...............................................................................................
//	Get value
//	Input:
// 			none
//	Output:
//			content as CONST_PCHAR
//	...............................................................................................
CONST_PCHAR TString::PChar(void) {
	return Length == 0 ? "" : (CONST_PCHAR)Value;
}
//	...............................................................................................
//	...............................................................................................
//	Get value
//	Input:
// 			none
//	Output:
//			content as INT32
//	...............................................................................................
INT32 TString::AsINT32(void) {
	return Length == 0 ? 0 : StrToINT32((CONST_PCHAR)Value, 0, ' ');
}
//	...............................................................................................
//	...............................................................................................
//	Get value
//	Input:
// 			none
//	Output:
//			content as UINT32
//	...............................................................................................
UINT32 TString::AsUINT32(void) {
	return Length == 0 ? 0 : StrToUINT32((CONST_PCHAR)Value, 0, ' ');
}
//	...............................................................................................
//	...............................................................................................
//	Get value
//	Input:
// 			none
//	Output:
//			content as INT64
//	...............................................................................................
INT64 TString::AsINT64(void) {
	return Length == 0 ? 0 : StrToINT64((CONST_PCHAR)Value, 0, ' ');
}
//	...............................................................................................
//	...............................................................................................
//	Get value
//	Input:
// 			none
//	Output:
//			content as UINT64
//	...............................................................................................
UINT64 TString::AsUINT64(void) {
	return Length == 0 ? 0 : StrToUINT64((CONST_PCHAR)Value, 0, ' ');
}
//	...............................................................................................
//	...............................................................................................
//	Get value
//	Input:
// 			none
//	Output:
//			content as DOUBLE
//	...............................................................................................
DOUBLE TString::AsDOUBLE(void) {
	return Length == 0 ? 0 : StrToDOUBLE((CONST_PCHAR)Value, 0.0, ' ');
}
//	...............................................................................................
//	...............................................................................................
//	Get value as wide char string
//	Input:
// 			oBuffer - output buffer
// 			iBufferLength - length of the output buffer
// 			iCodePage - code page of the input value for conversion or -1 for user default
//	Output:
//			number of characters written or -1 on error, -2 if output buffer too small
//	...............................................................................................
INT64 TString::AsPWChar(PWCHAR oBuffer, INT64 iBufferLength, INT32 iCodePage) {
	if ((oBuffer == NULL) || (iBufferLength <= 0)) return -1; // Empty string?

	if (Length == 0) { // Empty string?
		*oBuffer = 0; // Terminate the string
		return 0;
	}

#ifdef WINDOWS_SYSTEM
	INT32 L = MultiByteToWideChar(iCodePage == -1 ? CP_ACP : iCodePage, 0, Value, (INT32)Length, NULL, 0); // Determine required length
	if (L == 0) return -1; // Conversion failed?

	if (L >= iBufferLength) return -2; // Output buffer too small?

	L = MultiByteToWideChar(iCodePage == -1 ? CP_ACP : iCodePage, 0, Value, (INT32)Length, oBuffer, (INT32)iBufferLength);
	oBuffer[L] = 0; // Terminate the string
	return L; // Return number of characters written
#else
	size_t L = mbstowcs(NULL, Value, 0);
	if (L == (size_t)-1) return -1; // Conversion failed?

	if ((INT64)L > iBufferLength) return -2; // Output buffer too small?

	mbstowcs(oBuffer, Value, L + 1);
	oBuffer[L] = 0; // Terminate the string
	return (INT64)L; // Return number of characters written
#endif
}
//	...............................................................................................
//	...............................................................................................
//	Compare with a value
//	Input:
// 			iValue - value to compare with
// 			iStart - start position in this string
// 			iMaxLength - maximum length to compare or -1 for full length
//	Output:
//			0 if equal, <0 if less, >0 if greater
//	...............................................................................................
INT32 TString::Compare(CONST_PCHAR iValue, INT64 iStart, INT64 iMaxLength) {
	if (iStart < 0) iStart = 0; // Adjust start position

	if ((iStart >= Length) || (Length == 0)) { // This string is empty?
		if (IS_PCHAR_EMPTY(iValue)) return 0; // Both are empty
		return iMaxLength == 0 ? 0 : -1; // This is empty or less
	}
	if ((IS_PCHAR_EMPTY(iValue)) || (iMaxLength == 0)) { // Input string is empty?
		return 1; // This is greater or both are empty
	}

	INT64 CompareLength = Length - iStart; // Determine length to compare
	if (CompareLength == 0) return -1; // Nothing to compare?

	if ((iMaxLength < 0) || (CompareLength < iMaxLength)) { // Full length comparison
		CONST_PCHAR P1 = Value + iStart;
		CONST_PCHAR P2 = iValue;
		CONST_PCHAR E = P1 + CompareLength;

		while (P1 < E) {
			if (*P2 == 0) return 1; // iValue ended, this is greater
			if (*P1 != *P2) return (*P1 < *P2) ? -1 : 1; // Different characters
			P1++; P2++;
		}
		return (*P2 == 0) ? 0 : -1; // Both ended or iValue is longer
	}

	CONST_PCHAR P1 = Value + iStart;
	CONST_PCHAR P2 = iValue;
	CONST_PCHAR E1 = P1 + CompareLength;
	CONST_PCHAR E2 = P2 + iMaxLength;
	while (P2 < E2) {
		if (P1 == E1) return *P2 == 0 ? 0 : -1; // This ended, both ended or this is less
		if (*P1 != *P2) return (*P1 < *P2) ? -1 : 1; // Different characters
		P1++; P2++;
	}
	return 0; // Equal
}
//	...............................................................................................
//	...............................................................................................
//	Compare with a value
//	Input:
// 			iValue - value to compare with
// 			iStart - start position in this string
// 			iMaxLength - maximum length to compare or -1 for full length
//	Output:
//			0 if equal, <0 if less, >0 if greater
//	...............................................................................................
INT32 TString::Compare(TString* iValue, INT64 iStart, INT64 iMaxLength) {
	return Compare(iValue == NULL ? (CONST_PCHAR)NULL : (CONST_PCHAR)iValue->Value, iMaxLength); // Call the other overload
}
//	...............................................................................................
//	...............................................................................................
//	Compare with a value
//	Input:
// 			iValue - value to compare with
// 			iStart - start position in this string
// 			iMaxLength - maximum length to compare or -1 for full length
//	Output:
//			0 if equal, <0 if less, >0 if greater
//	...............................................................................................
INT32 TString::Compare(TString& iValue, INT64 iStart, INT64 iMaxLength) {
	return Compare((CONST_PCHAR)iValue.Value, iMaxLength); // Call the other overload
}
//	...............................................................................................
//	...............................................................................................
//	Compare with a value case insensitive
//	Input:
// 			iValue - value to compare with
// 			iStart - start position in this string
// 			iMaxLength - maximum length to compare or -1 for full length
//			iCodePage - code page to use for case conversion
//	Output:
//			0 if equal, <0 if less, >0 if greater
//	...............................................................................................
INT32 TString::CaseCompare(CONST_PCHAR iValue, INT64 iStart, INT64 iMaxLength, INT32 iCodePage) {
	if (iStart < 0) iStart = 0; // Adjust start position

	if ((iStart >= Length) || (Length == 0)) { // This string is empty?
		if (IS_PCHAR_EMPTY(iValue)) return 0; // Both are empty
		return iMaxLength == 0 ? 0 : -1; // This is empty or less
	}
	if ((IS_PCHAR_EMPTY(iValue)) || (iMaxLength == 0)) { // Input string is empty?
		return 1; // This is greater or both are empty
	}

	INT64 CompareLength = Length - iStart; // Determine length to compare
	if (CompareLength == 0) return -1; // Nothing to compare?

	MAKE_LOWER_CASE_TABLE_POINTER(CaseTable, iCodePage);
	MAKE_UPPER_CASE_TABLE_POINTER(CaseTableU, iCodePage);

	if ((iMaxLength < 0) || (CompareLength < iMaxLength)) { // Full length comparison
		CONST_PCHAR P1 = Value + iStart;
		CONST_PCHAR P2 = iValue;
		CONST_PCHAR E = P1 + CompareLength;

		while (P1 < E) {
			if (*P2 == 0) return 1; // iValue ended, this is greater
			BYTE C1 = *P1++; BYTE C2 = *P2++;
			if (CaseTableU[C1] == CaseTableU[C2]) continue;
			if (CaseTable[C1] == CaseTable[C2]) continue;

			return (CaseTable[C1] < CaseTable[C2]) ? -1 : 1; // Different characters
		}
		return *P2 == 0 ? 0 : -1; // Both ended or iValue is longer
	}

	CONST_PCHAR P1 = Value + iStart;
	CONST_PCHAR P2 = iValue;
	CONST_PCHAR E1 = P1 + CompareLength;
	CONST_PCHAR E2 = P2 + iMaxLength;
	while (P2 < E2) {
		if (P1 == E1) return *P2 == 0 ? 0 : -1; // This ended, both ended or this is less
		BYTE C1 = *P1++; BYTE C2 = *P2++;
		if (CaseTableU[C1] == CaseTableU[C2]) continue;
		if (CaseTable[C1] == CaseTable[C2]) continue;

		return (CaseTable[C1] < CaseTable[C2]) ? -1 : 1; // Different characters
	}
	return 0; // Equal
}
//	...............................................................................................
//	...............................................................................................
//	Compare with a value case insensitive
//	Input:
// 			iValue - value to compare with
// 			iStart - start position in this string
// 			iMaxLength - maximum length to compare or -1 for full length
//			iCodePage - code page to use for case conversion
//	Output:
//			0 if equal, <0 if less, >0 if greater
//	...............................................................................................
INT32 TString::CaseCompare(TString* iValue, INT64 iStart, INT64 iMaxLength, INT32 iCodePage) {
	return CaseCompare(iValue == NULL ? (CONST_PCHAR)NULL : (CONST_PCHAR)iValue->Value, iMaxLength, iCodePage); // Call the other overload
}
//	...............................................................................................
//	...............................................................................................
//	Compare with a value case insensitive
//	Input:
// 			iValue - value to compare with
// 			iStart - start position in this string
// 			iMaxLength - maximum length to compare or -1 for full length
//			iCodePage - code page to use for case conversion
//	Output:
//			0 if equal, <0 if less, >0 if greater
//	...............................................................................................
INT32 TString::CaseCompare(TString& iValue, INT64 iStart, INT64 iMaxLength, INT32 iCodePage) {
	return CaseCompare((CONST_PCHAR)iValue.Value, iMaxLength, iCodePage); // Call the other overload
}
//	...............................................................................................
//	...............................................................................................
//	Check equality with a value
//	Input:
// 			iValue - value to compare with
// 			iLength - length of the value or -1 for null-terminated string
//	Output:
//			true / false
//	...............................................................................................
BOOL TString::IsEqual(CONST_PCHAR iValue, INT64 iLength) {
	return Compare(iValue, 0, iLength) == 0; // Call the compare method
}
//	...............................................................................................
//	...............................................................................................
//	Check if string is empty
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TString::IsEmpty(void) {
	return Length == 0;
}
//	...............................................................................................
//	...............................................................................................
//	Append value to the end
//	Input:
// 			iValue - value to append
// 			iLength - length of the value or -1 for null-terminated string
//	Output:
//			none
//	...............................................................................................
void TString::AppendValue(CONST_PCHAR iValue, INT64 iLength) {
	if (IS_PCHAR_EMPTY(iValue)) return; // Nothing to append?

	INT64 L = (iLength < 0) ? FNC_STRLEN(iValue) : iLength; // Determine length
	if (L == 0) return; // Nothing to append?
	if (Reallocate(L, true)) { // Reallocate memory
		FNC_MEMCPY(Value + Length, iValue, L); // Copy the content
		Length += L; // Update length
		Value[Length] = 0; // Terminate the string
	}
}
//	...............................................................................................
//	...............................................................................................
//	Append value to the end
//	Input:
// 			iValue - value to append
//	Output:
//			none
//	...............................................................................................
void TString::AppendValue(TString& iValue) {
	AppendValue((CONST_PCHAR)iValue.Value, iValue.Length); // Call the other overload
}
//	...............................................................................................
//	...............................................................................................
//	Append value to the end
//	Input:
// 			iValue - value to append
//	Output:
//			none
//	...............................................................................................
void TString::AppendValue(TString* iValue) {
	if (iValue == NULL) return; // Nothing to append?
	AppendValue((CONST_PCHAR)iValue->Value, iValue->Length); // Call the other overload
}
//	...............................................................................................
//	...............................................................................................
//	Append value to the end
//	Input:
// 			iValue - value to append
//	Output:
//			none
//	...............................................................................................
void TString::AppendValue(INT32 iValue) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = INT32ToStr(iValue, BUF); // Convert to string
	AppendValue(BUF, L); // Append the value
}
//	...............................................................................................
//	...............................................................................................
//	Append value to the end
//	Input:
// 			iValue - value to append
//	Output:
//			none
//	...............................................................................................
void TString::AppendValue(UINT32 iValue) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = UINT32ToStr(iValue, BUF); // Convert to string
	AppendValue(BUF, L); // Append the value
}
//	...............................................................................................
//	...............................................................................................
//	Append value to the end
//	Input:
// 			iValue - value to append
//	Output:
//			none
//	...............................................................................................
void TString::AppendValue(INT64 iValue) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = INT64ToStr(iValue, BUF); // Convert to string
	AppendValue(BUF, L); // Append the value
}
//	...............................................................................................
//	...............................................................................................
//	Append value to the end
//	Input:
// 			iValue - value to append
//	Output:
//			none
//	...............................................................................................
void TString::AppendValue(UINT64 iValue) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = UINT64ToStr(iValue, BUF); // Convert to string
	AppendValue(BUF, L); // Append the value
}
//	...............................................................................................
//	...............................................................................................
//	Append value to the end
//	Input:
// 			iValue - value to append
// 			iDecimalPlaces - number of decimal places
// 			iDecimalPointChar - character to use as decimal point
//	Output:
//			none
//	...............................................................................................
void TString::AppendValue(DOUBLE iValue, INT32 iDecimalPlaces, CHAR iDecimalPointChar) {
	CHAR BUF[32]; // Buffer for string representation
	INT32 L = DOUBLEToStr(iValue, BUF, iDecimalPlaces, iDecimalPointChar); // Convert to string
	AppendValue(BUF, L); // Append the value
}
//	...............................................................................................
//	...............................................................................................
//	Append chars to the end
//	Input:
// 			iValue - char(s) to append
// 			iCount - number of chars to append
// 			iAppendOnlyIfNotExists - whether to append only if the char does not already exist on end of the string
//	Output:
//			none
//	...............................................................................................
void TString::AppendChars(CHAR iValue, INT64 iCount, BOOL iAppendOnlyIfNotExists) {
	if (iCount <= 0) return; // Nothing to append?
	if (iAppendOnlyIfNotExists) { // Check if the char already exists at the end
		if (Length > 0) {
			if (Value[Length - 1] == iValue) return; // Already exists
		}
	}
	if (Reallocate(iCount, true)) { // Reallocate memory
		//for (INT64 i = 0; i < iCount; i++) Value[Length + i] = iValue; // Append the chars
		FNC_MEMSET(Value + Length, iValue, iCount); // Append the chars
		Length += iCount; // Update length
		Value[Length] = 0; // Terminate the string
	}
}
//	...............................................................................................
//	...............................................................................................
//	Convert to lower case
//	Input:
// 			iCodePage - code page to use for case conversion
//	Output:
//			none
//	...............................................................................................
void TString::ToLowercase(INT32 iCodePage) {
	MAKE_LOWER_CASE_TABLE_POINTER(CaseTable, iCodePage); // Get the case conversion table

	for (INT64 i = 0; i < Length; i++) Value[i] = CaseTable[(BYTE)Value[i]]; // Convert each character
}
//	...............................................................................................
//	...............................................................................................
//	Convert to upper case
//	Input:
// 			iCodePage - code page to use for case conversion
//	Output:
//			none
//	...............................................................................................
void TString::ToUppercase(INT32 iCodePage) {
	MAKE_UPPER_CASE_TABLE_POINTER(CaseTable, iCodePage); // Get the case conversion table

	for (INT64 i = 0; i < Length; i++) Value[i] = CaseTable[(BYTE)Value[i]]; // Convert each character
}
//	...............................................................................................
//	...............................................................................................
//	Format the string
//	Input:
// 			iFormattedString - format string
// 			... - format arguments
//	Output:
//			none
//	...............................................................................................
void TString::Format(CONST_PCHAR iFormattedString, ...) {
	va_list args;
	va_start(args, iFormattedString);
	
	INT32 L = vsnprintf(NULL, 0, iFormattedString, args); // Determine required length
	va_end(args);

	va_start(args, iFormattedString);
	if (L == 0) SetLength(0);
	else {
		Reallocate(L + 16, false); // Reallocate memory
		Length = vsnprintf(Value, L + 1, iFormattedString, args); // Format the string
		Value[Length] = 0; // Terminate the string
	}
	va_end(args);
}
//	...............................................................................................
//	...............................................................................................
//	Get hash code of the string
//	Input:
// 			none
//	Output:
//			hash code
//	...............................................................................................
UINT64 TString::GetHashCode(void) {
	if (Length == 0) return 0; // Empty content?
	return GenerateHash64(Value, (INT64)Length); // Generate hash code
}
//	...............................................................................................
//	...............................................................................................
//	Get hash code of the string
//	Input:
// 			iCodePage - code page to use for case conversion
//	Output:
//			hash code
//	...............................................................................................
UINT64 TString::GetCaseHashCode(INT32 iCodePage) {
	if (Length == 0) return 0; // Empty content?
	MAKE_LOWER_CASE_TABLE_POINTER(CaseTable, iCodePage); // Get the case conversion table
	return GenerateHash64(Value, (INT64)Length, CaseTable); // Generate hash code
}
//	...............................................................................................
//	...............................................................................................
//	Find character in the string
//	Input:
// 			iValue - character to find
// 			iStartIndex - start index for the search
// 			iMaxCharsCount - maximum number of characters to search or -1 for full length
// 			iOccurrenceIndex - occurrence index to find (1 = first, 2 = second, etc.)
//	Output:
//			position of the character or -1 if not found
//	...............................................................................................
INT64 TString::FindChar(CHAR iValue, INT64 iStartIndex, INT64 iMaxCharsCount, INT64 iOccurrenceIndex) {
	if (Length == 0) return -1; // Empty content?
	if (iStartIndex < 0) iStartIndex = 0; // Adjust start index
	if (iStartIndex >= Length) return -1; // Start index beyond the content?
	if (iOccurrenceIndex <= 0) iOccurrenceIndex = 1; // Adjust occurrence index

	if ((iMaxCharsCount < 0) && (FCapacity > 0)) {
		CONST_PCHAR P = Value + iStartIndex - 1; // Current position
		while (true) {
			P = FNC_STRCHR(P + 1, iValue); // Find the character
			if (P == NULL) return -1; // Not found?
			if (--iOccurrenceIndex == 0) return (INT64)(P - Value); // Found the required occurrence?
		}
	}
	else {
		CONST_PCHAR P = Value + iStartIndex; // Current position
		INT64 L = iMaxCharsCount < 0 ? Length - iStartIndex : (MIN(Length - iStartIndex, iMaxCharsCount)); // Length to scan
		
		INT64 L1 = L / 16; // Number of 16-byte blocks (for SSE2)

		__m128i v = _mm_set1_epi8((BYTE)iValue); // Set the value to search

		while (L1 > 0) {
			__m128i x = _mm_loadu_si128((__m128i const*)(P)); // Load block
			__m128i cmp = _mm_cmpeq_epi8(x, v); // Compare
			INT32 mask = _mm_movemask_epi8(cmp); // Create mask
			
			INT64 offset = 0; // Offset within the block
			while (mask != 0) {
				if (mask & 1) { // Found?
					if (--iOccurrenceIndex == 0) return (INT64)(P - Value) + offset; // Found the required occurrence?
				}
				mask >>= 1; offset++; // Next character
			}
			P += 16; L1--; // Next block
		}
		L &= 15; // Remaining characters
		for (INT64 i = 0; i < L; i++) {
			if (*P == iValue) { // Found?
				if (--iOccurrenceIndex == 0) return (INT64)(P - Value); // Found the required occurrence?
			}
			P++;
		}
	}

	return -1; // Not found
}
//	...............................................................................................
//	...............................................................................................
//	Find character in the string case insensitive
//	Input:
// 			iValue - character to find
// 			iStartIndex - start index for the search
// 			iMaxCharsCount - maximum number of characters to search or -1 for full length
// 			iOccurrenceIndex - occurrence index to find (1 = first, 2 = second, etc.)
// 			iCodePage - code page to use for case conversion
//	Output:
//			position of the character or -1 if not found
//	...............................................................................................
INT64 TString::CaseFindChar(CHAR iValue, INT64 iStartIndex, INT64 iMaxCharsCount, INT64 iOccurrenceIndex, INT32 iCodePage) {
	MAKE_UPPER_CASE_TABLE_POINTER(CaseTableU, iCodePage); // Get the upper case conversion table
	MAKE_LOWER_CASE_TABLE_POINTER(CaseTableL, iCodePage); // Get the lower case conversion table

	CHAR C1 = CaseTableU[(BYTE)iValue]; CHAR C2 = CaseTableL[(BYTE)iValue];
	if (C1 == C2) return FindChar(iValue, iStartIndex, iMaxCharsCount, iOccurrenceIndex); // Same case?

	if (Length == 0) return -1; // Empty content?
	if (iStartIndex < 0) iStartIndex = 0; // Adjust start index
	if (iStartIndex >= Length) return -1; // Start index beyond the content?
	if (iOccurrenceIndex <= 0) iOccurrenceIndex = 1; // Adjust occurrence index

	CONST_PCHAR P = Value + iStartIndex; // Current position
	INT64 L = iMaxCharsCount < 0 ? Length - iStartIndex : MIN(Length - iStartIndex, iMaxCharsCount); // Length to scan

	INT64 L1 = L / 16; // Number of 16-byte blocks (for SSE2)

	__m128i v1 = _mm_set1_epi8((BYTE)C1); // Set the value to search
	__m128i v2 = _mm_set1_epi8((BYTE)C2); // Set the value to search

	while (L1 > 0) {
		__m128i x = _mm_loadu_si128((__m128i const*)(P)); // Load block
		__m128i cmp = _mm_cmpeq_epi8(x, v1); // Compare v1
		INT32 mask = _mm_movemask_epi8(cmp); // Create mask
		cmp = _mm_cmpeq_epi8(x, v2); // Compare v2
		mask |= _mm_movemask_epi8(cmp); // Create mask

		INT64 offset = 0; // Offset within the block
		while (mask != 0) {
			if (mask & 1) { // Found?
				if (--iOccurrenceIndex == 0) return (INT64)(P - Value) + offset; // Found the required occurrence?
			}
			mask >>= 1; offset++; // Next character
		}
		P += 16; L1--; // Next block
	}
	L &= 15; // Remaining characters
	for (INT64 i = 0; i < L; i++) {
		if ((*P == C1) || (*P == C2)) { // Found?
			if (--iOccurrenceIndex == 0) return (INT64)(P - Value); // Found the required occurrence?
		}
		P++;
	}

	return -1; // Not found
}
//	...............................................................................................
//	...............................................................................................
//	Find character in the string in reverse order
//	Input:
// 			iValue - character to find
// 			iStartIndex - start index for the search or <0 for end of string
// 			iMaxCharsCount - maximum number of characters to search or -1 for full length
// 			iOccurrenceIndex - occurrence index to find (1 = first, 2 = second, etc.)
//	Output:
//			position of the character or -1 if not found
//	...............................................................................................
INT64 TString::ReverseFindChar(CHAR iValue, INT64 iStartIndex, INT64 iMaxCharsCount, INT64 iOccurrenceIndex) {
	if (Length == 0) return -1; // Empty content?
	if IS_INDEX_OUT(iStartIndex, 0, Length) iStartIndex = Length - 1; // Adjust start index
	if (iOccurrenceIndex <= 0) iOccurrenceIndex = 1; // Adjust occurrence index

	INT64 L = iMaxCharsCount < 0 ? iStartIndex + 1 : (MIN(iStartIndex + 1, iMaxCharsCount)); // Length to scan
	if (L == 0) return -1; // Nothing to scan?

	INT64 L1 = L / 16; // Number of 16-byte blocks (for SSE2)

	CONST_PCHAR P = Value + iStartIndex; // Current position

	L &= 15; // Remaining characters

	for (INT64 i = 0; i < L; i++) {
		if (*P == iValue) { // Found?
			if (--iOccurrenceIndex == 0) return (INT64)(P - Value); // Found the required occurrence?
		}
		P--;
	}

	P++;
	__m128i v = _mm_set1_epi8((BYTE)iValue); // Set the value to search
	while (L1 > 0) {
		P -= 16; // Move to the start of the block
		__m128i x = _mm_loadu_si128((__m128i const*)(P)); // Load block
		__m128i cmp = _mm_cmpeq_epi8(x, v); // Compare
		INT32 mask = _mm_movemask_epi8(cmp); // Create mask

		INT64 offset = 15; // Offset within the block
		while ((mask & 0xffff) != 0) {
			if (mask & 0x8000) { // Found?
				if (--iOccurrenceIndex == 0) return (INT64)(P - Value) + offset; // Found the required occurrence?
			}
			mask <<= 1; offset--; // Next character
		}
		L1--; // Next block
	}

	return -1; // Not found
}
//	...............................................................................................
//	...............................................................................................
//	Find character in the string in reverse order case insensitive
//	Input:
// 			iValue - character to find
// 			iStartIndex - start index for the search or <0 for end of string
// 			iMaxCharsCount - maximum number of characters to search or -1 for full length
// 			iOccurrenceIndex - occurrence index to find (1 = first, 2 = second, etc.)
// 			iCodePage - code page to use for case conversion
//	Output:
//			position of the character or -1 if not found
//	...............................................................................................
INT64 TString::ReverseCaseFindChar(CHAR iValue, INT64 iStartIndex, INT64 iMaxCharsCount, INT64 iOccurrenceIndex, INT32 iCodePage) {

	MAKE_UPPER_CASE_TABLE_POINTER(CaseTableU, iCodePage); // Get the upper case conversion table
	MAKE_LOWER_CASE_TABLE_POINTER(CaseTableL, iCodePage); // Get the lower case conversion table

	CHAR C1 = CaseTableU[(BYTE)iValue]; CHAR C2 = CaseTableL[(BYTE)iValue];
	if (C1 == C2) return ReverseFindChar(iValue, iStartIndex, iMaxCharsCount, iOccurrenceIndex); // Same case?

	if (Length == 0) return -1; // Empty content?
	if IS_INDEX_OUT(iStartIndex, 0, Length) iStartIndex = Length - 1; // Adjust start index
	if (iOccurrenceIndex <= 0) iOccurrenceIndex = 1; // Adjust occurrence index

	INT64 L = iMaxCharsCount < 0 ? iStartIndex + 1 : (MIN(iStartIndex + 1, iMaxCharsCount)); // Length to scan
	if (L == 0) return -1; // Nothing to scan?

	INT64 L1 = L / 16; // Number of 16-byte blocks (for SSE2)

	CONST_PCHAR P = Value + iStartIndex; // Current position

	L &= 15; // Remaining characters

	for (INT64 i = 0; i < L; i++) {
		if ((*P == C1) || (*P == C2)) { // Found?
			if (--iOccurrenceIndex == 0) return (INT64)(P - Value); // Found the required occurrence?
		}
		P--;
	}

	P++;
	__m128i v1 = _mm_set1_epi8((BYTE)C1); // Set the value to search
	__m128i v2 = _mm_set1_epi8((BYTE)C2); // Set the value to search

	while (L1 > 0) {
		P -= 16; // Move to the start of the block
		__m128i x = _mm_loadu_si128((__m128i const*)(P)); // Load block
		__m128i cmp = _mm_cmpeq_epi8(x, v1); // Compare
		INT32 mask = _mm_movemask_epi8(cmp); // Create mask
		cmp = _mm_cmpeq_epi8(x, v2); // Compare v2
		mask |= _mm_movemask_epi8(cmp); // Create mask

		INT64 offset = 15; // Offset within the block
		while ((mask & 0xffff) != 0) {
			if (mask & 0x8000) { // Found?
				if (--iOccurrenceIndex == 0) return (INT64)(P - Value) + offset; // Found the required occurrence?
			}
			mask <<= 1; offset--; // Next character
		}
		L1--; // Next block
	}

	return -1; // Not found
}
//	...............................................................................................
