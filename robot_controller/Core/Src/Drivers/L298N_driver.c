/*
 * L298N_driver.c
 *
 *  Created on: Mar 10, 2024
 *      Author: pawel
 */

#include "L298N_driver.h"
#include "timers_configuration.h"

void L298N_update_pwm(L298N_driver* L298_driver, int pwm_count)
{
	__HAL_TIM_SetCompare(L298_driver->pwm_timer, L298_driver->pwm_channel, pwm_count);


}


void L298N_set_input_configuration(L298N_driver* L298_driver, E_L298N_MODE l298n_mode)
{

	if(l298n_mode == FORWARD)
	{
	  HAL_GPIO_WritePin(L298_driver->GPIOx_1, L298_driver->GPIO_Pin_1, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(L298_driver->GPIOx_2, L298_driver->GPIO_Pin_2, GPIO_PIN_RESET);

	}else if(l298n_mode == BACKWARD)
	{
	  HAL_GPIO_WritePin(L298_driver->GPIOx_1, L298_driver->GPIO_Pin_1, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(L298_driver->GPIOx_2, L298_driver->GPIO_Pin_2, GPIO_PIN_SET);
	}
	else if(l298n_mode == STOP)
	{
	  HAL_GPIO_WritePin(L298_driver->GPIOx_1, L298_driver->GPIO_Pin_1, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(L298_driver->GPIOx_2, L298_driver->GPIO_Pin_2, GPIO_PIN_RESET);
	}

}
