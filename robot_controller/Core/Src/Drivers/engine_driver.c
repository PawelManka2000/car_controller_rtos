/*
 * engine_driver.c
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#include "engine_driver.h"

void update_position(EngineInfo* eng_info)
{

	eng_info->last_position = eng_info->position;
	EncoderInfo* encoder_info = eng_info->encoder_info;
	update_encoder_info(encoder_info);
	int16_t encoder_diff = encoder_info->counter_value - encoder_info->last_counter_value;

	//encoder increase
	if (encoder_diff > 0){

		if (__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder_info->encoder_timer)){

			uint16_t postreload_count = abs(encoder_info->counter_value - __HAL_TIM_GET_AUTORELOAD(encoder_info->encoder_timer));
			int16_t position_change = encoder_info->last_counter_value + postreload_count;
			eng_info->position = eng_info->last_position - position_change;
		}else{

			eng_info->position = eng_info->last_position + encoder_diff;
		}
	}else if(encoder_diff < 0) //encoder decrease
	{
		if (!__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder_info->encoder_timer)){

			int16_t postreload_count = encoder_info->counter_value;
			int16_t prereload_count = __HAL_TIM_GET_AUTORELOAD(encoder_info->encoder_timer) - encoder_info->last_counter_value;
			int16_t position_change = postreload_count + prereload_count;
			eng_info->position = eng_info->last_position + position_change;

		}else{

			eng_info->position = eng_info->last_position + encoder_diff;
		}

	}


}



int32_t rotary_displacement(EngineInfo* eng_info){

	return eng_info->position - eng_info->last_position;
}
