#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//SPI���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
	
void SPI1_Config(void);			 //����SPI��
void SPI2_Config(void);			 //����SPI��

void SPI_SetSpeed(SPI_TypeDef* SPIx, u8 SPI_BaudRatePrescaler); //����SPI�ٶ� 
u8 SPI_ReadWriteByte(SPI_TypeDef* SPIx, u8 TxData);				//SPI���߶�дһ���ֽ�
		 
#endif

