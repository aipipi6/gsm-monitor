#include "tcp.h"
#include "gsm.h"
#include "uart_manager.h"

int connect_server(char *ip, int port)
{
	static char server_ip_port_cmd[48];
	int ret;
	ret = send_at_command("AT+CGATT=1\r\n", "OK", 3, 3000);//��������
	if(ret == FAILURE)
	{
		return AT_CGATT_ERROR;
	}
	
	ret = send_at_command("AT+CGACT=1,1\r\n", "OK", 3, 1000);//��������
	if(ret == FAILURE)
	{
		return AT_CGATT1_ERROR;
	}

	sprintf(server_ip_port_cmd, "AT+CIPSTART=\"TCP\",\"%s\", %d\r\n", ip, port);
	
	ret = send_at_command(server_ip_port_cmd, "CONNECT OK", 3, 1000);//���ӷ�����
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
	
	ret = send_at_command("AT+CIPSTATUS\r\n", "CONNECT OK", 3, 200);//��ѯ����״̬
	
	if(ret != SUCCESS) { //˵����������������״̬
		ret = connect_server(ip, port);
		if(ret != SUCCESS) {
			return ret; 
		}
	} 

	ret = send_at_command("AT+CIPSEND\r\n", ">", 3, 200);//������������
	if(ret != SUCCESS)
	{
		return AT_CIPSEND_ERROR;
	}
	
	UART_SEND_STRING(msg);
	
	ret = send_at_command(AT_END_CHAR, "SEND OK", 1, 3000);//���ͽ��������ȴ�����ok,�ȴ�5S��һ�Σ���Ϊ��������ʱ����ܽϳ�
	if(ret != SUCCESS)
	{
		return END_CHAR_ERROR;
	}
	
	return SUCCESS;
	
}

