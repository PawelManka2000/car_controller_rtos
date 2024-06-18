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
#include "parser_features.h"


float rotate = 0;
float speed = 0;
uint16_t timer_counter = 0;
char message[100];

//EngineInfo motor;
PIDController lb_pid_controller;
EncoderInfo lb_encoder_info;
MotorStruct lb_motor;
L298N_driver lb_L298N;
MotorState lb_motor_state;

//PIDController pid_controller;
PIDController lf_pid_controller;
EncoderInfo lf_encoder_info;
MotorStruct lf_motor;
L298N_driver lf_L298N;
MotorState lf_motor_state;


PIDController rb_pid_controller;
EncoderInfo rb_encoder_info;
MotorStruct rb_motor;
L298N_driver rb_L298N;
MotorState rb_motor_state;





DrivingSystem driving_system;
DrivingSystemIface drv_system_if;

float updater_timer_periods;
uint8_t cmd_data[CMD_CODE_LENGTH + MSG_PAYLOAD_LENGTH];

uint8_t pwm_output;
uint8_t velo;
uint64_t tick;
void generate_stair_signal_pwm(void);
void generate_random_signal_velo(void);


void prepare_for_motor_ini_lb(){


	init_encoder_info(&lb_encoder_info, &htim4);
	L298N_init(&lb_L298N, TIM_CHANNEL_1, &htim1, GPIOA, GPIO_PIN_0, GPIOA, GPIO_PIN_1);
	pid_init(&lb_pid_controller, MOTOR_Kp , MOTOR_Ki, MOTOR_Kd, MOTOR_ANTI_WINDUP);
	init_motor(&lb_motor, &lb_motor_state, &htim7, &lb_encoder_info, &lb_pid_controller, &lb_L298N);

	updater_timer_periods = CountPeriodS(lb_motor.motor_updater_tim);
}

void prepare_for_motor_ini_lf(){

	init_encoder_info(&lf_encoder_info, &htim5);
	L298N_init(&lf_L298N, TIM_CHANNEL_2, &htim1, GPIOA, GPIO_PIN_0, GPIOA, GPIO_PIN_1);
	pid_init(&lf_pid_controller, MOTOR_Kp , MOTOR_Ki, MOTOR_Kd, MOTOR_ANTI_WINDUP);
	init_motor(&lf_motor, &lf_motor_state, &htim7, &lf_encoder_info, &lf_pid_controller, &lf_L298N);

	updater_timer_periods = CountPeriodS(lf_motor.motor_updater_tim);
}

void prepare_for_motor_ini_rb(){

	init_encoder_info(&rb_encoder_info, &htim8);
	L298N_init(&rb_L298N, TIM_CHANNEL_3, &htim1, GPIOA, GPIO_PIN_8, GPIOA, GPIO_PIN_9);
	pid_init(&rb_pid_controller, MOTOR_Kp , MOTOR_Ki, MOTOR_Kd, MOTOR_ANTI_WINDUP);
	init_motor(&rb_motor, &rb_motor_state, &htim7, &rb_encoder_info, &rb_pid_controller, &rb_L298N);

	updater_timer_periods = CountPeriodS(lf_motor.motor_updater_tim);
}





//void prepare_for_motor_ini_rb(){
//
//	init_encoder_info(&eb_encoder_info, &htim5);
//	L298N_init(&rb_L298N, TIM_CHANNEL_2, &htim1, GPIOA, GPIO_PIN_0, GPIOA, GPIO_PIN_1);
//	pid_init(&pid_controller, MOTOR_Kp , MOTOR_Ki, MOTOR_Kd, MOTOR_ANTI_WINDUP);
//	init_motor(&lf_motor, &lf_motor_state, &htim7, &lf_encoder_info, &pid_controller, &lf_L298N);
//
//	updater_timer_periods = CountPeriodS(lf_motor.motor_updater_tim);
//	L298N_set_input_configuration(&lf_L298N, L298N_MODE_FORWARD);
//}


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


  prepare_for_motor_ini_lb();
  prepare_for_motor_ini_lf();
  prepare_for_motor_ini_rb();

  init_driving_system(&driving_system ,&lb_motor, &lf_motor, &rb_motor, &lb_motor);
  default_init_driving_system_if(&drv_system_if);

  velo = 0;
  pwm_output = 0;
  tick = 0;

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim7);

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);



  /* USER CODE END 2 */

  HAL_UART_Receive_IT(&hlpuart1, cmd_data, CMD_CODE_LENGTH + MSG_PAYLOAD_LENGTH);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  driving_system.velo_ctrl_flag = 1;
    while (1)
  {
//    	generate_stair_signal_pwm();
//    	generate_stair_signal();
//    	generate_random_signal_velo();
  }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	drv_system_if.exe_cmd(&driving_system, cmd_data);
	HAL_UART_Receive_IT(&hlpuart1, cmd_data, CMD_CODE_LENGTH + MSG_PAYLOAD_LENGTH);

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
			velo = 3;
		}
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

    if (htim->Instance == (TIM_TypeDef *)lb_motor.motor_updater_tim->Instance) {


//    	update_motor_position(lb_motor.motor_state, lb_motor.encoder_info);
//    	update_measured_velocity(&lb_motor);
//    	motor_state_set_velocity(&lb_motor_state, velo);
//    	L298N_set_pwm_count(lb_motor.L298N_driver, pwm_output);

    	driving_system_drive(&driving_system);
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
