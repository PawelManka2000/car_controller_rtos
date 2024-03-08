/*
 * engine_driver.c
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#include "engine_driver.h"

void update_position(EngineInfo* eng_info)
{
	EncoderInfo encoder_info = eng_info->encoder_info;
	update_encoder_info(&encoder_info);


}

int32_t rotary_displacement(EngineInfo* eng_info){
	return eng_info->position - eng_info->last_position;
}
