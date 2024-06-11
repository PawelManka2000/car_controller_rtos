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

	L298N_MODE_STOP,
	L298N_MODE_FORWARD,
	L298N_MODE_BACKWARD,

}EL298N_MODE;


typedef struct{

	uint32_t pwm_channel;
	TIM_HandleTypeDef* pwm_timer;
	uint8_t PWM_count;

	GPIO_TypeDef *GPIOx_1;
	uint16_t GPIO_Pin_1;

	GPIO_TypeDef *GPIOx_2;
	uint16_t GPIO_Pin_2;

}L298N_driver;

void L298N_init(L298N_driver* L298N_driver,
				uint32_t pwm_channel_,
				TIM_HandleTypeDef* pwm_timer_,
				GPIO_TypeDef* GPIOx_1_,
				uint16_t GPIO_Pin_1_,
				GPIO_TypeDef* GPIOx_2_,
				uint16_t GPIO_Pin_2_);

void L298N_set_pwm_count(L298N_driver* L298_driver, uint8_t new_pwm_count);
void L298N_set_input_configuration(L298N_driver* L298_driver, EL298N_MODE l298n_mode);

void L298N_update_pwm(L298N_driver* L298_driver);


#endif /* INC_DRIVERS_L298N_DRIVER_H_ */
