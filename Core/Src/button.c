#include "button.h"

int KeyReg0[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg1[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg2[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg3[NUM_BUTTONS] = {NORMAL_STATE};



int button_flag_press[NUM_BUTTONS] = {0,0,0,0};


int isButtonPress(int button_idx){
	if(button_flag_press[button_idx]==1){
		button_flag_press[button_idx]=0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
	for(int i=0;i<NUM_BUTTONS;i++){
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);
		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if(KeyReg3[i]!=KeyReg2[i]){
				KeyReg3[i]=KeyReg2[i];
				if (KeyReg2[i]==PRESSED_STATE){
						button_flag_press[i]=1;
				}
			}else{
				TimeOutForKeyPress[i]--;
				if(TimeOutForKeyPress[i]==0){
					KeyReg3[i]=NORMAL_STATE;
				}
			}
		}
	}
}
