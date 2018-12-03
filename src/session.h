#ifndef _SESSION_H_
#define _SESSION_H_

#include "cmd_agent.h"

#define MAX_RECV_BUFF_SIZE 1024

int handshake(int fd);
char* socket_read(int fd);

#endif
