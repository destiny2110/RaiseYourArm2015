/*
 * ImgProcess.h
 *
 *  Created on: 05-09-2015
 *      Author: The_Cuong
 */

#ifndef IMAGEPROCESS_IMGPROCESS_H_
#define IMAGEPROCESS_IMGPROCESS_H_

typedef enum{
	ForwardMOVE,
	LeftMOVE,
	RightMOVE,
	BackMOVE
}I_MOVE;

typedef enum{
	SouthWard,
	EastWard,
	WestWard,
	NorthWard
} I_DIR;

extern void pid_ImageProcess(void);
extern void pid_ImageProcess_init();

#endif /* IMAGEPROCESS_IMGPROCESS_H_ */
