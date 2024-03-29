/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *  version 0.0.1
 */

/**
 * @file	main.c
 * @brief	main code
 */
#include "include.h"
extern void SetPWM(uint32_t ulBaseAddr, uint32_t ulTimer, uint32_t ulFrequency, int32_t ucDutyCycle);

extern volatile float BatteryVoltage;
uint8_t IR_Calib_Step = 0;

/** \brief Button left interrupt handler
 *
 */
void ButtonLeftHandler(void)
{
	switch (system_GetState())
	{
		case SYSTEM_INITIALIZE:
			//LED1_ON();LED2_OFF();LED3_OFF();
			//speed_Enable_Hbridge(false);
			if (SW1_ON)
			{
				system_SetState(SYSTEM_CALIB_SENSOR);
				IR_Calib_Step = 0;
			}
			else
			{

				//loadIRData();
				speed_Enable_Hbridge(true);
				system_SetState(SYSTEM_RUN_IMAGE_PROCESSING);

			}

			break;
		/*
		case SYSTEM_CALIB_SENSOR:
			speed_Enable_Hbridge(false);
			saveIRData();
			system_SetState(SYSTEM_GET_MOTOR_MODEL);
			break;

		case SYSTEM_GET_MOTOR_MODEL:
			LED1_OFF();LED2_OFF();LED3_ON();
			if (SW2_ON)
			{
				system_SetState(SYSTEM_ESTIMATE_MOTOR_MODEL);
				speed_Enable_Hbridge(true);
				speed_set(MOTOR_LEFT,200);
				speed_set(MOTOR_RIGHT,200);
			}
			else
			{
				loadMotorModel();
				system_SetState(SYSTEM_WAIT_TO_RUN);
			}
			break;
		case SYSTEM_ESTIMATE_MOTOR_MODEL:
			speed_Enable_Hbridge(false);
			system_SetState(SYSTEM_SAVE_MOTOR_MODEL);
			break;
		case SYSTEM_SAVE_MOTOR_MODEL:
			saveMotorModel();
			system_SetState(SYSTEM_WAIT_TO_RUN);
			break;
		case SYSTEM_WAIT_TO_RUN:

			LED1_OFF();LED2_ON();LED3_OFF();
			system_SetState(SYSTEM_RUN_IMAGE_PROCESSING);

			//SysCtlDelay(SysCtlClockGet()/3);
			//system_SetState(SYSTEM_RUN_SOLVE_MAZE);
			//qei_setPosLeft(0);
			//qei_setPosRight(0);
			//speed_Enable_Hbridge(true);
			//break;

		//case SYSTEM_RUN_SOLVE_MAZE:
			//LED1_OFF();LED2_ON();LED3_ON();


			break;
		case SYSTEM_RUN_IMAGE_PROCESSING:
			LED1_ON();LED2_OFF();LED3_OFF();
			//speed_Enable_Hbridge(true);

			break;
			*/
		default:
			break;
	}
}

/** \brief Button right interrupt handler
 *
 */
void ButtonRightHandler(void)
{
	if (system_GetState() == SYSTEM_CALIB_SENSOR)
	{
		switch(IR_Calib_Step)
		{
			case 0:
				LED1_ON();
				LED2_OFF();
				LED3_OFF();
				IR_set_calib_value(IR_CALIB_BASE_LEFT);
				break;
			case 1:
				IR_set_calib_value(IR_CALIB_BASE_RIGHT);
				LED1_OFF();
				LED2_ON();
				LED3_OFF();
				break;
			case 2:
				IR_set_calib_value(IR_CALIB_BASE_FRONT_LEFT);
				IR_set_calib_value(IR_CALIB_BASE_FRONT_RIGHT);
				LED1_ON();
				LED2_ON();
				LED3_OFF();
				break;
			case 3:
				IR_set_calib_value(IR_CALIB_MAX_LEFT);
				LED1_OFF();
				LED2_OFF();
				LED3_ON();
				break;
			case 4:
				IR_set_calib_value(IR_CALIB_MAX_RIGHT);
				LED1_ON();
				LED2_OFF();
				LED3_ON();
				break;
			case 5:
				IR_set_calib_value(IR_CALIB_MAX_FRONT_LEFT);
				IR_set_calib_value(IR_CALIB_MAX_FRONT_RIGHT);
				LED1_OFF();
				LED2_ON();
				LED3_ON();
				break;
/*			case 6:
				IR_set_calib_value(IR_CALIB_UNLIMITED_FRONT_LEFT);
				IR_set_calib_value(IR_CALIB_UNLIMITED_FRONT_RIGHT);
				LED1_OFF();
				LED2_OFF();
				LED3_OFF();
				break;*/
		}
		IR_Calib_Step++;
		IR_Calib_Step %= 6;
	}
}

void main(void){
	system_SetState(SYSTEM_INITIALIZE);
	Config_System();
	EEPROMConfig();
	Timer_Init();
	speed_control_init();
    qei_init(20);
	wallFollow_init();
	HostCommInit();

	buzzer_init();
	BattSense_init();
	LED_Display_init();
	Switch_init();
	Button_init();
	IRDetector_init();


	ButtonRegisterCallback(BUTTON_LEFT, &ButtonLeftHandler);
	ButtonRegisterCallback(BUTTON_RIGHT, &ButtonRightHandler);

//	system_SetState(SYSTEM_RUN_IMAGE_PROCESSING);

//	buzzer_on(2000, 500);
//	buzzer_low_batterry_notify();
//	system_SetState(SYSTEM_ESTIMATE_MOTOR_MODEL);
//	speed_set(MOTOR_LEFT,1200);
//	speed_set(MOTOR_RIGHT, 100);
//	speed_Enable_Hbridge(true);
//	bluetooth_print("AT\r\n");
//	bluetooth_print("AT+NAME=NHH\r\n");
//	bluetooth_print("AT+PSWD=3393\r\n");
//	bluetooth_print("AT+UART=115200,0,0\r\n");

	pid_Wallfollow_set_follow(WALL_FOLLOW_RIGHT);
	qei_setPosLeft(0);
	qei_setPosRight(0);


	pid_ImageProcess_init();


	//system_SetState(SYSTEM_RUN_IMAGE_PROCESSING);


	while (1)
	{
		system_Process_System_State();
		//if (stop==9999)
		//{
		//	speed_set(MOTOR_LEFT,0);
		//	speed_set(MOTOR_RIGHT,0);
		//	speed_Enable_Hbridge(false);
		//}
	}

}
