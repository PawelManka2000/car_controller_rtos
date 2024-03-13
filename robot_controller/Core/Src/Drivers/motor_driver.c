/*
 * engine_driver.c
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#include "motor_driver.h"
#include "timers_configuration.h"
#include "engine_features.h"


void init_motor(MotorInfo *motor, TIM_HandleTypeDef *updater_tim, EncoderInfo *enc_inf_param, PIDController *pid_controller_, L298N_driver *L298N_)
{
	motor->engine_updater_tim = updater_tim;
	motor->encoder_info = enc_inf_param;
	motor->measured_velocity = 0;
	motor->set_velocity = 0;
	motor->L298N_driver = L298N_;
	motor->pid_controller = pid_controller_;

}


void regulate_velocity(MotorInfo *motor_info)
{
	int pwm_value = pid_calculate(motor_info->pid_controller, motor_info->set_velocity, motor_info->measured_velocity);
	motor_info->current_PWM = saturate_pwm(pwm_value);
	L298N_update_pwm(motor_info->L298N_driver, motor_info->current_PWM);

}

uint8_t saturate_pwm(int pwm_value){


	if (pwm_value < 0){
		pwm_value = 0;
	}else if(pwm_value > 100){
		pwm_value = 100;
	}
	return (uint8_t)pwm_value;

}

void update_position(MotorInfo* eng_info)
{

	eng_info->last_position = eng_info->position;
	EncoderInfo* encoder_info = eng_info->encoder_info;
	update_encoder_info(encoder_info);
	int16_t encoder_diff = encoder_info->counter_value - encoder_info->last_counter_value;
	int16_t position_change = 0;
	//encoder increase
	if (encoder_diff > 0){

		if (__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder_info->encoder_timer)){

			uint16_t postreload_count = abs(encoder_info->counter_value - __HAL_TIM_GET_AUTORELOAD(encoder_info->encoder_timer));
			position_change = -(encoder_info->last_counter_value + postreload_count); //- because its decreasing

		}else{
			position_change = encoder_diff;
		}
	}else if(encoder_diff < 0) //encoder decrease
	{
		if (!__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder_info->encoder_timer)){

			int16_t postreload_count = encoder_info->counter_value;
			int16_t prereload_count = __HAL_TIM_GET_AUTORELOAD(encoder_info->encoder_timer) - encoder_info->last_counter_value;
			int16_t position_change = postreload_count + prereload_count;

		}else{
			position_change = encoder_diff;
		}
	}

	float position_change_rad = convert_to_radians(position_change);
	eng_info->position = eng_info->last_position - position_change_rad;

}

void set_velocity(MotorInfo *motor, float velocity)
{
	motor->set_velocity = velocity;
}

void update_measured_velocity(MotorInfo* eng_info)
{
	float rotary_displacement_ = rotary_displacement(eng_info);
	float updater_timer_periods = CountPeriodS(eng_info->engine_updater_tim);

	eng_info->measured_velocity = (float)rotary_displacement_ /updater_timer_periods;

}


float rotary_displacement(MotorInfo* eng_info){

	return eng_info->position - eng_info->last_position;
}
