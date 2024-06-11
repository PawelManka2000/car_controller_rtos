/*
 * parser_features.c
 *
 *  Created on: Apr 30, 2024
 *      Author: Admin
 */

#ifndef SRC_FEATURES_PARSER_FEATURES_C_
#define SRC_FEATURES_PARSER_FEATURES_C_

#include "parser_features.h"


void parse_cmd_code(uint8_t* cmd, uint8_t* cmd_code){

	if (cmd[0] >= '0' && cmd[0] <= '9') {
		cmd_code[0] = cmd[0] - '0';

	}else{
		send_parsing_err("cmd[0] wrong format");
	}

	if (cmd[1] >= '0' && cmd[1] <= '9') {
		cmd_code[1] = cmd[1] - '0';
	}else{
		send_parsing_err("cmd[1] wrong format");
	}

}

void parse_payload(char* cmd, uint8_t* payload) {

    uint8_t cmd_index = 2;
    int i = 0;

    while (cmd[cmd_index] != CMD_END_CHAR) {

    	if(i == CMD_PAYLOAD_LENGTH-1){
    		send_parsing_err(" cmd end char not received");
    		break;
    	}
        payload[i] = cmd[cmd_index];
        i++;
        cmd_index++;
    }

    payload[i] = '\0';
}

void send_parsing_err(char* msg){

	char err_buffer[100];
	memset(err_buffer, '\0', sizeof(err_buffer));
	strcat(err_buffer, PARSING_ERR);
	strcat(err_buffer, msg);
	strcat(err_buffer, "\n\r");
	HAL_UART_Transmit(&hlpuart1,(uint8_t*) err_buffer, strlen(err_buffer),100);

}

#endif /* SRC_FEATURES_PARSER_FEATURES_C_ */
