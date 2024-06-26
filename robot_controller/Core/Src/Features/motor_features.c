/*
 * engine_features.c
 *
 *  Created on: Mar 9, 2024
 *      Author: pawel
 */

#include "motor_features.h"



float convert_to_radians(int32_t enc_position){

	return 2* M_PI * (float)enc_position / (float) ONE_ROTATION_TICKS;

}


uint8_t saturate_pwm(int pwm_value){


	if (pwm_value < PWM_MIN_VALUE){
		pwm_value = (uint8_t)PWM_MIN_VALUE;
	}else if(pwm_value > PWM_MAX_VALUE){
		pwm_value = (uint8_t)PWM_MAX_VALUE;
	}
	return (uint8_t)pwm_value;

}
