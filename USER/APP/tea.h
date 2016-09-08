/*********************************************************************
*						   TEA算法头文件
*						(c)copyright 2013,jdh
*						  All Right Reserved
*文件名:tea.h
*程序员:jdh
**********************************************************************/
/*********************************************************************
*说明:TEA加密解密算法
*TEA(Tiny Encryption Algorithm)是一种简单高效的加密算法，以加密解密速度快，
*实现简单著称。
*算法很简单，TEA算法每一次可以操作64-bit(8-byte)，采用128-bit(16-byte)作为key，
*算法采用迭代的形式，
*推荐的迭代轮数是64轮，最少32轮。
**********************************************************************/

#ifndef _TEA_H_
#define _TEA_H_

/*********************************************************************
*							头文件
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

