#include <radar.h>
			
unsigned char i = 0;
unsigned int len = 0;
void radarInit(void)
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = 0;
	TL0 = 0;
	ET0 = 0;
}

unsigned int radarGetDistance(void)
{
	SR_Trig = 1;
	Delay10us();
	SR_Trig = 0;
	while(!SR_Echo);
	TR0 = 1;
	while(SR_Echo);
	TR0 = 0;
	len = (TH0 <<8) + TL0;
	TH0 = 0;
	TL0 = 0;
	return len; 
}