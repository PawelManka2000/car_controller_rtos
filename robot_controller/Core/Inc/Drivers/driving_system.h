/*
 * driving_system.h
 *
 *  Created on: Apr 9, 2024
 *      Author: Admin
 */

#ifndef INC_DRIVERS_DRIVING_SYSTEM_H_
#define INC_DRIVERS_DRIVING_SYSTEM_H_

#include <string.h>
#include "motor_driver.h"
#include "uart_configuration.h"
#include "parser_features.h"

#define MSG_ID_POS 0
#define CMD_CODE_ID_POS 0
#define PAYLOAD_DV_MODE_POS 0

#define NO_OF_SIDE_MOTORS 2
#define STATE_SENDING_TIMEOUT 10
#define DRIVING_ERR "ERR_DRV "
#define ACK_RESP_HEADER "ACK "

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


typedef struct {
	MotorStruct *left_motors_lst[NO_OF_SIDE_MOTORS];
	MotorStruct *right_motors_lst[NO_OF_SIDE_MOTORS];
	uint8_t velo_ctrl_flag;

} DrivingSystem;

typedef struct {
	int (*exe_cmd)(DrivingSystem*, uint8_t*);
	void (*send_state)(DrivingSystem *driving_system);

} DrivingSystemIface;

void driving_system_drive(DrivingSystem* driving_system, float velo);

void init_driving_system(DrivingSystem *driving_system, MotorStruct *lb_motor,
		MotorStruct *lf_motor, MotorStruct *rb_motor, MotorStruct *rf_motor);

int execute_cmd(DrivingSystem *driving_system, uint8_t *cmd);

void send_state(DrivingSystem *driving_system);

void default_init_driving_system_if(DrivingSystemIface *drv_system_if);



void send_drv_err(char* msg);



#endif /* INC_DRIVERS_DRIVING_SYSTEM_H_ */
