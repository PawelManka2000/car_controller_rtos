/*
 * engine_driver.c
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#include <motor_features.h>
#include "motor_driver.h"
#include "timers_configuration.h"



void init_motor(
		MotorStruct *motor_struct,
		MotorState *motor_state_,
		TIM_HandleTypeDef *updater_tim_,
		EncoderInfo *enc_inf_param_,
		PIDController *pid_controller_,
		L298N_driver *L298N_)
{
	motor_struct->motor_state = motor_state_;
	motor_struct->motor_updater_tim = updater_tim_;
	motor_struct->updater_timer_periods = CountPeriodS(updater_tim_);
	motor_struct->encoder_info = enc_inf_param_;
	motor_struct->L298N_driver = L298N_;
	motor_struct->pid_controller = pid_controller_;

}

void str_motor_state(MotorState* motor_state, char* state_buffer){

	sprintf(state_buffer, "%d,%.2f,%.2f\n\r", motor_state->motor_id, motor_state->set_velocity, motor_state->measured_velocity);
}

void bytes_motor_state(MotorState* motor_state, uint8_t* state_payload){

	state_payload[0] = motor_state->motor_id;
	state_payload[1]=  (uint8_t)motor_state->measured_velocity;
	uint64_t position_uint = (int32_t)motor_state->position;

	state_payload[2] = (position_uint >> 0) & (0xFF);
	state_payload[3] = (position_uint >> 8) & (0xFF);
	state_payload[4] = (position_uint >> 16) & (0xFF);
	state_payload[5] = (position_uint >> 24) & (0xFF);



}


void regulate_velocity(MotorStruct *motor_struct)
{

	MotorState* current_motor_state = motor_struct->motor_state;
	uint16_t pwm_value = pid_calculate(	motor_struct->pid_controller,
										current_motor_state->set_velocity,
										current_motor_state->measured_velocity);
	uint8_t saturated_pwm_value = saturate_pwm(pwm_value);
	L298N_set_pwm_count(motor_struct->L298N_driver, saturated_pwm_value);

}



void update_motor_position(MotorState* motor_state, EncoderInfo* encoder_info)
{

	motor_state->last_position = motor_state->position;
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
			position_change = postreload_count + prereload_count;

		}else{
			position_change = encoder_diff;
		}
	}

	float position_change_rad = convert_to_radians(position_change);
	motor_state->position = motor_state->last_position - position_change_rad;

}

void motor_state_set_velocity(MotorState *motor_state, float velocity)
{
	motor_state->set_velocity = velocity;
}

void update_measured_velocity(MotorStruct* motor_struct)
{
	MotorState *curr_motor_state = motor_struct->motor_state;
	float rotary_displacement_ = rotary_displacement(curr_motor_state);
	curr_motor_state->measured_velocity = (float)rotary_displacement_ / motor_struct->updater_timer_periods;

}

float rotary_displacement(MotorState *motor_state){

	// physically displacement shouldn't be negative value, but this mean it has different direction
	// which will be pointed by position value
	return fabs(motor_state->position - motor_state->last_position);
}
