/*
 * driving_modes.h
 *
 *  Created on: Jun 11, 2024
 *      Author: Admin
 */

#ifndef INC_FEATURES_DRIVING_MODES_H_
#define INC_FEATURES_DRIVING_MODES_H_

#include "stm32g4xx_hal.h"
#include "driving_system.h"



typedef enum {

	DV_DIR_STOP = 0,
	DV_DIR_FORWARD = 1,
	DV_DIR_BACKWARD = 2,
	DV_DIR_LEFT = 3,
	DV_DIR_RIGHT = 4,

}EDvDir;

void drive_velo_dir(DrivingSystem* driving_system, EDvDir dv_dir, float velocity);
void drive_velo(DrivingSystem* driving_system, float velocity, EL298N_MODE left_dir, EL298N_MODE right_dir);

void drive_pwm_dir(DrivingSystem* driving_system, EDvDir dv_dir, uint8_t pwm);
void drive_pwm(DrivingSystem* driving_system, uint8_t pwm, EL298N_MODE left_dir, EL298N_MODE right_dir);


#endif /* INC_FEATURES_DRIVING_MODES_H_ */
