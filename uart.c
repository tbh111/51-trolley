#include <uart.h>

void uartInit(void)
{
	SCON=0x50;
	AUXR &=0xBF;
	AUXR &=0xFE;
	TMOD &=0x0F;
	TL1=0xE6;
	TH1=0xFF;
	ET1=0;
	TR1=1;
	REN=1;
	ES=1;	
}

void uartStrTx(char* str)
{
	unsigned int idx=0;
	while(*(str+idx)!='\0')
	{
		uartCharTx(*(str+idx));
		idx++;
  	}	
}

void uartCharTx(unsigned char data1)
{
	ES=0;
	SBUF = data1;
	TI = 0;
	while(!TI);
	ES=1;
}                                                                     