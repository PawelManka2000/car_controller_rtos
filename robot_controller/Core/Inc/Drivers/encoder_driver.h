/*
 * encoder_driver.h
 *
 *  Created on: Mar 8, 2024
 *      Author: pawel
 */

#ifndef INC_DRIVERS_ENCODER_DRIVER_H_
#define INC_DRIVERS_ENCODER_DRIVER_H_

#include "stm32g4xx_hal.h"

typedef struct{

	TIM_HandleTypeDef* encoder_timer;
	uint16_t counter_value;
	uint16_t last_counter_value;

}EncoderInfo;

void update_encoder_info(EncoderInfo* encoder_info);

#endif /* INC_DRIVERS_ENCODER_DRIVER_H_ */
