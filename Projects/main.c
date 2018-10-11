#include <stdio.h>
#include "delay.h"
#include "common.h"
#include "timer.h"
#include "uart_manager.h"
#include "string.h"

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

	}
}


/*********************************************END OF FILE**********************/

