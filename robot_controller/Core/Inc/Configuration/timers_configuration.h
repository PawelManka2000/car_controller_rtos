#ifndef __TIMER_CONFIGURATION
#define __TIMER_CONFIGURATION

#include "stm32g4xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;

float CountPeriodS(TIM_HandleTypeDef *htim);
void MX_TIM1_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_TIM5_Init(void);
void MX_TIM7_Init(void);
void MX_TIM8_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);


#endif /* __TIMER_CONFIGURATION */
