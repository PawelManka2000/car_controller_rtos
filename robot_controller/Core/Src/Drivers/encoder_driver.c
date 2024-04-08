/*
 * encoder_driver.c
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#include "encoder_driver.h"

void init_encoder_info(EncoderInfo* encoder_info, TIM_HandleTypeDef* encoder_timer_)
{
	encoder_info->encoder_timer=encoder_timer_;

}

void update_encoder_info(EncoderInfo* encoder_info)
{

	encoder_info->last_counter_value = encoder_info->counter_value;
	encoder_info->counter_value = __HAL_TIM_GET_COUNTER(encoder_info->encoder_timer);

}


