/*
 * engine_features.c
 *
 *  Created on: Mar 9, 2024
 *      Author: pawel
 */

#include "engine_features.h"

float convert_to_radians(int32_t enc_position){

	return 2* M_PI * (float)enc_position / (float) ONE_ROTATION_TICKS;

}
