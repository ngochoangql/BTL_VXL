#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"




#define NUM_BUTTONS		4
#define NUM_LEDS		6
#define NUM_TIMERS		6



#define INIT_AUTO		10
#define INIT_MANUAL		11
#define INIT_TUNING		12
#define RG				13
#define RY				14
#define GR				15
#define YR				16


#define M_RR			17
#define M_GR			18
#define M_YR			19
#define M_GG			20
#define M_YG			21
#define M_RG			22
#define M_YY			23
#define M_RY			24
#define M_GY			25


#define T_R				26
#define T_G				27
#define T_Y				28


#define TIMEOUT_LONG_PRESS	300
#define RED					30
#define YELLOW				31
#define GREEN				32



extern int status;
extern int IS_PEDESTRIAN;
uint16_t BUTTON_PIN[NUM_BUTTONS];
GPIO_TypeDef* BUTTON_PORT[NUM_BUTTONS];
uint16_t LED_PIN[NUM_LEDS];
GPIO_TypeDef* LED_PORT[NUM_LEDS];
extern int button_flag[NUM_BUTTONS];
extern int TIME_RED;
extern int TIME_YELLOW;
extern int TIME_GREEN;
extern int timer_counter[NUM_TIMERS];
extern int timer_flag[NUM_TIMERS];
extern int timeOutLongPress[NUM_BUTTONS];
extern int time_Pedestrian;
extern int time_Manual_mode;
extern int time_Pedestrian_Buzzer;
extern int time_Tuning_mode;
extern char st[50];
UART_HandleTypeDef huart2;
#endif /* INC_GLOBAL_H_ */
