#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "global.h"
#include "button.h"
#include "software_timer.h"

void setPedestrianLight(int color);
void setT1(int color);
void setT2(int color);

void send7SEG(int TIME,int color);
void fsm_automatic_run();
void fsm_manual_run();
void fsm_tuning_run();
#endif /* INC_FSM_H_ */
