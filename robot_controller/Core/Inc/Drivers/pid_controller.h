/*
 * pid_controller.h
 *
 *  Created on: Mar 10, 2024
 *      Author: pawel
 */

#ifndef INC_DRIVERS_PID_CONTROLLER_H_
#define INC_DRIVERS_PID_CONTROLLER_H_

typedef struct
{
	int previous_error;
	int total_error;
	float Kp;
	float Ki;
	float Kd;
	int anti_windup_limit;
}PIDController;

void pid_init(PIDController *pid_data, float kp_init, float ki_init, float kd_init, int anti_windup_limit_init);
void pid_reset(PIDController *pid_data);
int pid_calculate(PIDController *pid_data, float setpoint, float process_variable);

#endif /* INC_DRIVERS_PID_CONTROLLER_H_ */
