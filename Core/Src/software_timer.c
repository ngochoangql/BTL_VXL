#include "software_timer.h"

int timer_flag[NUM_TIMERS]= { 0 };
int timer_counter[NUM_TIMERS] = { 0 };

void setTimer(int index, int duration) {
	timer_flag[index] = 0;
	timer_counter[index] = duration;
}


void timerRun() {
	for (int i = 0; i < NUM_TIMERS; i++) {
		if (timer_counter[i] > 0) {
			timer_counter[i]--;
			if (timer_counter[i] == 0) {
				timer_flag[i] = 1;
			}
		}
	}
}
