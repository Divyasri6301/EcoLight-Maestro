//lcd.c

#include<LPC21xx.h>
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"
void WriteLCD(unsigned char anybyte)
{
IOCLR0=1<<LCD_RW;
WRITEBYTE(IOPIN0,LCD_DATA,anybyte);
IOSET0=1<<LCD_EN;
delay_us(1);
IOCLR0=1<<LCD_EN;
delay_ms(2);
}
void CmdLCD(unsigned char cmd)
{
IOCLR0=1<<LCD_RS;
WriteLCD(cmd);
}
void CharLCD(unsigned char asciival)
{
IOSET0=1<<LCD_RS;
WriteLCD(asciival);
}
void InitLCD(void)
{
IODIR0=(0xFF<<LCD_DATA)|1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
delay_ms(15);
CmdLCD(0X30);
delay_ms(4);
delay_us(100);
CmdLCD(0x30);
CmdLCD(MODE_8_BIT_2LINE);
CmdLCD(DSP_ON_CUR_BLINK);
CmdLCD(CLEAR_LCD);
CmdLCD(SHIFT_CUR_RIGHT);
CmdLCD(SHIFT_DISP_LEFT);
}
void StrLCD(char *p)
{
while(*p)
{
CharLCD(*p++);
}
}
void U32LCD(unsigned int num)
{
unsigned char a[10];
int i=0;
if(num==0)
{
CharLCD('0');
}
else
{
while(num>0)
{
a[i]=(num%10)+48;
i++;
num/=10;
}
for(--i;i>=0;i--)
{
CharLCD(a[i]);
}
}
}
void S32LCD(int snum)
{
if(snum<0)
{
CharLCD('-');
snum=-snum;
}
U32LCD(snum);
}
void F32LCD(float fNum,unsigned char nDP)
{
unsigned int num,i;
if(fNum<0.0)
{
CharLCD('-');
fNum=-fNum;
}
num=fNum;
U32LCD(num);
//CharLCD(num);
CharLCD('.');
for(i=0;i<nDP;i++)
{
fNum=(fNum-num)*10;
num=fNum;
CharLCD(num+48);
}
}
void BuildCGRAM(unsigned char *p,unsigned char nBytes)
{
unsigned int i;
CmdLCD(GOTO_CGRAM_START);
IOSET0=1<<LCD_RS;
for(i=0;i<nBytes;i++)
{
WriteLCD(p[i]);
}
CmdLCD(GOTO_LINE1_POS0);
}





