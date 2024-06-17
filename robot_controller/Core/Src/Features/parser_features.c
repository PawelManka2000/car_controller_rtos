/*
 * parser_features.c
 *
 *  Created on: Apr 30, 2024
 *      Author: Admin
 */

#ifndef SRC_FEATURES_PARSER_FEATURES_C_
#define SRC_FEATURES_PARSER_FEATURES_C_

#include "parser_features.h"

void parse_msg_cmd_id(uint8_t* cmd, uint8_t* msg_cmd_id){

	*msg_cmd_id = cmd[0];

}

void parse_cmd_code(uint8_t* cmd, uint8_t* cmd_code){

//	if (cmd[0] >= '0' && cmd[0] <= '9') {
//		cmd_code[0] = cmd[0] - '0';
//
//	}else{
//		send_parsing_err("cmd[0] wrong format");
//		return 1;
//	}
//
//	if (cmd[1] >= '0' && cmd[1] <= '9') {
//		cmd_code[1] = cmd[1] - '0';
//	}else{
//		send_parsing_err("cmd[1] wrong format");
//		return 1;
//	}
//	return 0;

	cmd_code[0] = cmd[1];
}

int parse_payload(uint8_t* cmd, uint8_t* payload) {

    uint8_t cmd_index = MSG_CMD_PAYLOAD_BEGIN;
    while (cmd[cmd_index] != MSG_END_CHAR) {

    	if((cmd_index-MSG_CMD_PAYLOAD_BEGIN) == MSG_PAYLOAD_LENGTH-1){
    		send_parsing_err("cmd end char not received");
    		return 1;
    	}
        payload[cmd_index-MSG_CMD_PAYLOAD_BEGIN] = cmd[cmd_index];
        cmd_index++;
    }

    payload[cmd_index-MSG_CMD_PAYLOAD_BEGIN] = '\0';
    return 0;
}

void send_parsing_err(char* msg){

	char err_buffer[100];
	memset(err_buffer, '\0', sizeof(err_buffer));
	strcat(err_buffer, PARSING_ERR);
	strcat(err_buffer, msg);
	strcat(err_buffer, "\n\r");
	HAL_UART_Transmit(&hlpuart1,(uint8_t*) err_buffer, strlen(err_buffer), PARSING_ERROR_TIMEOUT);

}

#endif /* SRC_FEATURES_PARSER_FEATURES_C_ */
