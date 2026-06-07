//rtc.h
#ifndef RTC_H

#define RTC_H
#include "types.h"
void RTC_Init(void);

void GetRTCTimeInfo(s32 *,s32 *,s32 *);

void DisplayRTCTime(u32,u32,u32);

void GetRTCDateInfo(s32 *,s32 *,s32 *);

void DisplayRTCDate(u32,u32,u32);
void SetRTCTimeInfo(u32,u32,u32);

void SetRTCDateInfo(u32,u32,u32);
void GetRTCDay(s32 *);

void DisplayRTCDay(u32);

void SetRTCDay(u32);
void SetRTCHour(u32);

void SetRTCMin(u32);

void SetRTCSec(u32);

void SetRTCDate(u32);

void SetRTCMonth(u32);

void SetRTCYear(u32);

void SetRTCDay(u32);
#endif

