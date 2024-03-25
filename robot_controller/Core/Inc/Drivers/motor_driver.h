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

#define MOTOR_Kp			0.06
#define MOTOR_Ki			3
#define MOTOR_Kd			0
#define MOTOR_ANTI_WINDUP	1000



typedef struct{

	float measured_velocity;
	float set_velocity;
	float position;
	float last_position;

	PIDController* pid_controller;
	EncoderInfo* encoder_info;
	TIM_HandleTypeDef* motor_updater_tim;
	L298N_driver* L298N_driver;

}MotorInfo;


void init_motor(MotorInfo *motor, TIM_HandleTypeDef *updater_tim, EncoderInfo *enc_inf_param, PIDController *pid_controller_, L298N_driver *L298N_);

void regulate_velocity(MotorInfo *motor);

void set_velocity(MotorInfo *motor, float velocity);

float rotary_displacement(MotorInfo* motor_info);

void update_position(MotorInfo* motor_info);

void update_measured_velocity(MotorInfo* motor_info);

uint8_t saturate_pwm(int pwm_value);

#endif /* INC_DRIVERS_MOTOR_DRIVER_H_ */
