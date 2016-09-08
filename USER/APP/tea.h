/*********************************************************************
*						   TEA�㷨ͷ�ļ�
*						(c)copyright 2013,jdh
*						  All Right Reserved
*�ļ���:tea.h
*����Ա:jdh
**********************************************************************/
/*********************************************************************
*˵��:TEA���ܽ����㷨
*TEA(Tiny Encryption Algorithm)��һ�ּ򵥸�Ч�ļ����㷨���Լ��ܽ����ٶȿ죬
*ʵ�ּ����ơ�
*�㷨�ܼ򵥣�TEA�㷨ÿһ�ο��Բ���64-bit(8-byte)������128-bit(16-byte)��Ϊkey��
*�㷨���õ�������ʽ��
*�Ƽ��ĵ���������64�֣�����32�֡�
**********************************************************************/

#ifndef _TEA_H_
#define _TEA_H_

/*********************************************************************
*							ͷ�ļ�
**********************************************************************/

#include "stm32f10x.h"


#define UID_BASE 0x1ffff7e8
#ifdef STM32F10X_LD
	#define ENCRYPTADD 0x08001000
#endif
#ifdef STM32F10X_MD
	#define ENCRYPTADD 0x0801FC00
#endif
#ifdef STM32F10X_HD
	#define ENCRYPTADD 0x0807F800
#endif

extern void WriteEncrypt(void);
extern char JudgeEncrypt(void);
#endif

