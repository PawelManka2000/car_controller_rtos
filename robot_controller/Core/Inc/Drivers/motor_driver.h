/*
 * engine_driver.h
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#ifndef INC_DRIVERS_MOTOR_DRIVER_H_
#define INC_DRIVERS_MOTOR_DRIVER_H_

#include "encoder_driver.h"
#include "timers_feature.h"
#include "pid_controller.h"
#include "L298N_driver.h"
#include <stdio.h>
#include <string.h>


#define STATE_BUFFER_LENGTH 40

typedef enum {

	LB = 1,
	RB = 2,
	RF = 3,
	LF = 4

}EMotorId;

typedef struct{

	float measured_velocity;
	float set_velocity;
	float position;
	float last_position;
	uint8_t motor_id;

}MotorState;


typedef struct{

	MotorState* motor_state;
	PIDController* pid_controller;
	EncoderInfo* encoder_info;
	TIM_HandleTypeDef* motor_updater_tim;
	float updater_timer_periods;
	L298N_driver* L298N_driver;

}MotorStruct;

void init_motor_state(MotorState *motor_state, EMotorId motor_id_);


void init_motor(
		MotorStruct *motor_struct,
		MotorState *motor_state_,
		TIM_HandleTypeDef *updater_tim_,
		EncoderInfo *enc_inf_param_,
		PIDController *pid_controller_,
		L298N_driver *L298N_);


void str_motor_state(MotorState* motor_state, char* state_buffer);

void motor_state_set_velocity(MotorState *motor_state, float velocity);

float rotary_displacement(MotorState *motor_state);

void update_motor_position(MotorState* motor_state, EncoderInfo* encoder_info);

void update_measured_velocity(MotorStruct* motor_struct);

void regulate_velocity(MotorStruct *motor);





#endif /* INC_DRIVERS_MOTOR_DRIVER_H_ */
