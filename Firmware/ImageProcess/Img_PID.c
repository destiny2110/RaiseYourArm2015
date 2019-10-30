/*
 * Img_PID.c
 *
 *  Created on: 05-09-2015
 *      Author: Th_ieCuong
 */
#include "../include.h"
#include "Img_PID.h"
void pid_imgSet_k_params(PID_PARAM* pid_param,float kp,float ki, float kd)
{
	pid_param->kp = kp;
	pid_param->ki = ki;
	pid_param->kd = kd;
}

float pid_imgProcess(PID_PARAM* pid_param,float ierror)
{
	pid_param->__ie = pid_param->_ie;
	pid_param->_ie = pid_param->ie;
	pid_param->ie = ierror;
	pid_param->_iu = pid_param->iu;
	pid_param->iu = pid_param->_iu + pid_param->kp * (pid_param->ie - pid_param->_ie)
			+ pid_param->ki * pid_param->iTs * pid_param->ie
			+ (pid_param->kd / pid_param->iTs) * (pid_param->ie - (2 * pid_param->_ie) + pid_param->__ie);


	if (pid_param->iu > pid_param->PID_Sat)
	{
		pid_param->iu = pid_param->PID_Sat;
	}
	else if (pid_param->iu < (-pid_param->PID_Sat))
	{
		pid_param->iu = -pid_param->PID_Sat;
	}

	return pid_param->iu;
}

void pid_imgReset(PID_PARAM* pid_param)
{
	pid_param->ie = 0;
	pid_param->_ie = 0;
	pid_param->__ie = 0;
	pid_param->iu = 0;
	pid_param->_iu = 0;
}
