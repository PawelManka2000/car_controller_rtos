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

#define NO_OF_SIDE_MOTORS 2
#define STATE_SENDING_TIMEOUT 100
#define DRIVING_ERR "ERR_DRV "

#define PWM_MODE_LIT "p"
#define CONTROL_MODE_LIT "c"

#define FORWARD_CMD_LIT "f"
#define BACKWARD_CMD_LIT "b"
#define STATE_CMD_LIT "s"

typedef struct {
	MotorStruct *left_motors_lst[NO_OF_SIDE_MOTORS];
	MotorStruct *right_motors_lst[NO_OF_SIDE_MOTORS];

} DrivingSystem;

typedef struct {
	void (*exe_cmd)(DrivingSystem*, uint8_t*);
	void (*send_state)(DrivingSystem *driving_system);

} DrivingSystemIface;

void init_driving_system(DrivingSystem *driving_system, MotorStruct *lb_motor,
		MotorStruct *lf_motor, MotorStruct *rb_motor, MotorStruct *rf_motor);

void execute_cmd(DrivingSystem *driving_system, uint8_t *cmd);

void send_state(DrivingSystem *driving_system);

void default_init_driving_system_if(DrivingSystemIface *drv_system_if);

void drive_forward(DrivingSystem* driving_system, float velocity);

void send_drv_err(char* msg);



#endif /* INC_DRIVERS_DRIVING_SYSTEM_H_ */
