//#include "sys.h"
//#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
//#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
//#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////

#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
u16 USART_TEST_DATA=0;         	//����Ĳ�������
u32 USART_TEST_ODRL=0;         	//����Ĳ�������
u32 USART_TEST_ODRH=0;         	//����Ĳ�������
u8  USART_TEST_CMD='0';         	//�˿�ѡ��
u8  PERIVAERAL_POWER=OFF;         	//��Χ��·��Դ����

void IOTest(u8 newcmd)
{
	if(newcmd==USART_TEST_CMD)
	{ 
		USART_TEST_DATA=USART_TEST_DATA<<1;
		switch(USART_TEST_DATA)
		{
		case 0x1:		USART_TEST_ODRH=0X00000000;USART_TEST_ODRL=0X3;	break;
		case 0x2:		USART_TEST_ODRH=0X00000000;USART_TEST_ODRL=0X30;	break;
		case 0x4:		USART_TEST_ODRH=0X00000000;USART_TEST_ODRL=0X300;	break;
		case 0x8:		USART_TEST_ODRH=0X00000000;USART_TEST_ODRL=0X3000;	break;
		case 0x10:		USART_TEST_ODRH=0X00000000;USART_TEST_ODRL=0X30000;	break;
		case 0x20:		USART_TEST_ODRH=0X00000000;USART_TEST_ODRL=0X300000;	break;
		case 0x40:		USART_TEST_ODRH=0X00000000;USART_TEST_ODRL=0X3000000;	break;
		case 0x80:		USART_TEST_ODRH=0X00000000;USART_TEST_ODRL=0X30000000;	break;

		case 0x100:		USART_TEST_ODRH=0X3;USART_TEST_ODRL=0X00000000;	break;
		case 0x200:		USART_TEST_ODRH=0X30;USART_TEST_ODRL=0X00000000;	break;
		case 0x400:		USART_TEST_ODRH=0X300;USART_TEST_ODRL=0X00000000;	break;
		case 0x800:		USART_TEST_ODRH=0X3000;USART_TEST_ODRL=0X00000000;	break;
		case 0x1000:	USART_TEST_ODRH=0X30000;USART_TEST_ODRL=0X00000000;	break;
		case 0x2000:	USART_TEST_ODRH=0X300000;USART_TEST_ODRL=0X00000000;	break;
		case 0x4000:	USART_TEST_ODRH=0X3000000;USART_TEST_ODRL=0X00000000;	break;
		case 0x8000:	USART_TEST_ODRH=0X30000000;USART_TEST_ODRL=0X00000000;	break;
		}
	}	
	else
	{
	   SetIOAsInput();
	   USART_TEST_CMD = newcmd;
	   USART_TEST_DATA= 0x0001;
	}

	switch(newcmd)
	{
	case  '0':    //'0'		//NO OPERATION
		SetIOAsInput();	
		break;
	case  '1':    //'1'
		RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��	   	 
		GPIOA->CRH=USART_TEST_ODRH;   	 
		GPIOA->CRL=USART_TEST_ODRL;  	 
	    GPIOA->ODR=USART_TEST_DATA;
		break;
	case  '2':    //'2'
		RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��	   	 
		GPIOB->CRH=USART_TEST_ODRH;   	 
		GPIOB->CRL=USART_TEST_ODRL;  	 
	    GPIOB->ODR=USART_TEST_DATA;
		break;
	case  '3':   //'3'
		RCC->APB2ENR|=1<<4;    //ʹ��PORTCʱ��	   	 
		GPIOC->CRH=USART_TEST_ODRH;   	 
		GPIOC->CRL=USART_TEST_ODRL;  	 
	    GPIOC->ODR=USART_TEST_DATA;
		break;
	case  '4':   //'4'
		RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	   	 
		GPIOD->CRH=USART_TEST_ODRH;   	 
		GPIOD->CRL=USART_TEST_ODRL;  	 
	    GPIOD->ODR=USART_TEST_DATA;
		break;
	case  '5':      //'5'
		RCC->APB2ENR|=1<<6;    //ʹ��PORTEʱ��	
		GPIOE->CRH=USART_TEST_ODRH;   	 
		GPIOE->CRL=USART_TEST_ODRL;  	 
	    GPIOE->ODR=USART_TEST_DATA;
		break;
	case  '6':      //'6'
		GPIOA->CRH=USART_TEST_ODRH;   	 
		GPIOA->CRL=USART_TEST_ODRL;  	 
	    GPIOA->ODR=~USART_TEST_DATA;
		break;
	case  '7':     //'7'
		GPIOB->CRH=USART_TEST_ODRH;   	 
		GPIOB->CRL=USART_TEST_ODRL;  	 
	    GPIOB->ODR=~USART_TEST_DATA;
		break;
	case  '8':   //'8'
		GPIOC->CRH=USART_TEST_ODRH;   	 
		GPIOC->CRL=USART_TEST_ODRL;  	 
	    GPIOC->ODR=~USART_TEST_DATA;
		break;
	case  '9':   //'9'
		GPIOD->CRH=USART_TEST_ODRH;   	 
		GPIOD->CRL=USART_TEST_ODRL;  	 
	    GPIOD->ODR=~USART_TEST_DATA;
		break;
	case  'a':      //'A'
		GPIOE->CRH=USART_TEST_ODRH;   	 
		GPIOE->CRL=USART_TEST_ODRL;  	 
	    GPIOE->ODR=~USART_TEST_DATA;
		break;
	default:
		USART_TEST_CMD = '0';	
		break;
	}

	printf("%c  %c  0x%x\r\n", newcmd,USART_TEST_CMD,USART_TEST_DATA);
	if(USART_TEST_DATA == 0x80000000)	USART_TEST_DATA=0x0001;	 
}

void SetIOAsInput(void)
{
	USART_TEST_DATA=0;	
	switch(USART_TEST_CMD)
	{
	case  '1':      //'1'		//PROGRAM FLASH
		GPIOA->CRH=USART_TEST_DATA;   	 
		GPIOA->CRL=USART_TEST_DATA;   	 
	    GPIOA->ODR=USART_TEST_DATA;
		break;
	case  '2':     //'2'		//ERASE SRAM
		GPIOB->CRH=USART_TEST_DATA;   	 
		GPIOB->CRL=USART_TEST_DATA;   	 
	    GPIOB->ODR=USART_TEST_DATA;
		break;
	case  '3':   //'3'		//RUN FLASH APP
		GPIOC->CRH=USART_TEST_DATA;   	 
		GPIOC->CRL|=USART_TEST_DATA;   	 
	    GPIOC->ODR=USART_TEST_DATA;
		break;
	case  '4':   //'4'		//RUN SRAM APP
		GPIOD->CRH=USART_TEST_DATA;   	 
		GPIOD->CRL=USART_TEST_DATA;   	 
	    GPIOD->ODR=USART_TEST_DATA;
		break;
	case  '5':      //'0'		//NO OPERATION
		GPIOE->CRH=USART_TEST_DATA;   	 
		GPIOE->CRL=USART_TEST_DATA;   	 
	    GPIOE->ODR=USART_TEST_DATA;
		break;
	default:
		break;
	}
}
  
void USART1_IRQHandler(void)
{
	u8 res;	
#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART1->SR&(1<<5))//���յ�����
	{	 
		res=USART1->DR; 
		//IOTest(res);
		RobotFuncTest(res);
		uart_showtittle();
	}
#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
	OSIntExit();  											 
#endif
} 
#endif										 
//��ʼ��IO ����1
//pclk2:PCLK2ʱ��Ƶ��(Mhz)
//bound:������
//CHECK OK
//091209
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬����
		  
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
#if EN_USART1_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж�
	USART1->CR1|=1<<8;    //PE�ж�ʹ��
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	//MY_NVIC_Init(3,3,USART1_IRQChannel,2);//��2��������ȼ� 
#endif
}

void uart_showtittle(void)
{
    printf("\r\nIO Test Main Menu!!!!!!!!!!:");
    printf("\r\n----TOGGLE POWER--------- 0");
    printf("\r\n----RED   LED ON--------- 1");
    printf("\r\n----GREEN LED ON--------- 2");
    printf("\r\n----ALL   LED ON--------- 3");
    printf("\r\n----ALL   LED OFF-------- 4");
    printf("\r\n----RIGHT BRUSH ON------- 5");
    printf("\r\n----RIGHT BRUSH OFF------ 6");
    printf("\r\n----LEFT  BRUSH ON------- 7");
    printf("\r\n----LEFT  BRUSH OFF------ 8");
    printf("\r\n----RIGHT WHEEL FORWARD-- 9");
    printf("\r\n----RIGHT WHEEL BACKWARD- A");
    printf("\r\n----RIGHT WHEEL OFF------ B");
    printf("\r\n----LEFT WHEEL FORWARD--- C");
    printf("\r\n----LEFT WHEEL BACKWARD-- D");
    printf("\r\n----LEFT WHEEL OFF------- E");
    printf("\r\n----FRONT PRESS --------- F");
    printf("\r\n----FRONT  SENSOR-------- G");
    printf("\r\n----BOTTOM SENSOR-------- H");
    printf("\r\n----TOP SENSOR----------- I");
    printf("\r\n----KEY------------------ J");
    printf("\r\n----BUZ ON--------------- K");
    printf("\r\n----BUZ OFF-------------- L");
    printf("\r\n----FAN ON--------------- M");
    printf("\r\n----FAN OFF-------------- N");
    printf("\r\n----CHARGE STATUS-------- O");
    printf("\r\n----RESIST STATUS-------- P");
    printf("\r\n\r\n");
}


void RobotFuncTest(u8 newcmd)
{
	switch(newcmd)
	{
	case  '0':    //----TOGGLE POWER--------- '0'
		PERIVERAL_POWER_CTRL(PERIVAERAL_POWER);
		break;
	case  '1':    //----RED   LED ON-------'1'
		LED_RED_CTRL(ON);
		break;
	case  '2':    //----GREEN LED ON-------'2'
		LED_GREEN_CTRL(ON);
		break;
	case  '3':    //----ALL   LED ON-------'3'
		LED_RED_CTRL(ON);
		LED_GREEN_CTRL(ON);
		break;
	case  '4':    //----ALL   LED OFF------'4'
		LED_RED_CTRL(OFF);
		LED_GREEN_CTRL(OFF);
		break;
	case  '5':    //----RIGHT BRUSH ON-----'5'
		Right_Brush_CTRL(ON);
		break;
	case  '6':    //----RIGHT BRUSH OFF----'6'
		Right_Brush_CTRL(OFF);
		break;
	case  '7':    //----LEFT  BRUSH ON-----'7'
		Left_Brush_CTRL(ON);
		break;
	case  '8':    //----LEFT  BRUSH OFF----'8'
		Left_Brush_CTRL(OFF);
		break;
	case  '9':    //----RIGHT WHEEL FORWARD-----'9'
		Right_Wheel_CTRL(FORWARD);
		break;
	case  'A':    //----RIGHT WHEEL BACKWARD----'A'
		Right_Wheel_CTRL(BACKWARD);
		break;
	case  'B':    //----RIGHT  WHEEL OFF--------'B'
		Right_Wheel_CTRL(OFF);
		break;
	case  'C':    //----LEFT WHEEL FORWARD------'C'
		Left_Wheel_CTRL(FORWARD);
		break;
	case  'D':    //----LEFT WHEEL BACKWARD-----'D'
		Left_Wheel_CTRL(BACKWARD);
		break;
	case  'E':    //----LEFT  WHEEL OFF---------'E'
		Left_Wheel_CTRL(OFF);
		break;
	case  'F':    //----FRONT PRESS -------'F'
		break;
	case  'G':    //----FRONT  SENSOR------'G'
		break;
	case  'H':    //----BOTTOM SENSOR------'H'
		break;
	case  'I':    //----TOP SENSOR---------'I'
		TOP_SENSOR_Input();
		break;
	case  'J':    //----KEY----------------'J'
		KEY_Input();
		break;
	case  'K':    //----BUZ ON---------------'K'
		BUZ_CTRL(ON);
		break;
	case  'L':    //----BUZ OFF--------------'L'
		BUZ_CTRL(OFF);
		break;
	case  'M':    //----FAN ON---------------'M'
		FAN_CTRL(ON);
		break;
	case  'N':    //----FAN OFF--------------'N'
		FAN_CTRL(OFF);
		break;
	case  'O':    //----CHARGE STATUS---------'O'
		printf("CHARGE status: %d", CHARGE_STATUS_Input());   	//PC.1);
		break;
	case  'P':    //----RESIST STATUS---------'P'
		RESIST_STATUS_Input();
		break;
	default:
		USART_TEST_CMD = '0';	
		break;
	}
}

void PERIVERAL_POWER_CTRL(u8 onoff)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��	   	 
	GPIOA->CRL&=0XF0FFFFFF; 
	GPIOA->CRL|=0X03000000; //PA.6 �������  �翪�� 
	if(onoff==OFF)
	{
	    GPIOA->ODR |= 1<<6;      //PA.6 �����
	    PERIVAERAL_POWER = ON;
	} 
	else if(onoff==ON)
	{
	    GPIOA->ODR &= ~(1<<6);      //PA.6 �����
	   PERIVAERAL_POWER = OFF;
	} 
	else
	{
	    GPIOA->ODR &= ~(1<<6);      //PA.6 �����
	   PERIVAERAL_POWER = OFF;
	} 
  printf("\r\nPERIVAERAL POWER--------- %s", (PERIVAERAL_POWER==ON)? "ON" :  "OFF");
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
	//GPIOA->CRL&=0XF0FFFFFF; 
	//GPIOA->CRL|=0X03000000; //PA.6 �������  �翪��   	 
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003; //PA.8 �������  �翪��   	 
	//GPIOA->CRH&=0XFFFF0FFF; 
	//GPIOA->CRH|=0X00003000; //PA.11 �������   	 
	GPIOC->CRH&=0XFFFFFFF0; 
	GPIOC->CRH|=0X00000003; //PC.8 �������   	 
	if(onoff==ON)
	{
	    //GPIOA->ODR |= 1<<11;      //PA.11 �����
	    //GPIOA->ODR |= 1<<6;      //PA.6 �����
	    GPIOA->ODR |= 1<<8;      //PA.8 �����
	    GPIOC->ODR |= 1<<8;      //PC.8 �����
	} 
	else if(onoff==OFF)
	{
	    //GPIOA->ODR &= ~(1<<11);      //PA.11 �����
	    //GPIOA->ODR &= ~(1<<6);      //PA.6 �����
	    GPIOA->ODR &= ~(1<<8);      //PA.8 �����
	    GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	} 
}

void Right_Wheel_CTRL(u8 onoff)
{
	//RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��	   	 
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��	   	 
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 
	//GPIOA->CRL&=0XF0FFFFFF; 
	//GPIOA->CRL|=0X03000000; //PA.6 �������  �翪��   	 
	GPIOB->CRL&=0XF0FFFFFF; 
	GPIOB->CRL|=0X03000000; //PB.6 �������   	 
	GPIOC->CRL&=0Xf0FFFFFF; 
	GPIOC->CRL|=0X03000000; //PC.6 7 8 9 �������   	 
	//GPIOC->CRH&=0XFFFFFF00; 
	//GPIOC->CRH|=0X00000033; //PC.6 7 8 9 �������   	 
	if(onoff==FORWARD)
	{
	    //GPIOA->ODR |= 1<<6;      //PA.6 �����
	    //GPIOB->ODR |= 1<<6;      //PB.6 �����
	    //GPIOC->ODR |= 1<<6;      //PC.6 �����
	    GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    GPIOC->ODR &= ~(1<<6);      //PC.6 �����
	    //GPIOC->ODR |= 1<<7;      //PC.7 �����
	    //GPIOC->ODR |= 1<<9;      //PC.9 �����
	} 
	else if(onoff==BACKWARD)
	{
	    //GPIOA->ODR |= 1<<6;      //PA.6 �����
	    GPIOB->ODR |= 1<<6;      //PB.6 �����
	    GPIOC->ODR &= ~(1<<6);      //PC.6 �����
	    //GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    //GPIOC->ODR &= ~(1<<6);      //PC.6 �����
	    //GPIOC->ODR |= 1<<7;      //PC.7 �����
	    //GPIOC->ODR |= 1<<9;      //PC.9 �����
	} 
	else if(onoff==OFF)
	{
	    //GPIOA->ODR &= ~(1<<6);      //PA.6 �����
	    GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    GPIOC->ODR &= ~(1<<6);      //PC.6 �����
	    //GPIOC->ODR &= ~(1<<7);      //PC.7 �����
	    //GPIOC->ODR &= ~(1<<9);      //PC.9 �����
	} 
}

void Left_Wheel_CTRL(u8 onoff)
{
	//RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��	   	 
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��	   	 
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 
	//GPIOA->CRL&=0XF0FFFFFF; 
	//GPIOA->CRL|=0X03000000; //PA.6 �������  �翪��   	 
	//GPIOA->CRH&=0XFFFFFFF0; 
	//GPIOA->CRH|=0X00000003; //PA.8 �������  �翪��   	 
	GPIOB->CRL&=0XF0FFFFFF; 
	GPIOB->CRL|=0X03000000; //PB.6 �������   	 
	//GPIOC->CRL&=0X00FFFFFF; 
	//GPIOC->CRL|=0X33000000; //PC.6 7 8 9 �������   	 
	GPIOC->CRH&=0XFFFFFFF0; 
	GPIOC->CRH|=0X00000003; //PC.8 �������   	 
	if(onoff==FORWARD)
	{
	    //GPIOA->ODR |= 1<<6;      //PA.6 �����
	    GPIOB->ODR |= 1<<6;      //PB.6 �����
	    GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	    //GPIOA->ODR |= 1<<8;      //PA.8 �����
	    //GPIOB->ODR |= 1<<6;      //PB.6 �����
	    //GPIOC->ODR |= 1<<8;      //PC.8 �����
	    //GPIOC->ODR |= 1<<7;      //PC.7 �����
	    //GPIOC->ODR |= 1<<9;      //PC.9 �����
	printf("LEFT WHEEL FORWARD");   	//PE1);
	} 
	else if(onoff==BACKWARD)
	{
	    //GPIOA->ODR |= 1<<6;      //PA.6 �����
	    GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	    //GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    //GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	    //GPIOC->ODR |= 1<<7;      //PC.7 �����
	    //GPIOC->ODR |= 1<<9;      //PC.9 �����
	printf("LEFT WHEEL BACKWARD");   	//PE1);
	} 
	else if(onoff==OFF)
	{
	    //GPIOA->ODR &= ~(1<<6);      //PA.6 �����
	    GPIOB->ODR &= ~(1<<6);      //PB.6 �����
	    GPIOC->ODR &= ~(1<<8);      //PC.8 �����
	    //GPIOC->ODR &= ~(1<<7);      //PC.7 �����
	    //GPIOC->ODR &= ~(1<<9);      //PC.9 �����
	printf("LEFT WHEEL OFF");   	//PE1);
	} 
}



void TOP_SENSOR_Input(void)
{
	RCC->APB2ENR|=1<<6;     //ʹ��PORTEʱ��
	GPIOE->CRL&=0XFFFFFFF0;	//PE0���ó����룬Ĭ������	  
	GPIOE->CRL|=0X00000008; 
	GPIOE->ODR|=1;	   	//PE0 ����
	printf("TOP SENSOR status: %ld", PEin(0));   	//PE0);
} 


void KEY_Input(void)
{
	RCC->APB2ENR|=1<<6;     //ʹ��PORTEʱ��
	GPIOE->CRL&=0XFFFFFF0F;	//PE1���ó����룬Ĭ������	  
	GPIOE->CRL|=0X00000080; 
	GPIOE->ODR|=2;	   	//PE1 ����
	  
	//GPIOE->CRL&=0XFFF000FF;	//PE2~4���ó�����	  
	//GPIOE->CRL|=0X00088800; 				   
	//GPIOE->ODR|=7<<2;	   	//PE2~4 ����
	printf("key status: %ld", PEin(1));   	//PE1);
} 

u8 CHARGE_STATUS_Input(void)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��	   	 
	GPIOC->CRL&=0XFFFFFF0F; 
	GPIOC->CRL|=0X00000080; //PC.1 ���ó����룬Ĭ������   	 
	GPIOC->ODR|=2;	   	//PC.1 ����
	return 	PCin(1);
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

	printf("RESIST STATUS: \r\n");   	//PE1);
	printf("PTA: 0(%ld) 2(%ld) 3(%ld) 4(%ld) 5(%ld) 7(%ld)\r\n", 
		PAin(0), PAin(2), PAin(3), PAin(4), PAin(5), PAin(7)); 
	printf("PTB: 1(%ld) 5(%ld) 13(%ld)\r\n", 
		PBin(1), PBin(5), PBin(13)); 
	printf("PTC: 4(%ld)\r\n", 
		PCin(4)); 
	printf("PTD: 1(%ld) 2(%ld) 3(%ld) 10(%ld) 12(%ld) 13(%ld) 14(%ld)\r\n", 
		PDin(1), PDin(2), PDin(3), PDin(10), PDin(12), PDin(13), PDin(14)); 
	printf("PTE: 0(%ld)\r\n", 
		PEin(0)); 
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
