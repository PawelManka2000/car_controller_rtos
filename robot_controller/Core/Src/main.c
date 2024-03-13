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
#include <motor_driver.h>
#include <timers_configuration.h>
#include "main.h"
#include "clock_configuration.h"
#include "gpio_configuration.h"
#include "uart_configuration.h"
#include "encoder_driver.h"


float rotate = 0;
float speed = 0;
uint16_t timer_counter = 0;
char message[100];

//EngineInfo motor;
EncoderInfo encoder_info = {.counter_value = 0, .last_counter_value =0, .encoder_timer =&htim4 };
MotorInfo motor;
PIDController pid_controller;

L298N_driver L298N_left_back = {
		.pwm_timer = &htim1,
		.pwm_channel=TIM_CHANNEL_1,
		.GPIOx_1 = GPIOA,
		.GPIOx_2 = GPIOA,
		.GPIO_Pin_1 = GPIO_PIN_0,
		.GPIO_Pin_2 = GPIO_PIN_1
};
int period;
float updater_timer_periods;

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM7_Init();
  MX_TIM8_Init();

  pid_init(&pid_controller, MOTOR_Kp , MOTOR_Ki, MOTOR_Kd, MOTOR_ANTI_WINDUP);
  init_motor(&motor, &htim7, &encoder_info, &pid_controller, &L298N_left_back);

  /* USER CODE BEGIN 2 */

  static __IO uint16_t pulseCounter = 0;
  static __IO uint16_t previous_pulseCounter = 0;


  HAL_TIM_Base_Start_IT(&htim7);
  HAL_TIM_Base_Start(&htim8);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);


  L298N_set_input_configuration(&L298N_left_back, FORWARD);
  set_velocity(&motor, 4);

  TIM1->CCR2 = 40;
  TIM1->CCR3 = 40;
  TIM1->CCR4 = 40;


  timer_counter = 1;

  /* USER CODE END 2 */

  static int diff;
  static int received_data_int;

  period = CountPeriodS(&htim7);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
  {


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

    if (htim->Instance == (TIM_TypeDef *)motor.engine_updater_tim->Instance) {

    	update_position(&motor);
    	update_measured_velocity(&motor);
    	regulate_velocity(&motor);

//

//        timer_counter = __HAL_TIM_GET_COUNTER(&htim4);
//        updater_timer_periods = CountPeriodS(motor.engine_updater_tim);
//  	    sprintf(message, "%.3f ", motor.measured_velocity);
//  	    HAL_UART_Transmit(&hlpuart1, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
    }



//  /* USER CODE END Callback 1 */
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
