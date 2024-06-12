/*
 * driving_system.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Admin
 */

#include "driving_system.h"
#include "driving_modes.h"

static char state_str[20];
static char states_buffer[80];
static void add_state_to_states_buffer(MotorState* motor_state);


void init_driving_system(DrivingSystem* driving_system, MotorStruct* lb_motor, MotorStruct* lf_motor, MotorStruct* rb_motor, MotorStruct* rf_motor)
{

	driving_system->left_motors_lst[0] = lb_motor;
	driving_system->left_motors_lst[1] = lf_motor;
	driving_system->right_motors_lst[0] = rb_motor;
	driving_system->right_motors_lst[1] = rf_motor;
	driving_system->velo_ctrl_flag = 1;
}

void default_init_driving_system_if(DrivingSystemIface* drv_system_if){

	drv_system_if->exe_cmd = execute_cmd;
	drv_system_if->send_state = send_state;
}

// TODO DELETE VELO
void driving_system_drive(DrivingSystem* driving_system, float velo){

//	if(driving_system->driving_mode_flag == DV_FLAG_CTRL_VELO){
//
//		for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i){
//
//			regulate_velocity(driving_system->left_motors_lst[i]);
//			regulate_velocity(driving_system->right_motors_lst[i]);
//		}
//	}else if(driving_system->driving_mode_flag == DV_FLAG_PWM){
//
////		L298N_update_pwm(driving_system->right_motors_lst[i]->L298N_driver, )
//	}

	// TODO change to NO_OF_SIDE_MOTORS WHEN APPEARS
//	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i){
	for(int i = 0; i < 1; ++i){


    	update_motor_position(driving_system->left_motors_lst[i]->motor_state, driving_system->left_motors_lst[i]->encoder_info);
    	update_measured_velocity(driving_system->left_motors_lst[i]);
    	motor_state_set_velocity(driving_system->left_motors_lst[i]->motor_state, velo);

		if(driving_system->velo_ctrl_flag){
			regulate_velocity(driving_system->left_motors_lst[i]);
//			regulate_velocity(driving_system->right_motors_lst[i]);
		}

		L298N_update_pwm(driving_system->left_motors_lst[i]->L298N_driver);
//		L298N_update_pwm(driving_system->right_motors_lst[i]->L298N_driver);


	}


}


void execute_cmd(DrivingSystem* driving_system, uint8_t* cmd){


	uint8_t cmd_code[] = "00";
	uint8_t payload[] = "000000";

	parse_cmd_code(cmd, cmd_code);
	parse_payload(cmd, payload);


	if(cmd_code[CMD_ID_POS] == CMD_ID_STATE_REQ)
	{
		send_state(driving_system);

	}else if(cmd_code[CMD_ID_POS] == CMD_ID_CTRL_VELO_REQ)
	{

	    float vel = 0;
	    sscanf(payload, "%f", &vel);
		drive_velo_dir(driving_system, cmd_code[DV_MODE_POS], vel);


	}else if(cmd_code[CMD_ID_POS] == CMD_ID_PWM_DRIVING_REQ){

	    uint8_t pwm = 0;
	    sscanf(payload, "%d", &pwm);

		drive_pwm_dir(driving_system, cmd_code[DV_MODE_POS], pwm);
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



void send_state(DrivingSystem* driving_system){


	memset(states_buffer, '\0', sizeof(states_buffer));

	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i){

		add_state_to_states_buffer(driving_system->left_motors_lst[i]->motor_state);
		add_state_to_states_buffer(driving_system->right_motors_lst[i]->motor_state);
	}

	HAL_UART_Transmit(&hlpuart1,(uint8_t*) states_buffer, strlen(states_buffer),STATE_SENDING_TIMEOUT);

}

