#include "tcp.h"

/** @brief  tcp_hello   클라이언트 측에서 서버측으로 전송하는 최초 패킷 생성
  * @params len         생성된 패킷의 길이
  * @return buff        생성된 패킷버퍼
  *         len         생성된 패킷의 길이
  */
char* tcp_hello(size_t *len) {
    const char *str = NULL;
    char *buff = NULL;

    json_object *json = json_object_new_object();
    json_object *agent_type = json_object_new_string(AGENT_TYPE_LINUX_NVIDIA);
    
    json_object_object_add(json, "agent_type", agent_type);

    str = json_object_get_string(json);

    *len = strlen(str);
    buff = strndup(str, len);

    //buff = (char*)malloc(SERVER_HELLO_PACKET_SIZE);
    return buff;
}

int append_null(char *str, int len) {
    len++;
    str = realloc(str, len);

    *(str + len) = '\0';

    return len;
}
