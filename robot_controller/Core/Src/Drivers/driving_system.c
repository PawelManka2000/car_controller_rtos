/*
 * driving_system.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Admin
 */

#include "driving_system.h"

void init_driving_system(DrivingSystem* driving_system, MotorStruct* lb_motor, MotorStruct* lf_motor, MotorStruct* rb_motor, MotorStruct* rf_motor)
{

	driving_system->left_motors_lst[0] = lb_motor;
	driving_system->left_motors_lst[1] = lf_motor;
	driving_system->right_motors_lst[0] = rb_motor;
	driving_system->right_motors_lst[1] = rf_motor;
}

void default_init_driving_system_if(DrivingSystemIface* drv_system_if){

	drv_system_if->exe_cmd = execute_cmd;
	drv_system_if->send_state = send_state;
}

void execute_cmd(DrivingSystem* driving_system, uint8_t* cmd){


	uint8_t* cmd_literall = cmd;
	uint8_t* send_state_literall = (uint8_t*)"ssss";

	if(strcmp(cmd_literall, send_state_literall) == 0){
		send_state(driving_system);
	}

}

void send_state(DrivingSystem* driving_system){


	MotorState* curr_motor_state = driving_system->left_motors_lst[0]->motor_state;
	uint8_t state_str[30];
	str_motor_state(curr_motor_state, state_str);
	HAL_UART_Transmit(&hlpuart1, state_str, sizeof(state_str),STATE_SENDING_TIMEOUT);
//	char state_str[] = "abcd";

	HAL_UART_Transmit(&hlpuart1, state_str, sizeof(state_str),STATE_SENDING_TIMEOUT);

}
