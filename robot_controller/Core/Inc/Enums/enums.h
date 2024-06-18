/*
 * enums.h
 *
 *  Created on: Jun 18, 2024
 *      Author: Admin
 */

#ifndef INC_ENUMS_ENUMS_H_
#define INC_ENUMS_ENUMS_H_

enum EMsgID{

	UNKNOWN = 0x00,
	MSG_CMD_REQUEST = 0x01,
	MSG_CMD_RESPONSE = 0x02,
	MSG_STATE = 0x03

};

// CMD_NAME
enum ECmdId{

	CMD_ID_UNKNOWN = 0x00,
	CMD_ID_STATE_REQ = 0x01,
	CMD_ID_CTRL_VELO_REQ = 0x02,
	CMD_ID_PWM_DRIVING_REQ = 0x03,
};

enum EDvModeFlag{

	DV_FLAG_CTRL_VELO = 0,
	DV_FLAG_PWM = 1,
};

enum ECmdStatus{

	CMD_SUCCESS = 0x1,
	CMD_ERROR = 0xFF,

};

#endif /* INC_ENUMS_ENUMS_H_ */
