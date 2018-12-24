#include "parse.h"

char* parse_json_to_string(json_object *json_obj) {
    enum json_type type;

    json_object_object_foreach(json_obj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_null :
                break;
            case json_type_boolean :
                break;
            case json_type_double :
                break;
            case json_type_int:
                break;
            case json_type_object:
                break;
            case json_type_array:
                break;
            case json_type_string: 
                printf("type: json_type_string, ");
                printf("value: [%s]\n", json_object_get_string(val));
                break;
        }
    }
    return json_object_get_string(val);
}

cmd_t* parse_json_cmd(json_object *json_obj) {
    enum    json_type type;
    cmd_t   *cmd = NULL;

    cmd = (cmd_t*)malloc(sizeof(cmd_t));
    json_object_object_foreach(json_obj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_null :
                break;
            case json_type_boolean :
                break;
            case json_type_double :
                break;
            case json_type_int:
                break;
            case json_type_object:
                break;
            case json_type_array:
                break;
            case json_type_string:
                if (strcmp(key, "commend_type") == 0) {
                    cmd->cmd_type = json_object_get_string(val);
                } else if (strcmp(key, "path") == 0) {
                    if (0 != json_object_get_string_len(val)) {
                        cmd->path = json_object_get_string(val);
                    } else {
                        cmd->path = (char*)malloc(sizeof(1));;
                        cmd->path = "\0";
                    }
                }
                break;
        }
    }
    return cmd;
}


/** @brief      parse_string_to_json    문자열을 JSON 오브젝트로 변환
 * @params     str     변환할 문자열
 * @return     json    JSON 오브젝트
 */
json_object* parse_string_to_json(char* str) {
    json_object *json;

    json = json_tokener_parse(str);

    return json;
}
