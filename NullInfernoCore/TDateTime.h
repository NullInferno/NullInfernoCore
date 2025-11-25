#pragma once

typedef struct {
	INT32 Year;
	INT32 Month;
	INT32 Day;
	INT32 Hour;
	INT32 Minute;
	INT32 Second;
	INT32 Millisecond;
} DATETIME_COMPONENTS, *PDATETIME_COMPONENTS;

// Date and time format specifiers for output:

// %d - day in month (01-31) without leading zero
// %dd - day in month (01-31) with leading zero
// %M - month (1-12) without leading zero
// %MM - month (01-12) with leading zero
// %y - year (two digits) with leading zero
// %yy - year (four digits) with leading zeros
// %H - hour (0-23) without leading zero in 24-hour format
// %HH - hour (00-23) with leading zero in 24-hour format
// %h - hour (1-12) without leading zero in 12-hour format
// %hh - hour (01-12) with leading zero 
// %m - minute (0-59) without leading zero
// %mm - minute (00-59) with leading zero
// %s - second (0-59) without leading zero
// %ss - second (00-59) with leading zero
// %t - zobrazenie AM/PM

// Date and time format specifiers for input:

// %d - day in month (01-31)
// %M - month (1-12)
// %y - year (two digits)
// %yy - year (four digits)
// %H - hour (0-23) in 24-hour format
// %h - hour (1-12) in 12-hour format
// %m - minute (0-59) without leading zero
// %s - second (0-59) without leading zero
// %t - AM/PM sign

//	...............................................................................................
//	Class TDateTime;
//	.............................................................................................
class TDateTime {
private:
	DATETIME FValue; // value
public:
	TDateTime(void); // Constructor
	TDateTime(DATETIME iValue); // Constructor
	TDateTime(TDateTime& iValue); // Constructor
	TDateTime(TDateTime* iValue); // Constructor
	~TDateTime(void); // Destructor
public:
	DATETIME GetValue(void); // Get date and time value
	BOOL IsValid(void); // Check if date and time value is valid
	INT32 GetMillisecond(void); // Get milliseconds
	INT32 GetSecond(void); // Get seconds
	INT32 GetMinute(void); // Get minutes
	INT32 GetHour(void); // Get hours
	INT32 GetDay(void); // Get day in month
	INT32 GetMonth(void); // Get month
	INT32 GetYear(void); // Get year
	BOOL GetLocalDateTime(PDATETIME_COMPONENTS oComponents); // Get local date and time components
	DATETIME GetLocalDateTime(void); // Get local date and time
public:
	BOOL SetValue(INT32 iYear, INT32 iMonth, INT32 iDay, INT32 iHour = 0, INT32 iMinute = 0, INT32 iSecond = 0, INT32 iMillisecond = 0); // Create content from components
	void SetValue(DATETIME iValue); // Set date and time value
	void SetValue(TDateTime& iValue); // Set date and time value
	void SetValue(TDateTime* iValue); // Set date and time value
	BOOL SetValue(CONST_PCHAR iValue, CONST_PCHAR iFormatString = ""); // Set date and time value from string
	void SetCurrentDateTime(BOOL iLocalDateTime = true); // Set current local date and time
public:
	void FormatDateTime(TString* oResult, CONST_PCHAR iUserFormatString = ""); // Format date and time to string
	INT32 Compare(DATETIME iValue); // Compare with another date and time value
	INT32 Compare(TDateTime* iValue); // Compare with another date and time value
	BOOL IsEqual(DATETIME iValue, BOOL iOnlySeconds = false); // Check equality with another date and time value
	BOOL IsEqual(TDateTime* iValue, BOOL iOnlySeconds = false); // Check equality with another date and time value
	BOOL IsEqual(INT32 iYear, INT32 iMonth, INT32 iDay, INT32 iHour = 0, INT32 iMinute = 0, INT32 iSecond = 0, INT32 iMilliseconds = 0); // Check equality with date and time components
public:
	void AddMilliseconds(INT64 iMilliseconds); // Add milliseconds to date and time value
	void AddSeconds(INT64 iSeconds); // Add seconds to date and time value
	void AddMinutes(INT64 iMinutes); // Add minutes to date and time value
	void AddHours(INT64 iHours); // Add hours to date and time value
	void AddDays(INT64 iDays); // Add days to date and time value
	void AddMonths(INT32 iMonths); // Add months to date and time value
	void AddYears(INT32 iYears); // Add years to date and time value
	void AddValue(DATETIME iValue); // Add another date and time value
	void AddValue(TDateTime* iValue); // Add another date and time value
	void AddValue(TDateTime& iValue); // Add another date and time value
	void SubtractValue(DATETIME iValue); // Subtract another date and time value
	void SubtractValue(TDateTime* iValue); // Subtract another date and time value
	void SubtractValue(TDateTime& iValue); // Subtract another date and time value
public:
	static INT64 FormatDateTime(DATETIME iValue, PCHAR oResult, INT64 iLength, CONST_PCHAR iUserFormatString = ""); // Format date and time to string
	static DATETIME ParseDateTime(CONST_PCHAR iValue, CONST_PCHAR iFormatString = ""); // Parse date and time from string
public:
	static DATETIME GetCurrentDateTime(BOOL iLocalDateTime = true); // Get current local date and time
	static BOOL DATETIMEToComponents(DATETIME iValue, PDATETIME_COMPONENTS oComponents); // Convert date and time value to components
	static DATETIME ComponentsToDATETIME(PDATETIME_COMPONENTS iComponents); // Convert components to date and time value
	static void SetDefaultOutputFormatString(CONST_PCHAR iFormatString); // Set default date and time format string for conversion to string
	static void SetDefaultInputFormatString(CONST_PCHAR iFormatString); // Set default format string for conversion from string
};
//	...............................................................................................
