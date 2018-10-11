#include <stdarg.h>	 	 	 	 
#include <string.h>	
#include <stdio.h>
#include "sys.h"
#include "usart.h"	  
 

uint8_t USART_TX_BUF[1024];

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{      
//	while((USART3->SR & 0x40) == 0){}//ѭ������,ֱ���������   
//    USART3->DR = (u8) ch;      
//	return ch;
//}
int fputc(int ch, FILE *f)
{      
	while((USART2->SR & 0x40) == 0){}//ѭ������,ֱ���������   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 



/******************************************************************************
******
*��������USART_bound()
������
*���ܣ����� ���ڲ�����
*������
*����ֵ��
*******************************************************************************
******/ 
void USART_bound(USART_TypeDef* USARTx, u32 bound)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

	USART_Init(USARTx, &USART_InitStructure); ; //��ʼ������
}
/******************************************************************************
******
*��������USART1_Config()
������
*���ܣ����� ����1
*������
*����ֵ��
*******************************************************************************
******/  
void USART1_Config(u32 bound)
{  
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	
#if EN_USART1_RX   //���ʹ���˽���
	NVIC_InitTypeDef NVIC_InitStructure;
#endif
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
//ʹ��USART1��GPIOAʱ��

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
	//USART ��ʼ������

#if EN_USART1_RX   //���ʹ���˽���
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ�ܴ���1�����ж� 
#endif

	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1	
	
	USART_bound(USART1, bound);
}
/******************************************************************************
******
*��������USART2_Config()
������
*���ܣ����� ����2
*������
*����ֵ��
*******************************************************************************
******/
void USART2_Config(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
#if EN_USART2_RX   //���ʹ���˽���
	NVIC_InitTypeDef NVIC_InitStructure;
#endif
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

#if EN_USART2_RX   //���ʹ���˽���
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ�ܴ���2�����ж� 
#endif
	
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
	
	USART_bound(USART2, bound);
}
/******************************************************************************
******
*��������USART2_Config()
������
*���ܣ����� ����2
*������
*����ֵ��
*******************************************************************************
******/
void USART3_Config(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	//USART3_TX   PB10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10

	//USART3_RX	  PB11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11 

	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
	
	USART_bound(USART3, bound);
}
/******************************************************************************
******
*��������USART_printf()
������
*���ܣ�����,printf ����
*������
*����ֵ��
*******************************************************************************
******/
void USART_printf(USART_TypeDef* USARTx, char* fmt,...)  
{  
	vu16 i; 
	vu16 length;
	va_list ap; 
	
	va_start(ap, fmt);
	vsprintf((char*)USART_TX_BUF, fmt, ap);
	va_end(ap);
	length = strlen((const char*)USART_TX_BUF);		//�˴η������ݵĳ���
	
	for (i = 0; i < length; i++)				//ѭ����������
	{
		USARTx->DR = USART_TX_BUF[i];
		while ((USARTx->SR & 0X40) == 0);//ѭ������,ֱ���������   
	} 
}
/******************************************************************************
******
*��������USART_Send()
������
*���ܣ�����,���ͺ���
*������
*����ֵ��
*******************************************************************************
******/
void USART_Send(USART_TypeDef* USARTx, uint8_t* buf, u16 length)  
{  
	u16 i;
	
	memcpy((uint8_t *)USART_TX_BUF, (const uint8_t *)buf, length);
	
	for (i = 0; i < length; i++)							//ѭ����������
	{
		USART_SendData(USARTx, (uint8_t) USART_TX_BUF[i]);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	} 
}
//----------------------------------------------END--------------------------
