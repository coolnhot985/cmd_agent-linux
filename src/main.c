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
    char    *haddr          = "13.125.12.123";
    struct sockaddr_in      server_addr;
    char    *recv_data      = NULL;
    int     fd              = 0;
    int     ret             = 0;

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

    /* hand shake to server */ 
    ret = handshake(fd);
    if (ret == 1) {
    } else {
        return 0;
    }

    /*  recv cmd */
    DEBUG("waiting .. ");
    while(1) {
        recv_data = socket_read(fd);
        DEBUG("cmd [%s]", recv_data);
    }
    close(fd);
}


