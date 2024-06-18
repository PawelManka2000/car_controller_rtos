/*
 * driving_modes.c
 *
 *  Created on: Jun 11, 2024
 *      Author: Admin
 */

#include "driving_modes.h"



void drive_velo_dir(DrivingSystem* driving_system, EDvDir dv_dir, float velocity){

	if(dv_dir == DV_DIR_STOP){
		drive_velo(driving_system, velocity, L298N_MODE_STOP, L298N_MODE_STOP);
	}else if(dv_dir == DV_DIR_FORWARD){
		drive_velo(driving_system, velocity, L298N_MODE_FORWARD, L298N_MODE_FORWARD);
	}else if(dv_dir == DV_DIR_BACKWARD){
		drive_velo(driving_system, velocity, L298N_MODE_BACKWARD, L298N_MODE_BACKWARD);
	}else if(dv_dir == DV_DIR_LEFT){
		drive_velo(driving_system, velocity, L298N_MODE_FORWARD, L298N_MODE_BACKWARD);
	}else if(dv_dir == DV_DIR_RIGHT){
		drive_velo(driving_system, velocity, L298N_MODE_BACKWARD, L298N_MODE_FORWARD);
	}
}

void drive_pwm_dir(DrivingSystem* driving_system, EDvDir dv_dir, uint8_t pwm){

	if(dv_dir == DV_DIR_STOP){
		drive_pwm(driving_system, pwm, L298N_MODE_STOP, L298N_MODE_STOP);
	}else if(dv_dir == DV_DIR_FORWARD){
		drive_pwm(driving_system, pwm, L298N_MODE_FORWARD, L298N_MODE_FORWARD);
	}else if(dv_dir == DV_DIR_BACKWARD){
		drive_pwm(driving_system, pwm, L298N_MODE_BACKWARD, L298N_MODE_BACKWARD);
	}else if(dv_dir == DV_DIR_LEFT){
		drive_pwm(driving_system, pwm, L298N_MODE_FORWARD, L298N_MODE_BACKWARD);
	}else if(dv_dir == DV_DIR_RIGHT){
		drive_pwm(driving_system, pwm, L298N_MODE_BACKWARD, L298N_MODE_FORWARD);
	}
}



void drive_velo(DrivingSystem* driving_system, float velocity, EL298N_MODE left_dir, EL298N_MODE right_dir)
{

	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i)
	{
		L298N_set_input_configuration(driving_system->left_motors_lst[i]->L298N_driver, left_dir);
		L298N_set_input_configuration(driving_system->right_motors_lst[i]->L298N_driver, right_dir);
		motor_state_set_velocity(driving_system->left_motors_lst[i]->motor_state, velocity);
		motor_state_set_velocity(driving_system->right_motors_lst[i]->motor_state, velocity);

	}
}


void drive_pwm(DrivingSystem* driving_system, uint8_t pwm, EL298N_MODE left_dir, EL298N_MODE right_dir){
	for(int i = 0; i < NO_OF_SIDE_MOTORS; ++i)
	{
		L298N_set_input_configuration(driving_system->left_motors_lst[i]->L298N_driver, left_dir);
		L298N_set_input_configuration(driving_system->right_motors_lst[i]->L298N_driver, right_dir);
		L298N_set_pwm_count(driving_system->left_motors_lst[i]->L298N_driver, pwm);
		L298N_set_pwm_count(driving_system->right_motors_lst[i]->L298N_driver, pwm);
	}

}
