/* 
 * File:   Globals.h
 * Author: atghosh
 *
 * Created on 3 August, 2013, 8:39 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H
#include <map>
#include <string>

static const char death_msg[] =  "I am sorry to say that the server has been shut!\n";

enum CMD {
    INSERT_CMD = 1, DELETE_CMD, FIND_CMD, DELALL_CMD, SHOW_CMD
};

enum TYPE {
    INT_TYPE = 6, FLOAT_TYPE, STRING_TYPE
};

struct parsed_vals {
    int cmd;
    int type;

    union {
        int int_data;
        float float_data;
        char *str_data;
    } data;
};
#endif	/* GLOBALS_H */

