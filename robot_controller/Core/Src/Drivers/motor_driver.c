/*
 * engine_driver.c
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#include "motor_driver.h"
#include "timers_configuration.h"
#include "engine_features.h"

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



void update_velocity(MotorInfo* eng_info){

	float rotary_displacement_ = rotary_displacement(eng_info);
	float updater_timer_periods = CountPeriodS(eng_info->engine_updater_tim);

	eng_info->measured_velocity = (float)rotary_displacement_ /updater_timer_periods;

}


float rotary_displacement(MotorInfo* eng_info){

	return eng_info->position - eng_info->last_position;
}
