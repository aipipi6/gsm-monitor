#include "tcp.h"
#include "gsm.h"
#include "uart_manager.h"

int connect_server(char *ip, int port)
{
	static char server_ip_port_cmd[48];
	int ret;
	ret = send_at_command("AT+CGATT=1\r\n", "OK", 3, 3000);//附着网络
	if(ret == FAILURE)
	{
		return AT_CGATT_ERROR;
	}
	
	ret = send_at_command("AT+CGACT=1,1\r\n", "OK", 3, 1000);//激活网络
	if(ret == FAILURE)
	{
		return AT_CGATT1_ERROR;
	}

	sprintf(server_ip_port_cmd, "AT+CIPSTART=\"TCP\",\"%s\", %d\r\n", ip, port);
	
	ret = send_at_command(server_ip_port_cmd, "CONNECT OK", 3, 1000);//连接服务器
	if(ret == FAILURE)
	{
		return AT_CIPSTART_ERROR;
	}
	return SUCCESS;
}


int tcp_send_msg_to_server(char *ip, int port, char *msg)
{
	int ret;
	
	ret = send_at_command("AT\r\n", "OK", 2, 100);
	if(ret != SUCCESS) {
		return ret;
	}
	
	ret = send_at_command("AT+CIPSTATUS\r\n", "CONNECT OK", 3, 200);//查询连接状态
	
	if(ret != SUCCESS) { //说明服务器处于连接状态
		ret = connect_server(ip, port);
		if(ret != SUCCESS) {
			return ret; 
		}
	} 

	ret = send_at_command("AT+CIPSEND\r\n", ">", 3, 200);//开发发送数据
	if(ret != SUCCESS)
	{
		return AT_CIPSEND_ERROR;
	}
	
	UART_SEND_STRING(msg);
	
	ret = send_at_command(AT_END_CHAR, "SEND OK", 1, 3000);//发送结束符，等待返回ok,等待5S发一次，因为发送数据时间可能较长
	if(ret != SUCCESS)
	{
		return END_CHAR_ERROR;
	}
	
	return SUCCESS;
	
}

