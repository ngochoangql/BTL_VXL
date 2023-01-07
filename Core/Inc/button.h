#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"
#include "main.h"


#define NORMAL_STATE 	SET
#define PRESSED_STATE 	RESET

extern int button_flag_press[NUM_BUTTONS];

extern int TimeOutForKeyPress[NUM_BUTTONS];


void getKeyInput();
int isButtonPress();
int isButtonLongPress();


#endif /* INC_BUTTON_H_ */
