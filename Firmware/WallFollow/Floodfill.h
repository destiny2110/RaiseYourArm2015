/*
 * Floodfill.h
 *
 *  Created on: 13-08-2015
 *      Author: THANH DANH
 */

#ifndef RYA_ROBOT_V1_1C_WALLFOLLOW_FLOODFILL_H_
#define RYA_ROBOT_V1_1C_WALLFOLLOW_FLOODFILL_H_

#define X_MAZE				3
#define Y_MAZE  			7

extern uint16_t Maze[X_MAZE][Y_MAZE];

extern void ClearMaze(void);
extern void InitMaze(int8_t x0, int8_t y0, int8_t goal_x, int8_t goal_y);
extern void UpdateMaze(int8_t x, int8_t y, DIRECTION direction);
extern MOVE GetDir(uint8_t x, uint8_t y, DIRECTION direction);

#endif /* RYA_ROBOT_V1_1C_WALLFOLLOW_FLOODFILL_H_ */
