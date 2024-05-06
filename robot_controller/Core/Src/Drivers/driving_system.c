/*
 * driving_system.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Admin
 */

#include "driving_system.h"


static char state_str[20];
static char states_buffer[80];
static void add_state_to_states_buffer(MotorState* motor_state);


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


	uint8_t cmd_code[] = "00";
	uint8_t payload[] = "0000000";

	parse_cmd_code(cmd, cmd_code);
	parse_payload(cmd, payload);


//	uint8_t* send_state_literall = (uint8_t*)STATE_CMD_LIT;
//	uint8_t* forward_state_literall = (uint8_t*)FORWARD_CMD_LIT;


	if(cmd_code[0] == 1)
	{
		send_state(driving_system);
	}else if(cmd_code[0] == 2)
	{

	    float vel = 0;
	    sscanf(payload, "%f", &vel);

		if(cmd_code[1] == 1)
		{
			send_state(driving_system);
//			vel = velocity_from_payload(payload);
//			drive_forward(driving_system, vel);

		}else if(cmd_code[1] == 2)
		{
//			drive_backward(driving_system, vel);
			send_drv_err("Backward not implemented");
		}

	}else if(cmd_code[0] == 3){

		send_drv_err("PWM Mode unimplemented");

	}
	else{
		uint8_t msg[] = "Undefined First Cmd Literall";
		send_drv_err(msg);
	}
}



void send_drv_err(char* msg){

	char err_buffer[100];
	memset(err_buffer, '\0', sizeof(err_buffer));
	strcat(err_buffer, DRIVING_ERR);
	strcat(err_buffer, msg);
	strcat(err_buffer, "\n\r");
	HAL_UART_Transmit(&hlpuart1,(uint8_t*) err_buffer, strlen(err_buffer),STATE_SENDING_TIMEOUT);

}


static void add_state_to_states_buffer(MotorState* motor_state){

	memset(state_str, '\0', sizeof(state_str));
	str_motor_state(motor_state, state_str);
	strcat(states_buffer, state_str);

}




void drive_forward(DrivingSystem* driving_system, float velocity){

	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i){

		set_velocity(driving_system->left_motors_lst[i]->motor_state, velocity);
		set_velocity(driving_system->right_motors_lst[i]->motor_state, velocity);
		add_state_to_states_buffer(driving_system->right_motors_lst[i]->motor_state);
	}

}


void send_state(DrivingSystem* driving_system){


	memset(states_buffer, '\0', sizeof(states_buffer));

	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i){

		add_state_to_states_buffer(driving_system->left_motors_lst[i]->motor_state);
		add_state_to_states_buffer(driving_system->right_motors_lst[i]->motor_state);
	}

	HAL_UART_Transmit(&hlpuart1,(uint8_t*) states_buffer, strlen(states_buffer),STATE_SENDING_TIMEOUT);

}

