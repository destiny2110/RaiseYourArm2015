/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *  version 0.0.1
 */

/**
 * @file	PID.h
 * @brief	PID wall controller
 */


#ifndef WALLFOLLOW_PID_H_
#define WALLFOLLOW_PID_H_

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	float u;
	float u_;
	float e;
	float e_;
	float e__;
	float Ts;
	float PID_Saturation;
} PID_PARAMETERS;

extern float pid_process(PID_PARAMETERS* pid_parameter,float error);                                     //***********
extern void pid_reset(PID_PARAMETERS* pid_parameter);                                                                                 //************
extern void pid_set_k_params(PID_PARAMETERS* pid_parameters,float Kp,float Ki, float Kd);                //************
#endif /* WALLFOLLOW_PID_H_ */
