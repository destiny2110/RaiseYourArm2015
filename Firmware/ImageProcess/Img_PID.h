/*
 * Img_PID.h
 *
 *  Created on: 05-09-2015
 *      Author: The_Cuong
 */

#ifndef IMAGEPROCESS_IMG_PID_H_
#define IMAGEPROCESS_IMG_PID_H_
typedef struct
{
	float kp;
	float ki;
	float kd;
	float iu;
	float _iu;
	float ie;
	float _ie;
	float __ie;
	float iTs;
	float PID_Sat;
} PID_PARAM;

extern float pid_imgProcess(PID_PARAM* pid_param,float ierror);
extern void pid_imgReset(PID_PARAM* pid_param);
extern void pid_imgSet_k_params(PID_PARAM* pid_param,float kp,float ki, float kd);





#endif /* IMAGEPROCESS_IMG_PID_H_ */
