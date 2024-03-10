/*
 * L298N_driver.h
 *
 *  Created on: Mar 10, 2024
 *      Author: pawel
 */

#ifndef INC_DRIVERS_L298N_DRIVER_H_
#define INC_DRIVERS_L298N_DRIVER_H_

#include "stm32g4xx_hal.h"
#include "timers_configuration.h"


typedef enum{

	STOP,
	FORWARD,
	BACKWARD,

}E_L298N_MODE;


typedef struct{

	uint32_t pwm_channel;
	TIM_HandleTypeDef* pwm_timer;

	GPIO_TypeDef *GPIOx_1;
	uint16_t GPIO_Pin_1;

	GPIO_TypeDef *GPIOx_2;
	uint16_t GPIO_Pin_2;

}L298N_driver;


void L298N_update_pwm(L298N_driver* L298_driver, int pwm_count);


void L298N_set_input_configuration(L298N_driver* L298_driver, E_L298N_MODE l298n_mode);
#endif /* INC_DRIVERS_L298N_DRIVER_H_ */
