/*
 * timers_features.c
 *
 *  Created on: Mar 9, 2024
 *      Author: pawel
 */

#include "timers_feature.h"

// Funkcja obliczająca okres w sekundach
float CountPeriodS(TIM_HandleTypeDef *htim) {
    uint32_t prescaler = htim->Init.Prescaler;
    uint32_t period = htim->Init.Period;
    uint32_t clock_freq = HAL_RCC_GetHCLKFreq();

    float period_seconds = (float)(prescaler * period) / (float)clock_freq;

    return period_seconds;
}
