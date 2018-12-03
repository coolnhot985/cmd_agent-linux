#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "json.h"
#include "cmd_agent.h"

#define BUF_LEN 128

int main(int argc, char *argv[]) {
    char    buf[BUF_LEN+1]  = {0, };
    char    *send_data      = NULL;
    char    *haddr          = "13.125.12.123";
    size_t  send_data_len   = 0;
    int     fd              = 0;
    int     n               = 0;
    struct sockaddr_in      server_addr;

    if((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("can't create socket\n");
        return 0;
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(haddr);
    server_addr.sin_port = htons(88);

    if (connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("can't connect.\n");
        return 0;
    }
    
    send_data = tcp_hello(&send_data_len);
    send(fd, send_data, send_data_len, MSG_NOSIGNAL);

    while((n = read(fd, buf, BUF_LEN)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
    }
    
    close(fd);
}


