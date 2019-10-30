/*
 * HostComm.h
 *
 *  Created on: Jul 15, 2015
 *      Author: Huan
 */

#ifndef HOSTCOMM_H_
#define HOSTCOMM_H_

typedef enum
{
	INCOMPLETE_MSG=0,
	LENGTH_ERROR,
	CRC_ERROR,
	ENDBYTE_ERROR,
	SUCCESS
}COMM_RESULT;


extern int x, y, x_dest, y_dest;
extern float angle, angle_2;



void HostCommInit();
COMM_RESULT HostComm_process(void);

#endif /* HOSTCOMM_H_ */
