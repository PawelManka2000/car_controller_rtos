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
#include "driving_system.h"
#include "cmd_listener.h"



float rotate = 0;
float speed = 0;
uint16_t timer_counter = 0;
char message[100];

//EngineInfo motor;
EncoderInfo encoder_info;
MotorStruct lb_motor;
PIDController pid_controller;
L298N_driver L298N_lb;
MotorState lb_motor_state;
DrivingSystem driving_system;
DrivingSystemIface drv_system_if;

float updater_timer_periods;
uint8_t cmd_data[10];

uint8_t pwm_output;
uint8_t velo;
uint64_t tick;
void generate_stair_signal(void);
void generate_random_signal_velo(void);


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

  init_encoder_info(&encoder_info, &htim4);
  L298N_init(&L298N_lb, TIM_CHANNEL_1, &htim1, GPIOA, GPIO_PIN_0, GPIOA, GPIO_PIN_1);
  pid_init(&pid_controller, MOTOR_Kp , MOTOR_Ki, MOTOR_Kd, MOTOR_ANTI_WINDUP);
  init_motor(&lb_motor, &lb_motor_state, &htim7, &encoder_info, &pid_controller, &L298N_lb);

  pwm_output = 0;
  tick = 0;
  velo = 0;

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_TIM_Base_Start(&htim8);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);


  updater_timer_periods = CountPeriodS(lb_motor.motor_updater_tim);
  L298N_set_input_configuration(&L298N_lb, FORWARD);
  init_driving_system(&driving_system ,&lb_motor, &lb_motor, &lb_motor, &lb_motor);
  default_init_driving_system_if(&drv_system_if);

  /* USER CODE END 2 */

  HAL_UART_Receive_IT(&hlpuart1, cmd_data, CMD_CODE_LENGTH + CMD_PAYLOAD_LENGTH);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
  {
    	generate_stair_signal_pwm();
//    	generate_stair_signal();
    	generate_random_signal_velo();
  }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{


	drv_system_if.exe_cmd(&driving_system, cmd_data);
	HAL_UART_Receive_IT(&hlpuart1, cmd_data, CMD_CODE_LENGTH + CMD_PAYLOAD_LENGTH);

}

void generate_stair_signal_pwm(void){

	if(tick == 100){
		pwm_output +=20;
		tick = 0;
		if (pwm_output >= 90){
			pwm_output = 0;
		}
	}
}

void generate_random_signal_velo(void){

	if(tick == 100){

		velo +=  2;
		tick = 0;
		if (velo >= 10){
			velo = 0;
		}
	}
}

//	char my_msg[100];
//	sprintf(my_msg, "%d \n\r", pwm_output);
//	HAL_UART_Transmit(&hlpuart1, my_msg, strlen(my_msg),10);





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

    if (htim->Instance == (TIM_TypeDef *)lb_motor.motor_updater_tim->Instance) {

    	update_motor_position(lb_motor.motor_state, lb_motor.encoder_info);
    	update_measured_velocity(&lb_motor);
    	set_velocity(&lb_motor_state, velo);

    	regulate_velocity(&lb_motor);
    	tick += 1;
//    	L298N_update_pwm(lb_motor.L298N_driver, pwm_output);

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
