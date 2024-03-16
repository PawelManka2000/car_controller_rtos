/*
 * low_pass_filter.h
 *
 *  Created on: Mar 16, 2024
 *      Author: pawel
 */

#ifndef INC_DRIVERS_LOW_PASS_FILTER_H_
#define INC_DRIVERS_LOW_PASS_FILTER_H_

#include <stdio.h>

#define N 10

typedef struct {
    float buffer[N];
    int index;
} LowPassFilter;


void init_low_pass_filter(LowPassFilter *filter);


float update_low_pass_filter(LowPassFilter *filter, float new_value);

#endif /* INC_DRIVERS_LOW_PASS_FILTER_H_ */
