/*
 * ImgProcess.c
 *
 *  Created on: 05-09-2015
 *      Author: The_Cuong
 */
#include "ImgProcess.h"
#include "../include.h"
#include "HostComm.h"
#include "Img_PID.h"

//#define TEST_GOSTRAIGHT
//#define TEST_LeftTurn
//#define TEST_RightTurn
#define TEST_TURNBACK

//#define TEST_ALGORITHMS

//#define TEST_AGORITHMS_2

//#define TEST_COORDETECT
//#define TEST_TURN




PID_PARAM pid_ImgProcessParam = {.kp = 1, .kd = 0.0, .ki = 0.001,
		.iTs = 0.020, .PID_Sat = 100, ._ie = 0, .__ie = 0, ._iu = 0};
PID_PARAM pid_ImgPosLeft = {.kp = 2, .kd = 0.0, .ki = 0.0001,
		.iTs = 0.020, .PID_Sat = 100, ._ie = 0, .__ie = 0, ._iu = 0};
PID_PARAM pid_ImgPosRight = {.kp = 2, .kd = 0.0, .ki = 0.0001,
		.iTs = 0.020, .PID_Sat = 100, ._ie = 0, .__ie = 0, ._iu = 0};

PID_PARAM pid_ImgProcessBackParam = {.kp = 2, .kd = 0.0, .ki = 0.001,
		.iTs = 0.020, .PID_Sat = 100, ._ie = 0, .__ie = 0, ._iu = 0};

// Private function //
static bool pid_BackStraight (float angle, float averageSpeed);
static bool pid_GoStraight (float angle, float averageSpeed);
static bool LeftTurn(int avrSpeedLeft, int avrSpeedRight,int turnPulse);
static bool RightTurn(int avrSpeedLeft, int avrSpeedRight,int turnPulse);
static bool BackStraightTurn(int deltaLeft,int deltaRight,int vLeftmax, int vRightmax);

// Private variable //
static int32_t encLeftTmp=0, x_temp;
static int32_t posLeftTmp=0,posRightTmp=0;
static int32_T avrSpeed, avrSpeedTmp;
static int32_t CtrlStep=1,moveStage=1;
static int32_t fwdPulse,turnPulse;
static I_MOVE Img_Move = ForwardMOVE;

static I_MOVE reImg_Move = ForwardMOVE;

static I_DIR Img_dir = SouthWard;
static TIMER_ID pid_ImageTimerID = INVALID_TIMER_ID;
static bool img_Controlflag = false;
static uint32_t ui32_msLoop = 0;



static I_MOVE get_IMove (int R_x, int R_y, int G_x, int G_y)
{

#ifdef TEST_COORDETECT
	if (R_y == G_y)
	{
		speed_set(MOTOR_LEFT,0);
		speed_set(MOTOR_RIGHT,0);
		speed_Enable_Hbridge(false);
		system_SetState(SYSTEM_INITIALIZE);
	}
#endif


#ifdef TEST_GOSTRAIGHT
	return ForwardMOVE;
#endif

#ifdef TEST_LeftTurn
	return LeftMOVE;
#endif

#ifdef TEST_RightTurn
	return RightMOVE;
#endif

#ifdef TEST_TURNBACK
	return BackMOVE;
#endif

#ifdef TEST_ALGORITHMS

	if ((reImg_Move==ForwardMOVE)&&(Img_dir==SouthWard))
	{
		if ( (R_y > (G_y-5)) && (R_y < (G_y + 5))    )    //   g-3<r<g+3   //   ((r>(g-3)) && (r<(g+3)))
		{
			return LeftMOVE;
		}
		else
		{
			return ForwardMOVE;
		}
	}

	if ((reImg_Move==ForwardMOVE)&&(Img_dir==EastWard))
	{
		if (abs(qei_getPosLeft()-encLeftTmp)<60000)
		{
			return ForwardMOVE;
		}
		else
		{
			return RightMOVE;
		}

		/*
		if (abs(x-x_temp)!=0)
		{
			return ForwardMOVE;
		}
		else
			return RightMOVE;
		*/
	}


	if ((reImg_Move==LeftMOVE)&&(Img_dir == EastWard))    // vua re trai xong
	{
		/*
		speed_set(MOTOR_LEFT,0);
		speed_set(MOTOR_RIGHT,0);
		speed_Enable_Hbridge(false);
		system_SetState(SYSTEM_INITIALIZE);
		while(1);
		*/

		return BackMOVE;
	}

	if ((reImg_Move==BackMOVE)&&(Img_dir == EastWard))
	{
		//return BackMOVE;

		if(abs(qei_getPosLeft()-encLeftTmp) < 60000)
		{
			return BackMOVE;
		}
		else
		{
			qei_setPosLeft(0);
			encLeftTmp = qei_getPosLeft();
			return ForwardMOVE;
		}

	}


	if ((reImg_Move==RightMOVE)&&(Img_dir==SouthWard))
	{
		return ForwardMOVE;
		//speed_set(MOTOR_LEFT,0);
		//speed_set(MOTOR_RIGHT,0);
	}

#endif

#ifdef TEST_AGORITHMS_2

	if((R_x < G_x +5))
	{
		if((R_y < G_y-5) || (R_y > G_y+5))
			if(Img_dir==SouthWard)
				return LeftMOVE;
			else if(Img_dir==EastWard)
				return ForwardMOVE;
			else if(Img_dir==NorthWard)
				return RightMOVE;
			else
				return BackMOVE;
		else
			if(Img_dir==SouthWard)
				return BackMOVE;
			else if(Img_dir==EastWard)
				return LeftMOVE;
			else if(Img_dir==NorthWard)
				return ForwardMOVE;
			else
				return RightMOVE;
	}
	else
	{
		if(R_y < G_y-5)
			if(Img_dir==SouthWard)
				return ForwardMOVE;
			else if(Img_dir==EastWard)
				return RightMOVE;
			else if(Img_dir==NorthWard)
				return BackMOVE;
			else
				return LeftMOVE;
		else if(R_y > G_y+5)
			if(Img_dir==SouthWard)
				return BackMOVE;
			else if(Img_dir==EastWard)
				return LeftMOVE;
			else if(Img_dir==NorthWard)
				return ForwardMOVE;
			else
				return RightMOVE;
		else
			if(Img_dir==SouthWard)
				return RightMOVE;
			else if(Img_dir==EastWard)
				return BackMOVE;
			else if(Img_dir==NorthWard)
				return LeftMOVE;
			else
				return ForwardMOVE;
	}

#endif

}


//**************************************************************************************
//
//**************************************************************************************
static void pid_ImageStopTimeout(void)
{
	if (pid_ImageTimerID != INVALID_TIMER_ID)
		TIMER_UnregisterEvent(pid_ImageTimerID);
	pid_ImageTimerID = INVALID_TIMER_ID;
}

static TIMER_ID pid_ImageRuntimeout(TIMER_CALLBACK_FUNC CallbackFcn, uint32_t msTime)
{
	pid_ImageStopTimeout();
	pid_ImageTimerID = TIMER_RegisterEvent(CallbackFcn, msTime);
	return pid_ImageTimerID;
}

static void pid_Imageprocess_callback(void)
{
	pid_ImageTimerID = INVALID_TIMER_ID;
	img_Controlflag = true;
	pid_ImageRuntimeout(&pid_Imageprocess_callback, ui32_msLoop);
}


void pid_ImageProcess_init()
{
	ui32_msLoop =  pid_ImgProcessParam.iTs * 1000;
	pid_ImageRuntimeout(&pid_Imageprocess_callback, ui32_msLoop);
}

//*************************************************************************
//
//*************************************************************************

static bool LeftTurn(int avrSpeedLeft, int avrSpeedRight,int turnPulse)
{
	static int vt, vp;
	switch (CtrlStep)
	{
	case 1:
		posLeftTmp = qei_getPosLeft();
		posRightTmp = qei_getPosRight();
		vp = 1; vt = 1;
		CtrlStep++;
	case 2:
		if (abs(qei_getPosLeft()-posLeftTmp) + abs(qei_getPosRight()-posRightTmp) < turnPulse)
		{
			speed_set(MOTOR_RIGHT,avrSpeedRight);
			speed_set(MOTOR_LEFT, 0);
			if((abs(qei_getPosRight()-posRightTmp) > (turnPulse*0.8*vp/8)) && vp<9)
			{
				if (avrSpeedRight<=24)
					avrSpeedRight -=24;
				vp++;
			}
			if ((abs(qei_getPosLeft()-posLeftTmp) > (turnPulse*0.2*vt/8)) && vt<9)
			{
				if (avrSpeedLeft>=4)
					avrSpeedLeft-=4;
				vt++;
			}
		}
		else
		{
			qei_setPosLeft(0);
			qei_setPosRight(0);
			speed_set(MOTOR_LEFT,avrSpeed);
			speed_set(MOTOR_RIGHT,avrSpeed);
			CtrlStep = 1;
			return true;
		}
		break;
	}
	return false;
}

static bool RightTurn(int avrSpeedLeft, int avrSpeedRight,int turnPulse)
{
	static int vt,vp;
	switch (CtrlStep)
	{
	case 1:
		posLeftTmp = qei_getPosLeft();
		posRightTmp = qei_getPosRight();
		vp =1; vt = 1;
		CtrlStep++;
	case 2:
		if (abs(qei_getPosLeft()-posLeftTmp) + abs(qei_getPosRight()-posRightTmp) < turnPulse)
		{
			speed_set(MOTOR_LEFT,avrSpeedLeft);
			speed_set(MOTOR_RIGHT,-avrSpeedRight);
			if((abs(qei_getPosLeft()-posLeftTmp)>(turnPulse*0.8*vp/8)) && (vp<9))
			{
				if (avrSpeedLeft >= 24)
					avrSpeedLeft -=24;
				vp++;
			}
			if((abs(qei_getPosRight()-posRightTmp)>(turnPulse*0.2*vt/8)) && (vp<9))
			{
				if (avrSpeedRight>=4)
					avrSpeedRight -=4;
				vt++;
			}
		}
		else
		{
			qei_setPosLeft(0);
			qei_setPosRight(0);
			speed_set(MOTOR_LEFT,avrSpeed);
			speed_set(MOTOR_RIGHT,avrSpeed);
			CtrlStep = 1;
			return true;
		}
		break;
	}
	return false;
}

static bool BackStraightTurn(int deltaLeft,int deltaRight,int vLeftmax, int vRightmax)
{
	static int oriLeft, oriRight;
	static bool done = true;
	int currentLeft=qei_getPosLeft();
	int currentRight=qei_getPosRight();

	if(done)
	{
		done = false;
		oriLeft=currentLeft;
		oriRight=currentRight;
	}
	if (abs(oriLeft+deltaLeft-currentLeft)>6000)
	{
		pid_ImgPosLeft.PID_Sat = vLeftmax;
		speed_set(MOTOR_LEFT,pid_imgProcess(&pid_ImgPosLeft,oriLeft+deltaLeft-currentLeft));
		pid_ImgPosRight.PID_Sat = vRightmax;
		speed_set(MOTOR_RIGHT,pid_imgProcess(&pid_ImgPosRight,oriRight+deltaRight-currentRight));
		done = false;
	}
	else
	{
		done = true;
		pid_imgReset(&pid_ImgPosLeft);
		pid_imgReset(&pid_ImgPosRight);
	}
	return done;
}


static bool pid_turn(float angle_2, float averageSpeed)
{
	static float e, u;
	int32_t speed;
	e= angle_2;
	u = pid_imgProcess(&pid_ImgProcessParam,e);

	speed = averageSpeed + (int32_t)(u / 2);

	speed_set(MOTOR_RIGHT, speed);
	speed_set(MOTOR_LEFT, 0);

}



static bool pid_GoStraight (float angle, float averageSpeed)
{
	static float e, u;
	int32_t set_speed[2];
	if ((angle!=0)&&(angle!=90))
	{
		if (angle > 45)
		{angle -= 90;}

		e = angle;
		u = pid_imgProcess(&pid_ImgProcessParam,e);
		set_speed[0] = averageSpeed + (int32_t)(u / 2);
		set_speed[1] = averageSpeed - (int32_t)(u / 2);

		speed_set(MOTOR_RIGHT, set_speed[0]);
		speed_set(MOTOR_LEFT, set_speed[1]);
	}
	else
	{
		speed_set(MOTOR_RIGHT, averageSpeed);
		speed_set(MOTOR_LEFT, averageSpeed);
	}

/*
	static float e, u;
	int32_t set_speed;
			if (angle != 0 && angle != 90)
			{
				if (angle < 45)
				{
					e = angle;
					u = pid_imgProcess(&pid_ImgProcessParam,e);
					set_speed = averageSpeed + (int32_t)(u / 2);

					speed_set(MOTOR_RIGHT, averageSpeed);
					speed_set(MOTOR_LEFT, set_speed);
				}

				if (angle > 45)
				{
					e = 90 - angle;
					u = pid_imgProcess(&pid_ImgProcessParam,e);
					set_speed = averageSpeed + (int32_t)(u / 2);

					speed_set(MOTOR_RIGHT, set_speed);
					speed_set(MOTOR_LEFT, averageSpeed);
				}

			}
			else
			{
				speed_set(MOTOR_RIGHT, averageSpeed);
				speed_set(MOTOR_LEFT, averageSpeed);
			}

*/

	return true;
}

static bool pid_BackStraight (float angle, float averageSpeed)
{
	LED1_ON();LED2_ON();LED3_ON();
	static float e, u;
	int32_t set_Bspeed[2];


	if ((angle!=0)&&(angle!=90))
	{
		if (angle > 45)
		{angle -= 90;}

		e = angle;
		u = pid_imgProcess(&pid_ImgProcessBackParam,e);
		set_Bspeed[0] = averageSpeed + (int32_t)(u / 2);
		set_Bspeed[1] = averageSpeed - (int32_t)(u / 2);

		speed_set(MOTOR_RIGHT, -set_Bspeed[0]);
		speed_set(MOTOR_LEFT, -set_Bspeed[1]);
	}
	else
	{
		speed_set(MOTOR_RIGHT, -averageSpeed);
		speed_set(MOTOR_LEFT, -averageSpeed);
	}

	return true;
}

void pid_ImageProcess(void)
{
	if (img_Controlflag)
	{
		img_Controlflag = false;
		if (HostComm_process()==SUCCESS)
		{
			LED2_ON();
			switch (Img_Move) // default I_Move = forwardMOVE //
			{
			case ForwardMOVE:   // di thang

				if (pid_GoStraight(angle,70))
				{
					reImg_Move = ForwardMOVE;
					Img_Move = get_IMove(x,y,x_dest,y_dest);
				}
				//				if (pid_turn(angle_2,70))
				//				{
				//					;
				//				}

				break;

			case LeftMOVE:    // re trai va lui lai
				LED1_ON();
				if (LeftTurn(0,140,7500))
				{
					/*
					speed_set(MOTOR_LEFT,0);
					speed_set(MOTOR_RIGHT,0);
					speed_Enable_Hbridge(false);
					system_SetState(SYSTEM_INITIALIZE);
					 */
					if (Img_dir == SouthWard)
					{
						Img_dir = EastWard;
					}
					else if (Img_dir == EastWard)
					{
						Img_dir = NorthWard;
					}
					else if (Img_dir == WestWard)
					{
						Img_dir = SouthWard;
					}
					else if (Img_dir == NorthWard)
					{
						Img_dir = WestWard;
					}

					reImg_Move = LeftMOVE;

					x_temp = x;
					pid_reset(&pid_ImgProcessBackParam);
					qei_setPosLeft(0);
					encLeftTmp = qei_getPosLeft();
					Img_Move = get_IMove(x,y,x_dest,y_dest);
				}
				//				if (pid_turn(angle_2,70))
				//					{
				//					;
				//					}


				break;

			case RightMOVE:   // re phai
				LED2_ON();
				if (RightTurn(140,0,7600))
				{
					if (Img_dir == SouthWard)
					{
						Img_dir = WestWard;
					}
					else if (Img_dir == EastWard)
					{
						Img_dir = SouthWard;
					}
					else if (Img_dir == WestWard)
					{
						Img_dir = NorthWard;
					}
					else if (Img_dir == NorthWard)
					{
						Img_dir = EastWard;
					}

					x_temp = x;
					pid_reset(&pid_ImgProcessParam);
					qei_setPosLeft(0);
					encLeftTmp = qei_getPosLeft();
					reImg_Move = RightMOVE;
					Img_Move = get_IMove(x,y,x_dest,y_dest);
				}
				break;
			case BackMOVE:
				LED1_ON();LED2_ON();LED3_ON();
				if (pid_BackStraight(angle,70))
				{
					reImg_Move = BackMOVE;
					Img_Move = get_IMove(x,y,x_dest,y_dest);
				}


				/*
				if (BackStraightTurn(-7000,-7000,100,100))
				{
					Img_Move = get_IMove(x,y,x_dest,y_dest);
				}
				 */

				break;
			}
		}
		else
		{
			LED1_OFF();LED2_OFF();LED3_OFF();
			//speed_set(MOTOR_RIGHT, 100);
			//speed_set(MOTOR_LEFT, 100);
		}
	}
}
