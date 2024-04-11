/*
 * driving_system.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Admin
 */

#include "driving_system.h"

static char state_str[30];

static void send_state(DrivingSystem* driving_system);
static execute_drv_cmd(DrivingSystem* driving_system, uint8_t* cmd);
static void drive_forward(DrivingSystem* driving_system, uint8_t* set_vel);
static void drive_backward(DrivingSystem* driving_system, uint8_t* set_vel);
static void drive_left(DrivingSystem* driving_system, uint8_t* set_vel);
static void drive_right(DrivingSystem* driving_system, uint8_t* set_vel);


void init_driving_system(DrivingSystem* driving_system, MotorStruct* lb_motor, MotorStruct* lf_motor, MotorStruct* rb_motor, MotorStruct* rf_motor)
{

	driving_system->left_motors_lst[0] = lb_motor;
	driving_system->left_motors_lst[1] = lf_motor;
	driving_system->right_motors_lst[0] = rb_motor;
	driving_system->right_motors_lst[1] = rf_motor;
}

void default_init_driving_system_if(DrivingSystemIface* drv_system_if){

	drv_system_if->exe_cmd = execute_cmd;
}

void execute_cmd(DrivingSystem* driving_system, uint8_t* cmd){


	uint8_t cmd_literall[] = {cmd[0], '\0'};
	uint8_t* send_state_literall = (uint8_t*)"s";

	if(strcmp(cmd_literall, SEND_STATE_SYM) == 0){
		send_state(driving_system);
	}else if(strcmp(cmd_literall, DRIVING_STATE_SYM) == 0){
		execute_drv_cmd(driving_system, cmd);
	}
}


static void send_state(DrivingSystem* driving_system){

	memset(state_str, '\0', sizeof(state_str));
	MotorState* curr_motor_state = driving_system->left_motors_lst[0]->motor_state;
	str_motor_state(curr_motor_state, state_str);
	HAL_UART_Transmit(&hlpuart1,(uint8_t*) state_str, sizeof(state_str),STATE_SENDING_TIMEOUT);

}

static void execute_drv_cmd(DrivingSystem* driving_system, uint8_t* cmd){

	uint8_t cmd_drv_sym[] = {cmd[1], '\0'};
    uint8_t set_vel[3]; // Allocate space for sliced string
    strncpy(set_vel, cmd_drv_sym + 2, 3); // Copy the sliced portion

	if(strcmp(cmd_drv_sym, FORWARD_SYM) == 0){
		drive_forward(driving_system, set_vel);
	}else if(strcmp(cmd_drv_sym, BACKWARD_SYM) == 0){
		drive_backward(driving_system, set_vel);
	}else if(strcmp(cmd_drv_sym, LEFT_SYM) == 0){
		drive_left(driving_system, set_vel);
	}else if(strcmp(cmd_drv_sym, RIGHT_SYM) == 0){
		drive_right(driving_system, set_vel);
	}
}



