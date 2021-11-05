#include "motor.h"

void motorInit(void)
{
	P_SW2 |= BIT7; // 使能访问XSFR
	PWMCKS = 0x00; // 配置PWM的输出初始电平为低电平
	PWMCFG = 0x00; // 选择PWM时钟 
	PWMC = CYCLE;  // 设置PWM周期

	ENA = 0;	   // 使能电机
	ENB = 0;

	PWM5CR = 0;
	PWM5T1 = 0;				   // 设置PWM5第一次反转的PWM计数
	PWM5T2 = CYCLE*50/100;	   // 设置PWM5第二次反转的PWM计数

	PWM4CR = 0;
	PWM4T1 = 0;
	PWM4T2 = CYCLE*50/100;

	PWMCR = BIT3+BIT2;		   // PWM输出使能
	PWMCR |= ENPWM;
	P_SW2 &= ~BIT7;

	motorSetState(0x00,0);
	//motorSetLeftSpeed(1);
	//motorSetRightSpeed(1);
}

void motorSetLeftSpeed(unsigned char wide)
{
	if(wide)
	{
		P_SW2 |= BIT7;
		PWM4T2 = (unsigned int)(CYCLE/(100.0/wide));
		P_SW2 &= ~BIT7;
		PWMCR |= BIT2;
	}
	else
	{
		PWMCR &= ~BIT2;
		ENA = 1;
	}
}

void motorSetRightSpeed(unsigned char wide)
{		
	if(wide)
	{
		P_SW2 |= BIT7;
		PWM5T2 = (unsigned int)(CYCLE/(100.0/wide));
		P_SW2 &= ~BIT7;
		PWMCR |= BIT3;
	}
	else
	{
		PWMCR &= ~BIT3;
		ENB = 1;
	}
}

void motorSetState(unsigned char state, unsigned char speed)
{
	motorSetLeftSpeed(speed);
	motorSetRightSpeed(speed);
	switch(state)
	{
		case 0x00:
			MOTOR_STOP();
		break;

		case 0x01:
			MOTOR_FORWARD();
		break;

		case 0x02:
			MOTOR_BACKWARD();
		break;

		case 0x03:
			MOTOR_TURNLEFT();
		break;

		case 0x04:
			MOTOR_TURNRIGHT();

		break;
		default: break;	
	}
}