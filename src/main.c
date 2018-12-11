#include "main.h"

#define BUF_LEN 128

typedef struct sockaddr_in  fd_in_t;
typedef struct sockaddr     fd_t;

int main(int argc, char *argv[]) {
    char    *haddr          = "13.125.12.123";
    int     fd              = 0;
    int     ret             = 0;

    fd_in_t server_addr;


    if((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("can't create socket\n");
        return 0;
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(haddr);
    server_addr.sin_port = htons(88);

    if (connect(fd, (fd_t *)&server_addr, sizeof(server_addr)) < 0) {
        printf("can't connect.\n");
        return 0;
    }

    while (1) {
        /* hand shake to server */ 
        ret = handshake(fd);
        if (ret == 1) {
        } else {
            return 0;
        }
    }
    close(fd);
    printf("done");
}


