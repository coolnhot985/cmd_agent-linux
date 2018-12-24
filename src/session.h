#ifndef _SESSION_H_
#define _SESSION_H_

#include "main.h"

#define MAX_RECV_BUFF_SIZE  1024
#define MAC_LEN             13

int handshake(int fd);
char* socket_read(int fd);
char* msg_client_info(size_t *len);
int append_null(char *str, int len);

#endif
