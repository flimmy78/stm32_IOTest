/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
**********************************************************************************/
#include "led.h"

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOC, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);	 // turn off all led
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
