#include "global.h"

int status = INIT_AUTO;

uint16_t BUTTON_PIN[NUM_BUTTONS] = {A0_Pin, A1_Pin, A2_Pin, A3_Pin};
GPIO_TypeDef *BUTTON_PORT[NUM_BUTTONS] = {A0_GPIO_Port, A1_GPIO_Port, A2_GPIO_Port	, A3_GPIO_Port};
uint16_t LED_PIN[NUM_LEDS] = {D2_Pin, D3_Pin, D4_Pin, D5_Pin, D6_Pin, D7_Pin};
GPIO_TypeDef* LED_PORT[NUM_LEDS] = {D2_GPIO_Port, D3_GPIO_Port, D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port};



int timeOutLongPress[NUM_BUTTONS] = {TIMEOUT_LONG_PRESS};
int TimeOutForKeyPress[NUM_BUTTONS] =  {300};
int TIME_RED = 300;
int TIME_YELLOW = 100;
int TIME_GREEN = 200;
int IS_PEDESTRIAN=0;
int time_Pedestrian=1500;
int time_Manual_mode=1500;
int time_Pedestrian_Buzzer=100;
int time_Tuning_mode=1500;
char st[50];
