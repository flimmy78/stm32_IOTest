/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：用3.5.0版本建的工程模板。         
 * 库版本  ：ST3.5.0
**********************************************************************************/
#include "stm32f10x.h"
#include "tea.h"


void Sys_Init(void);
void NVIC_Configuration(void);
void WriteEncrypt(void);
char JudgeEncrypt(void);
void GPIO_Configuration(void);
void ALL_IO_Trg(void);

/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
int main(void)
{
	Sys_Init();
  while(1)
	{
		ALL_IO_Trg();
	}
}
/* 
 * 函数名：Sys_Init
 * 描述  : 系统初始化函数
 * 输入  ：无
 * 输出  : 无
 */
void Sys_Init(void)
{
	NVIC_Configuration();
	GPIO_Configuration();
//	if(JudgeEncrypt()!=SUCCESS)
//	WriteEncrypt();
}
  

void NVIC_Configuration(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

}
void delay_ms(volatile uint32_t us)
{
	volatile u16 i=0;
	while(us--)
	{
		i=12000;
		while(i--);
	}
}
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		/* Enable GPIO_LED clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOG, &GPIO_InitStructure);

}
void ALL_IO_Trg(void)
{
	GPIO_Write(GPIOA,0xFFFF);
	GPIO_Write(GPIOB,0xFFFF);
	GPIO_Write(GPIOC,0xFFFF);
	GPIO_Write(GPIOD,0xFFFF);
	GPIO_Write(GPIOE,0xFFFF);
//	GPIO_Write(GPIOF,0xFFFF);
//	GPIO_Write(GPIOG,0xFFFF);
	delay_ms(100);
	
	GPIO_Write(GPIOA,0x0);
	GPIO_Write(GPIOB,0x0);
	GPIO_Write(GPIOC,0x0);
	GPIO_Write(GPIOD,0x0);
	GPIO_Write(GPIOE,0x0);
//	GPIO_Write(GPIOF,0x0);
//	GPIO_Write(GPIOG,0x0);
	delay_ms(1000);
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/


