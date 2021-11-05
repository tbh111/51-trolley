#ifndef _ULTRASOUND_H
#define _ULTRASOUND_H
#include <STC15.H>
#include <delay.h>

sbit SR_Trig = P1^5;
sbit SR_Echo = P1^4;


void radarInit(void);
unsigned int radarGetDistance(void);
#endif