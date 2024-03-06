#ifndef __TIMER_CONFIGURATION
#define __TIMER_CONFIGURATION

#include "stm32g4xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

void MX_TIM1_Init(void);
void MX_TIM4_Init(void);
void MX_TIM8_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);


#endif /* __TIMER_CONFIGURATION */
