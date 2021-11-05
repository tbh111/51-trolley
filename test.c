#include <STC15.H>
#include <motor.h>
#include <uart.h>
#include <delay.h>
#include <radar.h>
#include <math.h>
unsigned char bTemp;//串口接收到的数据
bit rx_flag=0;
int dis = 0;
int dis2 = 0;
int status = 0;
sbit alarm = P0^0;
unsigned char speed = 70;
//int counter = 0; 
unsigned char dis_buf[6];


void int2str(int distance, unsigned char *dis)
{
	if(distance > 0)
	{
		char num_10k = distance/10000+48; 
		char num_1k  = distance/1000%10+48;
		char num_100 = distance/100%10+48;
		char num_10  = distance/10%10+48;
		char num_1   = distance%10+48;
	
		*(dis)   = num_10k;
		*(dis+1) = num_1k;
		*(dis+2) = num_100;
		*(dis+3) = num_10;
		*(dis+4) = num_1;
		*(dis+5) = '\0';	
	}
	else
	{
		int i = 0;
		for(i; i<5; i++)
		{
			*(dis+i) = '0';
		}
		*(dis+5) = '\0';
	}
}



void main()
{
	// 设置P2.0-P2.7端口为准双向口输出
	P2M0 = 0x00;
	P2M1 = 0x00;
	motorInit();
	uartInit();
	radarInit();
	EA =1;
	alarm = 0;

	while(1)
	{


		dis = radarGetDistance();
		dis = dis*17;
		dis = dis/1000;
		Delay_Nms(200);
		dis2 = radarGetDistance();
		dis2 = dis2*17;
		dis2 = dis2/1000;
		if(status == 1){
			if(10 < dis && dis < 20)
			{		
				if(10 < dis2 && dis2 < 20)
				{
					int2str(dis, dis_buf);
					uartStrTx(dis_buf);
					uartStrTx(" cm\r\n");
					uartStrTx(" stop\r\n");
					speed = 70;
					speed = 70;
					motorSetState(0x00, speed);
					status = 0;
					alarm = 1;
	
				}
			}
		}
		//alarm = 0;	
		/*int2str(dis, dis_buf);
		uartStrTx("Dis: ");
		uartStrTx(dis_buf);
		uartStrTx(" cm\r\n");*/

		
		if(rx_flag)
		{
			rx_flag = 0;
			
			switch(bTemp){
			case'q'://停止
				uartStrTx("State:stop\r\n");
				speed = 50;
				motorSetState(0x00, speed);
				status = 0;
				alarm = 0;
			break;

			case'w'://前进
				uartStrTx("State:forward\r\n");
				speed = 50;
				motorSetState(0x01, speed);
				status = 1;
				alarm = 0;				  
			break;

			case's'://后退
				uartStrTx("State:backward\r\n");
				speed = 50;
				motorSetState(0x02, speed);
				status = 2;
				alarm = 0;
			break;

			case'a'://左转
				uartStrTx("State:left\r\n");
				speed = 50;
				motorSetState(0x03, speed);
				status = 3;
				alarm = 0;		
			break;

			case'd'://右转
				uartStrTx("State:right\r\n");
				speed = 50;
				motorSetState(0x04, speed);
				status = 4;
				alarm = 0;
			break;
			
			case'z':
				uartStrTx("State:accelerate\r\n");
				speed++;
				motorSetLeftSpeed(speed);
				motorSetRightSpeed(speed);
				uartCharTx(speed);
				uartCharTx(speed);
				uartStrTx("\r\n");
			break;

			case'x':
				//uartStrTx("State:decelerate\r\n");
				speed--;
				motorSetLeftSpeed(speed);
				motorSetRightSpeed(speed);
				uartCharTx(speed);
				uartCharTx(speed);
				//uartStrTx("\r\n");
			break;
				
				
			
			case'm'://发送距离信息
				int2str(dis, dis_buf);
				uartStrTx("Dis: ");
				uartStrTx(dis_buf);
				uartStrTx(" cm\r\n");
			break;
			default:break;
			}
		}
		//else
		//{
		//	uartStrTx("test\n");
		//}	

	}
}

//P40 中断源的中断号
void UART1_ISR(void) interrupt 4 
{
	
	/*串口接收*/
	if(RI)
	{
		RI=0;//清除中断标志
		bTemp=SBUF;//读出串口数据
		rx_flag=1;
    }
	if(TI)
	{
		TI=0;
    }
}                                                                                         