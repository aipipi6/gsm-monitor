#include <stdio.h>
#include "delay.h"
#include "common.h"
#include "timer.h"
#include "uart_manager.h"
#include "string.h"
#include "gsm.h"
#include "tcp.h"
#include "dht11.h"

#define MONITOR_INFO_JSON		\
	"{"							\
		"\"temperature\":%d,"	\
		"\"humidity\":%d"		\
	"}"
char *get_test_msg()
{
	static char msg[128];
	int tem, hum;
	dht11_getInfo(&tem, &hum);
	sprintf(msg, MONITOR_INFO_JSON, tem, hum);
	
	return msg;
}


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

