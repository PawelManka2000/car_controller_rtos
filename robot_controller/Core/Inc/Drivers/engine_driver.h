/*
 * engine_driver.h
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#ifndef INC_DRIVERS_ENGINE_DRIVER_H_
#define INC_DRIVERS_ENGINE_DRIVER_H_

#include "encoder_driver.h"

typedef struct{

	int16_t velocity;
	int32_t position;
	int32_t last_position;
	EncoderInfo encoder_info;
	TIM_HandleTypeDef* engine_updater_timer;

}EngineInfo;


int32_t rotary_displacement(EngineInfo* eng_info);

void update_position(EngineInfo* eng_info);




#endif /* INC_DRIVERS_ENGINE_DRIVER_H_ */
