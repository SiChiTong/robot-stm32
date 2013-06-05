#include "io.h"
#include "sys.h"
#include "usart.h"

u8  PERIVAERAL_POWER=OFF;         	//��Χ��·��Դ����

void PERIVERAL_POWER_CTRL(u8 onoff)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��	   	 
	GPIOA->CRL&=0XF0FFFFFF; 
	GPIOA->CRL|=0X03000000; //PA.6 �������  �翪�� 
	if(onoff==ON)
	{
	    GPIOA->ODR |= 1<<6;      //PA.6 �����
	    PERIVAERAL_POWER = ON;
	} 
	else 
	{
	    GPIOA->ODR &= ~(1<<6);      //PA.6 �����
	   PERIVAERAL_POWER = OFF;
	} 
  //printf("\r\nPERIVAERAL POWER--------- %s", (PERIVAERAL_POWER==ON)? "ON" :  "OFF");
}

void LED_RED_CTRL(u8 onoff)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 
	GPIOC->CRH&=0XFFFFF0FF; 
	GPIOC->CRH|=0X00000300; //PC.10 �������   	 
	if(onoff==ON)
	{
	    GPIOC->ODR |= 1<<10;      //PC.10 �����
	} 
	else if(onoff==OFF)
	{
	    GPIOC->ODR &= ~(1<<10);      //PC.10 �����
	} 
}

void LED_GREEN_CTRL(u8 onoff)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 
	GPIOC->CRH&=0XFFFF0FFF; 
	GPIOC->CRH|=0X00003000; //PC.10 �������   	 
	if(onoff==ON)
	{
	    GPIOC->ODR |= 1<<11;      //PC.11 �����
	} 
	else if(onoff==OFF)
	{
	    GPIOC->ODR &= ~(1<<11);      //PC.11 �����
	} 
}

void Right_Brush_CTRL(u8 onoff)
{
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��	   	 
	GPIOB->CRH&=0XF0FFFFFF; 
	GPIOB->CRH|=0X03000000; //PB.14 �������   	 
	if(onoff==ON)
	{
	    GPIOB->ODR |= 1<<14;      //PB.14 �����
	} 
	else if(onoff==OFF)
	{
	    GPIOB->ODR &= ~(1<<14);      //PB.14 �����
	} 
}

void Left_Brush_CTRL(u8 onoff)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��	   	 
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003; //PA.8 �������  �翪��	 
	GPIOC->CRH&=0XFFFFFFF0; 
	GPIOC->CRH|=0X00000003; //PC.8 �������   	 
	if(onoff==ON)
	{
	    GPIOA->ODR |= 1<<8;      //PA.8 �����
	    GPIOC->ODR |= 1<<8;      //PC.8 �����
	} 
	else if(onoff==OFF)
	{
	    GPIOA->ODR &= ~(1<<8);      //PA.8 �����
	    GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	} 
}

void Right_Wheel_CTRL(u8 onoff)
{   	 
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��	   	 
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	 
	GPIOB->CRL&=0XF0FFFFFF; 
	GPIOB->CRL|=0X03000000; //PB.6 �������   	 
	GPIOC->CRL&=0Xf0FFFFFF; 
	GPIOC->CRL|=0X03000000; //PC.6 7 8 9 �������   	 
	if(onoff==FORWARD)
	{
	    GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    GPIOC->ODR &= ~(1<<6);      //PC.6 �����
	} 
	else if(onoff==BACKWARD)
	{
	    GPIOB->ODR |= 1<<6;      //PB.6 �����
	    GPIOC->ODR &= ~(1<<6);      //PC.6 �����
	} 
	else if(onoff==OFF)
	{
	    GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    GPIOC->ODR &= ~(1<<6);      //PC.6 �����
	} 
}

void Left_Wheel_CTRL(u8 onoff)
{   	 
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��	   	 
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 	 
	GPIOB->CRL&=0XF0FFFFFF; 
	GPIOB->CRL|=0X03000000; //PB.6 �������   	   	 
	GPIOC->CRH&=0XFFFFFFF0; 
	GPIOC->CRH|=0X00000003; //PC.8 �������   	 
	if(onoff==FORWARD)
	{
	    GPIOB->ODR |= 1<<6;      //PB.6 �����
	    GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	//printf("LEFT WHEEL FORWARD");   	//PE1);
	} 
	else if(onoff==BACKWARD)
	{
	    GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	//printf("LEFT WHEEL BACKWARD");   	//PE1);
	} 
	else if(onoff==OFF)
	{
	    GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	//printf("LEFT WHEEL OFF");   	//PE1);
	} 
}



u8 TOP_SENSOR_Input(void)
{
	RCC->APB2ENR|=1<<6;     //ʹ��PORTEʱ��
	GPIOE->CRL&=0XFFFFFFF0;	//PE0���ó����룬Ĭ������	  
	GPIOE->CRL|=0X00000008; 
	GPIOE->ODR|=1;	   	//PE0 ����
	//printf("TOP SENSOR status: %ld", PEin(0));   	//PE0);
	return PEin(0);
} 


u8 KEY_Input(void)
{
	RCC->APB2ENR|=1<<6;     //ʹ��PORTEʱ��
	GPIOE->CRL&=0XFFFFFF0F;	//PE1���ó����룬Ĭ������	  
	GPIOE->CRL|=0X00000080; 
	GPIOE->ODR|=2;	   	//PE1 ����
	//printf("key status: %ld", PEin(1));   	//PE1);
	return PEin(1);
} 

u8 SENSORS_Top1(void)
{
    //�����ĳ��Ѱ·����Ĺ������
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	GPIOD->CRH&=0XFFF0FFFF;	//PD12���ó����룬Ĭ������	  
	GPIOD->CRH|=0X00080000; 
	//GPIOD->ODR|=2;	   	//PE1 ����
	//printf("key status: %ld", PDin(12));   	//PE1);
	return PDin(12);
}

u8 SENSORS_Top2(void)
{
    //��ǰ����ĳ��Ѱ·����Ĺ������
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	GPIOD->CRH&=0XFF0FFFFF;	//PD13���ó����룬Ĭ������	  
	GPIOD->CRH|=0X00800000; 
	//GPIOD->ODR|=2;	   	//PE1 ����
	//printf("key status: %ld", PDin(13));   	//PE1);
	return PDin(13);
}

u8 SENSORS_Top3(void)
{
    //��ǰ����ĳ��Ѱ·����Ĺ������
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	GPIOD->CRH&=0XF0FFFFFF;	//PD14���ó����룬Ĭ������	  
	GPIOD->CRH|=0X08000000; 
	//GPIOD->ODR|=2;	   	//PE1 ����
	//printf("key status: %ld", PDin(14));   	//PE1);
	return PDin(14);
}

u8 LEFT_WHEEL_SENSORS(void)
{
    //��������ź�����
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	GPIOD->CRL&=0XFFFFF0FF;	//PD2���ó����룬Ĭ������	  
	GPIOD->CRL|=0X00000800; 
	//GPIOD->ODR|=2;	   	//PE1 ����
	//printf("key status: %ld", PDin(14));   	//PE1);
	return PDin(2);
}

u8 LEFT_WHEEL_DOWN(void)
{
    //��������ź�����
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	GPIOD->CRL&=0XFFFFFF0F;	//PD1���ó����룬Ĭ������	  
	GPIOD->CRL|=0X00000080; 
	//GPIOD->ODR|=2;	   	//PE1 ����
	//printf("key status: %ld", PDin(14));   	//PE1);
	return PDin(1);
}
u8 RIGHT_WHEEL_SENSORS(void)
{
    //��������ź�����
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	GPIOD->CRL&=0XFFFF0FFF;	//PD3���ó����룬Ĭ������	  
	GPIOD->CRL|=0X00008000; 
	//GPIOD->ODR|=2;	   	//PE1 ����
	//printf("key status: %ld", PDin(14));   	//PE1);
	return PDin(3);
}
u8 RIGHT_WHEEL_DOWN(void)
{
    //��������ź�����
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	GPIOD->CRH&=0XFFFFF0FF;	//PD10���ó����룬Ĭ������	  
	GPIOD->CRH|=0X00000800; 
	//GPIOD->ODR|=2;	   	//PE1 ����
	//printf("key status: %ld", PDin(14));   	//PE1);
	return PDin(10);
}

u8 CHARGE_STATUS_Input(void)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 
	GPIOC->CRL&=0XFFFFFF0F; 
	GPIOC->CRL|=0X00000080; //PC.1 ���ó����룬Ĭ������   	 
	GPIOC->ODR|=2;	   	//PC.1 ����
	return PCin(1);
} 

void RESIST_STATUS_Input(void)
{
	//PA  0 2 3 4 5 7 
	//PB  1 5 13
	//PC  4
	//PD 1 2 3 10 12 13 14
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��	   	 
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��	   	 
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	RCC->APB2ENR|=1<<6;     //ʹ��PORTEʱ��

	GPIOA->CRL&=0X0F0000F0; 
	GPIOA->CRL|=0X80888808;    	 
	//GPIOA->ODR|=0X43;	   	//����

	GPIOB->CRL&=0XFF0FFFF0; 
	GPIOB->CRL|=0X00800008;    	 
	GPIOB->CRH&=0XFF0FFFFF; 
	GPIOB->CRH|=0X00800000;    	 
		   	 
	GPIOC->CRL&=0XFFF0FFFF; 
	GPIOC->CRL|=0X00080000; //PC.4 ���ó����룬Ĭ������   	 
	GPIOC->ODR|=0X10;	   	//PC.4 ����

	GPIOD->CRL&=0XFFFFF000; 
	GPIOD->CRL|=0X00000888;    	 
	GPIOD->CRH&=0XF000F0FF; 
	GPIOD->CRH|=0X08880800; 
	 
	GPIOE->CRL&=0XFFFFFFF0;	//PE0���ó����룬Ĭ������	  
	GPIOE->CRL|=0X00000008; 
	GPIOE->ODR|=1;	   	//PE0 ����

	/*printf("RESIST STATUS: \r\n");   	//PE1);
	printf("PTA: 0(%ld) 2(%ld) 3(%ld) 4(%ld) 5(%ld) 7(%ld)\r\n", 
		PAin(0), PAin(2), PAin(3), PAin(4), PAin(5), PAin(7)); 
	printf("PTB: 1(%ld) 5(%ld) 13(%ld)\r\n", 
		PBin(1), PBin(5), PBin(13)); 
	printf("PTC: 4(%ld)\r\n", 
		PCin(4)); 
	printf("PTD: 1(%ld) 2(%ld) 3(%ld) 10(%ld) 12(%ld) 13(%ld) 14(%ld)\r\n", 
		PDin(1), PDin(2), PDin(3), PDin(10), PDin(12), PDin(13), PDin(14)); 
	printf("PTE: 0(%ld)\r\n", 
		PEin(0)); */
} 

void BUZ_CTRL(u8 onoff)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��	   	 
	//GPIOA->CRL&=0XF0FFFFFF; 
	//GPIOA->CRL|=0X03000000; //PA.6 �������  �翪��   	 
	GPIOA->CRH&=0XFFFF0FFF; 
	GPIOA->CRH|=0X00003000; //PA.11 �������   	 
	if(onoff==ON)
	{
	    //GPIOA->ODR |= 1<<6;      //PA.6 �����
	    GPIOA->ODR |= 1<<11;      //PA.11 �����
	} 
	else if(onoff==OFF)
	{
	    //GPIOA->ODR &= ~(1<<6);      //PA.6 �����
	    GPIOA->ODR &= ~(1<<11);      //PA.11 �����
	} 
}

void FAN_CTRL(u8 onoff)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 
	//GPIOA->CRL&=0XF0FFFFFF; 
	//GPIOA->CRL|=0X03000000; //PA.6 �������  �翪��   	 
	GPIOC->CRH&=0XFFFFFF0F; 
	GPIOC->CRH|=0X00000030; //PC.9 �������   	 
	if(onoff==ON)
	{
	    //GPIOA->ODR |= 1<<6;      //PA.6 �����
	    GPIOC->ODR |= 1<<9;      //PC.9 �����
	} 
	else if(onoff==OFF)
	{
	    //GPIOA->ODR &= ~(1<<6);      //PA.6 �����
	    GPIOC->ODR &= ~(1<<9);      //PC.9 �����
	} 
}


