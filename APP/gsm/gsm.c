#include "gsm.h"
#include "uart_manager.h"

#define GSM_UART	USART1

extern u32 timer_10ms;

// 发送AT指令到串口
u8 send_at_command(char *cmd, char *check, u8 wait_times, u32 interval)
{
	u8 i;
	u32 delayTime;
	char *res;
	for(i = 0; i < wait_times; i++)
	{
		delayTime = timer_10ms + interval;
		clear_uart_buff();
		UART_SendString(GSM_UART, cmd);
		
		while(timer_10ms < delayTime) {
			res = get_uart_buff(NULL);
			if(strstr(res, check) != NULL) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

