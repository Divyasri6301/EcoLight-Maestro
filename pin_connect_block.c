#include<LPC21xx.h>
void CfgPortPinFunc(unsigned int portno,unsigned int pinno,unsigned int pinfunc)
{
	if(portno==0)
	{
		if((portno==0)&& portno<=15)
		{
			PINSEL0=(PINSEL0 & ~(3 << (pinno*2)))|(pinfunc << (pinno*2));
		}
	}
	else if(portno==16  && portno<=31)
	{
		PINSEL1=(PINSEL1&~(3<<(pinno-16)*2))|(pinfunc<<((pinno-16)*2));
	}
}



		