/*********************************************************************
*						   TEA�㷨���ļ�
*						(c)copyright 2013,jdh
*						  All Right Reserved
*�ļ���:hash.c
*����Ա:jdh
**********************************************************************/

/*********************************************************************
*							ͷ�ļ�
**********************************************************************/

#include "tea.h"

/*********************************************************************
*							����
**********************************************************************/
uint8_t EncryptKey[17]="g12d3c4568a9bef7";
/*********************************************************************
*							tea����
*����:v:Ҫ���ܵ�����,����Ϊ8�ֽ�
*     k:�����õ�key,����Ϊ16�ֽ�
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
*							tea����
*����:v:Ҫ���ܵ�����,����Ϊ8�ֽ�
*     k:�����õ�key,����Ϊ16�ֽ�
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
*							�����㷨
*����:src:Դ����,��ռ�ռ����Ϊ8�ֽڵı���.������ɺ�����Ҳ�������
*     size_src:Դ���ݴ�С,��λ�ֽ�
*     key:��Կ,16�ֽ�
*����:���ĵ��ֽ���
**********************************************************************/

uint16_t encrypt(uint8_t *src,uint16_t size_src,uint8_t *key)
{
	uint8_t a = 0;
	uint16_t i = 0;
	uint16_t num = 0;
	
	//�����Ĳ���Ϊ8�ֽڵı���
	a = size_src % 8;
	if (a != 0)
	{
		for (i = 0;i < 8 - a;i++)
		{
			src[size_src++] = 0;
		}
	}
	
	//����
	num = size_src / 8;
	for (i = 0;i < num;i++)
	{
		tea_encrypt((uint32_t *)(src + i * 8),(uint32_t *)key);
	}
	
	return size_src;
}

/*********************************************************************
*							�����㷨
*����:src:Դ����,��ռ�ռ����Ϊ8�ֽڵı���.������ɺ�����Ҳ�������
*     size_src:Դ���ݴ�С,��λ�ֽ�
*     key:��Կ,16�ֽ�
*����:���ĵ��ֽ���,���ʧ��,����0
**********************************************************************/

uint16_t decrypt(uint8_t *src,uint16_t size_src,uint8_t *key)
{
	uint16_t i = 0;
	uint16_t num = 0;
	
	//�жϳ����Ƿ�Ϊ8�ı���
	if (size_src % 8 != 0)
	{
		return 0;
	}
	
	//����
	num = size_src / 8;
	for (i = 0;i < num;i++)
	{
		tea_decrypt((uint32_t *)(src + i * 8),(uint32_t *)key);
	}
	
	return size_src;
}

//����
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
			//���� 
			encrypt((uint8_t *)CpuID,size,EncryptKey);

			FLASH_Unlock();  
			FLASH_ErasePage(ENCRYPTADD);
			//���Ҵ洢����
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
//����
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
		//��ȡ���������
		Code[0] =*(vu32*)(ENCRYPTADD);  
		Code[2] =*(vu32*)(ENCRYPTADD+4);  
 		Code[3] =*(vu32*)(ENCRYPTADD+8);  
		Code[1] =*(vu32*)(ENCRYPTADD+12); 
		//����
		decrypt((uint8_t*)Code,size,EncryptKey);	
	
		for(i=0;i<4;i++)
		{
			if(CpuID[i]!=Code[i])
				return ERROR;
		}
		return SUCCESS;
}
