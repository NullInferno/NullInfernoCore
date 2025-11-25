#include "NullInfernoCore.h"
#include "TDateTime.h"

// Difference between Windows and Unix epochs in seconds
#define EPOCH_DIFF_SECONDS 11644473600ULL
#define EPOCH_DIFF 116444736000000000ULL

PCHAR DefaultDateTimeOutputFormatString;
PCHAR DefaultDateTimeInputFormatString;

//	...............................................................................................
//	Format date and time to string
//	Input:
// 			oResult - output string
// 			iUserFormatString - user format string
//	Output:
//			none
//	...............................................................................................
void TDateTime::FormatDateTime(TString* oResult, CONST_PCHAR iUserFormatString) {
	if (oResult == NULL) return; // Invalid pointer
	
	oResult->SetLength(0); // Clear output
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value

	if (iUserFormatString == NULL) iUserFormatString = DefaultDateTimeOutputFormatString; // Use default format string if none provided
	if (IS_PCHAR_EMPTY(iUserFormatString)) return; // Empty format string?

	DATETIME_COMPONENTS C;
	if (!DATETIMEToComponents(FValue, &C)) return; // Split date and time value to components

	CONST_PCHAR P = iUserFormatString;
	while (*P != 0) {
		if (*P != '%') {
			oResult->AppendChars(*P, 1);
			P++;
			continue;
		}
		P++;
		if (*P == 0) return;
		if (*P == 'd') { // Day?
			if ((P[1] != 'd') || (P[1] == 0)) {
				oResult->AppendValue(C.Day);
				P++;
			} else {
				if (C.Day < 10) oResult->AppendChars('0', 1);
				oResult->AppendValue(C.Day);
				P += 2;
			}
			continue;
		}
		if (*P == 'M') { // Month?
			if ((P[1] != 'M') || (P[1] == 0)) {
				oResult->AppendValue(C.Month);
				P++;
			}
			else {
				if (C.Month < 10) oResult->AppendChars('0', 1);
				oResult->AppendValue(C.Month);
				P += 2;
			}
			continue;
		}
		if (*P == 'y') { // Year?
			if ((P[1] != 'y') || (P[1] == 0)) {
				INT32 Y = C.Year % 100;
				if (Y < 10) oResult->AppendChars('0', 1);
				oResult->AppendValue(Y);
				P++;
			}
			else {
				oResult->AppendValue(C.Year);
				P += 2;
			}
			continue;
		}
		if (*P == 'H') { // Hour 24-hour?
			if ((P[1] != 'H') || (P[1] == 0)) {
				oResult->AppendValue(C.Hour);
				P++;
			}
			else {
				if (C.Hour < 10) oResult->AppendChars('0', 1);
				oResult->AppendValue(C.Hour);
				P += 2;
			}
			continue;
		}
		if (*P == 'h') { // Hour 12-hour?
			INT32 H = C.Hour % 12; if (H == 0) H = 12;
			if ((P[1] != 'h') || (P[1] == 0)) {
				oResult->AppendValue(H);
				P++;
			}
			else {
				if (H < 10) oResult->AppendChars('0', 1);
				oResult->AppendValue(H);
				P += 2;
			}
			continue;
		}
		if (*P == 'm') { // Min?
			if ((P[1] != 'm') || (P[1] == 0)) {
				oResult->AppendValue(C.Minute);
				P++;
			}
			else {
				if (C.Minute < 10) oResult->AppendChars('0', 1);
				oResult->AppendValue(C.Minute);
				P += 2;
			}
			continue;
		}
		if (*P == 's') { // Sec?
			if ((P[1] != 's') || (P[1] == 0)) {
				oResult->AppendValue(C.Second);
				P++;
			}
			else {
				if (C.Second < 10) oResult->AppendChars('0', 1);
				oResult->AppendValue(C.Second);
				P += 2;
			}
			continue;
		}
		if (*P == 't') { // AM/PM ?
			if (C.Hour < 12) {
				oResult->AppendChars('A', 1);
				oResult->AppendChars('M', 1);
			} else {
				oResult->AppendChars('P', 1);
				oResult->AppendChars('M', 1);
			}
			P++;
			continue;
		}
	}
}
//	...............................................................................................
//	...............................................................................................
//	Compare with another date and time value
//	Input:
// 			iValue - date and time value to compare with
//	Output:
//			0 if equal, negative value if this < iValue, positive value if this > iValue
//	...............................................................................................
INT32 TDateTime::Compare(DATETIME iValue) {
	if (FValue == DATETIME_EMPTY) return iValue == DATETIME_EMPTY ? 0 : -1;
	if (iValue == DATETIME_EMPTY) return 1;
	return FValue == iValue ? 0 : (FValue < iValue ? -1 : 1);
}
//	...............................................................................................
//	...............................................................................................
//	Compare with another date and time value
//	Input:
// 			iValue - date and time value to compare with
//	Output:
//			0 if equal, negative value if this < iValue, positive value if this > iValue
//	...............................................................................................
INT32 TDateTime::Compare(TDateTime* iValue) {
	return Compare(iValue == NULL ? DATETIME_EMPTY : iValue->FValue); // Use other Compare method
}
//	...............................................................................................
//	...............................................................................................
//	Check equality with another date and time value
//	Input:
// 			iValue - date and time value to compare with
// 			iOnlySeconds - compare only up to seconds precision
//	Output:
//			true / false
//	...............................................................................................
BOOL TDateTime::IsEqual(DATETIME iValue, BOOL iOnlySeconds) {
	if (!iOnlySeconds) return Compare(iValue) == 0; // Use Compare method

	if (FValue == DATETIME_EMPTY) return iValue == DATETIME_EMPTY; // Both empty?
	if (iValue == DATETIME_EMPTY) return false; // One is empty, the other is not

	DATETIME_COMPONENTS C1, C2;
	if (!DATETIMEToComponents(FValue, &C1)) return false; // Invalid date and time value
	if (!DATETIMEToComponents(iValue, &C2)) return false; // Invalid date and time value
	return (C1.Year == C2.Year) && (C1.Month == C2.Month) && (C1.Day == C2.Day) &&
		(C1.Hour == C2.Hour) && (C1.Minute == C2.Minute) && (C1.Second == C2.Second);
}
//	...............................................................................................
//	...............................................................................................
//	Check equality with another date and time value
//	Input:
// 			iValue - date and time value to compare with
// 			iOnlySeconds - compare only up to seconds precision
//	Output:
//			true / false
//	...............................................................................................
BOOL TDateTime::IsEqual(TDateTime* iValue, BOOL iOnlySeconds) {
	if (iValue == NULL) return FValue == DATETIME_EMPTY; // Both empty?
	return IsEqual(iValue->FValue, iOnlySeconds); // Use other IsEqual method
}
//	...............................................................................................
//	...............................................................................................
//	Check equality with date and time components
//	Input:
// 			iYear - year component
// 			iMonth - month component
// 			iDay - day component
// 			iHour - hour component
// 			iMinute - minute component
// 			iSecond - second component
//	Output:
//			true / false
//	...............................................................................................
BOOL TDateTime::IsEqual(INT32 iYear, INT32 iMonth, INT32 iDay, INT32 iHour, INT32 iMinute, INT32 iSecond, INT32 iMilliseconds) {
	DATETIME_COMPONENTS C;
	C.Year = iYear; // Set components
	C.Month = iMonth;
	C.Day = iDay;
	C.Hour = iHour;
	C.Minute = iMinute;
	C.Second = iSecond;
	C.Millisecond = iMilliseconds;
	DATETIME D = ComponentsToDATETIME(&C); // Convert to DATETIME
	return IsEqual(D, true); // Use other IsEqual method
}
//	...............................................................................................
//	...............................................................................................
//	Add milliseconds to date and time value
//	Input:
// 			iMilliseconds - number of milliseconds to add (can be negative)
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddMilliseconds(INT64 iMilliseconds) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?
	if (iMilliseconds < 0) FValue -= (UINT64)(-iMilliseconds) * 10000ull;
	else FValue += iMilliseconds * 10000ull;
}
//	...............................................................................................
//	...............................................................................................
//	Add seconds to date and time value
//	Input:
// 			iSeconds - number of seconds to add (can be negative)
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddSeconds(INT64 iSeconds) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?
	if (iSeconds < 0) FValue -= (UINT64)(-iSeconds) * 10000000ull;
	else FValue += iSeconds * 10000000ull;
}
//	...............................................................................................
//	...............................................................................................
//	Add minutes to date and time value
//	Input:
// 			iMinutes - number of minutes to add (can be negative)
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddMinutes(INT64 iMinutes) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?
	if (iMinutes < 0) FValue -= (UINT64)(-iMinutes) * 10000000ull * 60ull;
	else FValue += iMinutes * 10000000ull * 60ull;
}
//	...............................................................................................
//	...............................................................................................
//	Add hours to date and time value
//	Input:
// 			iHours - number of hours to add (can be negative)
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddHours(INT64 iHours) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?
	if (iHours < 0) FValue -= (UINT64)(-iHours) * 10000000ull * 3600ull;
	else FValue += iHours * 10000000ull * 3600ull;
}
//	...............................................................................................
//	...............................................................................................
//	Add days to date and time value
//	Input:
// 			iDays - number of days to add (can be negative)
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddDays(INT64 iDays) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?
	if (iDays < 0) FValue -= (UINT64)(-iDays) * 10000000ull * 86400ull;
	else FValue += iDays * 10000000ull * 86400ull;
}
//	...............................................................................................
//	...............................................................................................
//	Add months to date and time value
//	Input:
// 			iMonths - number of months to add (can be negative)
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddMonths(INT32 iMonths) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?
	DATETIME_COMPONENTS C; // Components structure
	if (!DATETIMEToComponents(FValue, &C)) return; // Invalid date and time value

	INT32 D = C.Day > 28 ? C.Day - 28 : 0; // Day adjustment
	C.Day -= D;

	if (iMonths > 0) { // Adding months
		C.Year += iMonths / 12;
		C.Month += iMonths % 12;
		if (C.Month > 12) {
			C.Year++;
			C.Month -= 12;
		}
	}
	else { // Subtracting months
		iMonths = -iMonths;
		C.Year -= iMonths / 12;
		C.Month -= iMonths % 12;
		if (C.Month < 1) {
			C.Year--;
			C.Month += 12;
		}
	}
	FValue = ComponentsToDATETIME(&C); // Convert back to DATETIME
	if (D > 0) AddDays(D); // Add day adjustment
}
//	...............................................................................................
//	...............................................................................................
//	Add years to date and time value
//	Input:
// 			iYears - number of years to add (can be negative)
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddYears(INT32 iYears) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?

	DATETIME_COMPONENTS C; // Components structure
	if (!DATETIMEToComponents(FValue, &C)) return; // Invalid date and time value

	INT32 D = C.Day > 28 ? C.Day - 28 : 0; // Day adjustment
	C.Day -= D;

	if (iYears > 0) {
		C.Year += iYears;
	}
	else {
		iYears = -iYears;
		if (C.Year < iYears) {
			FValue = DATETIME_EMPTY; // Resulting date is invalid
			return;
		}
		C.Year -= iYears;
	}
	FValue = ComponentsToDATETIME(&C); // Convert back to DATETIME
	if (D > 0) AddDays(D); // Add day adjustment
}
//	...............................................................................................
//	...............................................................................................
//	Add another date and time value
//	Input:
// 			iValue - date and time value to add
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddValue(DATETIME iValue) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?
	if (iValue == DATETIME_EMPTY) return; // Empty input date and time value?
	FValue = FValue + iValue - EPOCH_DIFF;
}
//	...............................................................................................
//	...............................................................................................
//	Add another date and time value
//	Input:
// 			iValue - date and time value to add
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddValue(TDateTime* iValue) {
	if (iValue == NULL) return; // Invalid pointer
	AddValue(iValue->FValue); // Use other AddValue method
}
//	...............................................................................................
//	...............................................................................................
//	Add another date and time value
//	Input:
// 			iValue - date and time value to add
//	Output:
//			none
//	...............................................................................................
void TDateTime::AddValue(TDateTime& iValue) {
	AddValue(iValue.FValue); // Use other AddValue method
}
//	...............................................................................................
//	...............................................................................................
//	Subtract another date and time value
//	Input:
// 			iValue - date and time value to subtract
//	Output:
//			none
//	...............................................................................................
void TDateTime::SubtractValue(DATETIME iValue) {
	if (FValue == DATETIME_EMPTY) return; // Empty date and time value?
	if (iValue == DATETIME_EMPTY) return; // Empty input date and time value?
	FValue -= iValue;
}
//	...............................................................................................
//	...............................................................................................
//	Subtract another date and time value
//	Input:
// 			iValue - date and time value to subtract
//	Output:
//			none
//	...............................................................................................
void TDateTime::SubtractValue(TDateTime* iValue) {
	if (iValue == NULL) return; // Invalid pointer
	SubtractValue(iValue->FValue); // Use other SubtractValue method
}
//	...............................................................................................
//	...............................................................................................
//	Subtract another date and time value
//	Input:
// 			iValue - date and time value to subtract
//	Output:
//			none
//	...............................................................................................
void TDateTime::SubtractValue(TDateTime& iValue) {
	SubtractValue(iValue.FValue); // Use other SubtractValue method
}
//	...............................................................................................
//	...............................................................................................
//	Format date and time to string
//	Input:
// 			iValue - date and time value
// 			oResult - output buffer
// 			iLength - length of output buffer without terminating null character
// 			iFormatString - format string or NULL for default format
//	Output:
//			number of characters written (excluding terminating null character) or -1 if output buffer is too small
//	...............................................................................................
INT64 TDateTime::FormatDateTime(DATETIME iValue, PCHAR oResult, INT64 iLength, CONST_PCHAR iUserFormatString) {
	TDateTime D(iValue); // Create temporary TDateTime object
	TString S; D.FormatDateTime(&S, iUserFormatString); // Format to temporary string
	if (S.Length > iLength) return -1; // Output buffer too small
	FNC_STRCPY(oResult, S.Value); // Copy to output buffer
	return S.Length; // Return number of characters written
}
//	...............................................................................................
//	...............................................................................................
//	Parse date and time from string
//	Input:
// 			iValue - input string
// 			iFormatString - format string
//	Output:
//			parsed DATETIME value
//	...............................................................................................
DATETIME TDateTime::ParseDateTime(CONST_PCHAR iValue, CONST_PCHAR iFormatString) {
	if (IS_PCHAR_EMPTY(iValue)) return DATETIME_EMPTY; // Empty input string?

	if (iFormatString == NULL) iFormatString = DefaultDateTimeInputFormatString; // Use default format string if none provided
	if (IS_PCHAR_EMPTY(iFormatString)) return DATETIME_EMPTY; // Empty format string?

	CONST_PCHAR PV = iValue; // Pointer to current position in input string
	CONST_PCHAR PF = iFormatString; // Pointer to current position in format string

	DATETIME_COMPONENTS C; // Components structure
	FNC_MEMSET(&C, 0, sizeof(DATETIME_COMPONENTS)); // Clear components

	BOOL IsPM = false; // PM indicator
	BOOL Is12HourFormat = false; // 12-hour format indicator

	while (true) {
		if (*PF == 0) break;
		
		if (*PF != '%') { // no format specifier?
			if (*PF != *PV) return DATETIME_EMPTY;
			PF++;
			PV++;
			continue;
		}

		PF++;
		if (*PF == 0) return DATETIME_EMPTY;
		
		if (*PF == '%') { // Two '%'?
			if (*PV != '%') return DATETIME_EMPTY;
			PF++;
			PV++;
			continue;
		}

		if (*PF == 'd') { // '%d'?
			if ((*PV < '0') || (*PV > '9')) return DATETIME_EMPTY;
			UINT32 V = *PV - '0';
			PV++;
			if ((*PV >= '0') || (*PV <= '9')) {
				V = V*10 + (*PV - '0');
				PV++;
			}
			C.Day = V;
			if (*PV == 0) break;
			PF++;
			continue;
		}
		if (*PF == 'M') { // '%M'?
			if ((*PV < '0') || (*PV > '9')) return DATETIME_EMPTY;
			UINT32 V = *PV - '0';
			PV++;
			if ((*PV >= '0') || (*PV <= '9')) {
				V = V * 10 + (*PV - '0');
				PV++;
			}
			C.Month = V;
			if (*PV == 0) break;
			PF++;
			continue;
		}
		if (*PF == 'y') { // '%y'?
			if ((*PV < '0') || (*PV > '9')) return DATETIME_EMPTY;
			UINT32 V = *PV - '0';
			PV++;
			if ((*PV >= '0') || (*PV <= '9')) {
				V = V * 10 + (*PV - '0');
				PV++;
				if ((*PV >= '0') || (*PV <= '9')) {
					V = V * 10 + (*PV - '0');
					PV++;
					if ((*PV >= '0') || (*PV <= '9')) {
						V = V * 10 + (*PV - '0');
						PV++;
					}
				}
			}
			C.Year = V;
			if (*PV == 0) break;
			PF++;
			continue;
		}
		if (*PF == 'H') { // '%H'?
			if ((*PV < '0') || (*PV > '9')) return DATETIME_EMPTY;
			UINT32 V = *PV - '0';
			PV++;
			if ((*PV >= '0') || (*PV <= '9')) {
				V = V * 10 + (*PV - '0');
				PV++;
			}
			C.Hour = V;
			if (*PV == 0) break;
			PF++;
			continue;
		}
		if (*PF == 'h') { // '%h'?
			if ((*PV < '0') || (*PV > '9')) return DATETIME_EMPTY;
			UINT32 V = *PV - '0';
			PV++;
			if ((*PV >= '0') || (*PV <= '9')) {
				V = V * 10 + (*PV - '0');
				PV++;
			}
			C.Hour = V;
			Is12HourFormat = true;
			if (*PV == 0) break;
			PF++;
			continue;
		}
		if (*PF == 'm') { // '%m'?
			if ((*PV < '0') || (*PV > '9')) return DATETIME_EMPTY;
			UINT32 V = *PV - '0';
			PV++;
			if ((*PV >= '0') || (*PV <= '9')) {
				V = V * 10 + (*PV - '0');
				PV++;
			}
			C.Minute = V;
			if (*PV == 0) break;
			PF++;
			continue;
		}
		if (*PF == 's') { // '%s'?
			if ((*PV < '0') || (*PV > '9')) return DATETIME_EMPTY;
			UINT32 V = *PV - '0';
			PV++;
			if ((*PV >= '0') || (*PV <= '9')) {
				V = V * 10 + (*PV - '0');
				PV++;
			}
			C.Second = V;
			if (*PV == 0) break;
			PF++;
			continue;
		}
		if (*PF == 't') { // '%t'?
			if ((*PV == 'a') || (*PV == 'A')) { // AM?
				PV++;
				if ((*PV != 'm') && (*PV != 'M')) return DATETIME_EMPTY;
				PF++; PV++;
				continue;
			}
			if ((*PV != 'p') && (*PV != 'P')) return DATETIME_EMPTY; // Not PM?
			PV++;
			if ((*PV != 'm') && (*PV != 'M')) return DATETIME_EMPTY;
			PF++; PV++; IsPM = true;
			continue;
		}
		return DATETIME_EMPTY;
	}

	// Validate components
	if (C.Day < 1 || C.Day > 31) return DATETIME_EMPTY;
	if (C.Month < 1 || C.Month > 12) return DATETIME_EMPTY;
	if (C.Year < 1) return DATETIME_EMPTY;
	if (C.Minute < 0 || C.Minute > 59) return DATETIME_EMPTY;
	if (C.Second < 0 || C.Second > 59) return DATETIME_EMPTY;
	if (Is12HourFormat) { // 12-hour format?
		if (C.Hour < 1 || C.Hour > 12) return DATETIME_EMPTY;
		if (IsPM) { // PM?
			if (C.Hour < 12) C.Hour += 12;
		}
		else {
			if (C.Hour == 12) C.Hour = 0;
		}
	}
	else {
		if (C.Hour < 0 || C.Hour > 23) return DATETIME_EMPTY;
	}

	return ComponentsToDATETIME(&C); // Return as filetime
}
//	...............................................................................................
//	...............................................................................................
//	Get current local date and time
//	Input:
// 			iLocalDateTime - true for local date and time, false for UTC
//	Output:
//			current local date and time
//	...............................................................................................
DATETIME TDateTime::GetCurrentDateTime(BOOL iLocalDateTime) {
#ifdef WINDOWS_SYSTEM
	SYSTEMTIME ST; GetSystemTime(&ST); // Get current system time
	FILETIME FT, FT2; SystemTimeToFileTime(&ST, &FT); // Convert to file time
	if (iLocalDateTime) FileTimeToLocalFileTime(&FT, &FT2); // Convert to local file time
	else FT2 = FT; // Use UTC file time
	ULARGE_INTEGER U; U.LowPart = FT2.dwLowDateTime; U.HighPart = FT2.dwHighDateTime; // Convert to ULARGE_INTEGER
	return U.QuadPart; // Return the date and time value
#else

	struct timeval tv;

	gettimeofday(&tv, NULL); // Get current time

	struct tm tm_info;
	if (iLocalDateTime) localtime_r(&tv.tv_sec, &tm_info); // Convert to localtime
	else gmtime_r(&tv.tv_sec, &tm_info); // Convert to UTC

	DATETIME_COMPONENTS C; // Fill structure
	C.Year = tm_info.tm_year + 1900;
	C.Month = tm_info.tm_mon + 1;
	C.Day = tm_info.tm_mday;
	C.Hour = tm_info.tm_hour;
	C.Minute = tm_info.tm_min;
	C.Second = tm_info.tm_sec;
	C.Millisecond = tv.tv_usec / 1000;

	return ComponentsToDATETIME(&C); // Return as filetime
#endif
}
//	...............................................................................................
//	...............................................................................................
//	Convert date and time value to components
//	Input:
// 			iValue - date and time value
//			oComponents - pointer to components structure
//	Output:
//			none
//	...............................................................................................
BOOL TDateTime::DATETIMEToComponents(DATETIME iValue, PDATETIME_COMPONENTS oComponents) {
	if (oComponents == NULL) return false; // Invalid pointer
	if (iValue == DATETIME_EMPTY) { // Empty date and time value?
		FNC_MEMSET(oComponents, 0, sizeof(DATETIME_COMPONENTS));
		return false;
	}
#ifdef WINDOWS_SYSTEM
	ULARGE_INTEGER U; U.QuadPart = iValue; // Convert to ULARGE_INTEGER
	FILETIME FT; FT.dwLowDateTime = U.LowPart; FT.dwHighDateTime = U.HighPart; // Convert to FILETIME
	SYSTEMTIME ST; 
	
	if (FileTimeToSystemTime(&FT, &ST) == 0) { // Convert to system time
		FNC_MEMSET(oComponents, 0, sizeof(DATETIME_COMPONENTS));
		return false;
	}
	
	oComponents->Year = (INT32)ST.wYear; // Fill components
	oComponents->Month = (INT32)ST.wMonth;
	oComponents->Day = (INT32)ST.wDay;
	oComponents->Hour = (INT32)ST.wHour;
	oComponents->Minute = (INT32)ST.wMinute;
	oComponents->Second = (INT32)ST.wSecond;
	oComponents->Millisecond = (INT32)ST.wMilliseconds;
	return true; // Success
#else
	time_t Seconds = (iValue / 10000000ULL) - EPOCH_DIFF_SECONDS;
	UINT64 NS = iValue % 10000000ULL;

	struct tm tm_info;
	gmtime_r(&Seconds, &tm_info); // Convert to local time

	oComponents->Year = tm_info.tm_year + 1900; // Fill components
	oComponents->Month = tm_info.tm_mon + 1;
	oComponents->Day = tm_info.tm_mday;
	oComponents->Hour = tm_info.tm_hour;
	oComponents->Minute = tm_info.tm_min;
	oComponents->Second = tm_info.tm_sec;
	oComponents->Millisecond = NS / 10000;
	return true; // Success
#endif
}
//	...............................................................................................
//	...............................................................................................
//	Convert components to date and time value
//	Input:
// 			iComponents - pointer to components structure
//	Output:
//			DATETIME value
//	...............................................................................................
DATETIME TDateTime::ComponentsToDATETIME(PDATETIME_COMPONENTS iComponents) {
	if (iComponents == NULL) return DATETIME_EMPTY; // Invalid pointer

#ifdef WINDOWS_SYSTEM
	SYSTEMTIME ST;
	ST.wYear = (WORD)iComponents->Year; // Fill SYSTEMTIME structure
	ST.wMonth = (WORD)iComponents->Month;
	ST.wDay = (WORD)iComponents->Day;
	ST.wDayOfWeek = 0;
	ST.wHour = (WORD)iComponents->Hour;
	ST.wMinute = (WORD)iComponents->Minute;
	ST.wSecond = (WORD)iComponents->Second;
	ST.wMilliseconds = (WORD)iComponents->Millisecond;

	FILETIME FT;
	if (SystemTimeToFileTime(&ST, &FT) == 0) return DATETIME_EMPTY; // Convert to file time

	ULARGE_INTEGER U; U.LowPart = FT.dwLowDateTime; U.HighPart = FT.dwHighDateTime; // Convert to ULARGE_INTEGER
	return U.QuadPart; // Return the date and time value
#else
	struct tm tm_info;

	tm_info.tm_year = iComponents->Year - 1900;
	tm_info.tm_mon = iComponents->Month - 1;
	tm_info.tm_mday = iComponents->Day;
	tm_info.tm_hour = iComponents->Hour;
	tm_info.tm_min = iComponents->Minute;
	tm_info.tm_sec = iComponents->Second;
	tm_info.tm_wday = 0;
	tm_info.tm_isdst = -1;

	time_t Seconds = timegm(&tm_info);
	if (Seconds == (time_t)-1) return DATETIME_EMPTY;
	if ((tm_info.tm_year != iComponents->Year - 1900) || (tm_info.tm_mon != iComponents->Month - 1) || (tm_info.tm_mday != iComponents->Day) || (tm_info.tm_hour != iComponents->Hour) || (tm_info.tm_min != iComponents->Minute) || (tm_info.tm_sec != iComponents->Second)) return DATETIME_EMPTY;

	// Convert to FILETIME ticks (100 ns intervals since 1601)
	UINT64 FT = ((UINT64)(Seconds + EPOCH_DIFF_SECONDS) * 10000000ULL)
		+ (UINT64)iComponents->Millisecond * 10000ULL;

	return FT;
#endif
	return 0;
}
//	...............................................................................................
//	...............................................................................................
//	Set default date and time format string for conversion to string
//	Input:
// 			iFormatString - new format string
//	Output:
//			none
//	...............................................................................................
void TDateTime::SetDefaultOutputFormatString(CONST_PCHAR iFormatString) {
	if (DefaultDateTimeOutputFormatString != NULL) {
		PCHAR_FREE(DefaultDateTimeOutputFormatString);
		DefaultDateTimeOutputFormatString = NULL;
	}
	if (iFormatString != NULL) {
		DefaultDateTimeOutputFormatString = PCHAR_ALLOC(FNC_STRLEN(iFormatString) + 1);
		if (DefaultDateTimeOutputFormatString != NULL) FNC_STRCPY(DefaultDateTimeOutputFormatString, iFormatString);
	}
}
//	...............................................................................................
//	...............................................................................................
//	Set default format string for conversion from string
//	Input:
// 			iFormatString - new format string
//	Output:
//			none
//	...............................................................................................
void TDateTime::SetDefaultInputFormatString(CONST_PCHAR iFormatString) {
	if (DefaultDateTimeInputFormatString != NULL) {
		PCHAR_FREE(DefaultDateTimeInputFormatString);
		DefaultDateTimeInputFormatString = NULL;
	}
	if (iFormatString != NULL) {
		DefaultDateTimeInputFormatString = PCHAR_ALLOC(FNC_STRLEN(iFormatString) + 1);
		if (DefaultDateTimeInputFormatString != NULL) FNC_STRCPY(DefaultDateTimeInputFormatString, iFormatString);
	}
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TDateTime::TDateTime(void) {
	FValue = DATETIME_EMPTY; // Initialize as empty date and time value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - date and time value to set
//	Output:
//			none
//	...............................................................................................
TDateTime::TDateTime(DATETIME iValue) {
	FValue = iValue; // Save date and time value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - date and time value to set
//	Output:
//			none
//	...............................................................................................
TDateTime::TDateTime(TDateTime& iValue) {
	FValue = iValue.FValue; // Copy date and time value
}
//	...............................................................................................
//	...............................................................................................
//	Constructor
//	Input:
// 			iValue - date and time value to set
//	Output:
//			none
//	...............................................................................................
TDateTime::TDateTime(TDateTime* iValue) {
	FValue = iValue == NULL ? DATETIME_EMPTY : iValue->FValue; // Copy date and time value
}
//	...............................................................................................
//	...............................................................................................
//	Destructor
//	Input:
// 			none
//	Output:
//			none
//	...............................................................................................
TDateTime::~TDateTime(void) {
}
//	...............................................................................................
//	...............................................................................................
//	Get date and time value
//	Input:
// 			none
//	Output:
//			date and time value
//	...............................................................................................
DATETIME TDateTime::GetValue(void) {
	return FValue;
}
//	...............................................................................................
//	...............................................................................................
//	Check if date and time value is valid
//	Input:
// 			none
//	Output:
//			true / false
//	...............................................................................................
BOOL TDateTime::IsValid(void) {
	return FValue != DATETIME_EMPTY; // Check if date and time value is not empty
}
//	...............................................................................................
//	...............................................................................................
//	Get milliseconds
//	Input:
// 			none
//	Output:
//			value of milliseconds component (0 to 999)
//	...............................................................................................
INT32 TDateTime::GetMillisecond(void) {
	if (FValue == DATETIME_EMPTY) return -1; // Invalid date and time value?
	DATETIME_COMPONENTS C;
	return DATETIMEToComponents(FValue, &C) ? C.Millisecond : -1;
}
//	...............................................................................................
//	...............................................................................................
//	Get seconds
//	Input:
// 			none
//	Output:
//			value of seconds component (0 to 999)
//	...............................................................................................
INT32 TDateTime::GetSecond(void) {
	if (FValue == DATETIME_EMPTY) return -1; // Invalid date and time value?
	DATETIME_COMPONENTS C;
	return DATETIMEToComponents(FValue, &C) ? C.Second : -1;
}
//	...............................................................................................
//	...............................................................................................
//	Get minutes
//	Input:
// 			none
//	Output:
//			value of minutes component (0 to 999)
//	...............................................................................................
INT32 TDateTime::GetMinute(void) {
	if (FValue == DATETIME_EMPTY) return -1; // Invalid date and time value?
	DATETIME_COMPONENTS C;
	return DATETIMEToComponents(FValue, &C) ? C.Minute : -1;
}
//	...............................................................................................
//	...............................................................................................
//	Get hours
//	Input:
// 			none
//	Output:
//			value of hours component (0 to 999)
//	...............................................................................................
INT32 TDateTime::GetHour(void) {
	if (FValue == DATETIME_EMPTY) return -1; // Invalid date and time value?
	DATETIME_COMPONENTS C;
	return DATETIMEToComponents(FValue, &C) ? C.Hour : -1;
}
//	...............................................................................................
//	...............................................................................................
//	Get days
//	Input:
// 			none
//	Output:
//			value of days component (0 to 999)
//	...............................................................................................
INT32 TDateTime::GetDay(void) {
	if (FValue == DATETIME_EMPTY) return -1; // Invalid date and time value?
	DATETIME_COMPONENTS C;
	return DATETIMEToComponents(FValue, &C) ? C.Day : -1;
}
//	...............................................................................................
//	...............................................................................................
//	Get months
//	Input:
// 			none
//	Output:
//			value of months component (0 to 999)
//	...............................................................................................
INT32 TDateTime::GetMonth(void) {
	if (FValue == DATETIME_EMPTY) return -1; // Invalid date and time value?
	DATETIME_COMPONENTS C;
	return DATETIMEToComponents(FValue, &C) ? C.Month : -1;
}
//	...............................................................................................
//	...............................................................................................
//	Get years
//	Input:
// 			none
//	Output:
//			value of years component (0 to 999)
//	...............................................................................................
INT32 TDateTime::GetYear(void) {
	if (FValue == DATETIME_EMPTY) return -1; // Invalid date and time value?
	DATETIME_COMPONENTS C;
	return DATETIMEToComponents(FValue, &C) ? C.Year : -1;
}
//	...............................................................................................
//	...............................................................................................
//	Get local date and time
//	Input:
// 			none
//	Output:
//			DATETIME value
//	...............................................................................................
DATETIME TDateTime::GetLocalDateTime(void) {
	if (FValue == DATETIME_EMPTY) return false; // 

#ifdef WINDOWS_SYSTEM
	ULARGE_INTEGER U; U.QuadPart = FValue;
	FILETIME FT, FT2;
	FT.dwLowDateTime = U.LowPart; FT.dwHighDateTime = U.HighPart; // Convert to FILETIME
	FileTimeToLocalFileTime(&FT, &FT2); // Convert to local file time
	U.LowPart = FT2.dwLowDateTime; U.HighPart = FT2.dwHighDateTime; // Convert to ULARGE_INTEGER
	return U.QuadPart; // Return date and time value
#else
	time_t Seconds = (FValue / 10000000ULL) - EPOCH_DIFF_SECONDS;
	UINT64 NS = FValue % 10000000ULL;

	struct tm tm_info;
	localtime_r(&Seconds, &tm_info); // Convert to localtime

	DATETIME_COMPONENTS C; // Fill structure
	C.Year = tm_info.tm_year + 1900;
	C.Month = tm_info.tm_mon + 1;
	C.Day = tm_info.tm_mday;
	C.Hour = tm_info.tm_hour;
	C.Minute = tm_info.tm_min;
	C.Second = tm_info.tm_sec;
	C.Millisecond = NS / 1000;

	return ComponentsToDATETIME(&C); // Return as filetime
#endif
}
//	...............................................................................................
//	...............................................................................................
//	Get local date and time components
//	Input:
// 			oComponents - pointer to components structure
//	Output:
//			true / false
//	...............................................................................................
BOOL TDateTime::GetLocalDateTime(PDATETIME_COMPONENTS oComponents) {
	return DATETIMEToComponents(GetLocalDateTime(), oComponents); // Convert to components
}
//	...............................................................................................
//	...............................................................................................
//	Create content from components
//	Input:
// 			iYear - year component
// 			iMonth - month component (from 1 to 12)
// 			iDay - day in month component (from 1 to 31)
// 			iHour - hour component (from 0 to 23)
// 			iMinute - minute component (from 0 to 59)
// 			iSecond - second component (from 0 to 59)
// 			iMillisecond - millisecond component (from 0 to 999)
//	Output:
//			true / false
//	...............................................................................................
BOOL TDateTime::SetValue(INT32 iYear, INT32 iMonth, INT32 iDay, INT32 iHour, INT32 iMinute, INT32 iSecond, INT32 iMillisecond) {
	DATETIME_COMPONENTS C; // Fill components structure
	C.Year = iYear;
	C.Month = iMonth;
	C.Day = iDay;
	C.Hour = iHour;
	C.Minute = iMinute;
	C.Second = iSecond;
	C.Millisecond = iMillisecond;
	FValue = ComponentsToDATETIME(&C); // Convert to date and time value
	return FValue != DATETIME_EMPTY;
}
//	...............................................................................................
//	...............................................................................................
//	Set date and time value
//	Input:
// 			iValue - date and time value to set
//	Output:
//			none
//	...............................................................................................
void TDateTime::SetValue(DATETIME iValue) {
	FValue = iValue;
}
//	...............................................................................................
//	...............................................................................................
//	Set date and time value
//	Input:
// 			iValue - date and time value to set
//	Output:
//			none
//	...............................................................................................
void TDateTime::SetValue(TDateTime& iValue) {
	FValue = iValue.FValue;
}
//	...............................................................................................
//	...............................................................................................
//	Set date and time value
//	Input:
// 			iValue - date and time value to set
//	Output:
//			none
//	...............................................................................................
void TDateTime::SetValue(TDateTime* iValue) {
	FValue = iValue == NULL ? DATETIME_EMPTY : iValue->FValue;
}
//	...............................................................................................
//	...............................................................................................
//	Set date and time value
//	Input:
// 			iValue - date and time value to set
//			iFormatString - format string or NULL for default format
//	Output:
//			none
//	...............................................................................................
BOOL TDateTime::SetValue(CONST_PCHAR iValue, CONST_PCHAR iFormatString) {

	if (IS_PCHAR_EMPTY(iValue)) return false;
	FValue = ParseDateTime(iValue, iFormatString); // Parse date and time from string
	return FValue != DATETIME_EMPTY;
}
//	...............................................................................................
//	...............................................................................................
//	Set current local date and time
//	Input:
// 			iLocalDateTime - if true, set local date and time; if false, set UTC date and time
//	Output:
//			none
//	...............................................................................................
void TDateTime::SetCurrentDateTime(BOOL iLocalDateTime) {
	FValue = GetCurrentDateTime(iLocalDateTime); // Get current local date and time
}
//	...............................................................................................
