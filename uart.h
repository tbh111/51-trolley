#ifndef _UART_H
#define _UART_H
#include <STC15.H>

void uartInit(void);
void uartStrTx(char* str);
void uartCharTx(unsigned char data1);
#endif
