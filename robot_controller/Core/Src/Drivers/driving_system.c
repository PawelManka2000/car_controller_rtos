/*
 * driving_system.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Admin
 */

#include "driving_system.h"
#include "driving_modes.h"



static void add_states_payload_to_state_msg(MotorState* motor_state, uint8_t* offset, uint8_t* state_msg);


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
void driving_system_drive(DrivingSystem* driving_system){


	// TODO change to NO_OF_SIDE_MOTORS WHEN APPEARS
//	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i){
	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i){

    	update_motor_position(driving_system->left_motors_lst[i]->motor_state, driving_system->left_motors_lst[i]->encoder_info);
    	update_motor_position(driving_system->right_motors_lst[i]->motor_state, driving_system->right_motors_lst[i]->encoder_info);

    	update_measured_velocity(driving_system->left_motors_lst[i]);
    	update_measured_velocity(driving_system->right_motors_lst[i]);

		if(driving_system->velo_ctrl_flag){
			regulate_velocity(driving_system->left_motors_lst[i]);
			regulate_velocity(driving_system->right_motors_lst[i]);
		}

		L298N_update_pwm(driving_system->left_motors_lst[i]->L298N_driver);
		L298N_update_pwm(driving_system->right_motors_lst[i]->L298N_driver);


	}


}


int execute_cmd(DrivingSystem* driving_system, uint8_t* cmd){

	uint8_t cmd_id = 0x00;
	uint8_t cmd_code[] = {0x00};
	uint8_t payload[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	parse_msg_cmd_id(cmd, &cmd_id);
	if(cmd_id != MSG_CMD_REQUEST){
		return 1;
	}

    parse_cmd_code(cmd, cmd_code);
    if (parse_payload(cmd, payload)) {
        return 1;
    }


	if(cmd_code[CMD_CODE_ID_POS] == CMD_ID_STATE_REQ)
	{
		send_state(driving_system);

	}else if(cmd_code[CMD_CODE_ID_POS] == CMD_ID_CTRL_VELO_REQ)
	{
		int whole_number = payload[1];
		float fractional_part =  payload[2] /100.0;
		float vel = fractional_part + whole_number;

		drive_velo_dir(driving_system, payload[PAYLOAD_DV_MODE_POS], vel);
		driving_system->velo_ctrl_flag = 1;


	}else if(cmd_code[CMD_CODE_ID_POS] == CMD_ID_PWM_DRIVING_REQ){

	    uint8_t pwm = payload[1];
		drive_pwm_dir(driving_system, payload[PAYLOAD_DV_MODE_POS], pwm);
		driving_system->velo_ctrl_flag = 0;
	}
	else{
		char msg[] = "Undefined First Cmd Literall";
		send_drv_err(msg);
		return 1;
	}
	return 0;

}



void send_drv_err(char* msg){

	char err_buffer[100];
	memset(err_buffer, '\0', sizeof(err_buffer));
	strcat(err_buffer, DRIVING_ERR);
	strcat(err_buffer, msg);
	strcat(err_buffer, "\n\r");
	HAL_UART_Transmit(&hlpuart1,(uint8_t*) err_buffer, strlen(err_buffer), STATE_SENDING_TIMEOUT);

}


static void add_states_payload_to_state_msg(MotorState* motor_state, uint8_t* offset, uint8_t* state_msg){

	uint8_t state_payload[STATE_PAYLOAD_LENGTH];
	bytes_motor_state(motor_state, state_payload);

	for (int i = 0; i < STATE_PAYLOAD_LENGTH; i++){
		state_msg[*offset] = state_payload[i];
		*offset += 1;
	}

}

void send_ack(char* msg){
	char ack_buffer[100];
	memset(ack_buffer, '\0', sizeof(ack_buffer));
	strcat(ack_buffer, ACK_RESP_HEADER);
	strcat(ack_buffer, msg);
	strcat(ack_buffer, "\n\r");
	HAL_UART_Transmit(&hlpuart1,(uint8_t*) ack_buffer, strlen(ack_buffer), STATE_SENDING_TIMEOUT);

}

void send_resp(enum ECmdId cmd_code,uint8_t* cmd_status){


}


void send_state(DrivingSystem* driving_system){

	uint8_t state_msg_length = 2 + 4 * STATE_PAYLOAD_LENGTH;
	uint8_t state_msg[state_msg_length];
	state_msg[0] = MSG_STATE;
	uint8_t offset = 1;


	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i){

		add_states_payload_to_state_msg(driving_system->left_motors_lst[i]->motor_state, &offset, state_msg);
		add_states_payload_to_state_msg(driving_system->right_motors_lst[i]->motor_state, &offset, state_msg);
	}
	state_msg[state_msg_length-1] = MSG_END_CHAR;
	HAL_UART_Transmit(&hlpuart1,(uint8_t*) state_msg, sizeof(state_msg)/sizeof(state_msg[0]),STATE_SENDING_TIMEOUT);

}

