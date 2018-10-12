#ifndef __TCP_H__
#define __TCP_H__

#include "common.h"

#define TCP_SERVER_IP		"115.28.103.171"
#define TCP_SERVER_PORT		9096



#define TCP_SEND_MSG(msg)	tcp_send_msg_to_server(TCP_SERVER_IP, TCP_SERVER_PORT, msg)

int tcp_send_msg_to_server(char *ip, int port, char *msg);

#endif
