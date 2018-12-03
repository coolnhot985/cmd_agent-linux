#ifndef _TCP_H_
#define _TCP_H_

#include "cmd_agent.h"
#include "json.h"

#define SERVER_HELLO_PACKET_SIZE 128
char* tcp_hello(size_t *len);

#endif

