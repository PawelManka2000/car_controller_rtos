#include "pid_controller.h"
#include "motor_features.h"

void pid_init(PIDController *pid_data, float kp_init, float ki_init, float kd_init, int anti_windup_limit_init)
{
	pid_data->previous_error = 0;
	pid_data->total_error = 0;

	pid_data->Kp = kp_init;
	pid_data->Ki = ki_init;
	pid_data->Kd = kd_init;

	pid_data->anti_windup_limit = anti_windup_limit_init;
}

void pid_reset(PIDController *pid_data)
{
	pid_data->total_error = 0;
	pid_data->previous_error = 0;
}


float error = 0;
float p_term;
float i_term;
float d_term;
float pid_output;


uint8_t pid_calculate(PIDController *pid_data, float setpoint, float process_variable)
{

	error = setpoint - process_variable;
	pid_data->total_error += error;

	p_term = (float)(pid_data->Kp * error);
	i_term = (float)(pid_data->Ki * pid_data->total_error);
	d_term = (float)(pid_data->Kd * (error - pid_data->previous_error));

	pid_output = p_term + i_term + d_term;

    // Anti-windup
    if (pid_output < -pid_data->anti_windup_limit)
    {
        pid_output = -pid_data->anti_windup_limit;
        pid_data->total_error = pid_data->total_error - error;

    } else if (pid_output > pid_data->anti_windup_limit)
    {
        pid_output = pid_data->anti_windup_limit;
        pid_data->total_error = pid_data->total_error - error;
    }


	pid_data->previous_error = error;
	uint8_t saturated_pwm_value = saturate_pwm(pid_output);
	return saturated_pwm_value;
}
