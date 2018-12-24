#ifndef _PARSE_H_
#define _PARSE_H_

#include "main.h"
#include "json.h"

typedef struct _cmd_t {
    char    *cmd_type;
    char    *path;
}cmd_t;

char* parse_json_to_string(json_object *json_obj);
cmd_t* parse_json_cmd(json_object *json_obj);

#endif

