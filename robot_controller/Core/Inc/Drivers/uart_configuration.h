#ifndef __UART_CONFIGURATION
#define __CLOCK_CONFIGURATION

#include "stm32g4xx_hal.h"

extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart1;

void MX_LPUART1_UART_Init(void);
void MX_USART1_UART_Init(void);

#endif /* __UART_CONFIGURATION */
