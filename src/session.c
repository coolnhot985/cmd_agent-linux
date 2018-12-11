#include "session.h"

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

    DEBUG("send data [%s]", send_data);
    
    send(fd, send_data, send_data_len, MSG_NOSIGNAL);
    recv_data = socket_read(fd);                     /* SYN_ACK */
    if (strcmp(recv_data, "SYN_ACK") == 0) {            
        DEBUG("wait req...");
        recv_data = socket_read(fd);
    
    } else {
        DEBUG("FIN");
        return -1;
    }
    
    free(recv_data);
    return 1;
}

#if 0
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

    send(fd, send_data, send_data_len, MSG_NOSIGNAL);
    BREAK("send_data [%s]", send_data);
    recv_data = socket_read(fd);                     /* SYN_ACK */
    BREAK("recv_data [%s]", recv_data);
    if (strcmp(recv_data, "SYN_ACK") == 0) {            
        DEBUG("wait req...");
        recv_data = socket_read(fd);
    
        BREAK("commend [%s]", recv_data);
    } else {
        DEBUG("FIN");
        return -1;
    }
    
    free(recv_data);
    return 1;
}
#endif

char* socket_read(int fd) {
    int     len = 0;
    int     recv_len = 0;
    size_t  offset = 0;

    char    buff[MAX_RECV_BUFF_SIZE];
    char    *recv_data = NULL;

    recv_data = (char*)malloc(MAX_RECV_BUFF_SIZE);
    memset(recv_data, 0x0, MAX_RECV_BUFF_SIZE);

    while (len >= 0) {
        memset(buff, 0x00, MAX_RECV_BUFF_SIZE);
        len = read(fd, buff, MAX_RECV_BUFF_SIZE);
        //len = recv(fd, buff, MAX_RECV_BUFF_SIZE, MSG_DONTWAIT);
        if (len <= 0) {
            DEBUG("Fail .. ERR [%d]", len);
            return recv_data;
        }

        recv_len += len;
        recv_data = realloc(recv_data, recv_len);

        memcpy(recv_data + offset, buff, len);
        offset += len;

        if (recv_data[recv_len - 1] == '\0' || recv_data[recv_len] == '\0') {
            return recv_data;
        }
    }

    BREAK("recv_data [%s]", recv_data);

    return recv_data;
}

/** @brief  tcp_hello   클라이언트 측에서 서버측으로 전송하는 최초 패킷 생성
  * @params len         생성된 패킷의 길이
  * @return buff        생성된 패킷버퍼
  *         len         생성된 패킷의 길이
  */
char* tcp_hello(size_t *len) {
    const char *str = NULL;
    char *buff = NULL;
    
    char mac_addr[MAC_LEN] = {0, };
    mac_eth0(mac_addr);

    json_object *json = json_object_new_object();
    json_object *agent_type = json_object_new_string(AGENT_TYPE_LINUX_NVIDIA);
    json_object *miner_mac  = json_object_new_string(mac_addr);
    
    json_object_object_add(json, "agent_type", agent_type);
    json_object_object_add(json, "miner_mac", miner_mac);

    str = json_object_get_string(json);
    
    *len = strlen(str);
    buff = strndup(str, len);

    return buff;
}

int append_null(char *str, int len) {
    len++;
    str = realloc(str, len);

    *(str + len) = '\0';

    return len;
}
