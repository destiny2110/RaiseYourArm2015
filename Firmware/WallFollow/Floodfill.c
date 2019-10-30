/*
 * Floodfill.c
 *
 *  Created on: 13-08-2015
 *      Author: THANH DANH
 */


#include "../include.h"
#include "WallFollow.h"
#include "Floodfill.h"
#define IS_NORTH_WALL		0x8000
#define IS_SOUTH_WALL		0x4000
#define IS_WEST_WALL		0x2000
#define IS_EAST_WALL		0x1000
#define HAS_GONE 			0x0800

//#define WALL_UPDATE_DEBUG

extern bool isWallLeft, isWallRight, isWallFrontLeft,isWallFrontRight;

void ClearMaze(void);
void InitMaze(int8_t x0, int8_t y0, int8_t goal_x, int8_t goal_y);
void UpdateMaze(int8_t x, int8_t y, DIRECTION direction);
MOVE GetDir(uint8_t x, uint8_t y, DIRECTION direction);

uint16_t Array[3];
uint16_t Maze[X_MAZE][Y_MAZE];


static uint8_t GetMin(uint16_t Num1, uint16_t Num2, uint16_t Num3);


void ClearMaze(void)
{
	uint8_t i, j;
	for(i=0; i<X_MAZE; i++);
	{
		for(j =0; j<Y_MAZE; j++)
		{
			Maze[i][j]=0;
		}
	}
}

void InitMaze(int8_t x0, int8_t y0, int8_t goal_x, int8_t goal_y)
{
	uint8_t i, j;
	uint16_t count =1;
	for(i=0; i<X_MAZE; i++)
	{
		for(j=0; j<Y_MAZE; j++)
		{
			Maze[i][j] |= 0x00ff;
			Maze[i][j] &= ~HAS_GONE;
		}
	}
	Maze[goal_x][goal_y] = 0;    // edit here ?????????  default is maze[][] = 0
	while(count)
	{
		count =0;
		for(i=0; i<X_MAZE; i++)
		{
			for(j=0; j<Y_MAZE; j++)
			{
				if((i>0) && ((Maze[i][j] & 0xff) < (Maze[i-1][j] & 0xff)) && ((Maze[i - 1][j] & 0xff) == 0x00ff))
				{
					if(!(Maze[i][j] & IS_WEST_WALL))
					{
						Maze[i-1][j] &= 0xff00;// mat na 2 byte cao
						Maze[i-1][j] |= ((Maze[i][j] + 1) & 0xff); //mat na 2 byte thap
						count++;
					}
				}
				if ((i < X_MAZE-1) && ((Maze[i][j] & 0xff) < (Maze[i+1][j] & 0xff)) && ((Maze[i + 1][j] & 0xff) == 0x00ff))
				{
					if ((!(Maze[i][j] & IS_EAST_WALL)))
					{
						Maze[i+1][j] &= 0xff00;
						Maze[i+1][j] |= ((Maze[i][j] + 1) & 0xff);
						count++;
					}
				}
				if ((j > 0) && ((Maze[i][j] & 0xff) < (Maze[i][j - 1] & 0xff)) && ((Maze[i][j - 1] & 0xff) == 0x00ff))
				{
					if ((!(Maze[i][j] & IS_SOUTH_WALL)))
					{
						Maze[i][j - 1] &= 0xff00;
						Maze[i][j - 1] |= ((Maze[i][j] + 1) & 0xff);
						count++;
					}
				}
				if ((j < Y_MAZE-1) && ((Maze[i][j] & 0xff) < (Maze[i][j + 1] & 0xff)) && ((Maze[i][j + 1] & 0xff) == 0x00ff))
				{
					if ((!(Maze[i][j] & IS_NORTH_WALL)))
					{
						Maze[i][j + 1] &= 0xff00;
						Maze[i][j + 1] |= ((Maze[i][j] + 1) & 0xff);
						count++;
					}
				}
			}
		}
	}
	// he edit alot here
	//goc duoi trai
	if ((!(Maze[0][1] & IS_SOUTH_WALL)))  // edit a lot here
	{
		Maze[0][0] = Maze[0][1] + 1;
	}
	else if ((!(Maze[1][0] & IS_WEST_WALL)))
	{
		Maze[0][0] = Maze[1][0] + 1;
	}
	//goc tren trai
	if ((!(Maze[0][Y_MAZE-2] & IS_NORTH_WALL)))
	{
		Maze[0][Y_MAZE-1] = Maze[0][Y_MAZE-2]+1;
	}
	else if ((!(Maze[1][Y_MAZE-1] & IS_WEST_WALL)))
	{
		Maze[0][Y_MAZE-1] = Maze[1][Y_MAZE-1] + 1;
	}
	//goc duoi phai
	if ((!(Maze[X_MAZE-2][0] & IS_EAST_WALL)))
	{
		Maze[X_MAZE-1][0] |= Maze[X_MAZE-2][0] + 1;
	}
	else if ((!(Maze[X_MAZE-1][1] & IS_SOUTH_WALL)))
	{
		Maze[X_MAZE-1][0] |= Maze[X_MAZE-1][1] + 1;
	}

	//goc tren phai
	if ((!(Maze[X_MAZE-2][Y_MAZE-1] & IS_EAST_WALL)))
	{
		Maze[X_MAZE-1][Y_MAZE-1] |= Maze[X_MAZE-2][Y_MAZE-1] +1;
	}
	else if ((!(Maze[X_MAZE-1][Y_MAZE-2] & IS_NORTH_WALL)))
	{
		Maze[X_MAZE-1][Y_MAZE-1] |= Maze[X_MAZE-1][X_MAZE-2] + 1;
	}
	Maze[goal_x][goal_y] = 0;
}

void UpdateMaze(int8_t x, int8_t y, DIRECTION direction)
{
	//bluetooth_print("Update Map\r\n");
	Maze[x][y] |= HAS_GONE;
	switch(direction)
	{
	case UP_DIR:
// neu co tuong trai
		if(isWallLeft)
		{
			Maze[x][y] |= IS_WEST_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong tay, ");
#endif
			if(x !=0)
			{
				Maze[x-1][y] |=IS_EAST_WALL;
			}
		}

		if(isWallRight)
		{
			Maze[x][y] |= IS_EAST_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong dong, ");
#endif
			if(x!=X_MAZE-1)
				Maze[x+1][y] |=IS_WEST_WALL;
		}
		if(isWallFrontLeft &&isWallFrontRight)
		{
			Maze[x][y] |= IS_NORTH_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong bac \r\n");
#endif
			if(y != Y_MAZE-1)
				Maze[x][y+1] |= IS_SOUTH_WALL;
		}
		break;
	case RIGHT_DIR:
		if(isWallLeft)
		{
			Maze[x][y] |= IS_NORTH_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong bac, ");
#endif
			if(y != Y_MAZE-1)
				Maze[x][y+1] |= IS_SOUTH_WALL;
		}
		if(isWallRight)
		{
			Maze[x][y] |=IS_SOUTH_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong nam, ");
#endif
			if(y!=0)
				Maze[x][y-1] |= IS_NORTH_WALL;
		}
		if(isWallFrontLeft && isWallFrontRight)
		{
			Maze[x][y] |= IS_EAST_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong dong \r\n");
#endif
			if(x!=X_MAZE-1)
				Maze[x+1][y] |= IS_WEST_WALL;
		}
		break;

	case DOWN_DIR:
		if(isWallLeft)
		{
			Maze[x][y] |= IS_EAST_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong dong, ");
#endif
			if(x!=X_MAZE-1)
				Maze[x+1][y] |=IS_WEST_WALL;
		}
		if(isWallRight)
		{
			Maze[x][y] |= IS_WEST_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong tay, ");
#endif
			if(x != 0)
				Maze[x-1][y] |= IS_EAST_WALL;
		}
		if(isWallFrontLeft && isWallFrontRight)
		{
			Maze[x][y] |= IS_SOUTH_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong nam \r\n");
#endif
			if(y != 0)
				Maze[x][y-1] |= IS_NORTH_WALL;
		}
		break;
	case LEFT_DIR:
		if(isWallLeft)
		{
			Maze[x][y] |= IS_SOUTH_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong nam, ");
#endif
			if(y != 0)
				Maze[x][y-1] |= IS_NORTH_WALL;
		}
		if(isWallRight)
		{
			Maze[x][y] |= IS_NORTH_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong bac, ");
#endif
			if(y != Y_MAZE-1)
				Maze[x][y+1] |= IS_SOUTH_WALL;
		}
		if(isWallFrontLeft && isWallFrontRight)
		{
			Maze[x][y] |= IS_WEST_WALL;
#ifdef WALL_UPDATE_DEBUG
			bluetooth_print("Tuong tay \r\n");
#endif
			if(x!=0)
				Maze[x-1][y] |= IS_EAST_WALL;
		}
		break;
	}
}

static uint8_t GetMin(uint16_t Num0, uint16_t Num1, uint16_t Num2)
{

	if (Num1 > Num0)
	{
		if (Num0 > Num2)
			return (2);
		else
			return (0);
	}
	else if (Num1 > Num2)
	{
		return(2);
	}
	return (1);
}

MOVE GetDir(uint8_t x, uint8_t y, DIRECTION direction)
{
    // neu khong co tuong truoc
	if(!(isWallFrontLeft | isWallFrontRight))
	{
		switch(direction)
		{
		case UP_DIR:
			Array[1] = Maze[x][y+1] & (0x00ff | HAS_GONE);
			break;
		case RIGHT_DIR:
			Array[1] =  Maze[x+1][y] & (0x00ff | HAS_GONE);
			break;
		case DOWN_DIR:
			Array[1] = Maze[x][y-1] & (0x00ff | HAS_GONE);
			break;
		case LEFT_DIR:
			Array[1] = Maze[x-1][y] & (0x00ff | HAS_GONE);
		}
	}
	else
	{
		Array[1] = 0xffff;
	}

	// khong co tuong phai
	if(!isWallRight)
	{
		switch(direction)
		{
		case UP_DIR:
			Array[2] = Maze[x+1][y] & (0x00ff | HAS_GONE);
			break;
		case RIGHT_DIR:
			Array[2] = Maze[x][y-1] & (0x00ff | HAS_GONE);
			break;
		case DOWN_DIR:
			Array[2] = Maze[x-1][y] & (0x00ff | HAS_GONE);
			break;
		case LEFT_DIR:
			Array[2] = Maze[x][y+1] & (0x00ff | HAS_GONE);
			break;
		}
	}
	else
	{
		Array[2] = 0xffff;
	}

	// khong co tuong trai
	if(!isWallLeft)
	{
		switch(direction)
		{
		case UP_DIR:
			Array[0] = Maze[x-1][y] & (0x00ff | HAS_GONE);
			break;
		case RIGHT_DIR:
			Array[0] = Maze[x][y+1] & (0x00ff | HAS_GONE);
			break;
		case DOWN_DIR:
			Array[0] = Maze[x+1][y] & (0x00ff | HAS_GONE);
			break;
		case LEFT_DIR:
			Array[0] = Maze[x][y-1] & (0x00ff | HAS_GONE);
			break;
		}
	}
	else
	{
		Array[0] = 0xffff;
	}

	if(isWallLeft && ( isWallFrontLeft && isWallFrontRight) && isWallRight)     // co tuong truoc, trai, phai
		{
			bluetooth_print("Back \r\n");
			return TURN_BACK;
		}

	switch(GetMin(Array[0], Array[1], Array[2]))
	{
	case 0:
		bluetooth_print("Left\r\n");
		return TURN_LEFT;
		//break;
	case 1:
		bluetooth_print("Forward\r\n");
		return FORWARD;
		//break;
	case 2:
		bluetooth_print("Right\r\n");
		return TURN_RIGHT;
		//break;
	}
	return FORWARD;
}
