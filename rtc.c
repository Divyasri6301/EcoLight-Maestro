#include <LPC21xx.H>
#include "rtc_defines.h"

#include "types.h"

#include "lcd.h"

#include "lcd_defines.h"
// Array to hold names of days of the week^M

char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

/*^M

Initialize the Real-Time Clock (RTC)^M

This function disables the RTC, sets the prescaler values, ^M

and then enables the RTC.^M

*/

void RTC_Init(void) 

{

  // Disable and reset the RTC^M

        CCR = RTC_RESET;
#if (CPU == LPC2129) 

  // Set prescaler integer and fractional parts^M

        PREINT = PREINT_VAL;

        PREFRAC = PREFRAC_VAL;

        CCR = RTC_ENABLE; 

#elif(CPU == LPC2148)

  // Enable the RTC^M

        CCR = RTC_ENABLE | RTC_CLKSRC;  

#endif

}
/*^M

Get the current RTC time^M

hour Pointer to store the current hour^M

minute Pointer to store the current minute^M

second Pointer to store the current second^M

*/

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)

{

        *hour = HOUR;

        *minute = MIN;

        *second = SEC;

}
/*^M

Display the RTC time on LCD^M

hour value (0 23)^M

minute value (0 59)^M

second value (0 59) seperated by ':'^M

*/

void DisplayRTCTime(u32 hour, u32 minute, u32 second)

{

        CmdLCD(GOTO_LINE1_POS0);

        CharLCD((hour/10)+48);

        CharLCD((hour%10)+48);

        CharLCD(':');

        CharLCD((minute/10)+48);

        CharLCD((minute%10)+48);

        CharLCD(':');

        CharLCD((second/10)+48);

        CharLCD((second%10)+48);

}
/*^M

Get the current RTC date^M

day Pointer to store the current date (1 31)^M

month Pointer to store the current month (1 12)^M

year Pointer to store the current year (four digits)^M

*/

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)

{

        *date = DOM;

        *month = MONTH;

        *year = YEAR;

}
/*^M

Display the RTC date on LCD^M

Day of month (1 31)^M

Month (1 12)^M

Year (four digits) and seperated by '/'^M

*/

void DisplayRTCDate(u32 date, u32 month, u32 year)

{

        CmdLCD(GOTO_LINE2_POS0);

        CharLCD((date/10)+48);

        CharLCD((date%10)+48);

        CharLCD('/');

        CharLCD((month/10)+48);

        CharLCD((month%10)+48);

        CharLCD('/');

        U32LCD(year);

}
/*^M

Set the RTC time^M

Hour to set (0 23)^M

Minute to set (0 59)^M

Second to set (0 59)^M

*/

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)

{

        HOUR = hour;

        MIN = minute;

        SEC = second;

}
/*^M

Set the RTC date^M

day of month to set (1 31)^M

month to set (1 12)^M

year to set (four digits)^M

*/

void SetRTCDateInfo(u32 date, u32 month, u32 year)

{

        DOM = date;

        MONTH = month;

        YEAR = year;

}
/*^M

Get the current day of the week^M

dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)^M

*/

void GetRTCDay(s32 *day)

{

        *day = DOW;

}
/*^M

Display the current day of the week on LCD^M

dow (Day of Week) (0=Sunday, ..., 6=Saturday)^M

*/^M

void DisplayRTCDay(u32 day)^M

{^M

        CmdLCD(GOTO_LINE1_POS0+10);^M

        StrLCD(week[day]);^M

  ^M

}^M
^M
^M
/*^M

Set the day of the week in RTC^M

Day of Week to set (0=Sunday, ..., 6=Saturday)^M

*/^M

void SetRTCDay(u32 day)^M

{^M

        DOW = day;^M

}
#include <LPC21xx.H>^M
^M
^M
#include "rtc_defines.h"^M

#include "types.h"^M

#include "lcd.h"^M

#include "lcd_defines.h"^M
^M
^M
// Array to hold names of days of the week^M

char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};^M
^M
^M
^M

/*^M

Initialize the Real-Time Clock (RTC)^M

This function disables the RTC, sets the prescaler values, ^M

and then enables the RTC.^M

*/^M

void RTC_Init(void) ^M

{^M

  // Disable and reset the RTC^M

        CCR = RTC_RESET;^M
^M
^M
#if (CPU == LPC2129)    ^M

  // Set prescaler integer and fractional parts^M

        PREINT = PREINT_VAL;^M

        PREFRAC = PREFRAC_VAL;^M

        CCR = RTC_ENABLE; ^M

#elif(CPU == LPC2148)^M

  // Enable the RTC^M

        CCR = RTC_ENABLE | RTC_CLKSRC;  ^M

#endif^M

}^M
^M
^M
/*^M

Get the current RTC time^M

hour Pointer to store the current hour^M

minute Pointer to store the current minute^M

second Pointer to store the current second^M

*/^M

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)^M

{^M

        *hour = HOUR;^M

        *minute = MIN;^M

        *second = SEC;^M

}^M
^M
^M
/*^M

Display the RTC time on LCD^M

hour value (0 23)^M

minute value (0 59)^M

second value (0 59) seperated by ':'^M

*/^M

void DisplayRTCTime(u32 hour, u32 minute, u32 second)^M

{^M

        CmdLCD(GOTO_LINE1_POS0);^M

        CharLCD((hour/10)+48);^M

        CharLCD((hour%10)+48);^M

        CharLCD(':');^M

        CharLCD((minute/10)+48);^M

        CharLCD((minute%10)+48);^M

        CharLCD(':');^M

        CharLCD((second/10)+48);^M

        CharLCD((second%10)+48);^M

}^M
^M
^M
/*^M

Get the current RTC date^M

day Pointer to store the current date (1 31)^M

month Pointer to store the current month (1 12)^M

year Pointer to store the current year (four digits)^M

*/^M

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)^M

{^M

        *date = DOM;^M

        *month = MONTH;^M

        *year = YEAR;^M

}^M
^M
^M
/*^M

Display the RTC date on LCD^M

Day of month (1 31)^M

Month (1 12)^M

Year (four digits) and seperated by '/'^M

*/^M

void DisplayRTCDate(u32 date, u32 month, u32 year)^M

{^M

        CmdLCD(GOTO_LINE2_POS0);^M

        CharLCD((date/10)+48);^M

        CharLCD((date%10)+48);^M

        CharLCD('/');^M

        CharLCD((month/10)+48);^M

        CharLCD((month%10)+48);^M

        CharLCD('/');^M

        U32LCD(year);^M

}^M
^M
^M
/*^M

Set the RTC time^M

Hour to set (0 23)^M

Minute to set (0 59)^M

Second to set (0 59)^M

*/^M

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)^M

{^M

        HOUR = hour;^M

        MIN = minute;^M

        SEC = second;^M

}^M
^M
^M
/*^M

Set the RTC date^M

day of month to set (1 31)^M

month to set (1 12)^M

year to set (four digits)^M

*/^M

void SetRTCDateInfo(u32 date, u32 month, u32 year)^M

{^M

        DOM = date;^M

        MONTH = month;^M

        YEAR = year;^M

}^M
^M
^M
/*^M

Get the current day of the week^M

dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)^M

*/^M

void GetRTCDay(s32 *day)^M

{^M

        *day = DOW;^M

}^M
^M
^M
/*^M

Display the current day of the week on LCD^M

dow (Day of Week) (0=Sunday, ..., 6=Saturday)^M

*/^M

void DisplayRTCDay(u32 day)^M

{^M

        CmdLCD(GOTO_LINE1_POS0+10);^M

        StrLCD(week[day]);^M

  ^M

}^M
^M
^M
/*^M

Set the day of the week in RTC^M

Day of Week to set (0=Sunday, ..., 6=Saturday)^M

*/^M

void SetRTCDay(u32 day)^M

{^M

        DOW = day;^M

}
