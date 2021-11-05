#include "motor.h"

void motorInit(void)
{
	P_SW2 |= BIT7; // ʹ�ܷ���XSFR
	PWMCKS = 0x00; // ����PWM�������ʼ��ƽΪ�͵�ƽ
	PWMCFG = 0x00; // ѡ��PWMʱ�� 
	PWMC = CYCLE;  // ����PWM����

	ENA = 0;	   // ʹ�ܵ��
	ENB = 0;

	PWM5CR = 0;
	PWM5T1 = 0;				   // ����PWM5��һ�η�ת��PWM����
	PWM5T2 = CYCLE*50/100;	   // ����PWM5�ڶ��η�ת��PWM����

	PWM4CR = 0;
	PWM4T1 = 0;
	PWM4T2 = CYCLE*50/100;

	PWMCR = BIT3+BIT2;		   // PWM���ʹ��
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