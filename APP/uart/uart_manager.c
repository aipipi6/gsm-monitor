#include <string.h>
#include <stdio.h>
#include "usart.h"
#include "uart_manager.h"

#define UART1_Buff_SIZE  512
char   UART1_Buff[UART1_Buff_SIZE];
u16  UART1_BuffIndex = 0;

char *get_uart_buff(u16 *len)
{
	if(len != NULL) {
		*len = UART1_BuffIndex;
	}
	return UART1_Buff;
}

void clear_uart_buff()
{
	UART1_BuffIndex = 0;
	memset(UART1_Buff, 0, UART1_Buff_SIZE);
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	char data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{
		data =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据	
 		UART1_Buff[UART1_BuffIndex] = data;
		UART1_BuffIndex++;
		if(UART1_BuffIndex >= UART1_Buff_SIZE) {
			UART1_BuffIndex = 0;
		}
    } 
} 

void UART_SendString(USART_TypeDef* USARTx, char *str)
{
	while(*str)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET); 
		USART_SendData(USARTx, *str++);//发送当前字符
	}
}
