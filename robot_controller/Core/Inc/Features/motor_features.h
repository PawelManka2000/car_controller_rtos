/*
 * engine_features.h
 *
 *  Created on: Mar 9, 2024
 *      Author: pawel
 */

#ifndef INC_FEATURES_MOTOR_FEATURES_H_
#define INC_FEATURES_MOTOR_FEATURES_H_

#include <math.h>
#include "stm32g4xx_hal.h"


#define PWM_MIN_VALUE 0
#define PWM_MAX_VALUE 98
#define ONE_ROTATION_TICKS 3890

float convert_to_radians(int32_t enc_displacement);
uint8_t saturate_pwm(int pwm_value);

#endif /* INC_FEATURES_MOTOR_FEATURES_H_ */
