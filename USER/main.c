/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ������3������ÿ���������һ��LED���Թ̶���Ƶ��������˸��Ƶ�ʿɵ�����         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.0.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "includes.h"

OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		  //����ջ
  
int main(void)
{
  	BSP_Init();
	OSInit();
	OSTaskCreate(Task_Start,(void *)0,
	   &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);

	OSStart();
    return 0;
 }

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
