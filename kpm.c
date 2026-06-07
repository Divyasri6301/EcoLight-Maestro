//kpm.c

#include<lpc21xx.h>
#include "defines.h"
#include "kpm_defines.h"
unsigned int kpmLUT[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
void Init_KPM(void)
{
WRITENIBBLE(IODIR1,ROW0,15);
}
unsigned int ColScan(void)
{
unsigned int status;
status=(READNIBBLE(IOPIN1,COL0)<15)?0:1;
return status;
}
unsigned int RowCheck(void)
{
unsigned int r;
for(r=0;r<=3;r++)
{
WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
if(ColScan()==0)
{
break;
}
}
WRITENIBBLE(IOPIN1,ROW0,0);
return r;
}
unsigned int ColCheck(void)
{
unsigned int c;
for(c=0;c<=3;c++)
{
if(READBIT(IOPIN1,COL0+c)==0)
{
break;
}
}
return c;
}
unsigned int keyScan(void)
{
unsigned int r,c,key;
while(ColScan());
r=RowCheck();
c=ColCheck();
key=kpmLUT[r][c];
return key;
}


