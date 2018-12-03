#ifndef _TCP_H_
#define _TCP_H_

#include <sys/epoll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "cmd_agent.h"
#include "json.h"

#define SERVER_HELLO_PACKET_SIZE 128

char* tcp_hello(size_t *len);
int append_null(char *str, int len);

#endif

