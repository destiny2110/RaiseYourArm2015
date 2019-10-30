/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *  version 0.0.1
 */

/**
 * @file	WallFollow.c
 * @brief	wall follow controller
 */


#include "../include.h"
#include "WallFollow.h"
#include "Floodfill.h"

/*********************************************************
 *
 * DEFINE FOR TEST CODE
 *
*********************************************************/
//==========================================
// FORWARD TEST
//==========================================

//==========================================
// TURN LEFT TEST
//==========================================
//#define TEST_TURNLEFT_detect
//#define TEST_TURNLEFT_AfterGoStraightBeforeRURN
//#define TEST_TURNLEFT_STARTTURN
//#define TEST_TURNLEFT_startMOVEcheckwall
//#define TEST_TURNLEFT_AFTERTURN
//==========================================
// TURN RIGHT TEST
//==========================================
//#define TEST_TURNRIGHT_STOP
//#define TEST_TURNRIGHT_AfterGoALittleBit
//#define TEST_TURNRIGHT_AfterTURN
//#define TEST_TURNRIGHT_GoAfterTurn
//==========================================
// TURN BACK TEST
//==========================================
//#define TEST_TURNBACK_STOP
//#define TEST_TURNBACK_afterGoAlittleBit


//#define TEST_FORWARD_MOVE
//#define TEST_TURNBACK_FWD
//#define TEST_TURNBACK_TURN1
//#define TEST_TURNBACK_TURN2
//#define TEST_TURNBACK_BACKWARD
//#define TEST_AFTERTURNBACK
//#define _DEBUG_move
/**********************************************************
 *
 * DEFINE FOR SELECT MODE
 *
 *********************************************************/
//#define WALL_FOLLOW
#define FLOOD_FILL
//#define WALL_DEBUG
//#define _DEBUG_POS_
//#define MORE_ROLL



#define CELL_ENC 12700
#define CELL_FAR 11300

#define AVG_SPEED_FWD_FAST 200
#define AVG_SPEED_FWD 200
#define AVG_SPEED_FWD_SLOW 100
#define AVG_SPEED_BWD 120
#define  X_GOAL	6
#define	 Y_GOAL 8
#define  X_INIT 0
#define  Y_INIT 0

//* Private function prototype ----------------------------------------------*/
static void pid_process_callback(void);
static void pid_StopTimeout(void);
static TIMER_ID pid_Runtimeout(TIMER_CALLBACK_FUNC CallbackFcn, uint32_t msTime);



static MOVE getMove(bool isWallLeft,bool isWallFront,bool isWallRight);
static bool TurnBack(int fwdPulse, int avrSpeedLeft,int avrSpeedRight,int turnPulse,
		int resetEnc);
 bool TurnLeft(int fwdPulse,int avrSpeedLeft,int avrSpeedRight,int turnPulse, int fwdPulse2);
static bool TurnRight(int fwdPulse,int avrSpeedLeft,int avrSpeedRight,int turnPulse, int fwdPulse2);



extern int x, y, x_dest, y_dest;
extern float angle;






//* Private variables -------------------------------------------------------*/
static WALL_FOLLOW_SELECT e_wall_follow_select = WALL_FOLLOW_NONE;





//**********************************

//**********************************

static uint32_t ui32_msLoop = 0;
static TIMER_ID pid_TimerID = INVALID_TIMER_ID;

//**************

//**************


PID_PARAMETERS pid_wall_right = {.Kp = 0.06, .Kd = 0.0, .Ki = 0.001,
		.Ts = 0.020, .PID_Saturation = 250, .e_=0, .e__=0, .u_=0};

PID_PARAMETERS pid_wall_left = {.Kp = 0.09, .Kd = 0.0, .Ki = 0.001,
		.Ts = 0.020, .PID_Saturation = 250, .e_=0, .e__=0, .u_=0};
PID_PARAMETERS pid_posLeft = {.Kp = 0.035, .Kd = 0.00001, .Ki = 0.12,
		.Ts = 0.020, .PID_Saturation = 300, .e_=0, .e__=0, .u_=0};
PID_PARAMETERS pid_posRight = {.Kp = 0.035, .Kd = 0.0001, .Ki = 0.12,
		.Ts = 0.020, .PID_Saturation = 250, .e_=0, .e__=0, .u_=0};


static int8_t robotX=X_INIT,robotY=Y_INIT;
static DIRECTION currentDir=UP_DIR;
static int32_t encLeftTmp=0,encRightTmp=0, enc_pulse_reset=0, x_temp;
static int32_t posLeftTmp=0,posRightTmp=0;
static float leftError, rightError;
static int32_T avrSpeed, avrSpeedTmp;
static bool rqTurnLeft=false,rqTurnRight=false;
static int32_t CtrlStep=1,moveStage=1;
static int32_t fwdPulse,turnPulse;
bool isWallLeft, isWallRight, isWallFrontLeft,isWallFrontRight;
static MOVE eMove=FORWARD,preMove=NONE;
static bool ControlFlag = false;

static bool TurnLeft(int fwdPulse,int avrSpeedLeft,int avrSpeedRight,int turnPulse, int fwdPulse2);


//static I_MOVE Img_Move = ForwardMOVE;

static void clearPosition()
{
	encLeftTmp=0;
	encRightTmp=0;
	qei_setPosLeft(8800);//distance from robot head to start of current cell in pulses of encoder
	qei_setPosRight(8800);
}
static void initPos()
{
	robotX=X_INIT;
	robotY=Y_INIT;
	clearPosition();
}
//*****************************************************************************
//
//! Update robot position when moving in straight line
//!
//! \param none
//!
//!
//! \return none
//
//*****************************************************************************
static void forwardUpdate()
{
	//bluetooth_print("EncLeftTmp %d \r\n",encLeftTmp);
	if (qei_getPosLeft()-encLeftTmp>CELL_ENC)
	{
		encLeftTmp += CELL_ENC;
		switch (currentDir)
		{
		case UP_DIR:
			robotY++;
			break;
		case RIGHT_DIR :
			robotX++;
			break;
		case DOWN_DIR:
			robotY--;
			break;
		case LEFT_DIR:
			robotX--;
			break;
		}
/*/================================================
// edit here to find GOAL
		if (robotX==X_GOAL && robotY== Y_GOAL)
		{
			system_SetState(SYSTEM_INITIALIZE);
			speed_Enable_Hbridge(false);

			bluetooth_print("done \r\n ");
		}
//================================================*/
#ifdef _DEBUG_POS_
	//	bluetooth_print("x: %d y: %d Dir: %d \r\n",robotX,robotY,currentDir);
		//bluetooth_print("MAZE: %d, Gone: %d\r\n", Maze[robotX][robotY]&0xff, Maze[robotX][robotY]&0x800);
#endif
	}
}
//*****************************************************************************
//
//! Update robot position when detecting right/left wall
//!
//! \param none
//!
//!
//! \return none
//
//*****************************************************************************
static void forwardUpdateByWall()  // cap nhat toa do nguoc lai so voi forwardUpdate
{
	//bluetooth_print("enc_tmp %d \r\n", encLeftTmp);
	//bluetooth_print("enc %d \r\n", qei_getPosLeft());
	//11300:distance from head of robot to the start of current cell
	//when detecting right/left wall in pulses of encoder
	if ((qei_getPosLeft()-encLeftTmp)<(CELL_FAR-CELL_ENC/2))   // edit here CELL_FAR replace 11300 in the past
	{
		encLeftTmp-=CELL_ENC;
		switch (currentDir)
		{
		case 0:                     // UP_DIR
			robotY--;
			break;
		case 1:						// RIGHT_DIR
			robotX--;
			break;
		case 2:						// DOWN_DIR
			robotY++;
			break;
		case 3:
			robotX++;				// LEFT_DIR
			break;
		}

	}
	qei_setPosLeft(CELL_FAR);
	//qei_setPosLeft(11300);
	//UpdateMaze(robotX, robotY, currentDir);
	//InitMaze(X_INIT,Y_INIT, X_GOAL, Y_GOAL);
#ifdef _DEBUG_POS_
//		bluetooth_print("Update Pos by wall x: %d y: %d D: %d\r\n",robotX,robotY,currentDir);
		//bluetooth_print("MAZE: %d, Gone: %d\r\n", Maze[robotX][robotY]&0xff,Maze[robotX][robotY]&0x8000 );
#endif
		//bluetooth_print("final enc = %d \r\n ",qei_getPosLeft());
		//bluetooth_print("enc update = %d \r\n ",qei_getPosLeft());
}
/**
 * @brief Init Wall follow controller
 */
static void pid_Wallfollow_init()
{
	ui32_msLoop =  pid_wall_left.Ts * 1000;
	pid_Runtimeout(&pid_process_callback, ui32_msLoop);

}
/**
 * @brief Init Wall follow controller
 */
void wallFollow_init()
{
	pid_Wallfollow_init();
	initPos();
	eMove=FORWARD;
	currentDir=UP_DIR;
	avrSpeed=AVG_SPEED_FWD;
}
/**
 * @brief Wall follow controller
 */
static bool pid_wallfollow(float delta_IR_left, float delta_IR_right, float averageSpeed,
		WALL_FOLLOW_SELECT wall_follow_select)
{
	static float error, u, rightFirst=1;
	static WALL_FOLLOW_SELECT preSelect=WALL_FOLLOW_NONE;
	int32_t set_speed[2];

	if (preSelect==WALL_FOLLOW_NONE)
		if (preSelect!=wall_follow_select)
		{
			if (preSelect==WALL_FOLLOW_RIGHT)
				pid_reset(&pid_wall_right);
			else if (preSelect==WALL_FOLLOW_LEFT)
				pid_reset(&pid_wall_left);
		}

	switch (wall_follow_select)
	{
	case WALL_FOLLOW_NONE:	//Do nothing
		return true;
	case WALL_FOLLOW_LEFT:
		{
			error = -delta_IR_left;
			u = pid_process(&pid_wall_left,error);
		}
		break;
	case WALL_FOLLOW_RIGHT:
		{
			error = delta_IR_right;
			u = pid_process(&pid_wall_right,error);
		}
		break;
	case WALL_FOLLOW_BOTH:
		{
			error = delta_IR_right - delta_IR_left;
			u = pid_process(&pid_wall_right,error);
		}
		break;
	case WALL_FOLLOW_AUTO:
		if (rightFirst)
		{
			if (isWallRight)
			{

				error = delta_IR_right;
				u = pid_process(&pid_wall_right,error);
			}
			else if (isWallLeft)
			{
				pid_reset(&pid_wall_right);
				error = -delta_IR_left;
				u = pid_process(&pid_wall_left,error);
				rightFirst=0;
			}
		}
		else
		{
			if (isWallLeft)
			{
				error = -delta_IR_left;
				u = pid_process(&pid_wall_left,error);
			}
			else if (isWallRight)
			{
				pid_reset(&pid_wall_left);
				error = delta_IR_right;
				u = pid_process(&pid_wall_right,error);
				rightFirst=1;
			}
		}
		break;
	default:
		return false;
	}

	preSelect = wall_follow_select;

	set_speed[0] = averageSpeed + (int32_t)(u / 2);
	set_speed[1] = averageSpeed - (int32_t)(u / 2);

	speed_set(MOTOR_RIGHT, set_speed[0]);
	speed_set(MOTOR_LEFT, set_speed[1]);

	return true;
}

static void pid_process_callback(void)
{
	pid_TimerID = INVALID_TIMER_ID;
	ControlFlag = true;
	pid_Runtimeout(&pid_process_callback, ui32_msLoop);
}


void pid_Wallfollow_set_follow(WALL_FOLLOW_SELECT follow_sel)
{
	e_wall_follow_select = follow_sel;
}

static void pid_StopTimeout(void)
{
	if (pid_TimerID != INVALID_TIMER_ID)
		TIMER_UnregisterEvent(pid_TimerID);
	pid_TimerID = INVALID_TIMER_ID;
}

static TIMER_ID pid_Runtimeout(TIMER_CALLBACK_FUNC CallbackFcn, uint32_t msTime)
{
	pid_StopTimeout();
	pid_TimerID = TIMER_RegisterEvent(CallbackFcn, msTime);
	return pid_TimerID;
}

//add your algorithm code here
static MOVE getMove(bool isWallLeft,bool isWallFront,bool isWallRight)
{
#ifdef  WALL_FOLLOW
	if (e_wall_follow_select == WALL_FOLLOW_RIGHT)
	{
		if (!isWallRight)
		{
			return TURN_RIGHT;
		}
		else if (!isWallFront)
		{
			return FORWARD;
		}
		else if (!isWallLeft)
		{
			return TURN_LEFT;
		}
		else
		{
			return TURN_BACK;
		}
	}
	else if (e_wall_follow_select == WALL_FOLLOW_LEFT)
	{
		if (!isWallLeft)
		{
			return TURN_LEFT;
		}
		else if (!isWallFront)
		{
			return FORWARD;
		}
		else if (!isWallRight)
		{
			return TURN_RIGHT;
		}
		else
		{
			return TURN_BACK;
		}
	}
	return FORWARD;
#endif
#ifdef FLOOD_FILL
	return GetDir(robotX, robotY, currentDir);
#endif
}

//*****************************************************************************
//
//! Move robot a little bit (error +-500 pulses). Robot velocity is equal 0 after moving.
//! Make sure this function return true before calling it again.
//!
//! \param deltaLeft distance left motor will go
//! \param deltaRight distance right motor will go
//! \param velLeftMax max left velocity
//! \param velRightMax max right velocity
//!
//! \return true if done
//
//*****************************************************************************
static bool move(int deltaLeft,int deltaRight,int velLeftMax, int velRightMax)
{
	static int origLeft, origRight;
	static bool done = true;

	int currentLeft=qei_getPosLeft();
	int currentRight=qei_getPosRight();

	if (done)
	{
		done=false;
		origLeft=currentLeft;
		origRight=currentRight;
	}
	//bluetooth_print("move: %5d %5d\r\n",origLeft,currentLeft);
	if (abs(origLeft+deltaLeft-currentLeft)>500)
	{
		pid_posLeft.PID_Saturation = velLeftMax;
		speed_set(MOTOR_LEFT, pid_process(&pid_posLeft,origLeft+deltaLeft-currentLeft));
		pid_posRight.PID_Saturation = velRightMax;
		speed_set(MOTOR_RIGHT, pid_process(&pid_posRight,origRight+deltaRight-currentRight));
		done=false;
	}
	else
	{
#ifdef _DEBUG_move
	system_SetState(SYSTEM_INITIALIZE);
	speed_Enable_Hbridge(false);
	//bluetooth_print("move: %5d %5d %5d %5d\r\n",(int)left, (int)right,(int)pid_posLeft.u,(int)pid_posRight.u);
#endif
		done = true;
		pid_reset(&pid_posLeft);
		pid_reset(&pid_posRight);
	}


	return done;
}


static bool TurnRight(int fwdPulse,int avrSpeedLeft,int avrSpeedRight,int turnPulse,
		int resetEnc)
{
	static int vt,vp;
	LED1_OFF();LED2_OFF();LED3_ON();
	switch (CtrlStep)
	{
	case 1:
		posLeftTmp=qei_getPosLeft();
		CtrlStep=2;
		vt=1;
		vp=1;
		avrSpeedTmp=avrSpeed;
	case 2://go straight a little bit before turn right

		if ((abs(qei_getPosLeft()-posLeftTmp)<fwdPulse) ||
				(isWallFrontLeft && isWallFrontRight &&
				(IR_GetIrDetectorValue(3)>IR_get_calib_value(IR_CALIB_BASE_FRONT_RIGHT))&&
				(IR_GetIrDetectorValue(0)>IR_get_calib_value(IR_CALIB_BASE_FRONT_LEFT))))
		{
			if (qei_getPosLeft()<fwdPulse+posLeftTmp)
				avrSpeed = ((abs(fwdPulse + posLeftTmp - qei_getPosLeft()) / (fwdPulse / avrSpeedTmp)) / 2)
				+ (abs(avrSpeedLeft) + abs(avrSpeedRight)) / 2;
			else
				avrSpeed = (abs(avrSpeedLeft) + abs(avrSpeedRight)) / 4;
			if (isWallLeft)
				pid_wallfollow(leftError,rightError,avrSpeed,WALL_FOLLOW_LEFT);
			else
			{
				speed_set(MOTOR_RIGHT, avrSpeed);
				speed_set(MOTOR_LEFT, avrSpeed);
			}
		}
		else
		{
			// after go straight a little bit
			pid_reset(&pid_wall_left);
			pid_reset(&pid_wall_right);
			//bluetooth_print("Update after go a little bit y++? %d \r\n");  /// neu y khong tang thi tang cellfar len
			forwardUpdate();
			CtrlStep++;
			avrSpeed=avrSpeedTmp;
			//UpdateMaze(robotX,robotY,currentDir);
			//bluetooth_print("LastUpdate \r\n ");
#ifdef TEST_TURNRIGHT_AfterGoALittleBit
		system_SetState(SYSTEM_INITIALIZE);
		speed_Enable_Hbridge(false);
#endif
			//speed_Enable_Hbridge(false);
			//while(1);
		}
		break;
	case 3:
		posLeftTmp=qei_getPosLeft();
		posRightTmp=qei_getPosRight();
		CtrlStep++;
	case 4://turn 90 degree
		//bluetooth_print("TurningR_ \r\n ");
		//bluetooth_print("ctlStep %d \r\n",CtrlStep);

		if (abs(qei_getPosLeft()-posLeftTmp) + abs(qei_getPosRight()-posRightTmp) < turnPulse)
		{
			speed_set(MOTOR_LEFT, avrSpeedLeft);
			speed_set(MOTOR_RIGHT, -avrSpeedRight);
			if((abs(qei_getPosLeft()-posLeftTmp)>(turnPulse*0.8*vp/8)) && (vp<9))
			{
				if (avrSpeedLeft>=24)
					avrSpeedLeft-=24;
				vp++;
			}
			if((abs(qei_getPosRight()-posRightTmp)>(turnPulse*0.2*vt/8)) && (vt<9))
			{
				if (avrSpeedRight>=4)
					avrSpeedRight-=4;
				vt++;
			}
		}
		else
		{
			currentDir=(currentDir+RIGHT_DIR)%4;
			clearPosition();
			qei_setPosLeft(resetEnc);
			qei_setPosRight(resetEnc);
	//=========================================
			//bluetooth_print("dir update after turn \r\n");
			forwardUpdate();         // co the bo k? co the la CO
	//=========================================
			//bluetooth_print("stopupdatePOS");
			/*InitMaze(robotX, robotY, X_GOAL, Y_GOAL);
			UpdateMaze(robotX, robotY, currentDir);*/

			CtrlStep=1;
			pid_reset(&pid_wall_right);
			pid_reset(&pid_wall_left);
			speed_set(MOTOR_LEFT, avrSpeed);
			speed_set(MOTOR_RIGHT, avrSpeed);
			return true;
		}
		break;
	}
	return false;
}

//*****************************************************************************
//
//! Control two motor to make robot turn left 90 degree
//!
//! \param fwdPulse is the distance robot will go straight before turn right
//!, the robot will stand between the next cell of maze.
//! \param avrSpeedLeft is the speed of left motor.
//! \param avrSpeedRight is the speed of right motor.
//! \param turnPulse is the total pulse of two encoder after turn
//! \param resetEnc is reset value for encoder after turning 90 degree, ignore this if you don't want to estimate position
//! \return true if finish
//!			false if not
//
//*****************************************************************************
bool TurnLeft(int fwdPulse,int avrSpeedLeft,int avrSpeedRight,int turnPulse,
		int resetEnc)
{
	static int vt,vp;
	LED1_ON();LED2_OFF();LED3_OFF();
//	bluetooth_print("LS %d\r\n",CtrlStep);
	switch (CtrlStep)
	{
	case 1:
		posLeftTmp=qei_getPosLeft();
		CtrlStep++;
		avrSpeedTmp=avrSpeed;
	case 2://go straight alittle bit before turn
		if ((abs(qei_getPosLeft()-posLeftTmp)<fwdPulse) ||

				(isWallFrontLeft && isWallFrontRight &&
				(IR_GetIrDetectorValue(3)>IR_get_calib_value(IR_CALIB_BASE_FRONT_RIGHT))&&
				(IR_GetIrDetectorValue(0)>IR_get_calib_value(IR_CALIB_BASE_FRONT_LEFT))))

		{
			if (qei_getPosLeft()-posLeftTmp<fwdPulse)
				avrSpeed = ((abs(fwdPulse + posLeftTmp - qei_getPosLeft()) / (fwdPulse / avrSpeedTmp)) / 2)
					+ (abs(avrSpeedLeft) + abs(avrSpeedRight)) / 4;
			else
				avrSpeed = (abs(avrSpeedLeft) + abs(avrSpeedRight)) / 4;

			if (isWallRight)
				pid_wallfollow(leftError,rightError,avrSpeed,WALL_FOLLOW_RIGHT);
			else
			{
				speed_set(MOTOR_RIGHT, avrSpeed+2);
				speed_set(MOTOR_LEFT, avrSpeed);
			}
		}
		else
		{
			pid_reset(&pid_wall_right);
			pid_reset(&pid_wall_left);
			forwardUpdate();
			UpdateMaze(robotX,robotY,currentDir);
			CtrlStep++;
			avrSpeed=avrSpeedTmp;

#ifdef TEST_TURNLEFT_AfterGoStraightBeforeRURN
		system_SetState(SYSTEM_INITIALIZE);
		speed_Enable_Hbridge(false);
#endif
		}
#ifdef TEST_TURNLEFT_detect
		system_SetState(SYSTEM_INITIALIZE);
		speed_Enable_Hbridge(false);
#endif
		break;
	case 3:
		posLeftTmp=qei_getPosLeft();
		posRightTmp=qei_getPosRight();
		CtrlStep++;
		//UpdateMaze(robotX,robotY,currentDir);
		vp=1;
		vt=1;
	case 4://turn 90 degree

		if (abs(qei_getPosLeft()-posLeftTmp) + abs(qei_getPosRight()-posRightTmp) < turnPulse)

		{
			speed_set(MOTOR_RIGHT, avrSpeedRight);
			speed_set(MOTOR_LEFT, avrSpeedLeft);
			if((abs(qei_getPosRight()-posRightTmp)>(turnPulse*0.8*vp/8)) && (vp<9))
			{
				if (avrSpeedRight>=24)
					avrSpeedRight-=24;
				vp++;

			}
			if((abs(qei_getPosLeft()-posLeftTmp)>(turnPulse*0.2*vt/8)) && (vt<9))
			{
				if (avrSpeedLeft>=4)
					avrSpeedLeft-=4;
				vt++;
			}
		}
		else    // after turn
		{
			currentDir=(currentDir+LEFT_DIR)%4;
			clearPosition();
			qei_setPosLeft(resetEnc);
			qei_setPosRight(resetEnc);
			forwardUpdate();

			/*InitMaze(robotX, robotY, X_GOAL, Y_GOAL);
			UpdateMaze(robotX, robotY, currentDir);*/

			CtrlStep=1;
			pid_reset(&pid_wall_left);
			pid_reset(&pid_wall_right);
			speed_set(MOTOR_LEFT, avrSpeed);
			speed_set(MOTOR_RIGHT, avrSpeed);
			return true;
		}

		break;
	}
	return false;

}

//*****************************************************************************
//
//! Control two motor to make robot turn back 180 degree.
//!
//! \param fwdPulse is the distance robot will go straight before turn right
//!, the robot will stand between the next cell of maze.
//! \param avrSpeedLeft is the speed of left motor.
//! \param avrSpeedRight is the speed of right motor.
//! \param NumPulse is the total pulse of two encoder after turn
//! \param resetEnc is the reset value for encoder after turning back
//! \return true if finish
//!			false if not
//
static bool TurnBack(int fwdPulse, int avrSpeedLeft,int avrSpeedRight,int turnPulse,
		int resetEnc)
{
	LED1_ON();LED2_ON();LED3_ON();
	switch (CtrlStep)
	{
	case 1:
	{
		posLeftTmp = qei_getPosLeft();
		avrSpeedTmp = avrSpeed;
		CtrlStep++;
	}
	case 2://go forward a litte bit
	{

		if (abs(qei_getPosLeft()-posLeftTmp)<fwdPulse)
		{
			avrSpeed = ((abs(fwdPulse + posLeftTmp - qei_getPosLeft()) / (fwdPulse / avrSpeedTmp)) / 4)
					+ (abs(avrSpeedLeft) + abs(avrSpeedRight)) / 2;
			if (isWallRight)
				pid_wallfollow(leftError,rightError,avrSpeed,WALL_FOLLOW_RIGHT);
			else if (isWallLeft)
				pid_wallfollow(leftError,rightError,avrSpeed,WALL_FOLLOW_LEFT);
			else
			{
				speed_set(MOTOR_RIGHT, avrSpeed);
				speed_set(MOTOR_LEFT, avrSpeed);
			}
		}
		else
		{

		//	bluetooth_print("x++ ?");//
			forwardUpdate();

#ifdef TEST_TURNBACK_afterGoAlittleBit
			system_SetState(SYSTEM_INITIALIZE);
			speed_Enable_Hbridge(false);
#endif

			pid_reset(&pid_wall_left);
			pid_reset(&pid_wall_right);

			//UpdateMaze(robotX,robotY,currentDir);
			//bluetooth_print("back update pos");
			CtrlStep++;
			avrSpeed = avrSpeedTmp;
		}
		break;
	}
	case 3:
		posLeftTmp=qei_getPosLeft();
		posRightTmp=qei_getPosRight();
		CtrlStep++;
	case 4://turing 90 degree
	{
		if ((abs(qei_getPosLeft()-posLeftTmp)+abs(qei_getPosRight()-posRightTmp))<turnPulse)
		{
			speed_set(MOTOR_RIGHT, avrSpeedRight);
			speed_set(MOTOR_LEFT, avrSpeedLeft);
		}
		else
		{
			currentDir=(currentDir+LEFT_DIR)%4;
#ifdef TEST_TURNBACK_TURN1
			bluetooth_print("CurDir %d \r\n", currentDir);
			system_SetState(SYSTEM_INITIALIZE);
			speed_Enable_Hbridge(false);
#endif
			CtrlStep++;
		}
		break;
	}
	case 5:
		posLeftTmp=qei_getPosLeft();
		posRightTmp=qei_getPosRight();
		CtrlStep++;
	case 6://turning another 90 degree
	{
		if ((abs(qei_getPosLeft()-posLeftTmp)+abs(qei_getPosRight()-posRightTmp))<turnPulse)
		{
			speed_set(MOTOR_RIGHT, -avrSpeedLeft);
			speed_set(MOTOR_LEFT, -avrSpeedRight);
		}
		else
		{
			currentDir=(currentDir+LEFT_DIR)%4;
#ifdef TEST_TURNBACK_TURN2
			bluetooth_print("CurDir %d \r\n", currentDir);
			system_SetState(SYSTEM_INITIALIZE);
			speed_Enable_Hbridge(false);
#endif
			clearPosition();
			qei_setPosLeft(resetEnc);
			qei_setPosRight(resetEnc);
			forwardUpdate();
			//InitMaze(robotX, robotY, X_GOAL, Y_GOAL);
		//	UpdateMaze(robotX, robotY, currentDir);

			CtrlStep=1;
			return true;
		}
		break;
	}
	}
	return false;
}
//*****************************************************************************
//
//! Control robot to go straight forward by following wall
//!
//!
//! \return true if left/right wall is detected
//!			false if no left/right wall is detected
//

static bool Forward()
{
	LED1_OFF();LED2_ON();LED3_OFF();
	//bluetooth_print("%d\r\n",avrSpeed);

	// neu mat mot trong hai tuong
	if ((!isWallLeft) || (!isWallRight))
	{
		//bluetooth_print("ENCdetectWall %d \r\n",qei_getPosLeft());
		forwardUpdateByWall();
		//forwardUpdate();
		//UpdateMaze(robotX,robotY,currentDir);
		return true;
	}

	// co ca tuong trai lan tuong phai
	forwardUpdate();
	UpdateMaze(robotX,robotY,currentDir);
	if (avrSpeed<AVG_SPEED_FWD_FAST-20)
		avrSpeed+=20;
	else if (avrSpeed>AVG_SPEED_FWD_FAST)
		avrSpeed=AVG_SPEED_FWD_FAST;

	if (isWallRight)
	{
		//bluetooth_print("bam tuong phai \r\n");
		pid_wallfollow(leftError,rightError, avrSpeed,WALL_FOLLOW_RIGHT);
	}
	else if (isWallLeft)
	{
		//bluetooth_print("bam tuong trai \r\n");
		pid_wallfollow(leftError,rightError, avrSpeed,WALL_FOLLOW_LEFT);
	}
	else
	{
		speed_set(MOTOR_RIGHT, avrSpeed);
		speed_set(MOTOR_LEFT, avrSpeed);
	}

	return false;
}






void pid_Wallfollow_process(void)
{
}


/*
	if (ControlFlag)
	{
		static int i;
		pid_Runtimeout(&pid_process_callback, ui32_msLoop);
		ControlFlag = false;

		leftError=(float)IR_get_calib_value(IR_CALIB_BASE_LEFT) - (float)IR_GetIrDetectorValue(1);
		rightError=(float)IR_get_calib_value(IR_CALIB_BASE_RIGHT) - (float)IR_GetIrDetectorValue(2);
		isWallLeft = IR_GetIrDetectorValue(1)<IR_get_calib_value(IR_CALIB_MAX_LEFT);
		isWallRight = IR_GetIrDetectorValue(2)<IR_get_calib_value(IR_CALIB_MAX_RIGHT);
		isWallFrontLeft = IR_GetIrDetectorValue(0)<IR_get_calib_value(IR_CALIB_MAX_FRONT_LEFT);
		isWallFrontRight = IR_GetIrDetectorValue(3)<IR_get_calib_value(IR_CALIB_MAX_FRONT_RIGHT);


		switch(eMove)
		{
		case FORWARD:
			switch (moveStage)
			{
			case 1:
			//============================
			// Mat mot trong hai tuong ben
				if (Forward())
					moveStage++;
			//============================

			//============================
			// Co tuong truoc
				if (isWallFrontLeft| isWallFrontRight)
				{
					preMove=eMove;
				//	InitMaze(X_INIT,Y_INIT,X_GOAL,Y_GOAL);
					eMove=getMove(isWallLeft,isWallFrontLeft|isWallFrontRight,isWallRight);
				}
			//============================

				break;
			case 2:
				posLeftTmp=qei_getPosLeft();
			//	bluetooth_print("PosLeftTmp %d \r\n",posLeftTmp);
				moveStage++;
				i=1;
				avrSpeedTmp=avrSpeed;
			case 3://slow down
				//bluetooth_print("EncNow? %d \r\n",qei_getPosLeft());
				forwardUpdate();    // de lam gi ?
				if (!isWallLeft)
				{
					rqTurnLeft=true;
				}
				if (!isWallRight)
				{
					rqTurnRight=true;
				}
			// cai nay la cai gi khong biet nua @@  KHONG CO TUONG TRUOC
				if ((abs(qei_getPosLeft()-posLeftTmp)<5000)
						&& (!isWallFrontLeft) && (!isWallFrontRight))
				{
					if ((abs(qei_getPosLeft()-posLeftTmp)>i*500) && (avrSpeed>AVG_SPEED_FWD-40))
					{
						avrSpeed -= 30;
						i++;
					}
					if (isWallLeft|isWallRight)
					{
						//bluetooth_print("auto");
						pid_wallfollow(leftError,rightError, avrSpeed,WALL_FOLLOW_AUTO);
					}


					else
					{
						pid_reset(&pid_wall_left);
						pid_reset(&pid_wall_right);
						speed_set(MOTOR_RIGHT, avrSpeed);
						speed_set(MOTOR_LEFT, avrSpeed);
					}
				}
				else
				{

#ifdef TEST_FORWARD_MOVE
					system_SetState(SYSTEM_INITIALIZE);
					speed_Enable_Hbridge(false);
#endif
					preMove=eMove;
					InitMaze(X_INIT,Y_INIT,X_GOAL,Y_GOAL);
					eMove=getMove(!rqTurnLeft,isWallFrontLeft|isWallFrontRight,!rqTurnRight);
					if (eMove==FORWARD)
					avrSpeed=AVG_SPEED_FWD;
					rqTurnLeft=false;
					rqTurnRight=false;
					moveStage=1;
				}
				break;
			}
			break;

		case TURN_LEFT:
			LED1_ON();LED2_OFF();LED3_OFF();
			switch (moveStage)
			{
			case 1:
				if ((preMove==TURN_LEFT )||(preMove = TURN_RIGHT))//after turning left or right
					//test
					// ____
					// |   |
					// | | |
				{
					fwdPulse=4800;
			//		bluetooth_print("fwdL %d ",fwdPulse);
					enc_pulse_reset= CELL_ENC/2+100;
				}
				else if ((preMove==BACKWARD) && (avrSpeed<AVG_SPEED_FWD_FAST))
					//after turning back
					//test
					// ___
					// |__   |
					//    |__|
				{
			//		bluetooth_print("fwdL %d ",fwdPulse);
					fwdPulse=3500;
				}
				else//after moving forward
					//test
					// ___
					// ___  |
					//    | |
					//    |_|
				{
					fwdPulse=4000; //2700
			//		bluetooth_print("fwdL %d ",fwdPulse);
					enc_pulse_reset=CELL_ENC/2 + 1000;
				}
				moveStage++;

			case 2:
				if (TurnLeft(fwdPulse,60,210,7300,enc_pulse_reset))//   40 280 8900
				{
#ifdef TEST_TURNLEFT_AFTERTURN
		system_SetState(SYSTEM_INITIALIZE);
		speed_Enable_Hbridge(false);
#endif
					moveStage++;
				}
				break;
			case 3:
				posLeftTmp=qei_getPosLeft();
				moveStage++;
			case 4:
				//go straight a little bit to check wall
				forwardUpdate();
				if (abs(qei_getPosLeft()-posLeftTmp)<2500)
				{
					if (abs(qei_getPosLeft()-posLeftTmp)>1000)
					{
						if (!isWallRight)
						{
							rqTurnRight=1;
						}

						if (!isWallLeft)
						{
							rqTurnLeft=1;
						}
					}
					avrSpeed=AVG_SPEED_FWD_SLOW;
					if (isWallLeft|isWallRight)
						pid_wallfollow(leftError,rightError, avrSpeed,WALL_FOLLOW_AUTO);
					else
					{
						pid_reset(&pid_wall_left);
						pid_reset(&pid_wall_right);
						speed_set(MOTOR_RIGHT, avrSpeed);//left motor is faster
						speed_set(MOTOR_LEFT, avrSpeed);
					}
				}
				else
				{
					//time to check front wall
					preMove=eMove;
				//	InitMaze(X_INIT,Y_INIT,X_GOAL,Y_GOAL);
					eMove=getMove(!rqTurnLeft,isWallFrontLeft|isWallFrontRight,!rqTurnRight);
					rqTurnLeft=false;
					rqTurnRight=false;
					moveStage=1;
					pid_reset(&pid_wall_left);
					pid_reset(&pid_wall_right);
				}
#ifdef TEST_TURNLEFT_startMOVEcheckwall
					speed_Enable_Hbridge(false);
#endif
			}
			break;

		case TURN_RIGHT:
			LED1_OFF();LED2_OFF();LED3_ON();
			switch (moveStage)
			{
			case 1:
				if (!FORWARD)//after turning left or right
					//test
					// ____
					// |   |
					// | | |
				{
					fwdPulse=5500;// ban ngay: 6000, dem 5000
					enc_pulse_reset=CELL_ENC/2+100;
			//		bluetooth_print("fwdPulseR %d ",fwdPulse);
					//bluetooth_print("after moving lr\r\n");
				}

				else if ((preMove==BACKWARD) && (avrSpeed<AVG_SPEED_FWD_FAST))
					//after turning back
					//test//sua
					// 	  ____
					// |  ____
					// |__|
				{
		//			bluetooth_print("after moving back\r\n");
					fwdPulse=4500;
		//			bluetooth_print("fwdPulseR %d ",fwdPulse);
				}
				else//after moving forward
					//test
					//   _____
					// | _____
					// | |
					// |_|
				{
					//bluetooth_print("after moving Forward\r\n");
					fwdPulse=4000;// ngay 4000, dem 4000
					enc_pulse_reset= CELL_ENC/2 + 2500;
		//			bluetooth_print("fwdPulseR %d \r\n",fwdPulse);
				}
				moveStage++;
			case 2:
				if (TurnRight(fwdPulse,200,40,7600,enc_pulse_reset))//1700+CELL_ENC  7070
				{
					//forwardUpdateByWall();

#ifdef TEST_TURNRIGHT_AfterTURN
		bluetooth_print("ENC = afterTurn %d \r\n",qei_getPosLeft());
		bluetooth_print("stopupdate??????????");
		system_SetState(SYSTEM_INITIALIZE);
		speed_Enable_Hbridge(false);

#endif
					moveStage++;
					//speed_Enable_Hbridge(false);
					//while(1);
				}
#ifdef TEST_TURNRIGHT_STOP
			system_SetState(SYSTEM_INITIALIZE);
			bluetooth_print("pulse %d",qei_getPosLeft());
			speed_Enable_Hbridge(false);
#endif
				break;

			case 3:
				posRightTmp=qei_getPosRight();
				moveStage++;
			case 4:    //      go alittle bit after turn to check wall
		//		bluetooth_print("carefull?");
		//		forwardUpdate();  //?

#ifdef TEST_TURNRIGHT_GoAfterTurn
					bluetooth_print("stop????????");
					speed_Enable_Hbridge(false);
					system_SetState(SYSTEM_INITIALIZE);
#endif
				if (abs(qei_getPosRight()-posRightTmp)<1700)//1000
				{
					if (abs(qei_getPosRight()-posRightTmp)>1200)
					{
						if (!isWallRight)
						{
							rqTurnRight=1;
						}
						if (!isWallLeft)
						{
							rqTurnLeft=1;
						}
					}
					avrSpeed=AVG_SPEED_FWD_SLOW;
					if (isWallLeft|isWallRight)
						pid_wallfollow(leftError,rightError, avrSpeed,WALL_FOLLOW_AUTO);
					else
					{
						pid_reset(&pid_wall_left);
						pid_reset(&pid_wall_right);
						speed_set(MOTOR_RIGHT, avrSpeed);
						speed_set(MOTOR_LEFT, avrSpeed);
					}
				}
				else
				{
					//forwardUpdate();
					//UpdateMaze(robotX,robotY,currentDir);

					preMove=eMove;
					//InitMaze(X_INIT,Y_INIT,X_GOAL,Y_GOAL);
					eMove=getMove(!rqTurnLeft,isWallFrontLeft|isWallFrontRight,!rqTurnRight);
					rqTurnLeft=false;
					rqTurnRight=false;
					moveStage=1;
					pid_reset(&pid_wall_left);
					pid_reset(&pid_wall_right);
				}
			}
//edit	//		forwardUpdate();
			break;

		case TURN_BACK:
			LED1_ON();LED2_ON();LED3_ON();
			UpdateMaze(robotX, robotY, currentDir);
//			bluetooth_print("ir %d %d %d %d \r\n ",IR_GetIrDetectorValue(1) ,IR_GetIrDetectorValue(2),IR_GetIrDetectorValue(0),IR_GetIrDetectorValue(3));
			switch (moveStage)
			{
			case 1:
				if (preMove==FORWARD)
				{
					fwdPulse=6000;// ngay 7000, dem 6000
		//			bluetooth_print("fwdB %d :",fwdPulse);
				}

				else
				{
					fwdPulse=7000;//ban ngay 9000, dem 7000
		//			bluetooth_print("fwdB %d :",fwdPulse);
				}
				moveStage++;
			case 2:
				if (TurnBack(fwdPulse,-140,60,7100,7500))
				{
					//forwardUpdate();
					//UpdateMaze(robotX,robotY,currentDir);
					moveStage++;
				}
#ifdef TEST_TURNBACK_STOP
			system_SetState(SYSTEM_INITIALIZE);
			speed_Enable_Hbridge(false);
	//		bluetooth_print("stop");
#endif
				break;
			case 3:
				if (move(-9500,-8000,AVG_SPEED_BWD,AVG_SPEED_BWD))  // lui lai
				{
					forwardUpdate();
					//UpdateMaze(robotX,robotY,currentDir);
#ifdef TEST_AFTERTURNBACK
					system_SetState(SYSTEM_INITIALIZE);
					speed_Enable_Hbridge(false);
#endif

					avrSpeed = AVG_SPEED_FWD_SLOW;
					preMove=eMove;
					eMove=FORWARD;
					//InitMaze(X_INIT,Y_INIT,X_GOAL,Y_GOAL);
					//eMove=getMove(isWallLeft,isWallFrontLeft|isWallFrontRight,isWallRight);
					moveStage = 1;
				}
			}
			break;




		}
	}
}

*/








