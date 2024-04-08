#ifndef __GPIO_CONFIGURATION
#define __GPIO_CONFIGURATION

#include "stm32g4xx_hal.h"


#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA


void MX_GPIO_Init(void);

#endif /* __GPIO_CONFIGURATION */
