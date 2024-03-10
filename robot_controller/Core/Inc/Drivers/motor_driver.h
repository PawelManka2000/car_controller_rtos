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

#define MOTOR_Kp					4.5
#define MOTOR_Ki					0.8
#define MOTOR_Kd					0.5
#define MOTOR_ANTI_WINDUP			        1000

typedef struct{

	float measured_velocity;
	float set_velocity;

	int actual_PWM;
	PIDController pid_controller;

	float position;
	float last_position;
	EncoderInfo* encoder_info;
	TIM_HandleTypeDef* engine_updater_tim;
	L298N_driver* L298N_driver;

}MotorInfo;


//void init_motor_info(MotorInfo *motor, TIM_HandleTypeDef *updater_tim, EncoderInfo *enc_inf_param)
//{
//	motor->engine_updater_tim = updater_tim;
//	motor->encoder_info = enc_inf_param;
//	motor->measured_velocity = 0;
//	motor->set_velocity = 0;
//	motor->L298N_driver = 0;
//}
//
//void motor_calculate_speed(MotorInfo *motor)
//{
////	motor_update_count(m);
////
////	m->measured_speed = (m->pulse_count * TIMER_FREQENCY * SECOND_IN_MINUTE) / m->resolution;
////
////	int output = pid_calculate(&(m->pid_controller), m->set_speed, m->measured_speed);
////
////	m->actual_PWM += output;
////
////	if(m->actual_PWM >= 0)
////	{
////		drv8835_set_motorA_direction(CW);
////		drv8835_set_motorA_speed(m->actual_PWM);
////	}
////	else
////	{
////		drv8835_set_motorA_direction(CCW);
////		drv8835_set_motorA_speed(-m->actual_PWM);
////	}
//}





float rotary_displacement(MotorInfo* eng_info);

void update_position(MotorInfo* eng_info);

void update_velocity(MotorInfo* eng_info);


#endif /* INC_DRIVERS_MOTOR_DRIVER_H_ */
