// main.c

#include <LPC21xx.h>
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "adc_defines.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "adc.h"
#include "defines.h"

// ----------------- CONFIG -----------------
#define LEDS     (0x0F << 20)   // P0.20-P0.23 as LEDs
#define LDR_CH   2              // ADC channel connected to LDR
#define LDR_THRESHOLD 400       // ADC threshold for darkness
#define BUZZER   (1 << 25)      // Buzzer pin

// ----------------- GLOBALS -----------------
volatile unsigned char edit_mode = 0;   // Flag set by interrupt
unsigned int adcVal;
float ldrVolt;

// ----------------- FUNCTION DECLARATIONS -----------------
void Init_Peripherals(void);
void LED_Control(unsigned int hour, unsigned int min);
void Enter_Edit_Menu(void);
int GetNumberFromKeypad(int digits, int minVal, int maxVal);
void Beep(unsigned int ms);

// ----------------- BUZZER -----------------
void Beep(unsigned int ms)
{
    IOSET0 = BUZZER;
    delay_ms(ms);
    IOCLR0 = BUZZER;
}

// ----------------- EXT INTERRUPT ISR -----------------
__irq void EINT1_ISR(void)
{
        //EXT
    edit_mode = 1;   // Signal main loop to enter edit menu
    Beep(100);
               // Beep when switch pressed
    EXTINT = 1 << 1; // Clear EINT0 flag
    VICVectAddr = 0; // Acknowledge Interrupt
}

// ----------------- INIT PERIPHERALS -----------------
void Init_Peripherals(void)
{
    // LCD
    InitLCD();

    // RTC
    RTC_Init();

    // ADC
    Init_ADC();

    // KEYPAD
    Init_KPM();
        SetRTCTimeInfo(20, 50, 0);
        SetRTCDateInfo(24, 8, 2025);
        SetRTCDay(1);


    // LEDs + Buzzer
    IODIR0 |= LEDS | BUZZER;

    // External Interrupt 0 (for switch input)
    PINSEL0 &= ~(3 << 28);
        PINSEL0 |= (3<<28);   // as EINT1
    EXTMODE |= (1 << 1);     // Edge-sensitive
    EXTPOLAR &= ~(1 << 1); // Falling edge
    VICIntEnable |= (1 << 15);
    VICVectCntl0 = (1 << 5) | 15;
    VICVectAddr0 = (unsigned int)EINT1_ISR;
}

// ----------------- LED CONTROL -----------------
void LED_Control(unsigned int hour, unsigned int min)
{
    if ((hour >= 18 && hour <= 23) || (hour < 6))
    {
        // Between 6PM and 6AM → check LDR
        Read_ADC(LDR_CH, &adcVal, &ldrVolt);
        if (adcVal < LDR_THRESHOLD)
            IOSET0 = LEDS;  // Switch ON
        else
            IOCLR0 = LEDS;  // Switch OFF
    }
    else
    {
        IOCLR0 = LEDS; // Daytime → OFF
    }
}

// ----------------- INPUT FUNCTION -----------------
int GetNumberFromKeypad(int digits, int minVal, int maxVal)
{
    int val = 0, i;
    for (i = 0; i < digits; i++)
    {
        int key = keyScan();
        CharLCD(key + '0');
        val = val * 10 + key;
    }
    if (val < minVal || val > maxVal)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Input!");
        Beep(100); delay_ms(100); Beep(100); // 2 short beeps
        delay_ms(1000);
        return -1; // invalid
    }
    return val;
}

// ----------------- EDIT RTC MENU -----------------
void Enter_Edit_Menu(void)
{
    int choice = 0;
    while (1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("1. EDIT RTC");
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("2. EXIT");

        choice = keyScan();

        if (choice == 1) // EDIT RTC
        {
            int hr, min, sec, date, month, year, day;

            // Hour
            CmdLCD(CLEAR_LCD);
            StrLCD("Hour(0-23):");
            hr = GetNumberFromKeypad(2, 0, 23);
            if (hr < 0) continue;

            // Minute
            CmdLCD(CLEAR_LCD);
            StrLCD("Min(0-59):");
            min = GetNumberFromKeypad(2, 0, 59);
            if (min < 0) continue;

            // Second
            CmdLCD(CLEAR_LCD);
            StrLCD("Sec(0-59):");
            sec = GetNumberFromKeypad(2, 0, 59);
            if (sec < 0) continue;

            // Date
            CmdLCD(CLEAR_LCD);
            StrLCD("Date(1-31):");
            date = GetNumberFromKeypad(2, 1, 31);
            if (date < 0) continue;

            // Month
            CmdLCD(CLEAR_LCD);
            StrLCD("Month(1-12):");
            month = GetNumberFromKeypad(2, 1, 12);
            if (month < 0) continue;

            // Year
            CmdLCD(CLEAR_LCD);
            StrLCD("Year(2020-2099):");
            year = GetNumberFromKeypad(4, 2020, 2099);
            if (year < 0) continue;

            // Day of Week
            CmdLCD(CLEAR_LCD);
            StrLCD("Day(0-SUN..6-SAT):");
            day = GetNumberFromKeypad(1, 0, 6);
            if (day < 0) continue;

            // Set RTC
            SetRTCTimeInfo(hr, min, sec);
            SetRTCDateInfo(date, month, year);
            SetRTCDay(day);

            CmdLCD(CLEAR_LCD);
            StrLCD("RTC UPDATED!");
            Beep(300); // Long beep for success
            delay_ms(2000);
        }
        else if (choice == 2) // EXIT
        {
            CmdLCD(CLEAR_LCD);
            StrLCD("Exit Edit Mode");
            Beep(150);
            delay_ms(1000);
            break;
        }
    }
    edit_mode = 0; // Return to normal mode
}

// ----------------- MAIN -----------------
int main(void)
{
    s32 hour, min, sec, date, month, year, day;

    Init_Peripherals();

    CmdLCD(CLEAR_LCD);
    StrLCD("EcoLight Maestro");
    delay_ms(2000);

    while (1)
    {
        if (edit_mode)
        {
            Enter_Edit_Menu();
        }
        else
        {
            // Fetch time/date/day from RTC
            GetRTCTimeInfo(&hour, &min, &sec);
            GetRTCDateInfo(&date, &month, &year);
            GetRTCDay(&day);

            // Display time, date, day
            DisplayRTCTime(hour, min, sec);
            DisplayRTCDate(date, month, year);
            DisplayRTCDay(day);

            // Control LEDs based on time + LDR
            LED_Control(hour, min);

            delay_ms(500); // Refresh rate
        }
    }