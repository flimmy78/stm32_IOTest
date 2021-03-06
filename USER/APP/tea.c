/*********************************************************************
*						   TEA算法主文件
*						(c)copyright 2013,jdh
*						  All Right Reserved
*文件名:hash.c
*程序员:jdh
**********************************************************************/

/*********************************************************************
*							头文件
**********************************************************************/

#include "tea.h"

/*********************************************************************
*							函数
**********************************************************************/
uint8_t EncryptKey[17]="g12d3c4568a9bef7";
/*********************************************************************
*							tea加密
*参数:v:要加密的数据,长度为8字节
*     k:加密用的key,长度为16字节
**********************************************************************/

static void tea_encrypt(uint32_t *v,uint32_t *k) 
{
	uint32_t y = v[0],z = v[1],sum = 0,i;        
	uint32_t delta = 0x9e3779b9;                
	uint32_t a = k[0],b = k[1],c = k[2],d = k[3];  
	
	for (i = 0;i < 32;i++) 
	{                        
		sum += delta;
		y += ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
		z += ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
	}
	v[0] = y;
	v[1] = z;
}

/*********************************************************************
*							tea解密
*参数:v:要解密的数据,长度为8字节
*     k:解密用的key,长度为16字节
**********************************************************************/

static void tea_decrypt(uint32_t *v,uint32_t *k) 
{
	uint32_t y = v[0],z = v[1],sum = 0xC6EF3720,i; 
	uint32_t delta = 0x9e3779b9;            
	uint32_t a = k[0],b = k[1],c = k[2],d = k[3];    
	
	for (i = 0;i < 32;i++) 
	{                         
		z -= ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
		y -= ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
		sum -= delta;                     
	}
	v[0] = y;
	v[1] = z;
}

/*********************************************************************
*							加密算法
*参数:src:源数据,所占空间必须为8字节的倍数.加密完成后密文也存放在这
*     size_src:源数据大小,单位字节
*     key:密钥,16字节
*返回:密文的字节数
**********************************************************************/

uint16_t encrypt(uint8_t *src,uint16_t size_src,uint8_t *key)
{
	uint8_t a = 0;
	uint16_t i = 0;
	uint16_t num = 0;
	
	//将明文补足为8字节的倍数
	a = size_src % 8;
	if (a != 0)
	{
		for (i = 0;i < 8 - a;i++)
		{
			src[size_src++] = 0;
		}
	}
	
	//加密
	num = size_src / 8;
	for (i = 0;i < num;i++)
	{
		tea_encrypt((uint32_t *)(src + i * 8),(uint32_t *)key);
	}
	
	return size_src;
}

/*********************************************************************
*							解密算法
*参数:src:源数据,所占空间必须为8字节的倍数.解密完成后明文也存放在这
*     size_src:源数据大小,单位字节
*     key:密钥,16字节
*返回:明文的字节数,如果失败,返回0
**********************************************************************/

uint16_t decrypt(uint8_t *src,uint16_t size_src,uint8_t *key)
{
	uint16_t i = 0;
	uint16_t num = 0;
	
	//判断长度是否为8的倍数
	if (size_src % 8 != 0)
	{
		return 0;
	}
	
	//解密
	num = size_src / 8;
	for (i = 0;i < num;i++)
	{
		tea_decrypt((uint32_t *)(src + i * 8),(uint32_t *)key);
	}
	
	return size_src;
}

//加密
void WriteEncrypt(void)  
{   
//			int i;
			uint16_t size;
			uint32_t CpuID[4];         
			size=sizeof(CpuID);
			//CPUID  
			CpuID[0]=*(vu32*)(UID_BASE);  
			CpuID[1]=*(vu32*)(UID_BASE+4);  
			CpuID[2]=*(vu32*)(UID_BASE+8);          
			CpuID[3]=*(vu32*)(UID_BASE+8);
			//加密 
			encrypt((uint8_t *)CpuID,size,EncryptKey);

			FLASH_Unlock();  
			FLASH_ErasePage(ENCRYPTADD);
			//打乱存储数据
			FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);  
			FLASH_ProgramWord(ENCRYPTADD+0*4, CpuID[0]);  
			FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);  
			FLASH_ProgramWord(ENCRYPTADD+1*4, CpuID[2]);  
			FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);  
			FLASH_ProgramWord(ENCRYPTADD+2*4, CpuID[3]);  
			FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);  
			FLASH_ProgramWord(ENCRYPTADD+3*4, CpuID[1]);  
	
			FLASH_Lock();
}  
//解密
char JudgeEncrypt(void)  
{    
		int i;
		uint16_t size;
		uint32_t Code[4];
    uint32_t CpuID[4];         
		size=sizeof(CpuID);
    //CPUID  
    CpuID[0]=*(vu32*)(UID_BASE);  
    CpuID[1]=*(vu32*)(UID_BASE+4);  
    CpuID[2]=*(vu32*)(UID_BASE+8);      
    CpuID[3]=*(vu32*)(UID_BASE+8);  
		//读取保存的数据
		Code[0] =*(vu32*)(ENCRYPTADD);  
		Code[2] =*(vu32*)(ENCRYPTADD+4);  
 		Code[3] =*(vu32*)(ENCRYPTADD+8);  
		Code[1] =*(vu32*)(ENCRYPTADD+12); 
		//解密
		decrypt((uint8_t*)Code,size,EncryptKey);	
	
		for(i=0;i<4;i++)
		{
			if(CpuID[i]!=Code[i])
				return ERROR;
		}
		return SUCCESS;
}
