#include <stdio.h>
#include "delay.h"
#include "common.h"
#include "timer.h"
#include "uart_manager.h"
#include "string.h"
#include "gsm.h"
#include "tcp.h"

char *get_test_msg()
{
	static char msg[128];
	static u32 count = 0;
	sprintf(msg, "test msg%d", count++);
	
	return msg;
}

#define MONITOR_INFO_JSON		\
	"{"							\
		"\"temperature\":%d,"	\
		"\"humidity\":%d"		\		
	"}"

int main(void)
{			
 	delay_init();	    	 // ��ʱ������ʼ��
	
	TIM3_Int_Init(99, 7199);     //10ms�ж�	
	USART1_Config(115200);		// GMS��������		
	USART2_Config(115200);		// DEBUG����
	delay_ms(1000);
	
	LOGln("***** Warehouse monitoring system start *****");
	
	while(1)
	{
		if(is_time5000ms()) {
			char *msg = get_test_msg();
			TCP_SEND_MSG(msg);
		}
	}
}


/*********************************************END OF FILE**********************/

