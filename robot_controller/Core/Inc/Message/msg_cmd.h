/*
 * msg_cmd.h
 *
 *  Created on: Apr 30, 2024
 *      Author: Admin
 */

#ifndef INC_MESSAGE_MSG_CMD_H_
#define INC_MESSAGE_MSG_CMD_H_



typedef struct{

	uint16_t cmd_code;
	uint8_t payload[8];

}MsgCmd;




#endif /* INC_MESSAGE_MSG_CMD_H_ */
