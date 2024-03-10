/*
 * timers_feature.h
 *
 *  Created on: Mar 9, 2024
 *      Author: pawel
 */

#ifndef INC_FEATURES_TIMERS_FEATURE_H_
#define INC_FEATURES_TIMERS_FEATURE_H_

#include "stm32g4xx_hal.h"

// Funkcja obliczająca okres w sekundach
float CountPeriodS(TIM_HandleTypeDef *htim);

#endif /* INC_FEATURES_TIMERS_FEATURE_H_ */
