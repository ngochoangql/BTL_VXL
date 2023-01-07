#include "fsm.h"
#include "string.h"
#include <stdio.h>
UART_HandleTypeDef huart2;
int count;
void setPedestrianLight(int color){
	switch (color) {
	case RED:
		HAL_GPIO_WritePin(LED_PORT[4], LED_PIN[4], 1);
		HAL_GPIO_WritePin(LED_PORT[5], LED_PIN[5], 0);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_PORT[4], LED_PIN[4], 1);
		HAL_GPIO_WritePin(LED_PORT[5], LED_PIN[5], 1);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_PORT[4], LED_PIN[4], 0);
		HAL_GPIO_WritePin(LED_PORT[5], LED_PIN[5], 1);
		break;
	default:
		HAL_GPIO_WritePin(LED_PORT[4], LED_PIN[4], 0);
		HAL_GPIO_WritePin(LED_PORT[5], LED_PIN[5], 0);
		break;
	}
}
void setT1(int color) {
	switch (color) {
	case RED:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 1);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 0);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 1);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 1);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 0);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 1);
		break;
	default:
		break;
	}
}
void setT2(int color) {
	switch (color) {
	case RED:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 1);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 0);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 1);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 1);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 0);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 1);
		break;
	default:
		break;
	}
}

void send7SEG(int TIME,int color){
	if (color==RED){
		sprintf(st, "!R %d#\r\n", TIME/100);
	}
	if (color==GREEN){
		sprintf(st, "!G %d#\r\n", TIME/100);
	}
	if (color==YELLOW){
		sprintf(st, "!Y %d#\r\n", TIME/100);
	}
	HAL_UART_Transmit_IT(&huart2, (void*)st, sizeof(st));

}
void fsm_automatic_run(){
	switch(status){
	case INIT_AUTO:
		setT1(RED);
		setT2(GREEN);
		setTimer(4, 100);
		count=TIME_RED;
		send7SEG(TIME_RED,RED);
		setTimer(0, TIME_RED);
		setTimer(1, TIME_GREEN);
		if(IS_PEDESTRIAN==1){
			//HAL_GPIO_WritePin(GPIOA,D12_Pin, RESET);
			//setTimer(3, time_Pedestrian_Buzzer);
		}
		status=RG;
		break;
	case RG:
		if(timer_flag[4]==1){
			count-=100;
			send7SEG(count,RED);
			setTimer(4, 100);
		}
		if(timer_flag[3]==1)
			//HAL_GPIO_WritePin(GPIOA	,D12_Pin, SET);
		if(timer_flag[2]==1)
			IS_PEDESTRIAN=0;
		if(IS_PEDESTRIAN==1){
			setPedestrianLight(GREEN);
		}else
			setPedestrianLight(0);
		if(timer_flag[1]==1){
			setTimer(1, TIME_YELLOW);
			setTimer(4, 100);
			status=RY;
		}
		if(isButtonPress(0)==1){
			IS_PEDESTRIAN=1;
			setTimer(2, time_Pedestrian);
		}
		if(isButtonPress(2)==1){
			status=INIT_MANUAL;
			setPedestrianLight(0);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
			setPedestrianLight(0);
		}
		break;
	case RY:
		if(timer_flag[4]==1){
			count-=100;
			if(count==0)
				count=TIME_GREEN;
			send7SEG(count,RED);
			setTimer(4, 100);
		}
		setT1(RED);
		setT2(YELLOW);
		if(timer_flag[2]==1)
			IS_PEDESTRIAN=0;
		if(IS_PEDESTRIAN==1){
			setPedestrianLight(YELLOW);
		}else
			setPedestrianLight(0);
		if(timer_flag[0]==1 && timer_flag[1]==1){
			setT1(GREEN);
			setT2(RED);
			setTimer(0, TIME_GREEN);
			setTimer(1, TIME_RED);
			send7SEG(TIME_GREEN,GREEN);
			setTimer(4, 100);
			status=GR;
		}
		if(isButtonPress(0)==1){
			IS_PEDESTRIAN=1;
			setTimer(2, time_Pedestrian);
		}
		if(isButtonPress(2)==1){
			status=INIT_MANUAL;
			setPedestrianLight(0);
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
			setPedestrianLight(0);
		}
		break;
	case GR:
		if(timer_flag[4]==1){
			count-=100;
			if(count==0)
				count=TIME_YELLOW;
			send7SEG(count,GREEN);
			setTimer(4, 100);
		}
		if(timer_flag[2]==1)
			IS_PEDESTRIAN=0;
		if(IS_PEDESTRIAN==1){
			setPedestrianLight(RED);
		}else
			setPedestrianLight(0);
		if(timer_flag[0]==1){
			setTimer(0, TIME_YELLOW);
			send7SEG(TIME_YELLOW,YELLOW);
			setTimer(4, 100);
			status=YR;

		}
		if(isButtonPress(0)==1){
			IS_PEDESTRIAN=1;
			setTimer(2, time_Pedestrian);
		}
		if(isButtonPress(2)==1){
			status=INIT_MANUAL;
			setPedestrianLight(0);
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
			setPedestrianLight(0);
		}
		break;
	case YR:
		if(timer_flag[4]==1){
			count-=100;
			if(count==0)
				count=TIME_RED;
			send7SEG(count,YELLOW);
			setTimer(4, 100);
		}
		setT1(YELLOW);
		setT2(RED);
		if(timer_flag[2]==1)
			IS_PEDESTRIAN=0;
		if(IS_PEDESTRIAN==1){
			setPedestrianLight(RED);
		}else
			setPedestrianLight(0);
		if(timer_flag[0]==1 && timer_flag[1]==1){
			status=INIT_AUTO;
			setTimer(4, 100);
		}
		if(isButtonPress(0)==1){
			IS_PEDESTRIAN=1;
			setTimer(2, time_Pedestrian);
		}
		if(isButtonPress(2)==1){
			status=INIT_MANUAL;
			setPedestrianLight(0);
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
			setPedestrianLight(0);
		}
		break;
	default:
		break;
	}
}
void fsm_manual_run(){
	switch(status){
	case INIT_MANUAL:
		status=M_RR;
		break;
	case M_RR:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(RED);
		setT2(RED);
		if (isButtonPress(0)==1){
			status=M_GR;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_RG;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case M_GR:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(GREEN);
		setT2(RED);
		if (isButtonPress(0)==1){
			status=M_YR;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_GG;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case M_YR:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(YELLOW);
		setT2(RED);
		if (isButtonPress(0)==1){
			status=M_RR;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_YG;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case M_RG:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(RED);
		setT2(GREEN);
		if (isButtonPress(0)==1){
			status=M_GG;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_RY;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case M_GG:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(GREEN);
		setT2(GREEN);
		if (isButtonPress(0)==1){
			status=M_YG;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_GY;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case M_YG:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(YELLOW);
		setT2(GREEN);
		if (isButtonPress(0)==1){
			status=M_RG;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_YY;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case M_YY:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(YELLOW);
		setT2(YELLOW);
		if (isButtonPress(0)==1){
			status=M_RY;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_YR;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case M_RY:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(RED);
		setT2(YELLOW);
		if (isButtonPress(0)==1){
			status=M_GY;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_RR;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case M_GY:
		if(timer_flag[0]==1 || isButtonPress(2)==1)
			status=INIT_AUTO;
		setT1(GREEN);
		setT2(YELLOW);
		if (isButtonPress(0)==1){
			status=M_YY;
			setTimer(0, time_Manual_mode);
		}
		if (isButtonPress(1)==1){
			status=M_GR;
			setTimer(0, time_Manual_mode);
		}
		if(isButtonPress(3)==1){
			status=INIT_TUNING;
			setTimer(5, time_Tuning_mode);
		}
		break;
	default:
		break;
	}
}
void fsm_tuning_run(){
	switch(status){
	case INIT_TUNING:
		setT1(RED);
		setT2(RED);
		status=T_R;
		break;
	case T_R:
		setT1(RED);
		setT2(RED);
		if(isButtonPress(0)==1){
			TIME_RED+=100;
			if(TIME_RED/100>99)
				TIME_RED=100;
			send7SEG(TIME_RED, RED);
		}
		if(isButtonPress(1)==1){
			TIME_RED-=100;
			if(TIME_RED/100==0)
				TIME_RED=9900;
			send7SEG(TIME_RED, RED);
		}
		if(isButtonPress(2)==1 || timer_flag[5]==1)
			status=INIT_AUTO;
		if(isButtonPress(3)==1){
			status=T_G;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case T_G:
		setT1(GREEN);
		setT2(GREEN);
		if(isButtonPress(0)==1){
			TIME_GREEN+=100;
			if(TIME_GREEN/100>99)
				TIME_GREEN=100;
			send7SEG(TIME_GREEN, GREEN);
		}
		if(isButtonPress(1)==1){
			TIME_GREEN-=100;
			if(TIME_GREEN/100==0)
				TIME_GREEN=9900;
			send7SEG(TIME_GREEN, GREEN);
		}
		if(isButtonPress(2)==1 || timer_flag[5]==1 || timer_flag[5]==1)
			status=INIT_AUTO;
		if(isButtonPress(3)==1){
			status=T_Y;
			setTimer(5, time_Tuning_mode);
		}
		break;
	case T_Y:

		setT1(YELLOW);
		setT2(YELLOW);
		if(isButtonPress(0)==1){
			TIME_YELLOW+=100;
			if(TIME_YELLOW/100>99)
				TIME_YELLOW=100;
			send7SEG(TIME_YELLOW, YELLOW);
		}
		if(isButtonPress(1)==1){
			TIME_YELLOW-=100;
			if(TIME_YELLOW/100==0)
				TIME_YELLOW=9900;
			send7SEG(TIME_YELLOW, YELLOW);
		}
		if(isButtonPress(2)==1 || timer_flag[5]==1)
			status=INIT_AUTO;
		if(isButtonPress(3)==1){
			status=T_R;
			setTimer(5, time_Tuning_mode);
		}
		break;
	default:
		break;
	}
}






