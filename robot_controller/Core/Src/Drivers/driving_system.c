/*
 * driving_system.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Admin
 */

#include "driving_system.h"
#include "string.h"

static char state_str[20];
static char states_buffer[80];
static void add_state_to_states_buffer(MotorState* motor_state);
static void parse_payload(uint8_t* cmd, uint8_t* payload, uint8_t length);


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


	uint8_t cmd_code[] = {cmd[0], cmd[1], '\0'};
	uint8_t cmd_code_0[] = {cmd[0], '\0'};
	uint8_t cmd_code_1[] = {cmd[1], '\0'};

	uint8_t cmd_length = sizeof(cmd)/sizeof(cmd[0]);
	uint8_t payload[cmd_length];
	parse_payload(cmd, payload, cmd_length);


	uint8_t* send_state_literall = (uint8_t*)STATE_CMD_LIT;
	uint8_t* forward_state_literall = (uint8_t*)FORWARD_CMD_LIT;


	if(strcmp(cmd_code_0, send_state_literall) == 0)
	{
		send_state(driving_system);
	}
	else if(strcmp(cmd_code_0, (uint8_t*)CONTROL_MODE_LIT) == 0)
	{

	    float vel;
	    sscanf(payload, "%f", &vel);

		if(strcmp(cmd_code_1, forward_state_literall) == 0)
		{
			drive_forward(driving_system, vel);

		}else if(strcmp(cmd_code_1, (uint8_t*)BACKWARD_CMD_LIT) == 0)
		{
//			drive_backward(driving_system, vel);
		}
	}else if(strcmp(cmd_code_0, (uint8_t*)PWM_MODE_LIT) == 0){

		uint8_t msg[] = "PWM Mode uunimplemented";
		send_drv_err(msg);

	}else{
		uint8_t msg[] = "Undefined First Cmd Literall";
		send_drv_err(msg);
	}
}



void send_drv_err(uint8_t* msg){

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

static void parse_payload(uint8_t* cmd, uint8_t* payload, uint8_t length){

	memset(payload, '\0', sizeof(payload));
	strncpy(payload, cmd + 1, sizeof(cmd)/sizeof(cmd[0]));
	payload[length] = '\0';
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

