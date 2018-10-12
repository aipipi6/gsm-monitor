#ifndef __GSM_H__
#define __GSM_H__
#include "common.h"

#define AT_ACK_OK		0
#define AT_ACK_ERR		-1

#define COMMUNITE_ERROR       -1 
#define NO_SIM_CARD_ERROR     -2
#define SIM_CARD_NO_REG_ERROR -3
#define CALL_ERROR			  -4
#define AT_CPMS_ERROR		  -5
#define AT_CMGF_ERROR		  -6
#define AT_CSCS_ERROR		  -7
#define AT_CMGS_ERROR         -8
#define END_CHAR_ERROR		  -9
#define AT_CGATT_ERROR   	  -11
#define AT_CGACT_ERROR	      -12
#define AT_CIPSTART_ERROR	  -13
#define AT_CIPSEND_ERROR	  -14
#define AT_CIPMUX_ERROR       -15
#define AT_CIPQSEND_ERROR     -16
#define AT_CSTT_ERROR		  -17
#define AT_CIICR_ERROR		  -18
#define AT_CGATT1_ERROR       -50
#define EAT0_ERROR            -51

#define GSM_UART	USART1
#define UART_SEND_STRING(str) 	UART_SendString(GSM_UART, str);

int send_at_command(char *cmd, char *check, u8 wait_times, u32 interval);

extern char AT_END_CHAR[2];


#endif
