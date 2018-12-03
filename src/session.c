#include "session.h"
#include "tcp.h"


int handshake(int fd) {
    char    *send_data      = NULL;
    char    *recv_data      = NULL;
    size_t  send_data_len   = 0;

    /* TCP_HELLO packet's mean SYN */
    send_data = tcp_hello(&send_data_len);

#if 0
    send_data_len++;
    send_data = realloc(send_data, send_data_len);
    *(send_data + send_data_len) = '\0';
#endif
    
    send_data_len = append_null(send_data, send_data_len);

    send(fd, send_data, send_data_len, MSG_DONTWAIT);
    recv_data = socket_read(fd);                        /* SYN_ACK */
    if (strcmp(recv_data, "SYN_ACK") == 0) {            /* ACK */
        recv_data = socket_read(fd);
        DEBUG("ACK");
    } else {
        DEBUG("FIN");
        return -1;
    }
    
    free(recv_data);
    return 1;
}

char* socket_read(int fd) {
    char    buff[MAX_RECV_BUFF_SIZE] = {'\0'};
    char    *recv_data = NULL;

    int     len = 0;

    recv_data = (char*)malloc(MAX_RECV_BUFF_SIZE);

    while (len == 0) {
        len += read(fd, buff, MAX_RECV_BUFF_SIZE);
        if (len < 0) {
            return recv_data;
        }
        recv_data = realloc(recv_data, len);
        memcpy(recv_data, buff, len);
    }

    return recv_data;
}

