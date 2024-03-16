/*
 * low_pass_filter.c
 *
 *  Created on: Mar 16, 2024
 *      Author: pawel
 */
#include "low_pass_filter.h"

void init_low_pass_filter(LowPassFilter *filter) {
    int i;
    for (i = 0; i < N; i++) {
        filter->buffer[i] = 0.0f;
    }
    filter->index = 0;
}

 float update_low_pass_filter(LowPassFilter *filter, float new_value){
    filter->buffer[filter->index] = new_value;
    filter->index = (filter->index + 1) % N;


    float sum = 0.0f;
    int i;
    for (i = 0; i < N; i++) {
        sum += filter->buffer[i];
    }
    return sum / N;
}
