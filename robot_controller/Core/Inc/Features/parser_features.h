/*
 * parser_features.h
 *
 *  Created on: Apr 30, 2024
 *      Author: Admin
 */

#ifndef INC_FEATURES_PARSER_FEATURES_H_
#define INC_FEATURES_PARSER_FEATURES_H_

#include "uart_configuration.h"

#define PARSING_ERR "ERR_PARSE "
#define MSG_PAYLOAD_LENGTH 6
#define CMD_CODE_LENGTH 2

#define MSG_CMD_PAYLOAD_BEGIN 2

#define MSG_END_CHAR 0xFE
#define PARSING_ERROR_TIMEOUT 10

void parse_msg_cmd_id(uint8_t* cmd, uint8_t* msg_cmd_id);

void parse_cmd_code(uint8_t* cmd, uint8_t* cmd_code);

int parse_payload(uint8_t* cmd, uint8_t* payload);

void velocity_from_payload();

void pwm_from_payload();

void send_parsing_err(char* msg);

#endif /* INC_FEATURES_PARSER_FEATURES_H_ */
