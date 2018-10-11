#ifndef __MSG_MANAGER_H__
#define __MSG_MANAGER_H__

#include "usart.h"
#include "common.h"


void clear_uart_buff(void);
char *get_uart_buff(u16 *len);
void UART_SendString(USART_TypeDef* USARTx, char *str);

#endif
