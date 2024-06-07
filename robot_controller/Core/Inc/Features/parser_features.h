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
#define PAYLOAD_LENGHT 8
#define CMD_END_CHAR 'f'

void parse_cmd_code(char* cmd, char* cmd_code);

void parse_payload(char* cmd, char* payload);

float velocity_from_payload(char* payload);

void pwm_from_payload();

void send_parsing_err(char* msg);

#endif /* INC_FEATURES_PARSER_FEATURES_H_ */
