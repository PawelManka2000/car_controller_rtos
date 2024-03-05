/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* USER CODE BEGIN 3 */
#include "main.h"
#include "clock_configuration.h"
#include "gpio_configuration.h"
#include "uart_configuration.h"
#include "timers_configuration.h"


float rotate = 0;
float speed = 0;
int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();

  HAL_TIM_Base_Start(&htim8);
  /* USER CODE BEGIN 2 */

  static __IO uint16_t pulseCounter = 0;
  static __IO uint16_t previous_pulseCounter = 0;

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);


  TIM1->CCR1 = 40;
  TIM1->CCR2 = 40;
  TIM1->CCR3 = 40;
  TIM1->CCR4 = 40;




  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  char message[100];
  static int diff;
  static uint8_t received_data[3];
  static int received_data_int;

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  previous_pulseCounter = pulseCounter;
	  pulseCounter = __HAL_TIM_GET_COUNTER(&htim8);
	  diff = (pulseCounter - previous_pulseCounter);
	  speed = (pulseCounter - previous_pulseCounter)/20;

	  sprintf(message, "Dane to %d \n\r", (int)round(speed));
	  sprintf(&(message[strlen(message)]), "pulse to %d \n\r", (int)round(pulseCounter));
	  sprintf(&(message[strlen(message)]), "roznica to %d \n\r", (int)round(diff));

	  HAL_UART_Receive(&hlpuart1, received_data, 3, 100);
	  sscanf((char*)received_data, "%d", &received_data_int);

	  sprintf(&(message[strlen(message)]), "to %d \n\r", received_data_int);

	  HAL_UART_Transmit(&hlpuart1, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
	  HAL_Delay(1000);




  }

}


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/* USER CODE END 3 */
