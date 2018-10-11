#include <stdio.h>
#include "delay.h"
#include "common.h"
#include "timer.h"
#include "uart_manager.h"
#include "string.h"

int main(void)
{			
 	delay_init();	    	 // 延时函数初始化
	
	TIM3_Int_Init(99, 7199);     //10ms中断	
	USART1_Config(115200);		// GMS串口设置		
	USART2_Config(115200);		// DEBUG串口
	delay_ms(1000);
	
	LOGln("***** Warehouse monitoring system start *****");
	while(1)
	{

	}
}


/*********************************************END OF FILE**********************/

