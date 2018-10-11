#include "gsm.h"
#include "uart_manager.h"

#define GSM_UART	USART1

extern u32 timer_10ms;

#define AT_LOG_SWITCH		1

/**
 *	���ܣ�	����ATָ�����
 *	������	cmd			ATָ��
 *			check		��ⷵ��ֵ�Ƿ�check�ַ���
 *			wait_times 	��ʱ����෢�ʹ���
 *			interval	�ȴ��������ʱ�䣬��λms
 */
u8 send_at_command(char *cmd, char *check, u8 wait_times, u32 interval)
{
	u8 i;
	u32 delayTime;
	char *res;
	for(i = 0; i < wait_times; i++)
	{
		delayTime = timer_10ms + interval / 10;
		clear_uart_buff();
		UART_SendString(GSM_UART, cmd);
		UART_SendString(GSM_UART, "\r\n");
	#if AT_LOG_SWITCH
		LOGln("[send]\r\n%s", cmd);
	#endif
		while(timer_10ms < delayTime) {
			res = get_uart_buff(NULL);
			if(strstr(res, check) != NULL) {
	#if AT_LOG_SWITCH
		LOGln("[recv]\r\n%s", res);
	#endif
				return TRUE;
			}
		}
	}
	#if AT_LOG_SWITCH
		LOGln("send error");
	#endif
	return FALSE;
}

