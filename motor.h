#ifndef _MOTOR_H
#define _MOTOR_H
#include <STC15.H>

sbit IN1 = P2^7;
sbit IN2 = P2^6;
sbit IN3 = P2^5;
sbit IN4 = P2^4;

sbit ENA = P2^3;
sbit ENB = P2^2;

#define PWM4 ENA
#define PWM5 ENB

#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)

#define CYCLE 0x7fff1
#define ENPWM 0x80

#define MOTOR_STOP() {IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 0;}
#define MOTOR_FORWARD() {IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 1;}
#define MOTOR_BACKWARD() {IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;}
#define MOTOR_TURNLEFT() {IN1 = 1; IN2 = 0; IN3 = 1; IN4 = 0;}
#define MOTOR_TURNRIGHT() {IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 1;}

void motorInit(void);
void motorSetLeftSpeed(unsigned char wide);
void motorSetRightSpeed(unsigned char wide);
void motorSetState(unsigned char state, unsigned char speed);
#endif
