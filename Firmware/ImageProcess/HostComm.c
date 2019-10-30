/*
 * HostComm.c
 *
 *  Created on: Jul 14, 2015
 *      Author: Huan
 */

#include "../include.h"
#include "HostComm.h"


#define UPDATE_TIME_MS 20
#define MAX_MSG_LEN_BYTE 50
#define MIN_MSG_LEN_BYTE 6
#define START_BYTE 0xA5

#define SRC_ID 1//robot
#define DEST_ID 0//PC

#define END_BYTE 0x0D

int x, y, x_dest, y_dest;
float angle, angle_2;

enum MSG_CODE
{
	MSG_UPDATE_POS=0,
	MSG_TIME,
	MSG_BOX,
	MSG_WAYPOINT,
	MSG_TRACK_BOT,
	MSG_UPDATE_BOT,
	MSG_SPEED_SET,
	MSG_START_TEST,
	MSG_SET_PID,
	MSG_IMG_UPDATE,
	MSG_STOP,
};

extern uint8_t IR_Calib_Step;
extern PID_PARAMETERS pid_wall;

static TIMER_ID HostComm_TimerID = INVALID_TIMER_ID;
static bool HostCommFlag = false;

static uint32_t rcvMsgByte=0;
static uint8_t rcvMsg[MAX_MSG_LEN_BYTE];
static uint32_t rcvMsgLen=0;

static uint8_t data[MAX_MSG_LEN_BYTE];
static int32_t len;

static void HostCommTimeoutCallBack(void)
{
	HostComm_TimerID = INVALID_TIMER_ID;
	HostCommFlag = true;
	if (HostComm_TimerID != INVALID_TIMER_ID)
		TIMER_UnregisterEvent(HostComm_TimerID);
	HostComm_TimerID = TIMER_RegisterEvent(&HostCommTimeoutCallBack, UPDATE_TIME_MS);
}


void HostCommInit()
{
	bluetooth_init(115200);
	if (HostComm_TimerID != INVALID_TIMER_ID)
		TIMER_UnregisterEvent(HostComm_TimerID);
	HostComm_TimerID = TIMER_RegisterEvent(&HostCommTimeoutCallBack, UPDATE_TIME_MS);

}



uint16_t calcCheckSum(uint8_t *data, uint8_t len)
{
    uint16_t sum=0;
    int i;
    for (i=0; i<len; i++)
    {
        sum+=data[i];
    }
    return sum;
}
static COMM_RESULT handleMsg(int msgCode,uint8_t* payload)
{
	LED2_ON();
	switch (msgCode)
	{
	case MSG_START_TEST:
		speed_Enable_Hbridge(true);
		break;

	case MSG_SPEED_SET:
	{
		int speedLeft,speedRight;
		speedLeft=payload[0]|payload[1]<<8|payload[2]<<16|payload[3]<<24;
		speedRight=payload[4]|payload[5]<<8|payload[6]<<16|payload[7]<<24;
		speed_set(MOTOR_LEFT,speedLeft);
		speed_set(MOTOR_RIGHT,speedRight);
		break;
	}
	case MSG_IMG_UPDATE:
	{
		angle = (payload[0]|payload[1]<<8);
		angle_2 = (payload[2]|payload[3]<<8);
		x = payload[4]|payload[5]<<8;
		y = payload[6]|payload[7]<<8;
		x_dest = payload[8]|payload[9]<<8;
		y_dest = payload[10]|payload[11]<<8;

		break;
	}
//	case MSG_STOP:
//	{
//		stop = payload[0]|payload[1]<<8;
//	}

	}
	return SUCCESS;
}
COMM_RESULT HostComm_process(void)
{
	//0xa5 +length 2 +msg type 1+src id 1+dest id 1+msg id 1+payload+crc 2+0xd
	if (HostCommFlag)
	{
		HostCommFlag = false;
		//send
	

		//receive
		len=bluetooth_recv(data,MAX_MSG_LEN_BYTE,false);
		if (len)
		{
			int i;
			for (i=0;i<len;i++)
			{
				if (rcvMsgByte==0)
				{
					if (data[i]==START_BYTE)
					{
						rcvMsg[rcvMsgByte++] = data[i];
					}
					continue;
				}
				rcvMsg[rcvMsgByte++] = data[i];
				if (rcvMsgByte==3)
				{
					rcvMsgLen = rcvMsg[1] + (rcvMsg[2]<<8) + 6;
					if (rcvMsgLen<MIN_MSG_LEN_BYTE)
					{
						rcvMsgByte = 0;
						return LENGTH_ERROR;
					}
				}
				if (rcvMsgByte==rcvMsgLen)
				{
					uint16_t crc;
					rcvMsgByte = 0;
				    crc=calcCheckSum(data+3,rcvMsgLen-6);
					if (crc != (data[rcvMsgLen-3]|(data[rcvMsgLen-2]<<8)))
						return CRC_ERROR;
					if (rcvMsg[rcvMsgLen-1]!=END_BYTE)
						return ENDBYTE_ERROR;
					return handleMsg(rcvMsg[3],rcvMsg+7);
				}
			}
		}

	}
	return INCOMPLETE_MSG;
}
